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

#include "org/apache/harmony/security/x509/CPolicyQualifierInfoHelper.h"
#include "ASN1Sequence.h"
#include "ASN1Oid.h"
#include "CASN1Any.h"

using Org::Apache::Harmony::Security::Asn1::ASN1Sequence;
using Org::Apache::Harmony::Security::Asn1::ASN1Oid;
using Org::Apache::Harmony::Security::Asn1::CASN1Any;
using Org::Apache::Harmony::Security::Asn1::EIID_IASN1Sequence;
using Org::Apache::Harmony::Security::Asn1::IASN1Any;
using Org::Apache::Harmony::Security::Asn1::IASN1Type;
using Org::Apache::Harmony::Security::Asn1::IASN1Type;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace X509 {

CAR_SINGLETON_IMPL(CPolicyQualifierInfoHelper)
CAR_INTERFACE_IMPL(CPolicyQualifierInfoHelper, Singleton, IPolicyQualifierInfoHelper)

ECode CPolicyQualifierInfoHelper::GetASN1(
    /* [out] */ IASN1Sequence** ppAsn1)
{
    AutoPtr<ArrayOf<IASN1Type*> > types = ArrayOf<IASN1Type*>::Alloc(2);
    AutoPtr<IASN1Type> t1;
    ASN1Oid::GetInstance((IASN1Type**)&t1);
    types->Set(0, t1);
    AutoPtr<IASN1Any> aa;
    CASN1Any::GetInstance((IASN1Any**)&aa);
    types->Set(1, IASN1Type::Probe(aa));

    // Contains only ASN1 DER decoder currently
    AutoPtr<ASN1Sequence> ASN1 = new ASN1Sequence();
    ASN1->constructor(types);
    *ppAsn1 = (IASN1Sequence*)ASN1->Probe(EIID_IASN1Sequence);
    REFCOUNT_ADD(*ppAsn1);
    return NOERROR;
}

} // namespace X509
} // namespace Security
} // namespace Harmony
} // namespace Apache
} // namespace Org