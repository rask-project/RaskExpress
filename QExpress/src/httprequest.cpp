#include <functional>
#include <QJsonObject>
#include <QDataStream>
#include <iostream>
#include "httprequest.h"
#include "httpparser.h"
#include "request.h"
#include "response.h"
#include "urlparser.h"

QEX_BEGIN_NAMESPACE

HttpRequest::HttpRequest(qintptr &handle, Config &config, std::map<QString, Router *> &router):
    m_handle(handle),
    m_config(config),
    m_socket(nullptr),
    m_router(router)
{}

HttpRequest::~HttpRequest()
{
    delete m_socket;
    m_router.clear();
}

void HttpRequest::run()
{
    setSocket();

    m_socket->setReadBufferSize(m_config.config["maxUploadSize"].toInt());
    if (m_socket->ConnectedState > 0) {
        if (m_socket->waitForReadyRead()) {
            QByteArray data;
            try {
                m_socket->flush();
                data = m_socket->readAll();
            } catch (const std::bad_alloc& error) {
                qDebug() << "Error:" << error.what();
            }

            std::cout << data.constData();
            HttpParser parser(data);
            routeMatch(parser);
        }
    } else {
        qDebug() << "Connection state:" << m_socket->ConnectedState << m_socket->ConnectingState;
    }
}

void HttpRequest::setSocket()
{
    m_socket = new QTcpSocket;
    m_socket->setSocketDescriptor(m_handle);
}

void HttpRequest::routeMatch(HttpParser &parser)
{
    Response response(*m_socket);
    if (!parser.isValid()) {
        response.status(HTTP::STATUS::CODE::BadRequest);
        response.send(HTTP::STATUS::TEXT(HTTP::STATUS::CODE::BadRequest));
        return;
    }

    QString url = parser.url();
    QString method = parser.method();
    UrlParser urlParser(url);

    for (const auto& router: m_router) {
        const QString& basePath = router.first;
        urlParser.setBasePath(basePath);

        if (urlParser.basePathMatch()) {
            for (const auto& route: router.second->routes()) {
                bool requestFound = (method == route.method && urlParser.pathNameMatch(route.regExp, route.parameters));
                if (requestFound) {
                    parser.setParams(urlParser.params());

                    Request request(parser);
                    if (!runMiddlewares(route.middlewares, request, response))
                        return;

                    (route.functor)(request, response);
                    return;
                }
            }
        }
    }

    response.status(HTTP::STATUS::CODE::NotFound);
    response.send(HTTP::STATUS::TEXT(HTTP::STATUS::CODE::NotFound));
}

bool HttpRequest::runMiddlewares(const Middlewares &middlewares, Request &request, Response &response)
{
    for (const auto& middleware: middlewares) {
        if (!(std::get<0>(middleware))(request, response, std::get<1>(middleware)))
            return false;
    }
    return true;
}

QEX_END_NAMESPACE
