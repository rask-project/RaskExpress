#ifndef REQUEST_H
#define REQUEST_H

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

    inline qint64& contentLength() noexcept { return m_httpParser.contentLength(); }

    inline QByteArray& url() noexcept { return m_httpParser.url(); }

    inline QByteArray& method() noexcept { return m_httpParser.method(); }

    inline QByteArray& httpVersion() noexcept { return m_httpParser.httpVersion(); }

    inline QByteArray& contentType() noexcept { return m_httpParser.contentType(); }

    inline QMultiMap<QByteArray, QByteArray>& header() noexcept { return m_httpParser.header(); }

    inline QMultiMap<QByteArray, QByteArray>& body() noexcept { return m_httpParser.body(); }

    inline QJsonValue bodyJson() noexcept { return m_httpParser.bodyJson(); };

    inline QMultiMap<QByteArray, QByteArray>& query() noexcept { return m_httpParser.query(); }

    inline QMultiMap<QByteArray, QMultiMap<QByteArray, QByteArray>>& files() noexcept { return m_httpParser.files(); }

    inline QMultiMap<QByteArray, QByteArray>& params() { return m_httpParser.params(); }

    inline QByteArray getParam(const QByteArray& key) { return m_httpParser.params().value(key); }

    inline void setMiddlewareData(const QString& key, const QVariant& data) { m_middlewareData.insert(std::move(key), std::move(data)); }

    inline void setMiddlewareData(QString&& key, QVariant&& data) { m_middlewareData.insert(std::move(key), std::move(data)); }

    inline MiddlewareData& middlewareData() { return m_middlewareData; }
};

QEX_END_NAMESPACE

#endif // REQUEST_H