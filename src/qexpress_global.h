#ifndef QEXPRESS_GLOBAL_H
#define QEXPRESS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QEXPRESS_LIBRARY)
#  define QEXPRESS_EXPORT Q_DECL_EXPORT
#else
#  define QEXPRESS_EXPORT Q_DECL_IMPORT
#endif

#define QEX_BEGIN_NAMESPACE namespace QExpress {
#define QEX_END_NAMESPACE }

#endif // QEXPRESS_GLOBAL_H
