#ifndef QEXPRESSSERVER_H
#define QEXPRESSSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QThreadPool>
#include <map>
#include <algorithm>

#include "httprequest.h"
#include "router.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class QExpressServer : public QTcpServer
{
private:
    QThreadPool m_pool;
    std::map<QString, Router*> m_router;

public:
    explicit QExpressServer();
    ~QExpressServer() override;

    inline void router(const QString &url, Router* router) noexcept { m_router[url] = router; }
protected:
    void incomingConnection(qintptr handle) override;
};

QEX_END_NAMESPACE

#endif // QEXPRESSSERVER_H
