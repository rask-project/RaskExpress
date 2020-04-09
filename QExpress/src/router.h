#ifndef ROUTE_H
#define ROUTE_H

#include <map>
#include <vector>
#include <tuple>
#include <functional>
#include <QMutex>
#include <QMutexLocker>
#include <QRegularExpression>

#include "request.h"
#include "response.h"
#include "requeststatic.h"
#include "qexpress_consts.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

class ObjectRouter;

typedef std::function<void(QExpress::Request& request, QExpress::Response& response)> RouteFunctor;
typedef std::function<bool(QExpress::Request& request, QExpress::Response& response, QVariant)> Middleware;

typedef std::vector<ObjectRouter> Routes;
typedef std::vector<std::tuple<Middleware, QVariant>> Middlewares;

class ObjectRouter
{
    void getRegExpFromPath();
public:
    QString pathName;
    QByteArray method;
    QRegularExpression regExp;
    QStringList parameters;
    RouteFunctor functor;
    Middlewares middlewares;
    bool m_endLimit;

    ObjectRouter(const QString& path, const RouteFunctor& functor, const QByteArray& method, const bool& endLimit = true);
    ObjectRouter(const QString& path, const RouteFunctor& functor, const QByteArray& method, const Middlewares& midd, const bool& endLimit = true);
};

class Router
{
    Routes m_routes;
    mutable QMutex m_mutex;
public:
    Router(): m_routes() {}

    inline Routes& routes() { return m_routes; }

    void Get(const QString& url, RouteFunctor&& functor);
    void Get(const QString& url, Middlewares& middlewares, RouteFunctor&& functor);
    void Get(const QString& url, Middlewares&& middlewares, RouteFunctor&& functor);

    void Post(const QString& url, RouteFunctor&& functor);
    void Post(const QString& url, Middlewares& middlewares, RouteFunctor&& functor);
    void Post(const QString& url, Middlewares&& middlewares, RouteFunctor&& functor);

    void Put(const QString& url, RouteFunctor&& functor);
    void Put(const QString& url, Middlewares& middlewares, RouteFunctor&& functor);
    void Put(const QString& url, Middlewares&& middlewares, RouteFunctor&& functor);

    void Delete(const QString& url, RouteFunctor&& functor);
    void Delete(const QString& url, Middlewares& middlewares, RouteFunctor&& functor);
    void Delete(const QString& url, Middlewares&& middlewares, RouteFunctor&& functor);

    void Patch(const QString& url, RouteFunctor&& functor);
    void Patch(const QString& url, Middlewares& middlewares, RouteFunctor&& functor);
    void Patch(const QString& url, Middlewares&& middlewares, RouteFunctor&& functor);

    void Head(const QString& url, RouteFunctor&& functor);
    void Head(const QString& url, Middlewares& middlewares, RouteFunctor&& functor);
    void Head(const QString& url, Middlewares&& middlewares, RouteFunctor&& functor);

    void Trace(const QString& url, RouteFunctor&& functor);
    void Trace(const QString& url, Middlewares& middlewares, RouteFunctor&& functor);
    void Trace(const QString& url, Middlewares&& middlewares, RouteFunctor&& functor);

    void route(const QString& method, const QString& url, RouteFunctor&& functor);
    void route(const QString& method, const QString& url, Middlewares& middlewares, RouteFunctor&& functor);
    void route(const QString& method, const QString& url, Middlewares&& middlewares, RouteFunctor&& functor);

    void Static(const QString& url, StaticConfig &&config);
    void Static(const QString& url, Middlewares& middlewares, StaticConfig &&config);
    void Static(const QString& url, Middlewares&& middlewares, StaticConfig &&config);
};

QEX_END_NAMESPACE

#endif // ROUTE_H
