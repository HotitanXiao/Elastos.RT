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

#include "org/conscrypt/OpenSSLDHKeyPairGenerator.h"
#include "org/conscrypt/NativeCrypto.h"
#include "org/conscrypt/OpenSSLDHPrivateKey.h"
#include "org/conscrypt/OpenSSLDHPublicKey.h"
#include "org/conscrypt/OpenSSLKey.h"

using Elastos::Core::INumber;
using Elastos::Math::CBigIntegerHelper;
using Elastos::Math::IBigIntegerHelper;
using Elastos::Security::CKeyPair;

namespace Org {
namespace Conscrypt {

static AutoPtr<IBigInteger> InitDEFAULT_GENERATOR()
{
    AutoPtr<IBigIntegerHelper> helper;
    CBigIntegerHelper::AcquireSingleton((IBigIntegerHelper**)&helper);
    AutoPtr<IBigInteger> ret;
    helper->ValueOf(2, (IBigInteger**)&ret);
    return ret;
}

AutoPtr<IBigInteger> OpenSSLDHKeyPairGenerator::DEFAULT_GENERATOR = InitDEFAULT_GENERATOR();

CAR_INTERFACE_IMPL(OpenSSLDHKeyPairGenerator, KeyPairGeneratorSpi,
        IOpenSSLDHKeyPairGenerator)

OpenSSLDHKeyPairGenerator::OpenSSLDHKeyPairGenerator()
    : mPrimeBits(1024)
{
    mGenerator = DEFAULT_GENERATOR;
}

ECode OpenSSLDHKeyPairGenerator::constructor()
{
    return NOERROR;
}

ECode OpenSSLDHKeyPairGenerator::GenerateKeyPair(
    /* [out] */  IKeyPair** result)
{
    VALIDATE_NOT_NULL(result)
    AutoPtr<OpenSSLKey> key;
    if (mPrime != NULL) {
        AutoPtr<ArrayOf<Byte> > pArray;
        mPrime->ToByteArray((ArrayOf<Byte>**)&pArray);
        AutoPtr<ArrayOf<Byte> > gArray;
        mGenerator->ToByteArray((ArrayOf<Byte>**)&gArray);
        Int64 val;
        NativeCrypto::EVP_PKEY_new_DH(pArray, gArray, NULL, NULL, &val);
        key = new OpenSSLKey();
        key->constructor(val);
    }
    else {
        Int64 gVal;
        INumber::Probe(mGenerator)->Int64Value(&gVal);
        Int64 val;
        NativeCrypto::DH_generate_parameters_ex(mPrimeBits, gVal, &val);
        key = new OpenSSLKey();
        key->constructor(val);
    }

    Int64 ctx;
    key->GetPkeyContext(&ctx);
    NativeCrypto::DH_generate_key(ctx);

    AutoPtr<OpenSSLDHPrivateKey> privKey = new OpenSSLDHPrivateKey();
    privKey->constructor(IOpenSSLKey::Probe(key));
    AutoPtr<OpenSSLDHPublicKey> pubKey = new OpenSSLDHPublicKey();
    pubKey->constructor(IOpenSSLKey::Probe(key));

    return CKeyPair::New(IPublicKey::Probe(pubKey), IPrivateKey::Probe(privKey), result);
}

ECode OpenSSLDHKeyPairGenerator::Initialize(
    /* [in] */ Int32 keysize,
    /* [in] */ ISecureRandom* random)
{
    mPrime = NULL;
    mPrimeBits = keysize;
    mGenerator = DEFAULT_GENERATOR;
    return NOERROR;
}

ECode OpenSSLDHKeyPairGenerator::Initialize(
    /* [in] */ IAlgorithmParameterSpec* params,
    /* [in] */ ISecureRandom* random)
{
    mPrime = NULL;
    mPrimeBits = 1024;
    mGenerator = DEFAULT_GENERATOR;

    if (IDHParameterSpec::Probe(params) != NULL) {
        AutoPtr<IDHParameterSpec> dhParams = IDHParameterSpec::Probe(params);

        dhParams->GetP((IBigInteger**)&mPrime);
        AutoPtr<IBigInteger> gen;
        dhParams->GetG((IBigInteger**)&gen);
        if (gen != NULL) {
            mGenerator = gen;
        }
    }
    else if (params != NULL) {
        // throw new InvalidAlgorithmParameterException("Params must be DHParameterSpec");
        return E_INVALID_ALGORITHM_PARAMETER_EXCEPTION;
    }
    return NOERROR;
}

} // namespace Conscrypt
} // namespace Org
