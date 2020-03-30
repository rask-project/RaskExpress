#include "qexpress.h"
#include <iostream>
#include <QDebug>

QString logFileName;

void writeLog(QtMsgType type, const QMessageLogContext &logContext, const QString &msg)
{
    QString date = QDateTime::currentDateTime().toString(Qt::DateFormat::ISODate);
    QTextStream out(stdout);

    QString typeStr;
    switch (type) {
    case QtDebugMsg: typeStr = "Debug"; break;
    case QtWarningMsg: typeStr = "Warning"; break;
    case QtCriticalMsg: typeStr = "Critical"; break;
    case QtInfoMsg: typeStr = "Info"; break;
    case QtFatalMsg: typeStr = "Fatal"; break;
    }

    QFile file(logFileName);
    if (file.open(QIODevice::Append)) {
        out.setDevice(&file);
    } else {
        out << date << " [" << typeStr << "] " << logFileName << ": " << file.errorString().toLatin1().constData() << '\n';
    }

    out << date << " [" << typeStr << "]";

    if (logContext.file != nullptr || logContext.function != nullptr)
        out << " (" << logContext.file << ":" << logContext.function << ")";
    out << ": " << msg.toLatin1().constData() << '\n';

    if (type == QtFatalMsg) {
        out << " [" << typeStr << "]" << ": Server is down\n";
        file.close();
        abort();
    }
    file.close();
}

QEX_BEGIN_NAMESPACE

QExpress::QExpress(int argc, char *argv[], Config &config):
    m_application(argc, argv),
    m_config(config),
    m_server(new QExpressServer(m_config)),
    m_host(QHostAddress::Any),
    m_port(m_config.config["port"].toInt())
{
    logFileName = m_config.config["logFileName"].toString();
    qInstallMessageHandler(writeLog);
}

QExpress::~QExpress()
{
    delete m_server;
}

int QExpress::start()
{
    if (!m_server->listen(m_host, m_port)) {
        qFatal("%s", m_server->errorString().toLatin1().constData());
        return -1;
    }

    qDebug() << "Server running in" << m_port;
    return m_application.exec();
}

QEX_END_NAMESPACE
