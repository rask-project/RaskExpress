#include "qexpressserver.h"

QEX_BEGIN_NAMESPACE

QExpressServer::QExpressServer(Config &config):
    m_config(config)
{
    thread()->setPriority(QThread::TimeCriticalPriority);
    m_pool.setMaxThreadCount(m_config.config["maxThread"].toInt());
    m_pool.setExpiryTimeout(m_config.config["timeout"].toInt());
}

QExpressServer::~QExpressServer()
{
    std::for_each(m_router.begin(), m_router.end(), [](std::pair<QString, Router*> item) { delete item.second; });
    m_router.clear();
}

void QExpressServer::incomingConnection(qintptr handle)
{
    m_pool.start(new HttpRequest(handle, m_config, m_router), QThread::LowPriority);
}


QEX_END_NAMESPACE
