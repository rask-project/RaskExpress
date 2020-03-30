#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QRunnable>
#include <map>
#include <QTcpSocket>

#include "config.h"
#include "router.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class HttpRequest : public QRunnable
{
    qintptr m_handle;
    Config m_config;
    QTcpSocket *m_socket;
    std::map<QString, Router*> m_router;

public:
    HttpRequest(qintptr &handle, Config& config, std::map<QString, Router *> &router);
    ~HttpRequest() override;

    void run() override;

private:
    void setSocket();
    void routeMatch(HttpParser& parser);
    bool runMiddlewares(const Middlewares &middlewares, Request& request, Response& response);
};

QEX_END_NAMESPACE

#endif // HTTPREQUEST_H
