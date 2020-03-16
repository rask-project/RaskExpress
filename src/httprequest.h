#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QRunnable>
#include <QTcpSocket>

#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class HttpRequest : public QRunnable
{
    qintptr m_handle;
    QTcpSocket *m_socket;

public:
    HttpRequest(qintptr &handle);
    ~HttpRequest() override;

    void run() override;

private:
    void setSocket();
};

QEX_END_NAMESPACE

#endif // HTTPREQUEST_H
