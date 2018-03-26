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

#ifndef __LIBCORE_ICU_CNATIVEPLURALRULESHELPER_H__
#define __LIBCORE_ICU_CNATIVEPLURALRULESHELPER_H__

#include "elastos/core/Singleton.h"
#include "_Libcore_ICU_CNativePluralRulesHelper.h"

using Elastos::Core::Singleton;
using Elastos::Utility::ILocale;

namespace Libcore {
namespace ICU {

CarClass(CNativePluralRulesHelper)
    , public Singleton
    , public INativePluralRulesHelper
{
    CAR_SINGLETON_DECL()

public:
    CAR_INTERFACE_DECL()

    CARAPI ForLocale(
        /* [in] */ ILocale * locale,
        /* [out] */ INativePluralRules ** outrules);
};

} // namespace ICU
} // namespace Libcore

#endif //__LIBCORE_ICU_CNATIVEPLURALRULESHELPER_H__
