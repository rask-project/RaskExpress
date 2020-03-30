#include "config.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QHostAddress>
#include <QDebug>

QEX_BEGIN_NAMESPACE

Config::Config(const QString &filename):
    m_filename(filename)
{
    config = QJsonObject({
                             { "port", 8080 },
                             { "maxThread", 200 },
                             { "timeout", 60000 },
                             { "maxUploadSize", 20971520 },
                             { "logFileName", "qexpress.log" }
                         });

    if (!filename.isEmpty())
        loadConfigFile();
}

void Config::loadConfigFile()
{
    QFile configFile(m_filename);
    if (!configFile.exists()) {
        qDebug() << "Config file" << m_filename << "does not exist";
        return;
    }

    if (!configFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Config file" << m_filename << "was not loaded";
    }

    QTextStream in(&configFile);
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(in.readAll().toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "An error occurred while parsing JSON file:" << error.errorString();
        return;
    }

    if (!doc.isObject()) {
        qDebug() << "JSON content is not a valid object";
        return;
    }

    for (const auto& key: doc.object().keys()) {
        if  (config[key].type() == QJsonValue::Bool)
            config[key] = doc.object()[key].toBool();
        if  (config[key].type() == QJsonValue::Double)
            config[key] = doc.object()[key].toDouble();
        if  (config[key].type() == QJsonValue::String)
            config[key] = doc.object()[key].toString();
        if  (config[key].type() == QJsonValue::Array)
            config[key] = doc.object()[key].toArray();
        if  (config[key].type() == QJsonValue::Object)
            config[key] = doc.object()[key].toObject();
        if  (config[key].type() == QJsonValue::Null)
            config[key] = 0;
    }

    configFile.close();
}

QEX_END_NAMESPACE
