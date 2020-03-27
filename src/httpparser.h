#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QObject>
#include <QMultiMap>
#include <QVector>
#include <QByteArray>
#include <QJsonValue>
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class QEXPRESS_EXPORT HttpParser
{
    bool m_valid;
    bool m_multiPart;
    QByteArray m_url;
    QByteArray m_method;
    QByteArray m_httpVersion;
    QByteArray m_contentType;
    qint64 m_contentLength;
    QByteArray m_headerString;
    QByteArray m_bodyString;

    QMultiMap<QByteArray, QByteArray> m_header;
    QMultiMap<QByteArray, QByteArray> m_params;
    QMultiMap<QByteArray, QByteArray> m_body;
    QJsonValue m_bodyJson;
    QMultiMap<QByteArray, QByteArray> m_query;
    QMultiMap<QByteArray, QMultiMap<QByteArray, QByteArray>> m_files;

public:
    HttpParser(QByteArray &data);

    inline bool isValid() { return m_valid; }

    inline qint64& contentLength() noexcept { return m_contentLength; }

    inline QByteArray& url() noexcept { return m_url; }

    inline QByteArray& method() noexcept { return m_method; }

    inline QByteArray& httpVersion() noexcept { return m_httpVersion; }

    inline QByteArray& contentType() noexcept { return m_contentType; }

    inline QMultiMap<QByteArray, QByteArray>& header() noexcept { return m_header; }

    inline QMultiMap<QByteArray, QByteArray>& body() noexcept { return m_body; }

    inline QJsonValue bodyJson() noexcept { return m_bodyJson; };

    inline QMultiMap<QByteArray, QByteArray>& query() noexcept { return m_query; }

    inline QMultiMap<QByteArray, QMultiMap<QByteArray, QByteArray>>& files() noexcept { return m_files; }

    inline QMultiMap<QByteArray, QByteArray>& params() { return m_params; }

    inline QByteArray getParam(const QByteArray& key) { return m_params.value(key); }

    inline void setParams(const QMultiMap<QByteArray, QByteArray>& params) { m_params = params; }

private:
    bool parseHttpData(QByteArray &data);
    void parseHeader();
    void parseUrl();
    void parseBody();
    void parseMultiPart();
    void extractCookies();

    QByteArray& queryDecoded(QByteArray& query);
    QByteArray& removeCharsFromEnd(QByteArray& query);
};

QEX_END_NAMESPACE

#endif // HTTPPARSER_H
