#include "httpparser.h"
#include "qexpress_consts.h"

#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

QEX_BEGIN_NAMESPACE

HttpParser::HttpParser(QByteArray &data):
    m_valid(false),
    m_multiPart(false),
    m_url(),
    m_method(),
    m_httpVersion(),
    m_contentType(),
    m_contentLength(0),
    m_header(),
    m_params(),
    m_body(),
    m_query(),
    m_files()
{
    if (parseHttpData(data)) {
        parseHeader();
        parseUrl();
        parseBody();

        if (m_multiPart)
            parseMultiPart();
    }
}

bool HttpParser::parseHttpData(QByteArray &data)
{
    int index = data.indexOf(HTTP::END_OF_MESSAGE);
    if (index > -1) {
        index += 4;
        const int size = data.size();
        m_bodyString = data.mid(index, size);

        data.remove(index, size);
        m_headerString = std::move(data);

        m_valid = true;
    } else {
        m_valid = false;
    }
    return m_valid;
}

void HttpParser::parseHeader()
{
    m_headerString.replace("\r", "");
    QByteArrayList lines(m_headerString.split('\n'));

    QByteArrayList firstLine;
    if (!lines.empty()) {
        firstLine = lines.at(0).split(' ');
        lines.removeAt(0);
    }
    if (firstLine.size() < 3) {
        m_valid = false;
        return;
    }

    m_method = std::move(firstLine[0]).toUpper();
    m_url = std::move(firstLine[1]);
    m_httpVersion = std::move(firstLine[2]);

    for (QByteArray& line: lines) {
        int colonPos = line.indexOf(':');
        if (colonPos > -1) {
            QByteArray key(line.left(colonPos).trimmed());
            QByteArray value(line.mid(colonPos + 1).trimmed());

            if (key == HTTP::CONTENT_TYPE) {
                if (value.contains(HTTP::BOUNDARY)) {
                    QByteArrayList contentTypeSplit(value.split(';'));
                    value = std::move(contentTypeSplit[0]);

                    QByteArrayList boundaryList = contentTypeSplit[1].trimmed().split('=');
                    m_header.insert(std::move(boundaryList[0]), std::move(boundaryList[1]));
                }
            }
            m_header.insert(std::move(key), std::move(value));
        }
    }

    m_contentLength = m_header.value(HTTP::CONTENT_LENGTH).toLongLong();
    m_contentType = m_header.value(HTTP::CONTENT_TYPE);
    m_multiPart = m_contentType.contains(HTTP::MULTIPART);

    if (m_method != HTTP::METHOD::POST && m_method != HTTP::METHOD::PUT && m_method != HTTP::METHOD::PATCH)
        m_bodyString.clear();

    if (m_header.contains(HTTP::COOKIE))
        extractCookies();
    m_headerString.clear();
}

void HttpParser::parseUrl()
{
    if (m_url.contains('?')) {
        QByteArrayList urlSplited(m_url.split('?'));
        m_url = std::move(urlSplited[0]);

        QByteArrayList queryStringList(urlSplited[1].split('&'));
        for (QByteArray& query: queryStringList) {
            QByteArrayList querySplited(query.split('='));
            if (querySplited.size() == 2)
                m_query.insert(std::move(querySplited[0]), std::move(queryDecoded(querySplited[1])));
            else
                m_query.insert(std::move(querySplited[0]), "");
        }
    }
}

void HttpParser::parseBody()
{
    if (m_contentType.contains(HTTP::URLENCODED)) {
        if (m_bodyString.contains("&")) {
            QByteArrayList bodyAmpersendSplit(m_bodyString.split('&'));
            for (QByteArray& item: bodyAmpersendSplit) {
                QByteArrayList itemSplited(item.split('='));
                if (itemSplited.size() == 2) {
                    m_body.insert(std::move(itemSplited[0]), std::move(queryDecoded(itemSplited[1])));
                } else {
                    m_body.insert(std::move(itemSplited[0]), "");
                }
            }
        } else {
            QByteArrayList bodySplited(m_bodyString.split('='));
            if (bodySplited.size() == 2)
                m_body.insert(std::move(bodySplited.first()), std::move(bodySplited.last()));
            else
                m_body.insert(std::move(bodySplited.first()), "");
        }
    } else if (m_contentType.contains(HTTP::APPLICATION_JSON)) {
        QJsonDocument doc = QJsonDocument::fromJson(m_bodyString);
        if (doc.isObject())
            m_bodyJson = doc.object();
        else if (doc.isArray())
            m_bodyJson = doc.array();
    }
}

void HttpParser::parseMultiPart()
{
    if (m_bodyString.size() == m_contentLength) {
        QStringList listFormData;
        QString boundary;

        m_bodyString
                .replace("--" + m_header.value(HTTP::BOUNDARY) + "--\r\n", "")
                .replace("--" + m_header.value(HTTP::BOUNDARY) + "\r\n", "");

        m_bodyString.remove(0, (HTTP::CONTENT_DISPOSITION_COLON_SPACE + HTTP::FORM_DATA_COLON_SPACE).size());
        int contentFormDataPos = m_bodyString.indexOf(HTTP::CONTENT_DISPOSITION_COLON_SPACE + HTTP::FORM_DATA_COLON_SPACE);

        do {
            QByteArray item = m_bodyString.mid(0, contentFormDataPos);

            if (item.startsWith(HTTP::FORM_DATA_NAME_EQUAL)) {
                item.remove(0, HTTP::FORM_DATA_NAME_EQUAL.size());

                int separatorPos = item.indexOf(HTTP::FORM_DATA_SEPARATOR);
                QByteArray key = item.mid(0, separatorPos).replace("\"", "");
                item.remove(0, separatorPos + HTTP::FORM_DATA_SEPARATOR.size());

                if (key.contains(';')) {
                    int semicolonPos = key.indexOf(';');
                    QByteArray fieldName = key.mid(0, semicolonPos);
                    key.remove(0, semicolonPos + 1);

                    key.replace(HTTP::END_LINE, ";");
                    QByteArrayList fileData(key.trimmed().split(';'));
                    QMultiMap<QByteArray, QByteArray> fileRequest;
                    for (QByteArray& itemFile: fileData) {
                        if (itemFile.contains(HTTP::FILENAME_EQUAL)) {
                            int filenamePos = itemFile.indexOf(HTTP::FILENAME_EQUAL);
                            itemFile.remove(0, filenamePos + HTTP::FILENAME_EQUAL.size());
                            fileRequest.insert(HTTP::FILENAME, std::move(itemFile));
                        }
                        if (itemFile.contains(HTTP::CONTENT_TYPE_COLON_SPACE)) {
                            int contentTypePos = itemFile.indexOf(HTTP::CONTENT_TYPE_COLON_SPACE);
                            itemFile.remove(0, contentTypePos + HTTP::CONTENT_TYPE_COLON_SPACE.size());
                            fileRequest.insert(HTTP::CONTENT_TYPE, std::move(itemFile));
                        }
                    }
                    fileRequest.insert("content", item);
                    m_files.insert(fieldName, std::move(fileRequest));
                } else {
                    m_body.insert(key, std::move(removeCharsFromEnd(item)));
                }
            }

            m_bodyString.remove(0, contentFormDataPos);
            m_bodyString.remove(0, (HTTP::CONTENT_DISPOSITION_COLON_SPACE + HTTP::FORM_DATA_COLON_SPACE).size());
            contentFormDataPos = m_bodyString.indexOf(HTTP::CONTENT_DISPOSITION_COLON_SPACE + HTTP::FORM_DATA_COLON_SPACE);
        } while (contentFormDataPos > -1);
    }
}

void HttpParser::extractCookies()
{
}

QByteArray& HttpParser::queryDecoded(QByteArray& query) {
    query = QUrl::fromPercentEncoding(query.replace("+", " ")).toUtf8();
    return query;
}

QByteArray& HttpParser::removeCharsFromEnd(QByteArray &query)
{
    return query.endsWith(HTTP::END_LINE) ? query.replace(HTTP::END_LINE, "") : query;
}

QEX_END_NAMESPACE
