#include "qexpress.h"

QEX_BEGIN_NAMESPACE

QExpress::QExpress(int argc, char *argv[]):
    m_application(argc, argv),
    m_server(new QExpressServer)
{}

QExpress::~QExpress()
{
    delete m_server;
}

int QExpress::start()
{
    if (!m_server->listen(QHostAddress::Any, 8080)) {
        qDebug() << "Error: " << m_server->errorString() << '\n';
        return -1;
    }

    return m_application.exec();
}

QEX_END_NAMESPACE
