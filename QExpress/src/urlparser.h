#ifndef URLPARSER_H
#define URLPARSER_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include "QMap"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class UrlParser
{
    QString m_urlBase;
    QString m_basePath;
    QString m_pathNameUrlBase;
    QByteArray m_pathName;
//    std::vector<std::pair<QByteArray, QByteArray>> m_params;
    QMap<QByteArray, QByteArray> m_params;

    UrlParser(const UrlParser& other) = delete;
    UrlParser& operator=(const UrlParser& other) = delete;
public:
    explicit UrlParser(QString& urlBase);

    inline void setBasePath(const QString& basePath) { m_basePath = basePath; }
    inline bool basePathMatch() { return m_urlBase.startsWith(m_basePath); }

    inline QByteArray pathName() { return m_pathName; }
    bool pathNameMatch(const QRegularExpression& regExp, const QStringList& parameters);

//    const std::vector<std::pair<QByteArray, QByteArray>>& params() { return m_params; }
    const QMap<QByteArray, QByteArray>& params() { return m_params; }
};

QEX_END_NAMESPACE

#endif // URLPARSER_H
