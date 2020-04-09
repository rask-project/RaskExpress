#include <functional>
#include <QJsonObject>
#include <QDataStream>
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
    if (m_socket->state() == QTcpSocket::ConnectedState) {
        HttpParser parser(m_socket, m_config);
        routeMatch(parser);
    } else {
        qWarning() << "Connection state:" << m_socket->state();
    }
}

void HttpRequest::setSocket()
{
    m_socket = new QTcpSocket;
    m_socket->setSocketDescriptor(m_handle);
}

void HttpRequest::routeMatch(HttpParser &parser)
{
    Request request(parser);
    Response response(*m_socket, request);

    if (parser.timeout()) {
        response.status(HTTP::STATUS::CODE::RequestTimeout);
        response.send(HTTP::STATUS::TEXT(HTTP::STATUS::CODE::RequestTimeout));
        return;
    }

    if (parser.maxUploadSize()) {
        response.status(HTTP::STATUS::CODE::PayloadTooLarge);
        response.send(HTTP::STATUS::TEXT(HTTP::STATUS::CODE::PayloadTooLarge));
        return;
    }

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
                    parser.setPathName(urlParser.pathName());
                    parser.setParams(urlParser.params());

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
