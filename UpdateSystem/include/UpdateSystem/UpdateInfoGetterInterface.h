/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_UPDATESYSTEM_UPDATEINFOGETTERINTERFACE_H_
#define _GGS_UPDATESYSTEM_UPDATEINFOGETTERINTERFACE_H_

#include "UpdateInfoGetterResultInterface.h"
#include "UpdateInfoContainer.h"

namespace GGS { 
  namespace UpdateSystem {

    class UpdateInfoGetterInterface {
    public:
      ~UpdateInfoGetterInterface() {}
      virtual void start() = 0;
      virtual void setResultCallback(GGS::UpdateSystem::UpdateInfoGetterResultInterface *result) = 0;
      virtual UpdateInfoContainer *updateInfo() const = 0;
    };

  }
}
#endif // _GGS_UPDATESYSTEM_UPDATEINFOGETTERINTERFACE_H_