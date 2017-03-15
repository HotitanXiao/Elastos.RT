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

#ifndef __ORG_APACHE_HARMONY_SECURITY_X509_CX509PUBLICKEY_H__
#define __ORG_APACHE_HARMONY_SECURITY_X509_CX509PUBLICKEY_H__

#include "_Org_Apache_Harmony_Security_X509_CX509PublicKey.h"
#include "Elastos.CoreLibrary.IO.h"
#include <elastos/core/Object.h>

using Elastos::Core::Object;
using Elastos::IO::ISerializable;
using Elastos::Security::IKey;
using Elastos::Security::IPublicKey;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace X509 {

CarClass(CX509PublicKey)
    , public Object
    , public IX509PublicKey
    , public IPublicKey
    , public IKey
    , public ISerializable
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    CARAPI GetAlgorithm(
        /* [out] */ String* pAlgorithm);

    CARAPI GetFormat(
        /* [out] */ String* pFormat);

    CARAPI GetEncoded(
        /* [out, callee] */ ArrayOf<Byte>** ppEncoded);

    CARAPI ToString(
        /* [out] */ String* pStr);

    CARAPI constructor(
        /* [in] */ const String& algorithm,
        /* [in] */ ArrayOf<Byte>* pEncoded,
        /* [in] */ ArrayOf<Byte>* pKeyBytes);

private:
    String mAlgorithm;
    AutoPtr<ArrayOf<Byte> > mEncoded;
    AutoPtr<ArrayOf<Byte> > mKeyBytes;
};

} //namespace X509
} //namespace Security
} //namespace Harmony
} //namespace Apache
} //namespace Org

#endif // __ORG_APACHE_HARMONY_SECURITY_X509_CX509PUBLICKEY_H__
