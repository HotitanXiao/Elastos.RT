//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __ELASTOS_DROID_SYSTEM_CSTRUCTTIMEVALHELPER_H__
#define __ELASTOS_DROID_SYSTEM_CSTRUCTTIMEVALHELPER_H__

#include "core/Singleton.h"
#include "_Elastos_Droid_System_CStructTimevalHelper.h"


namespace Elastos {
namespace Droid {
namespace System {

CarClass(CStructTimevalHelper)
    , public Singleton
    , public IStructTimevalHelper
{
public:
    CAR_SINGLETON_DECL()

    CAR_INTERFACE_DECL()

    CARAPI FromMillis(
        /* [in] */ Int64 millis,
        /* [out] */ IStructTimeval** tv);
};

} // namespace System
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_SYSTEM_CSTRUCTTIMEVALHELPER_H__
