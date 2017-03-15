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

#ifndef __ORG_APACHE_HARMONY_SECURITY_X509_ALGORITHMIDENTIFIER_H__
#define __ORG_APACHE_HARMONY_SECURITY_X509_ALGORITHMIDENTIFIER_H__

#include "Elastos.CoreLibrary.Apache.h"
#include "org/apache/harmony/security/asn1/ASN1Sequence.h"
#include <elastos/core/Object.h>

using Org::Apache::Harmony::Security::Asn1::ASN1Sequence;
using Org::Apache::Harmony::Security::Asn1::IASN1Sequence;
using Org::Apache::Harmony::Security::Asn1::IBerInputStream;
using Org::Apache::Harmony::Security::Asn1::IASN1Type;
using Elastos::Core::Object;
using Elastos::Core::IStringBuilder;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace X509 {

class AlgorithmIdentifier
    : public Object
    , public IAlgorithmIdentifier
{
private:
    class MyASN1Sequence
        : public ASN1Sequence
    {
    public:
        CARAPI GetDecodedObject(
            /* [in] */ IBerInputStream* bis,
            /* [out] */ IInterface** object);

        CARAPI GetValues(
            /* [in] */ IInterface* object,
            /* [in] */ ArrayOf<IInterface*>* values);

        TO_STRING_IMPL("AlgorithmIdentifier::MyASN1Sequence")
    };

public:
    CAR_INTERFACE_DECL()

    CARAPI GetAlgorithm(
        /* [out] */ String* pAlgorithm);

    CARAPI GetAlgorithmName(
        /* [out] */ String* pAlgorithmName);

    CARAPI GetParameters(
        /* [out, callee] */ ArrayOf<Byte>** ppParameters);

    CARAPI GetEncoded(
        /* [out, callee] */ ArrayOf<Byte>** ppEncoded);

    CARAPI Equals(
        /* [in] */ IInterface* pAi,
        /* [out] */ Boolean* pResult);

    CARAPI GetHashCode(
        /* [out] */ Int32* pResult);

    CARAPI DumpValue(
        /* [in] */ IStringBuilder* pSb);

    CARAPI constructor(
        /* [in] */ const String& algorithm);

    CARAPI constructor(
        /* [in] */ const String& algorithm,
        /* [in] */ ArrayOf<Byte>* pParameters);

    /**
     * For testing when algorithmName is not known, but algorithm OID is.
     */
    CARAPI constructor(
        /* [in] */ const String& algorithm,
        /* [in] */ const String& algorithmName);

    static CARAPI GetASN1(
        /* [out] */ IASN1Sequence** ppAsn1);

    static CARAPI SetASN1(
        /* [in] */ IASN1Sequence* pAsn1);

private:
    CARAPI constructor(
        /* [in] */ const String& algorithm,
        /* [in] */ ArrayOf<Byte>* pParameters,
        /* [in] */ ArrayOf<Byte>* encoding);

    static CARAPI_(AutoPtr<IASN1Sequence>) initASN1();

public:
    /**
     * Custom AlgorithmIdentifier DER encoder/decoder
     */
    static AutoPtr<IASN1Sequence> ASN1;

private:
    /** the value of algorithm field */
    String mAlgorithm;

    /** the name of the algorithm */
    String mAlgorithmName;

    /** the value of parameters field */
    AutoPtr<ArrayOf<Byte> > mParameters;

    /** the encoding of AlgorithmIdentifier value */
    AutoPtr<ArrayOf<Byte> > mEncoding;
};

} //namespace X509
} //namespace Security
} //namespace Harmony
} //namespace Apache
} //namespace Org

#endif // __ORG_APACHE_HARMONY_SECURITY_X509_ALGORITHMIDENTIFIER_H__
