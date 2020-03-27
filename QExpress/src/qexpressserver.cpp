#include "qexpressserver.h"

QEX_BEGIN_NAMESPACE

QExpressServer::QExpressServer()
{
    thread()->setPriority(QThread::TimeCriticalPriority);
    m_pool.setMaxThreadCount(200);
    m_pool.setExpiryTimeout(60000);
}

QExpressServer::~QExpressServer()
{
    std::for_each(m_router.begin(), m_router.end(), [](std::pair<QString, Router*> item) { delete item.second; });
    m_router.clear();
}

void QExpressServer::incomingConnection(qintptr handle)
{
    m_pool.start(new HttpRequest(handle, m_router), QThread::LowPriority);
}


QEX_END_NAMESPACE
