#ifndef QEXPRESS_H
#define QEXPRESS_H

#include <QCoreApplication>
#include "config.h"
#include "qexpressserver.h"
#include "router.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class QEXPRESS_EXPORT QExpress
{
    QCoreApplication m_application;
    Config m_config;
    QExpressServer *m_server;

    const QHostAddress m_host;
    const int m_port;

    QExpress(const QExpress& other) = delete;
    QExpress& operator=(const QExpress& other) = delete;

public:
    QExpress(int argc, char *argv[], Config& config);
    ~QExpress();

    inline void router(const QString &url, Router* router) noexcept { m_server->router(url, router); }

    int start();
};

QEX_END_NAMESPACE

#endif // QEXPRESS_H
