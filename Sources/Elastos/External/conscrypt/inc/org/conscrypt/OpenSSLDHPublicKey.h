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

#ifndef __ORG_CONSCRYPT_OPENSSLDHPUBLICKEY_H__
#define __ORG_CONSCRYPT_OPENSSLDHPUBLICKEY_H__

#include <elastos/coredef.h>
#include <Elastos.CoreLibrary.Extensions.h>
#include <Elastos.CoreLibrary.IO.h>
#include <Elastos.CoreLibrary.Security.h>
#include <elastos/core/Object.h>
#include "_Org.Conscrypt.h"
#include "org/conscrypt/OpenSSLKey.h"

using Elastos::IO::IObjectInputStream;
using Elastos::IO::IObjectOutputStream;
using Elastos::Math::IBigInteger;
using Elastos::Security::IPublicKey;
using Elastos::Security::IKey;
using Elastosx::Crypto::Interfaces::IDHKey;
using Elastosx::Crypto::Interfaces::IDHPublicKey;
using Elastosx::Crypto::Spec::IDHParameterSpec;
using Elastosx::Crypto::Spec::IDHPublicKeySpec;

namespace Org {
namespace Conscrypt {

class OpenSSLDHPublicKey
    : public IOpenSSLDHPublicKey
    , public IDHPublicKey
    , public IDHKey
    , public IKey
    , public IPublicKey
    , public IOpenSSLKeyHolder
    , public Object
{
public:
    CAR_INTERFACE_DECL()

    OpenSSLDHPublicKey();

    CARAPI constructor(
        /* [in] */ IOpenSSLKey* key);

    CARAPI constructor(
        /* [in] */ IDHPublicKeySpec* dhKeySpec);

    // @Override
    CARAPI GetOpenSSLKey(
        /* [out] */ IOpenSSLKey** result);

    static CARAPI GetInstance(
        /* [in] */ IDHPublicKey* dhPublicKey,
        /* [out] */ IOpenSSLKey** result);

    // @Override
    CARAPI GetParams(
        /* [out] */ IDHParameterSpec** result);

    // @Override
    CARAPI GetAlgorithm(
        /* [out] */ String* result);

    // @Override
    CARAPI GetFormat(
        /* [out] */ String* result);

    // @Override
    CARAPI GetEncoded(
        /* [out, callee] */ ArrayOf<Byte>** result);

    // @Override
    CARAPI GetY(
        /* [out] */ IBigInteger** result);

    // @Override
    CARAPI GetHashCode(
        /* [out] */ Int32* result);

    // @Override
    CARAPI Equals(
        /* [in] */ IInterface* obj,
        /* [out] */ Boolean* result);

    // @Override
    CARAPI ToString(
        /* [out] */ String* result);

private:
    CARAPI_(void) EnsureReadParams();

    CARAPI_(void) ReadObject(
        /* [in] */ IObjectInputStream* stream);

    CARAPI_(void) WriteObject(
        /* [in] */ IObjectOutputStream* stream);

private:
    static const Int64 serialVersionUID = 6123717708079837723L;

    /*transient*/ AutoPtr<OpenSSLKey> mKey;

    /** base prime */
    /*transient*/ AutoPtr<ArrayOf<Byte> > mP;

    /** generator */
    /*transient*/ AutoPtr<ArrayOf<Byte> > mG;

    /** public key */
    /*transient*/ AutoPtr<ArrayOf<Byte> > mY;

    /*transient*/ Object mParamsLock; // = new Object();

    /*transient*/ Boolean mReadParams;
};

} // namespace Conscrypt
} // namespace Org

#endif //__ORG_CONSCRYPT_OPENSSLDHPUBLICKEY_H__
