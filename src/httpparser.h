#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QByteArray>
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
    QMultiMap<QByteArray, QByteArray> m_body;
    QMultiMap<QByteArray, QByteArray> m_query;
    QMultiMap<QByteArray, QByteArray> m_parameters;
    QMultiMap<QByteArray, QMultiMap<QByteArray, QByteArray>> m_files;

public:
    HttpParser(QByteArray &data);

    inline bool isValid() { return m_valid; }

private:
    bool parseHttpData(QByteArray &data);
    void parseHeader();
    void parseBody();
    void parseMultiPart();
    void extractCookies();

    QByteArray& queryDecoded(QByteArray& query);
    QByteArray& removeCharsFromEnd(QByteArray& query);
};

QEX_END_NAMESPACE

#endif // HTTPPARSER_H
