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

#ifndef __ORG_APACHE_HARMONY_SECURITY_ASN1_CASN1ANY_H__
#define __ORG_APACHE_HARMONY_SECURITY_ASN1_CASN1ANY_H__

#include "_Org_Apache_Harmony_Security_Asn1_CASN1Any.h"
#include "org/apache/harmony/security/asn1/ASN1Type.h"

using Elastos::IO::IInputStream;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace Asn1 {

CarClass(CASN1Any)
    , public ASN1Type
    , public IASN1Any
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    static CARAPI GetInstance(
        /* [out] */ IASN1Any** instance);

    static CARAPI_(AutoPtr<IASN1Any>) Init();

    CARAPI GetId(
        /* [out] */ Int32* id);

    CARAPI GetConstrId(
        /* [out] */ Int32* constrId);

    CARAPI Decode(
        /* [in] */ ArrayOf<Byte>* encoded,
        /* [out] */ IInterface** object);

    CARAPI Decode(
        /* [in] */ ArrayOf<Byte>* encoded,
        /* [in] */ Int32 offset,
        /* [in] */ Int32 encodingLen,
        /* [out] */ IInterface** object);

    CARAPI Decode(
        /* [in] */ IInputStream* is,
        /* [out] */ IInterface** object);

    CARAPI Verify(
        /* [in] */ ArrayOf<Byte>* encoded);

    CARAPI Verify(
        /* [in] */ IO::IInputStream* is);

    CARAPI Encode(
        /* [in] */ IInterface* object,
        /* [out, callee] */ ArrayOf<Byte>** encode);

    CARAPI Decode(
        /* [in] */ IBerInputStream* bis,
        /* [out] */ IInterface** object);

    CARAPI CheckTag(
        /* [in] */ Int32 identifier,
        /* [out] */ Boolean* checkTag);

    CARAPI GetDecodedObject(
        /* [in] */ IBerInputStream* bis,
        /* [out] */ IInterface** object);

    CARAPI EncodeASN(
        /* [in] */ IBerOutputStream* bos);

    CARAPI EncodeContent(
        /* [in] */ IBerOutputStream* bos);

    CARAPI SetEncodingContent(
        /* [in] */ IBerOutputStream* bos);

    CARAPI GetEncodedLength(
        /* [in] */ IBerOutputStream* bos,
        /* [out] */ Int32 * pLength);

    CARAPI ToString(
        /* [out] */ String* result);

    CARAPI constructor();

private:
    /** default implementation */
    static AutoPtr<IASN1Any> sASN1;// = new ASN1Any();
};

} // namespace Asn1
} // namespace Security
} // namespace Harmony
} // namespace Apache
} // namespace Org

#endif // __ORG_APACHE_HARMONY_SECURITY_ASN1_CASN1ANY_H__
