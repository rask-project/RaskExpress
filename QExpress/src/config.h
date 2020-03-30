#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QMultiMap>
#include <QJsonObject>
#include <QFile>

#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE



class QEXPRESS_EXPORT Config
{
    QString m_filename;

public:
    Config(const QString& filename = "");
    QJsonObject config;

private:
    void loadConfigFile();
};

QEX_END_NAMESPACE

#endif // CONFIG_H
