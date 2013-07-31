/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef UPDATESYSTEM_GLOBAL_H
#define UPDATESYSTEM_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtCore/QDebug>

#if defined(UPDATESYSTEM_LIBRARY)
#  define UPDATESYSTEMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UPDATESYSTEMSHARED_EXPORT Q_DECL_IMPORT
#endif

#define SIGNAL_CONNECT_CHECK(X) { bool result = X; Q_ASSERT_X(result, __FUNCTION__ , #X); }

#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

#endif // UPDATESYSTEM_GLOBAL_H
