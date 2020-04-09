#include "requeststatic.h"

QEX_BEGIN_NAMESPACE

RequestStatic::RequestStatic(const StaticConfig &config):
    m_static(config)
{}

void RequestStatic::function(Request &request, Response &response)
{
    QStringList filenameList;

    if (m_static.find("wwwPath") != m_static.end())
        filenameList << m_static["wwwPath"].toString();
    else
        filenameList << ".";

    if (m_static.find("rootPath") != m_static.end())
        filenameList << m_static["rootPath"].toString();

    filenameList << request.pathName;

    QString filename = filenameList.join("/").replace("//", "/");
    QFile file(filename);
    if (!file.exists()) {
        response.status(QExpress::HTTP::STATUS::CODE::NotFound);
        response.send(QExpress::HTTP::STATUS::TEXT(QExpress::HTTP::STATUS::CODE::NotFound));
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        response.status(QExpress::HTTP::STATUS::CODE::BadRequest);
        response.send(QExpress::HTTP::STATUS::TEXT(QExpress::HTTP::STATUS::CODE::BadRequest));
        return;
    }

    QMimeDatabase mimeDB;
    QMimeType mime = mimeDB.mimeTypeForFile(filename);
    response.addHeader("Content-Type", mime.name().toUtf8());

    response.send(file.readAll());
}

QEX_END_NAMESPACE
