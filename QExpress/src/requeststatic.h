#ifndef REQUESTSTATIC_H
#define REQUESTSTATIC_H

#include <map>
#include <QVariant>
#include <QMimeDatabase>
#include <QMimeType>
#include <QFile>

#include "request.h"
#include "response.h"
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE

typedef std::map<QString, QVariant> StaticConfig;

class RequestStatic
{
    StaticConfig m_static;

public:
    RequestStatic(const StaticConfig& config);

    void function(Request& request, Response& response);
};

QEX_END_NAMESPACE

#endif // REQUESTSTATIC_H
