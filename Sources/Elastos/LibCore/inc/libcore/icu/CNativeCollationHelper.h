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

#ifndef __LIBCORE_ICU_ICU_CNATIVECOLLATIONHELPER_H__
#define __LIBCORE_ICU_ICU_CNATIVECOLLATIONHELPER_H__

#include "_Libcore_ICU_CNativeCollationHelper.h"
#include "elastos/core/Singleton.h"

using Elastos::Core::Singleton;
using Elastos::Utility::ILocale;

namespace Libcore {
namespace ICU {

CarClass(CNativeCollationHelper)
    , public Singleton
    , public INativeCollationHelper
{
public:
    CAR_SINGLETON_DECL()

    CAR_INTERFACE_DECL()

    CARAPI CloseCollator(
        /* [in] */ Int64 address);

    CARAPI Compare(
        /* [in] */ Int64 address,
        /* [in] */ const String& source,
        /* [in] */ const String& target ,
        /* [out] */ Int32 * value);

    CARAPI GetAttribute(
        /* [in] */ Int64 address,
        /* [in] */ Int32 type,
        /* [out] */ Int32 * value);

    CARAPI GetCollationElementIterator(
        /* [in] */ Int64 address,
        /* [in] */ const String& source,
        /* [out] */ Int64 * value);

    CARAPI GetRules(
        /* [in] */ Int64 address,
        /* [out] */ String * str);

    CARAPI GetSortKey(
        /* [in] */ Int64 address,
        /* [in] */ const String& source,
        /* [out, callee] */ ArrayOf<Byte> ** outarray);

    CARAPI OpenCollator(
        /* [in] */ ILocale* locale,
        /* [out] */ Int64 * value);

    CARAPI OpenCollatorFromRules(
        /* [in] */ const String& rules,
        /* [in] */ Int32 normalizationMode,
        /* [in] */ Int32 collationStrength,
        /* [out] */ Int64 * value);

    CARAPI SafeClone(
        /* [in] */ Int64 address,
        /* [out] */ Int64 * value);

    CARAPI SetAttribute(
        /* [in] */ Int64 address,
        /* [in] */ Int32 type,
        /* [in] */ Int32 value);

    CARAPI CloseElements(
        /* [in] */ Int64 address);

    CARAPI GetMaxExpansion(
        /* [in] */ Int64 address,
        /* [in] */ Int32 order,
        /* [out] */ Int32 * value);

    CARAPI GetOffset(
        /* [in] */ Int64 address,
        /* [out] */ Int32 * value);

    CARAPI GetNext(
        /* [in] */ Int64 address,
        /* [out] */ Int32 * value);

    CARAPI GetPrevious(
        /* [in] */ Int64 address,
        /* [out] */ Int32 * value);

    CARAPI Reset(
        /* [in] */ Int64 address);

    CARAPI SetOffset(
        /* [in] */ Int64 address,
        /* [in] */ Int32 offset);

    CARAPI SetText(
        /* [in] */ Int64 address,
        /* [in] */ const String& source);
};

} // namespace ICU
} // namespace Libcore

#endif //__LIBCORE_ICU_ICU_CNATIVECOLLATIONHELPER_H__
