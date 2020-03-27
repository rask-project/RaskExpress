#include "router.h"

QEX_BEGIN_NAMESPACE

ObjectRouter::ObjectRouter(const QString& path, const RouteFunctor& functor, const QByteArray& method):
    pathName(path),
    method(method),
    regExp(),
    functor(functor),
    middlewares()
{
    getRegExpFromPath();
}

ObjectRouter::ObjectRouter(const QString &path, const RouteFunctor &functor, const QByteArray &method, const Middlewares &midd):
    pathName(path),
    method(method),
    regExp(),
    functor(std::move(functor)),
    middlewares(std::move(midd))
{
    getRegExpFromPath();
}

void ObjectRouter::getRegExpFromPath()
{
    regExp = QRegularExpression(QString(('^' + pathName + (pathName.endsWith('/') ? "" : "/?") + "$"))
                                  .replace(QRegularExpression("([\\/\\.])"), "\\/")
                                  .replace(QRegularExpression("\\\\/:(\\w+)"), "\\/(?:([^\\/]+?))"));
    if (pathName.indexOf("/:") > -1) {
        QString getParams = pathName;
        getParams.replace(QRegularExpression("\\/((\\w+|\\d+|-)+)"), "");
        parameters = getParams.split("/:");
        parameters.removeAll("");
    }
}

void Router::Get(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::GET));
}

void Router::Get(const QString &url, Middlewares &middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::GET, std::move(middlewares)));
}

void Router::Get(const QString &url, Middlewares &&middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::GET, std::move(middlewares)));
}

void Router::Post(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::POST));
}

void Router::Put(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::PUT));
}

void Router::Delete(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::DELETE));
}

void Router::Patch(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::PATCH));
}

void Router::Head(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::HEAD));
}

void Router::Trace(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::TRACE));
}

void Router::route(const QString& method, const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), method.toUtf8()));
}

QEX_END_NAMESPACE
