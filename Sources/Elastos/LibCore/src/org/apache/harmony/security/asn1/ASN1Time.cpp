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

#include <ASN1Time.h>
#include "CBerInputStream.h"
#include "elastos/utility/CGregorianCalendar.h"
#include "elastos/utility/CTimeZoneHelper.h"

using Elastos::Utility::CGregorianCalendar;
using Elastos::Utility::CTimeZoneHelper;
using Elastos::Utility::ICalendar;
using Elastos::Utility::ITimeZoneHelper;
using Elastos::Utility::ICalendar;
using Elastos::Utility::IDate;
using Elastos::Utility::ITimeZone;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace Asn1 {

ASN1Time::ASN1Time()
{}

ECode ASN1Time::constructor(
    /* [in] */ Int32 tagNumber)
{
    return ASN1StringType::constructor(tagNumber);
}

ECode ASN1Time::GetDecodedObject(
    /* [in] */ IBerInputStream* bis,
    /* [out] */ IInterface** object)
{
    AutoPtr<ICalendar> c;
    AutoPtr<ITimeZoneHelper> tzh;
    AutoPtr<ITimeZone> tz;
    CTimeZoneHelper::AcquireSingleton((ITimeZoneHelper**)&tzh);
    tzh->GetTimeZone(String("GMT"), (ITimeZone**)&tz);
    CGregorianCalendar::New(tz, (ICalendar**)&c);
    AutoPtr<ArrayOf<Int32> > times = ((CBerInputStream*)bis)->mTimes;
    c->Set(ICalendar::YEAR, (*times)[0]);
    c->Set(ICalendar::MONTH, (*times)[1] - 1);
    c->Set(ICalendar::DAY_OF_MONTH, (*times)[2]);
    c->Set(ICalendar::HOUR_OF_DAY, (*times)[3]);
    c->Set(ICalendar::MINUTE, (*times)[4]);
    c->Set(ICalendar::SECOND, (*times)[5]);
    c->Set(ICalendar::MILLISECOND, (*times)[6]);
    AutoPtr<IDate> date;
    c->GetTime((IDate**)&date);
    *object = date.Get();
    REFCOUNT_ADD(*object)
    return NOERROR;
}

} // namespace Asn1
} // namespace Security
} // namespace Harmony
} // namespace Apache
} // namespace Org
