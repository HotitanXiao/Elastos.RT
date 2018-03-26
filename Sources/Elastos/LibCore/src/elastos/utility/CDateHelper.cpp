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

#include "elastos/utility/CDateHelper.h"
#include "elastos/utility/Date.h"

namespace Elastos {
namespace Utility {

CAR_SINGLETON_IMPL(CDateHelper)
CAR_INTERFACE_IMPL(CDateHelper, Singleton, IDateHelper)

ECode CDateHelper::Parse(
    /* [in] */ const String& string,
    /* [out] */ Int64* value)
{
    return Date::Parse(string, value);
}

ECode CDateHelper::UTC(
    /* [in] */ Int32 year,
    /* [in] */ Int32 month,
    /* [in] */ Int32 day,
    /* [in] */ Int32 hour,
    /* [in] */ Int32 minute,
    /* [in] */ Int32 second,
    /* [out] */ Int64* value)
{
    VALIDATE_NOT_NULL(value);
    *value = Date::UTC(year, month, day, hour, minute, second);
    return NOERROR;
}

} // Utility
} // Elastos
