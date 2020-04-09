#include "response.h"
#include <QDateTime>

QEX_BEGIN_NAMESPACE

Response::Response(QTcpSocket &socket, Request &request):
    m_socket(socket),
    m_request(request),
    m_content(),
    m_headers(),
    m_statusCode(HTTP::STATUS::CODE::Ok),
    m_statusText(),
    m_maxSizeResponse(32768)
{}

void Response::status(int statusCode)
{
    m_statusCode = statusCode;
    m_statusText = HTTP::STATUS::TEXT(statusCode);
}

void Response::status(HTTP::STATUS::CODE statusCode)
{
    m_statusCode = statusCode;
    m_statusText = HTTP::STATUS::TEXT(statusCode);
}

void Response::send(const QByteArray &data)
{
    m_content = std::move(data);
    sendData();
}

void Response::send(const QJsonObject &json)
{
    if (!m_headers.contains(HTTP::CONTENT_TYPE))
        m_headers.insert(HTTP::CONTENT_TYPE, HTTP::RESPONSE::CONTENT_TYPE::APPLICATION_JSON_UTF8);
    else if (m_headers.value(HTTP::CONTENT_TYPE) != HTTP::RESPONSE::CONTENT_TYPE::APPLICATION_JSON_UTF8)
        m_headers[HTTP::CONTENT_TYPE] = HTTP::RESPONSE::CONTENT_TYPE::APPLICATION_JSON_UTF8;
    m_content = QJsonDocument(json).toJson();
    sendData();
}

void Response::send(const QJsonArray &json)
{
    if (!m_headers.contains(HTTP::CONTENT_TYPE))
        m_headers.insert(HTTP::CONTENT_TYPE, HTTP::RESPONSE::CONTENT_TYPE::APPLICATION_JSON_UTF8);
    else if (m_headers.value(HTTP::CONTENT_TYPE) != HTTP::RESPONSE::CONTENT_TYPE::APPLICATION_JSON_UTF8)
        m_headers[HTTP::CONTENT_TYPE] = HTTP::RESPONSE::CONTENT_TYPE::APPLICATION_JSON_UTF8;
    m_content = QJsonDocument(json).toJson();
    sendData();
}

void Response::sendData()
{
    if (!m_content.isEmpty()) {
        m_headers.insert(HTTP::CONTENT_LENGTH, QByteArray::number(m_content.size()));
        m_headers.insert(HTTP::SERVER, HTTP::SERVER_VERSION);
        m_headers.insert(HTTP::DATE, QByteArray(QDateTime::currentDateTimeUtc().toString("ddd, dd MMM yyyy hh:mm:ss").toLatin1() + " GMT"));

        bool greaterThenLimit = m_content.size() > m_maxSizeResponse;
        if (!greaterThenLimit) {
            sendHeaders();
            writeByteArray(m_content);
        } else {
            m_headers.insert(HTTP::TRANSFER_ENCODING, HTTP::CHUNKED);
            sendHeaders();

            int totalSize = (m_content.size() / m_maxSizeResponse) + 1;
            for (int i = 0, last = 0; i < totalSize; ++i, last += m_maxSizeResponse) {
                QByteArray responseSplited = m_content.mid(last, m_maxSizeResponse);
                writeByteArray(QByteArray::number(responseSplited.size(), 16) + HTTP::END_LINE);
                writeByteArray(std::move(responseSplited));
                writeByteArray(HTTP::END_LINE);
            }
            writeByteArray(HTTP::END_OF_MESSAGE_WITH_ZERO);
        }
        closeConnection();
    }
}

void Response::sendHeaders()
{
    if (!m_headers.contains(HTTP::CONTENT_TYPE))
        m_headers.insert(HTTP::CONTENT_TYPE, HTTP::RESPONSE::CONTENT_TYPE::TEXT_PLAIN_UTF8);

    QByteArray header(HTTP::HTTP_1_1);
    header.reserve(100);
    header.push_back(QByteArray::number(m_statusCode));
    if (!m_statusText.isEmpty()) {
        header.push_back(' ');
        header.push_back(m_statusText);
    }
    header.push_back(HTTP::END_LINE);

    QByteArrayList keys(m_headers.keys());
    for (const QByteArray& key: keys) {
        header.push_back(key);
        header.push_back(HTTP::SEPARATOR);
        header.push_back(m_headers.value(key));
        header.push_back(HTTP::END_LINE);
    }
    header.push_back(HTTP::END_LINE);
    writeByteArray(header);
}

void Response::writeByteArray(const QByteArray &data)
{
    if (m_socket.ConnectedState > 0 && data.size() > 0) {
        m_socket.write(data, data.size());
        m_socket.flush();

        if (m_socket.ConnectedState > 0) {
            m_socket.waitForBytesWritten();
        }
    }
}

void Response::closeConnection()
{
    m_socket.disconnectFromHost();
    m_content.clear();
    m_time = std::chrono::high_resolution_clock::now();
    logResponse();
}

void Response::logResponse()
{
    std::chrono::high_resolution_clock::time_point start = m_request.time;
    std::chrono::high_resolution_clock::time_point end = m_time;
    QString typeTime("s");
    int time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    if (time == 0) {
        typeTime = "ms";
        time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    if (time == 0) {
        typeTime = "ns";
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    qInfo().noquote()
            << m_request.method
            << m_request.url
            << m_statusCode
            << m_headers["Content-Length"]
            << QString("%1%2").arg(time).arg(typeTime);
}

QEX_END_NAMESPACE
