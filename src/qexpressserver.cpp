#include "qexpressserver.h"

QEX_BEGIN_NAMESPACE

QExpressServer::QExpressServer()
{
    thread()->setPriority(QThread::TimeCriticalPriority);
}

void QExpressServer::incomingConnection(qintptr handle)
{
    qDebug() << "New Connection:" << handle;
    m_pool.start(new HttpRequest(handle));
}


QEX_END_NAMESPACE
