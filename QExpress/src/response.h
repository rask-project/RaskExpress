#ifndef RESPONSE_H
#define RESPONSE_H

#include <QTcpSocket>
#include <QJsonDocument>
#include "qexpress_consts.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class QEXPRESS_EXPORT Response
{
    QTcpSocket& m_socket;
    QByteArray m_content;
    QMap<QByteArray, QByteArray> m_headers;
    int m_statusCode;
    QByteArray m_statusText;
    const int m_maxSizeResponse;

public:
    explicit Response(QTcpSocket& socket);
    ~Response() noexcept {}

    inline void addHeader(const QByteArray& name, const QByteArray& value) { m_headers.insert(name, value); }

    void status(int statusCode);
    void status(HTTP::STATUS::CODE statusCode);
    void send(const QByteArray& data);
    void send(const QJsonObject& json);
    void send(const QJsonArray& json);

private:
    void sendData();
    void sendHeaders();
    void writeByteArray(const QByteArray& data);
    void closeConnection();
};

QEX_END_NAMESPACE

#endif // RESPONSE_H
