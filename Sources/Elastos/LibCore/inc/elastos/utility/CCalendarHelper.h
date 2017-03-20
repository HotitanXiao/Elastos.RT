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

#ifndef __ELASTOS_UTILITY_CCALENDARHELPER_H__
#define __ELASTOS_UTILITY_CCALENDARHELPER_H__

#include "_Elastos_Utility_CCalendarHelper.h"
#include "elastos/core/Singleton.h"

using Elastos::Core::Singleton;
using Elastos::Utility::ILocale;

namespace Elastos{
namespace Utility{

CarClass(CCalendarHelper)
    , public Singleton
    , public ICalendarHelper
{
public:
    CAR_SINGLETON_DECL()

    CAR_INTERFACE_DECL()

    CARAPI GetAvailableLocales(
        /* [out, callee] */ ArrayOf<ILocale*>** locales);

    CARAPI GetInstance(
        /* [out] */ ICalendar ** ppCalenar);

    CARAPI GetInstance(
        /* [in] */ ILocale * pLocale,
        /* [out] */ ICalendar ** ppCalenar);

    CARAPI GetInstance(
        /* [in] */ ITimeZone * pTimezone,
        /* [out] */ ICalendar ** ppCalenar);

    CARAPI GetInstance(
        /* [in] */ ITimeZone * pTimezone,
        /* [in] */ ILocale * pLocale,
        /* [out] */ ICalendar ** ppCalenar);
};

} // namespace Utility
} // namespace Elastos

#endif // __ELASTOS_UTILITY_CCALENDARHELPER_H__