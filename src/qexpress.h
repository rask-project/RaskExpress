#ifndef QEXPRESS_H
#define QEXPRESS_H

#include <QCoreApplication>
#include "qexpressserver.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class QEXPRESS_EXPORT QExpress
{
    QCoreApplication m_application;
    QExpressServer m_server;
public:
    QExpress(int argc, char *argv[]);
};

QEX_END_NAMESPACE

#endif // QEXPRESS_H
