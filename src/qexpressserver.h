#ifndef QEXPRESSSERVER_H
#define QEXPRESSSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QThreadPool>
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class QExpressServer : public QTcpServer
{

public:
    QExpressServer();
};

QEX_END_NAMESPACE

#endif // QEXPRESSSERVER_H
