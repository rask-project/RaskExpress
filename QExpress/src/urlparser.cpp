#include "urlparser.h"
#include <QRegularExpressionMatch>
#include <QDebug>

QEX_BEGIN_NAMESPACE

UrlParser::UrlParser(QString &urlBase):
    m_urlBase(urlBase),
    m_basePath(),
    m_pathNameUrlBase(),
    m_pathName(),
    m_params()
{}

bool UrlParser::pathNameMatch(const QRegularExpression &regExp, const QStringList &parameters)
{
    m_pathNameUrlBase = m_urlBase.mid(m_basePath.size());
    if (m_pathNameUrlBase == "")
        m_pathNameUrlBase = "/";

    QRegularExpressionMatch match = regExp.match(m_pathNameUrlBase);
    if (match.hasMatch()) {
        m_pathName = m_pathNameUrlBase.toUtf8();

        for (int i = 1; i < match.capturedTexts().size(); ++i) {
            QByteArray key = parameters.at(i -1).toUtf8();
            QByteArray value = match.captured(i).toUtf8();

            m_params.insert(std::move(key), std::move(value));
        }
        return true;
    }
    return false;
}

QEX_END_NAMESPACE
