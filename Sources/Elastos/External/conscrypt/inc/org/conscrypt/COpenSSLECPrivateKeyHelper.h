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

#ifndef __ORG_CONSCRYPT_COPENSSLECPRIVATEKEYHELPER_H__
#define __ORG_CONSCRYPT_COPENSSLECPRIVATEKEYHELPER_H__

#include "_Org_Conscrypt_COpenSSLECPrivateKeyHelper.h"
#include "elastos/core/Singleton.h"

using Elastos::Security::Interfaces::IECPrivateKey;

namespace Org {
namespace Conscrypt {

CarClass(COpenSSLECPrivateKeyHelper)
    , public Singleton
    , public IOpenSSLECPrivateKeyHelper
{
public:
    CAR_SINGLETON_DECL()

    CAR_INTERFACE_DECL()

    CARAPI WrapPlatformKey(
        /* [in] */ IECPrivateKey* ecPrivateKey,
        /* [out] */ IOpenSSLKey** result);

    CARAPI GetInstance(
        /* [in] */ IECPrivateKey* ecPrivateKey,
        /* [out] */ IOpenSSLKey** result);
};

} // namespace Conscrypt
} // namespace Org

#endif //__ORG_CONSCRYPT_COPENSSLECPRIVATEKEYHELPER_H__
