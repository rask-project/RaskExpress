#include "router.h"

QEX_BEGIN_NAMESPACE

ObjectRouter::ObjectRouter(const QString& path, const RouteFunctor& functor, const QByteArray& method, const bool &endLimit):
    pathName(path),
    method(method),
    regExp(),
    functor(functor),
    middlewares(),
    m_endLimit(endLimit)
{
    getRegExpFromPath();
}

ObjectRouter::ObjectRouter(const QString &path, const RouteFunctor &functor, const QByteArray &method, const Middlewares &midd, const bool &endLimit):
    pathName(path),
    method(method),
    regExp(),
    functor(std::move(functor)),
    middlewares(std::move(midd)),
    m_endLimit(endLimit)
{
    getRegExpFromPath();
}

void ObjectRouter::getRegExpFromPath()
{
    regExp = QRegularExpression(QString(('^' + pathName + (pathName.endsWith('/') ? "" : "/?") + (m_endLimit ? "$" : "")))
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

void Router::Post(const QString &url, Middlewares &middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::POST, std::move(middlewares)));
}

void Router::Post(const QString &url, Middlewares &&middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::POST, std::move(middlewares)));
}

void Router::Put(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::PUT));
}

void Router::Put(const QString &url, Middlewares &middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::PUT, std::move(middlewares)));
}

void Router::Put(const QString &url, Middlewares &&middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::PUT, std::move(middlewares)));
}

void Router::Delete(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::DELETE));
}

void Router::Delete(const QString &url, Middlewares &middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::DELETE, std::move(middlewares)));
}

void Router::Delete(const QString &url, Middlewares &&middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::DELETE, std::move(middlewares)));
}

void Router::Patch(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::PATCH));
}

void Router::Patch(const QString &url, Middlewares &middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::PATCH, std::move(middlewares)));
}

void Router::Patch(const QString &url, Middlewares &&middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::PATCH, std::move(middlewares)));
}

void Router::Head(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::HEAD));
}

void Router::Head(const QString &url, Middlewares &middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::HEAD, std::move(middlewares)));
}

void Router::Head(const QString &url, Middlewares &&middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::HEAD, std::move(middlewares)));
}

void Router::Trace(const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::TRACE));
}

void Router::Trace(const QString &url, Middlewares &middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::TRACE, std::move(middlewares)));
}

void Router::Trace(const QString &url, Middlewares &&middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), HTTP::METHOD::TRACE, std::move(middlewares)));
}

void Router::route(const QString& method, const QString& url, RouteFunctor&& functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), method.toUtf8()));
}

void Router::route(const QString &method, const QString &url, Middlewares &middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), method.toUtf8(), std::move(middlewares)));
}

void Router::route(const QString &method, const QString &url, Middlewares &&middlewares, RouteFunctor &&functor)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), std::move(functor), method.toUtf8(), std::move(middlewares)));
}

void Router::Static(const QString &url, StaticConfig &&config)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), [config](QExpress::Request& request, QExpress::Response& response) {
                           RequestStatic requestStatic(config);
                           requestStatic.function(request, response);
                       }, HTTP::METHOD::GET, false));
}

void Router::Static(const QString &url, Middlewares &middlewares, StaticConfig &&config)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), [config](QExpress::Request& request, QExpress::Response& response) {
                           RequestStatic requestStatic(config);
                           requestStatic.function(request, response);
                       }, HTTP::METHOD::GET, std::move(middlewares), false));
}

void Router::Static(const QString &url, Middlewares &&middlewares, StaticConfig &&config)
{
    QMutexLocker locker(&m_mutex);
    m_routes.push_back(ObjectRouter(std::move(url), [config](QExpress::Request& request, QExpress::Response& response) {
                           RequestStatic requestStatic(config);
                           requestStatic.function(request, response);
                       }, HTTP::METHOD::GET, std::move(middlewares), false));
}

QEX_END_NAMESPACE
