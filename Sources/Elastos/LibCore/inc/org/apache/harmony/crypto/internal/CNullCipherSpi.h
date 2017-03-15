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

#ifndef __ORG_APACHE_HARMONY_CRYPTO_INTERNAL_CNULLCIPHERSPI_H__
#define __ORG_APACHE_HARMONY_CRYPTO_INTERNAL_CNULLCIPHERSPI_H__

#include "_Org_Apache_Harmony_Crypto_Internal_CNullCipherSpi.h"
#include "elastosx/crypto/CipherSpi.h"

using Elastos::Security::IAlgorithmParameters;
using Elastos::Security::IKey;
using Elastos::Security::ISecureRandom;
using Elastos::Security::Spec::IAlgorithmParameterSpec;
using Elastosx::Crypto::CipherSpi;
using Elastosx::Crypto::INullCipherSpi;
using Elastos::IO::IByteBuffer;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Crypto {
namespace Internal {

CarClass(CNullCipherSpi)
    , public CipherSpi
    , public INullCipherSpi
{
public:
    CAR_OBJECT_DECL();
    CAR_INTERFACE_DECL();

    CARAPI EngineSetMode(
        /* [in] */ const String& mode);

    CARAPI EngineSetPadding(
        /* [in] */ const String& adding);

    CARAPI EngineGetBlockSize(
        /* [out] */ Int32* size);

    CARAPI EngineGetOutputSize(
        /* [in] */ Int32 inputLen,
        /* [out] */ Int32* size);

    CARAPI EngineGetIV(
        /* [out, callee] */ ArrayOf<Byte>** iv);

    CARAPI EngineGetParameters(
        /* [out] */ IAlgorithmParameters **param);

    CARAPI EngineInit(
        /* [in] */ Int32 opmode,
        /* [in] */ IKey* key,
        /* [in] */ ISecureRandom* random);

    CARAPI EngineInit(
        /* [in] */ Int32 opmode,
        /* [in] */ IKey* key,
        /* [in] */ IAlgorithmParameterSpec* params,
        /* [in] */ ISecureRandom* random);

    CARAPI EngineInit(
        /* [in] */ Int32 opmode,
        /* [in] */ IKey* key,
        /* [in] */ IAlgorithmParameters* params,
        /* [in] */ ISecureRandom* random);

    CARAPI EngineUpdate(
        /* [in] */ ArrayOf<Byte>* input,
        /* [in] */ Int32 inputOffset,
        /* [in] */ Int32 inputLen,
        /* [out, callee] */ ArrayOf<Byte>** op);

    CARAPI EngineUpdate(
        /* [in] */ ArrayOf<Byte>* ip,
        /* [in] */ Int32 inputOffset,
        /* [in] */ Int32 inputLen,
        /* [out] */ ArrayOf<Byte>* op,
        /* [in] */ Int32 outputOffset,
        /* [out] */ Int32* number);

    CARAPI EngineUpdate(
        /* [in] */ IByteBuffer* ip,
        /* [in] */ IByteBuffer* op,
        /* [out] */ Int32* number);

    CARAPI EngineDoFinal(
        /* [in] */ ArrayOf<Byte>* ip,
        /* [in] */ Int32 inputOffset,
        /* [in] */ Int32 inputLen,
        /* [out, callee] */ ArrayOf<Byte>** bytes);

    CARAPI EngineDoFinal(
        /* [in] */ ArrayOf<Byte>* ip,
        /* [in] */ Int32 inputOffset,
        /* [in] */ Int32 inputLen,
        /* [out] */ ArrayOf<Byte>* op,
        /* [in] */ Int32 outputOffset,
        /* [out] */ Int32* number);

    CARAPI EngineDoFinal(
        /* [in] */ IByteBuffer* ip,
        /* [in] */ IByteBuffer* op,
        /* [out] */ Int32* number);

    CARAPI EngineWrap(
        /* [in] */ IKey* keyToWrap,
        /* [out, callee] */ ArrayOf<Byte>** wrappedKey);

    CARAPI EngineUnwrap(
        /* [in] */ ArrayOf<Byte>* wrappedKey,
        /* [in] */ const String& wrappedKeyAlgorithm,
        /* [in] */ Int32 wrappedKeyType,
        /* [out] */ IKey** key);

    CARAPI EngineGetKeySize(
        /* [in] */ IKey* key,
        /* [out] */ Int32* size);

private:
    // TODO: Add your private member variables here.
};

} // namespace Internal
} // namespace Crypto
} // namespace Harmony
} // namespace Apache
} // namespace Org

#endif // __ORG_APACHE_HARMONY_CRYPTO_INTERNAL_CNULLCIPHERSPI_H__
