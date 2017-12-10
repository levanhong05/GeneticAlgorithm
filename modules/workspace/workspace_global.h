#ifndef WORKSPACE_GLOBAL_H
#define WORKSPACE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WORKSPACE_LIBRARY)
#   define WORKSPACESHARED_EXPORT Q_DECL_EXPORT
#else
#   define WORKSPACESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WORKSPACE_GLOBAL_H

