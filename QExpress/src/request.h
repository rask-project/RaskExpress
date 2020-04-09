#ifndef REQUEST_H
#define REQUEST_H

#include <chrono>
#include <QMap>
#include <QTcpSocket>
#include "httpparser.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

typedef  QMap<QString, QVariant> MiddlewareData;

class QEXPRESS_EXPORT Request
{
    HttpParser& m_httpParser;
    MiddlewareData m_middlewareData;

public:
    explicit Request(HttpParser& parser): m_httpParser(parser), m_middlewareData() {}

    qint64& contentLength = m_httpParser.contentLength();

    QByteArray& url = m_httpParser.url();

    QByteArray& method = m_httpParser.method();

    QByteArray& httpVersion = m_httpParser.httpVersion();

    QByteArray& contentType = m_httpParser.contentType();

    QMap<QByteArray, QByteArray>& header = m_httpParser.header();

    inline QByteArray& getHeader(const QByteArray& name) { return m_httpParser.header()[name]; }

    QMap<QByteArray, QByteArray>& body = m_httpParser.body();

    QJsonValue bodyJson = m_httpParser.bodyJson();

    QMap<QByteArray, QByteArray>& query = m_httpParser.query();

    QMap<QByteArray, QMap<QByteArray, QByteArray>>& files = m_httpParser.files();

    QMap<QByteArray, QByteArray>& params = m_httpParser.params();

    inline QByteArray getParam(const QByteArray& key) { return m_httpParser.params()[key]; }

    QByteArray& pathName = m_httpParser.pathName();

    inline void setMiddlewareData(const QString& key, const QVariant& data) { m_middlewareData.insert(std::move(key), std::move(data)); }

    inline void setMiddlewareData(QString&& key, QVariant&& data) { m_middlewareData.insert(std::move(key), std::move(data)); }

    MiddlewareData& middlewareData = m_middlewareData;

    std::chrono::high_resolution_clock::time_point& time = m_httpParser.time();
};

QEX_END_NAMESPACE

#endif // REQUEST_H
