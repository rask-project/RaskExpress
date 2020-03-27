#include "qexpress.h"

QEX_BEGIN_NAMESPACE

QExpress::QExpress(int argc, char *argv[]):
    m_application(argc, argv),
    m_server(new QExpressServer),
    m_host(QHostAddress::Any),
    m_port(8213)
{}

QExpress::~QExpress()
{
    delete m_server;
}

int QExpress::start()
{
    if (!m_server->listen(m_host, m_port)) {
        qDebug() << "Error: " << m_server->errorString() << '\n';
        return -1;
    }

    qDebug() << "Server running in" << m_port;
    return m_application.exec();
}

QEX_END_NAMESPACE
