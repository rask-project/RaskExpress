#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QRunnable>
#include <map>
#include <QTcpSocket>

#include "router.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class HttpRequest : public QRunnable
{
    qintptr m_handle;
    QTcpSocket *m_socket;
    std::map<QString, Router*> m_router;

public:
    HttpRequest(qintptr &handle, std::map<QString, Router *> &router);
    ~HttpRequest() override;

    void run() override;

private:
    void setSocket();
    void routeMatch(HttpParser& parser);
    bool runMiddlewares(const Middlewares &middlewares, Request& request, Response& response);
};

QEX_END_NAMESPACE

#endif // HTTPREQUEST_H
