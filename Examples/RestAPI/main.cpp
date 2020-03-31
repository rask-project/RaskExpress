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
    Q_UNUSED(request);
    response.send(QJsonObject{
                      { "server", QString(QExpress::HTTP::SERVER_VERSION) }
                  });
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
