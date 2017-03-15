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

#include "ASN1OctetString.h"
#include "CASN1OctetString.h"
#include "core/CArrayOf.h"
#include "core/CByte.h"
#include "utility/Arrays.h"

using Elastos::Core::IArrayOf;
using Elastos::Core::CArrayOf;
using Elastos::Core::IByte;
using Elastos::Core::EIID_IByte;
using Elastos::Core::CByte;
using Elastos::Utility::Arrays;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace Asn1 {

INIT_PROI_3 const AutoPtr<IASN1OctetString> ASN1OctetString::ASN1 = InitASN1();

CAR_INTERFACE_IMPL(ASN1OctetString, ASN1StringType, IASN1OctetString)

AutoPtr<IASN1OctetString> ASN1OctetString::InitASN1()
{
    AutoPtr<IASN1OctetString> asn1Obj;
    CASN1OctetString::New((IASN1OctetString**)&asn1Obj);
    return asn1Obj;
}

ECode ASN1OctetString::constructor()
{
    return ASN1StringType::constructor(IASN1Constants::TAG_OCTETSTRING);
}

ECode ASN1OctetString::GetInstance(
    /* [out] */ IASN1OctetString** instance)
{
    VALIDATE_NOT_NULL(instance)
    *instance = ASN1;
    REFCOUNT_ADD(*instance)
    return NOERROR;
}

ECode ASN1OctetString::Decode(
    /* [in] */ IBerInputStream* bis,
    /* [out] */ IInterface** object)
{
    VALIDATE_NOT_NULL(object);
    *object = NULL;
    FAIL_RETURN(bis->ReadOctetString());

    Boolean isVerify;
    if (bis->GetVerify(&isVerify), isVerify) {
        return NOERROR;
    }
    return GetDecodedObject(bis, object);
}

ECode ASN1OctetString::GetDecodedObject(
    /* [in] */ IBerInputStream* bis,
    /* [out] */ IInterface** object)
{
    AutoPtr< ArrayOf<Byte> > buffer;
    bis->GetBuffer((ArrayOf<Byte>**)&buffer);
    Int32 offset;
    bis->GetContentOffset(&offset);
    Int32 length;
    bis->GetLength(&length);
    AutoPtr< ArrayOf<Byte> > result;
    Arrays::CopyOfRange(buffer, offset, offset + length, (ArrayOf<Byte>**)&result);
    Int32 size = result->GetLength();
    AutoPtr<IArrayOf> arrays;
    CArrayOf::New(EIID_IByte, size, (IArrayOf**)&arrays);
    for (Int32 i = 0; i < size; i++) {
        AutoPtr<IByte> byteObj;
        CByte::New((*result)[i], (IByte**)&byteObj);
        arrays->Set(i, byteObj);
    }
    *object = arrays;
    REFCOUNT_ADD(*object);
    return NOERROR;
}

ECode ASN1OctetString::EncodeContent(
    /* [in] */ IBerOutputStream* bos)
{
    return bos->EncodeOctetString();
}

ECode ASN1OctetString::SetEncodingContent(
    /* [in] */ IBerOutputStream* bos)
{
    AutoPtr<IInterface> content;
    bos->GetContent((IInterface**)&content);
    Int32 length;
    IArrayOf::Probe(content)->GetLength(&length);
    return bos->SetLength(length);
}

} // namespace Asn1
} // namespace Security
} // namespace Harmony
} // namespace Apache
} // namespace Org
