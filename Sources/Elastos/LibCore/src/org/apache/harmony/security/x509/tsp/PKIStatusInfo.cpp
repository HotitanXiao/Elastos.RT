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

#include "org/apache/harmony/security/x509/tsp/PKIStatusInfo.h"
#include "org/apache/harmony/security/x509/tsp/PKIStatus.h"
#include "org/apache/harmony/security/x509/tsp/PKIFailureInfo.h"
#include "org/apache/harmony/security/asn1/CASN1Integer.h"
#include "org/apache/harmony/security/asn1/CBitString.h"
#include "org/apache/harmony/security/asn1/ASN1SequenceOf.h"
#include "org/apache/harmony/security/asn1/ASN1StringType.h"
#include "org/apache/harmony/security/asn1/ASN1BitString.h"
#include <elastos/core/StringBuilder.h>
#include "elastos/math/CBigIntegerHelper.h"
#include <elastos/core/CoreUtils.h>
#include "core/CArrayOf.h"
#include "core/CByte.h"

using Org::Apache::Harmony::Security::Asn1::IBitString;
using Org::Apache::Harmony::Security::Asn1::IASN1Type;
using Org::Apache::Harmony::Security::Asn1::CASN1Integer;
using Org::Apache::Harmony::Security::Asn1::CBitString;
using Org::Apache::Harmony::Security::Asn1::ASN1SequenceOf;
using Org::Apache::Harmony::Security::Asn1::IASN1Integer;
using Org::Apache::Harmony::Security::Asn1::ASN1StringType;
using Org::Apache::Harmony::Security::Asn1::ASN1BitString;
using Elastos::Core::IArrayOf;
using Elastos::Core::CArrayOf;
using Elastos::Core::IByte;
using Elastos::Core::CByte;
using Elastos::Core::EIID_IByte;
using Elastos::Core::StringBuilder;
using Elastos::Core::CoreUtils;
using Elastos::Math::IBigInteger;
using Elastos::Math::IBigIntegerHelper;
using Elastos::Math::CBigIntegerHelper;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace X509 {
namespace Tsp {

ECode PKIStatusInfo::MyASN1Sequence::GetDecodedObject(
    /* [in] */ IBerInputStream* bis,
    /* [out] */ IInterface** object)
{
    VALIDATE_NOT_NULL(object);

    AutoPtr<IInterface> con;
    bis->GetContent((IInterface**)&con);
    AutoPtr<IArrayOf> values = IArrayOf::Probe(con);

    Int32 failInfoValue = -1;
    AutoPtr<IInterface> obj;
    values->Get(2, (IInterface**)&obj);
    if (obj != NULL) {
        AutoPtr<ArrayOf<Boolean> > failInfoBoolArray;
        IBitString::Probe(obj)->ToBooleanArray((ArrayOf<Boolean>**)&failInfoBoolArray);
        for (Int32 i = 0; i < failInfoBoolArray->GetLength(); i++) {
            if ((*failInfoBoolArray)[i]) {
                failInfoValue = i;
                break;
            }
        }
    }

    AutoPtr<IInterface> obj2;
    values->Get(0, (IInterface**)&obj2);
    Int32 value;
    CASN1Integer::ToIntValue(obj2, &value);
    AutoPtr<IPKIStatus> status;
    PKIStatus::GetInstance(value, (IPKIStatus**)&status);

    AutoPtr<IInterface> obj3;
    values->Get(1, (IInterface**)&obj3);

    AutoPtr<IPKIFailureInfo> info;
    PKIFailureInfo::GetInstance(failInfoValue, (IPKIFailureInfo**)&info);
    AutoPtr<PKIStatusInfo> tmp = new PKIStatusInfo();
    tmp->constructor(status, IList::Probe(obj3), info);
    *object = TO_IINTERFACE(tmp);
    REFCOUNT_ADD(*object);
    return NOERROR;
}

ECode PKIStatusInfo::MyASN1Sequence::GetValues(
    /* [in] */ IInterface* object,
    /* [in] */ ArrayOf<IInterface*>* values)
{
    AutoPtr<PKIStatusInfo> psi = (PKIStatusInfo*)IPKIStatusInfo::Probe(object);
    Int32 status;
    psi->mStatus->GetStatus(&status);
    AutoPtr<IBigIntegerHelper> helper;
    CBigIntegerHelper::AcquireSingleton((IBigIntegerHelper**)&helper);
    AutoPtr<IBigInteger> b;
    helper->ValueOf(status, (IBigInteger**)&b);
    AutoPtr<ArrayOf<Byte> > bytes;
    b->ToByteArray((ArrayOf<Byte>**)&bytes);
    AutoPtr<IArrayOf> array = CoreUtils::ConvertByteArray(bytes);
    values->Set(0, TO_IINTERFACE(array));

    values->Set(1, TO_IINTERFACE(psi->mStatusString));
    if (psi->mFailInfo != NULL) {
        // set the needed bit in the bit string
        Int32 mValue;
        PKIFailureInfo::GetMaxValue(&mValue);
        AutoPtr<ArrayOf<Boolean> > failInfoBoolArray = ArrayOf<Boolean>::Alloc(mValue);
        Int32 value;
        psi->mFailInfo->GetValue(&value);
        (*failInfoBoolArray)[value] = TRUE;
        AutoPtr<IBitString> bs;
        CBitString::New(failInfoBoolArray, (IBitString**)&bs);
        values->Set(2, TO_IINTERFACE(bs));
    }
    else {
        values->Set(2, NULL);
    }
    return NOERROR;
}

AutoPtr<IASN1Sequence> PKIStatusInfo::initASN1()
{
    AutoPtr<IASN1Integer> integer;
    CASN1Integer::GetInstance((IASN1Integer**)&integer);

    AutoPtr<ASN1SequenceOf> so = new ASN1SequenceOf();
    so->constructor(IASN1Type::Probe(ASN1StringType::UTF8STRING));

    AutoPtr<IASN1Type> instance;
    ASN1BitString::GetInstance((IASN1Type**)&instance);

    AutoPtr<ArrayOf<IASN1Type*> > array = ArrayOf<IASN1Type*>::Alloc(3);
    array->Set(0, IASN1Type::Probe(integer));
    array->Set(1, IASN1Type::Probe(so));
    array->Set(2, instance);

    AutoPtr<ASN1Sequence> tmp = new MyASN1Sequence();
    tmp->constructor(array);
    tmp->SetOptional(1);
    tmp->SetOptional(2);
    return IASN1Sequence::Probe(tmp);
}

AutoPtr<IASN1Sequence> PKIStatusInfo::ASN1 = initASN1();

CAR_INTERFACE_IMPL(PKIStatusInfo, Object, IPKIStatusInfo)

ECode PKIStatusInfo::ToString(
    /* [out] */ String* pStr)
{
    VALIDATE_NOT_NULL(pStr);

    StringBuilder res;
    res += "-- PKIStatusInfo:";
    res += "\nPKIStatus : ";
    res += mStatus;
    res += "\nstatusString:  ";
    res += TO_CSTR(mStatusString);
    res += "\nfailInfo:  ";
    res += mFailInfo;
    res += "\n-- PKIStatusInfo End\n";
    return res.ToString(pStr);
}

ECode PKIStatusInfo::GetFailInfo(
    /* [out] */ IPKIFailureInfo** pFailInfo)
{
    VALIDATE_NOT_NULL(pFailInfo);

    *pFailInfo = mFailInfo;
    REFCOUNT_ADD(*pFailInfo);
    return NOERROR;
}

ECode PKIStatusInfo::GetStatus(
    /* [out] */ IPKIStatus** pStatus)
{
    VALIDATE_NOT_NULL(pStatus);

    *pStatus = mStatus;
    REFCOUNT_ADD(*pStatus);
    return NOERROR;
}

ECode PKIStatusInfo::GetStatusString(
    /* [out] */ IList** ppList)
{
    VALIDATE_NOT_NULL(ppList);

    *ppList = mStatusString;
    REFCOUNT_ADD(*ppList);
    return NOERROR;
}

ECode PKIStatusInfo::constructor(
    /* [in] */ IPKIStatus* pkiStatus,
    /* [in] */ IList* pStatusString,
    /* [in] */ IPKIFailureInfo* failInfo)
{
    mStatus = pkiStatus;
    mStatusString = pStatusString;
    mFailInfo = failInfo;
    return NOERROR;
}

ECode PKIStatusInfo::GetASN1(
    /* [out] */ IASN1Sequence** ppAsn1)
{
    VALIDATE_NOT_NULL(ppAsn1);

    *ppAsn1 = ASN1;
    REFCOUNT_ADD(*ppAsn1);
    return NOERROR;
}

ECode PKIStatusInfo::SetASN1(
    /* [in] */ IASN1Sequence* pAsn1)
{
    ASN1 = pAsn1;
    return NOERROR;
}

} // namespace Tsp
} // namespace X509
} // namespace Security
} // namespace Harmony
} // namespace Apache
} // namespace Org