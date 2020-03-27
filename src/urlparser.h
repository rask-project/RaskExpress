#ifndef URLPARSER_H
#define URLPARSER_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class UrlParser
{
    QString m_urlBase;
    QString m_basePath;
    QString m_pathNameUrlBase;
    QString m_pathName;
    QMultiMap<QByteArray, QByteArray> m_params;

    UrlParser(const UrlParser& other) = delete;
    UrlParser& operator=(const UrlParser& other) = delete;
public:
    explicit UrlParser(QString& urlBase);

    inline void setBasePath(const QString& basePath) { m_basePath = basePath; }
    inline bool basePathMatch() { return m_urlBase.startsWith(m_basePath); }

    inline void setPathName(const QString& pathName) { m_pathName = pathName; }
    bool pathNameMatch(const QRegularExpression& regExp, const QStringList& parameters);

    const QMultiMap<QByteArray, QByteArray>& params() { return m_params; }
};

QEX_END_NAMESPACE

#endif // URLPARSER_H
