#include "qexpressserver.h"

QEX_BEGIN_NAMESPACE

QExpressServer::QExpressServer()
{
    thread()->setPriority(QThread::TimeCriticalPriority);
}

QEX_END_NAMESPACE
