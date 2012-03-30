/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_VERSION_H_
#define _GGS_UPDATESYSTEM_VERSION_H_

#ifndef HUDSON_BUILD
    #define FILEVER          1,0,0,0
    #define PRODUCTVER       FILEVER
    #define STRFILEVER       "1,0,0,0"
    #define STRPRODUCTVER    STRFILEVER

    #define COMPANYNAME      "GGS"
    #define FILEDESCRIPTION  "Developer version of GameNet UpdateSystem library"
    #define INTERNALNAME     "UpdateSystem"
    #define LEGALCOPYRIGHT   "Copyright(c) 2010 - 2012"

    #ifdef DEBUG 
        #define ORIGINALFILENAME "UpdateSystemX86d.dll"
    #else
        #define ORIGINALFILENAME "UpdateSystemX86.dll"
    #endif

    #define PRODUCTNAME      "GameNet UpdateSystem library"
#else
    #define FILEVER          $$MAJOR$$,$$MINOR$$,$$HUDSON_BUILD$$,$$SVN_REVISION$$
    #define PRODUCTVER       FILEVER
    #define STRFILEVER       "$$MAJOR$$,$$MINOR$$,$$HUDSON_BUILD$$,$$SVN_REVISION$$"
    #define STRPRODUCTVER    STRFILEVER

    #define COMPANYNAME      "$$COMPANYNAME$$"
    #define FILEDESCRIPTION  "$$FILEDESCRIPTION$$"
    #define INTERNALNAME     "$$INTERNALNAME$$"
    #define LEGALCOPYRIGHT   "$$LEGALCOPYRIGHT$$"
    #define ORIGINALFILENAME "$$FILENAME$$"
    #define PRODUCTNAME      "$$PRODUCTNAME$$"
#endif

#endif //_GGS_UPDATESYSTEM_VERSION_H_




