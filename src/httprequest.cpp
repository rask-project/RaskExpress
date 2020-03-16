#include "httprequest.h"
#include "httpparser.h"

QEX_BEGIN_NAMESPACE

HttpRequest::HttpRequest(qintptr &handle):
    m_handle(handle),
    m_socket(nullptr)
{

}

HttpRequest::~HttpRequest()
{
    delete m_socket;
}

void HttpRequest::run()
{
    setSocket();

    if (m_socket->ConnectedState > 0) {
        if (m_socket->waitForReadyRead()) {
            QByteArray request;

            try {
                request = m_socket->readAll();
            } catch (const std::bad_alloc& error) {
                qDebug() << "Error:" << error.what();
            }

            HttpParser parser(request);
        }
    } else {
        qDebug() << "Connection state:" << m_socket->ConnectedState<< m_socket->ConnectingState;
    }
}

void HttpRequest::setSocket()
{
    m_socket = new QTcpSocket;
    m_socket->setSocketDescriptor(m_handle);
}

QEX_END_NAMESPACE
