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

#include "org/apache/harmony/security/x509/CDistributionPoint.h"
#include "org/apache/harmony/security/x509/CDistributionPointName.h"
#include "org/apache/harmony/security/x509/CReasonFlags.h"
#include "org/apache/harmony/security/x509/CGeneralNames.h"
#include "org/apache/harmony/security/asn1/ASN1Type.h"
#include "org/apache/harmony/security/asn1/CASN1Explicit.h"
#include "org/apache/harmony/security/asn1/CASN1Implicit.h"
#include <elastos/core/CoreUtils.h>
#include <elastos/core/StringBuilder.h>
#include "core/CArrayOf.h"
#include "core/CByte.h"

using Org::Apache::Harmony::Security::X509::CDistributionPointName;
using Org::Apache::Harmony::Security::Asn1::ASN1Type;
using Org::Apache::Harmony::Security::Asn1::IASN1Type;
using Org::Apache::Harmony::Security::Asn1::IASN1Explicit;
using Org::Apache::Harmony::Security::Asn1::CASN1Explicit;
using Org::Apache::Harmony::Security::Asn1::IASN1Implicit;
using Org::Apache::Harmony::Security::Asn1::CASN1Implicit;
using Elastos::Core::IArrayOf;
using Elastos::Core::CArrayOf;
using Elastos::Core::IByte;
using Elastos::Core::CByte;
using Elastos::Core::CoreUtils;
using Elastos::Core::StringBuilder;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace X509 {

ECode CDistributionPoint::MyASN1Sequence::GetDecodedObject(
    /* [in] */ IBerInputStream* bis,
    /* [out] */ IInterface** object)
{
    VALIDATE_NOT_NULL(object);

    AutoPtr<IInterface> con;
    bis->GetContent((IInterface**)&con);
    AutoPtr<IArrayOf> values = IArrayOf::Probe(con);

    AutoPtr<IInterface> obj0;
    values->Get(0, (IInterface**)&obj0);

    AutoPtr<IInterface> obj1;
    values->Get(1, (IInterface**)&obj1);

    AutoPtr<IInterface> obj2;
    values->Get(2, (IInterface**)&obj2);

    AutoPtr<IDistributionPoint> point;
    CDistributionPoint::New(IDistributionPointName::Probe(obj0),
            IReasonFlags::Probe(obj1), IGeneralNames::Probe(obj2),
            (IDistributionPoint**)&point);
    *object = TO_IINTERFACE(point);
    REFCOUNT_ADD(*object);
    return NOERROR;
}

ECode CDistributionPoint::MyASN1Sequence::GetValues(
    /* [in] */ IInterface* object,
    /* [in] */ ArrayOf<IInterface*>* values)
{
    CDistributionPoint* dp = (CDistributionPoint*)IDistributionPoint::Probe(object);
    values->Set(0, TO_IINTERFACE(dp->mDistributionPoint));
    values->Set(1, TO_IINTERFACE(dp->mReasons));
    values->Set(2, TO_IINTERFACE(dp->mCRLIssuer));
    return NOERROR;
}

AutoPtr<IASN1Sequence> CDistributionPoint::initASN1()
{
    AutoPtr<IASN1Explicit> explicit0;
    CASN1Explicit::New(0, IASN1Type::Probe(CDistributionPointName::ASN1), (IASN1Explicit**)&explicit0);
    AutoPtr<IASN1Implicit> implicit1;
    CASN1Implicit::New(1, IASN1Type::Probe(CReasonFlags::ASN1), (IASN1Implicit**)&implicit1);
    AutoPtr<IASN1Implicit> implicit2;
    CASN1Implicit::New(2, IASN1Type::Probe(CGeneralNames::ASN1), (IASN1Implicit**)&implicit2);

    AutoPtr<ArrayOf<IASN1Type*> > array = ArrayOf<IASN1Type*>::Alloc(3);
    array->Set(0, IASN1Type::Probe(explicit0));
    array->Set(1, IASN1Type::Probe(implicit1));
    array->Set(2, IASN1Type::Probe(implicit2));

    AutoPtr<ASN1Sequence> tmp = new MyASN1Sequence();
    tmp->constructor(array);
    tmp->SetOptional(0);
    tmp->SetOptional(1);
    tmp->SetOptional(2);
    return IASN1Sequence::Probe(tmp);
}

INIT_PROI_9 AutoPtr<IASN1Sequence> CDistributionPoint::ASN1 = initASN1();

CAR_OBJECT_IMPL(CDistributionPoint)

CAR_INTERFACE_IMPL(CDistributionPoint, Object, IDistributionPoint)

ECode CDistributionPoint::DumpValue(
    /* [in] */ IStringBuilder* sb,
    /* [in] */ const String& prefix)
{
    sb->Append(prefix);
    sb->Append(String("Distribution Point: [\n"));
    if (mDistributionPoint != NULL) {
        mDistributionPoint->DumpValue(sb, prefix + String("  "));
    }
    if (mReasons != NULL) {
        mReasons->DumpValue(sb, prefix + String("  "));
    }
    if (mCRLIssuer != NULL) {
        sb->Append(prefix);
        sb->Append(String("  CRL Issuer: [\n"));
        mCRLIssuer->DumpValue(sb, prefix + String("    "));
        sb->Append(prefix);
        sb->Append(String("  ]\n"));
    }
    sb->Append(prefix);
    sb->Append(String("]\n"));
    return NOERROR;
}

ECode CDistributionPoint::constructor(
    /* [in] */ IDistributionPointName* distributionPoint,
    /* [in] */ IReasonFlags* reasons,
    /* [in] */ IGeneralNames* cRLIssuer)
{
    if ((reasons != NULL) && (distributionPoint == NULL) && (cRLIssuer == NULL)) {
        //throw new IllegalArgumentException("DistributionPoint MUST NOT consist of only the reasons field");
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }
    mDistributionPoint = distributionPoint;
    mReasons = reasons;
    mCRLIssuer = cRLIssuer;
    return NOERROR;
}

ECode CDistributionPoint::GetASN1(
    /* [out] */ IASN1Sequence** ppAsn1)
{
    VALIDATE_NOT_NULL(ppAsn1);

    *ppAsn1 = ASN1;
    REFCOUNT_ADD(*ppAsn1);
    return NOERROR;
}

ECode CDistributionPoint::SetASN1(
    /* [in] */ IASN1Sequence* pAsn1)
{
    ASN1 = pAsn1;
    return NOERROR;
}

} // namespace X509
} // namespace Security
} // namespace Harmony
} // namespace Apache
} // namespace Org