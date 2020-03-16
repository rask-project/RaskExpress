#ifndef QEXPRESSSERVER_H
#define QEXPRESSSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QThreadPool>

#include "httprequest.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class QExpressServer : public QTcpServer
{
private:
    QThreadPool m_pool;
public:
    explicit QExpressServer();

protected:
    void incomingConnection(qintptr handle) override;
};

QEX_END_NAMESPACE

#endif // QEXPRESSSERVER_H
