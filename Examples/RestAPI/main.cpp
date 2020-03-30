#include <qexpress/qexpress.h>
#include <qexpress/config.h>
#include <qexpress/router.h>
#include <qexpress/request.h>
#include <qexpress/response.h>
#include <QDateTime>
#include <chrono>
#include <ctime>
#include <ratio>

void about(QExpress::Request& request, QExpress::Response& response) {
    response.send(QJsonObject{
                      { "server", QString(QExpress::HTTP::SERVER_VERSION) }
                  });
    std::chrono::high_resolution_clock::time_point start = request.time();
    std::chrono::high_resolution_clock::time_point end = response.time();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    qDebug().noquote()
            << request.method()
            << request.url()
            << response.getStatus()
            << response.getHeader("Content-Length")
            << QString("%1ms").arg(ms);
}

int main(int argc, char *argv[])
{
    QExpress::Config config;
    QExpress::QExpress server(argc, argv, config);

    QExpress::Router routerAbout;

    routerAbout.Get("/", about);

    server.router("/about", &routerAbout);

    return server.start();
}
