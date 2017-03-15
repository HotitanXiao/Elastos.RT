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

#ifndef __ORG_APACHE_HARMONY_SECURITY_ASN1_CASN1GENERALIZEDTIME_H__
#define __ORG_APACHE_HARMONY_SECURITY_ASN1_CASN1GENERALIZEDTIME_H__

#include "_Org_Apache_Harmony_Security_Asn1_CASN1GeneralizedTime.h"
#include "org/apache/harmony/security/asn1/ASN1Time.h"

using Elastos::IO::IInputStream;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace Asn1 {

CarClass(CASN1GeneralizedTime)
    , public ASN1Time
    , public IASN1GeneralizedTime
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    static AutoPtr<IASN1Type> Init();

    static CARAPI GetInstance(
        /* [out] */ IASN1GeneralizedTime** instance);

    CARAPI Decode(
        /* [in] */ IBerInputStream* bis,
        /* [out] */ IInterface** object);

    CARAPI EncodeContent(
        /* [in] */ IBerOutputStream* bos);

    CARAPI SetEncodingContent(
        /* [in] */ IBerOutputStream* bos);

    CARAPI constructor();

private:
    // default implementation
    static AutoPtr<IASN1Type> sASN1;

    // FIXME support only one format for encoding, do we need others?
    //
    // According to X.680:
    // four digit year, seconds always presented
    // and fractional-seconds elements without
    // trailing 0's (must be cut later from content)
    static String GEN_PATTERN;// = "yyyyMMddHHmmss.SSS";
};

} // namespace Asn1
} // namespace Security
} // namespace Harmony
} // namespace Apache
} // namespace Org

#endif // __ORG_APACHE_HARMONY_SECURITY_ASN1_CASN1GENERALIZEDTIME_H__
