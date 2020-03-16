#ifndef QEXPRESS_H
#define QEXPRESS_H

#include <QCoreApplication>
#include "qexpressserver.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class QEXPRESS_EXPORT QExpress
{
    QCoreApplication m_application;
    QExpressServer *m_server;

    const QHostAddress m_host;
    const int m_port;

public:
    QExpress(int argc, char *argv[]);
    ~QExpress();

    int start();
};

QEX_END_NAMESPACE

#endif // QEXPRESS_H
