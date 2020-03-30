#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <chrono>
#include <QObject>
#include <QMap>
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

    QMap<QByteArray, QByteArray> m_header;
    QMap<QByteArray, QByteArray> m_params;
    QMap<QByteArray, QByteArray> m_body;
    QJsonValue m_bodyJson;
    QMap<QByteArray, QByteArray> m_query;
    QMultiMap<QByteArray, QMultiMap<QByteArray, QByteArray>> m_files;
    std::chrono::high_resolution_clock::time_point m_time;

public:
    HttpParser(QByteArray &data);

    inline bool isValid() { return m_valid; }

    inline qint64& contentLength() noexcept { return m_contentLength; }

    inline QByteArray& url() noexcept { return m_url; }

    inline QByteArray& method() noexcept { return m_method; }

    inline QByteArray& httpVersion() noexcept { return m_httpVersion; }

    inline QByteArray& contentType() noexcept { return m_contentType; }

    inline QMap<QByteArray, QByteArray>& header() noexcept { return m_header; }

    inline QMap<QByteArray, QByteArray>& body() noexcept { return m_body; }

    inline QJsonValue bodyJson() noexcept { return m_bodyJson; };

    inline QMap<QByteArray, QByteArray>& query() noexcept { return m_query; }

    inline QMultiMap<QByteArray, QMultiMap<QByteArray, QByteArray>>& files() noexcept { return m_files; }

    inline QMap<QByteArray, QByteArray>& params() { return m_params; }

    inline QByteArray getParam(const QByteArray& key) { return m_params.value(key); }

    inline void setParams(const QMultiMap<QByteArray, QByteArray>& params) { m_params = params; }

    inline std::chrono::high_resolution_clock::time_point& time() { return m_time; }

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
