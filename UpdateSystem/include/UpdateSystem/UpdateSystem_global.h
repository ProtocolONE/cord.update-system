#pragma once

#include <QtCore/qglobal.h>

#ifdef UPDATESYSTEM_STATIC_LIBRARY
#  define UPDATESYSTEMSHARED_EXPORT 
#else

#if defined(UPDATESYSTEM_LIBRARY)
#  define UPDATESYSTEMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UPDATESYSTEMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif

#define SIGNAL_CONNECT_CHECK(X) { bool result = X; Q_ASSERT_X(result, __FUNCTION__ , #X); }

#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

