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

#ifndef __ELASTOS_SECURITY_CERT_CERTSTORE_H__
#define __ELASTOS_SECURITY_CERT_CERTSTORE_H__

#include "Elastos.CoreLibrary.Security.h"
#include "elastos/core/Object.h"

using Elastos::Core::Object;
using Elastos::Security::IProvider;
using Elastos::Utility::ICollection;

namespace Elastos {
namespace Security {
namespace Cert {

class CertStore
    : public Object
    , public ICertStore
{
public:
    CAR_INTERFACE_DECL()

    static CARAPI GetInstance(
        /* [in] */ const String& type,
        /* [in] */ ICertStoreParameters *params,
        /* [out] */ ICertStore **certStore);

    static CARAPI GetInstance(
        /* [in] */ const String& type,
        /* [in] */ ICertStoreParameters *params,
        /* [in] */ const String& provider,
        /* [out] */ ICertStore **certStore);

    static CARAPI GetInstance(
        /* [in] */ const String& type,
        /* [in] */ ICertStoreParameters *params,
        /* [in] */ IProvider *provider,
        /* [out] */ ICertStore **certStore);

    static CARAPI GetDefaultType(
        /* [out] */ String *type);

    CARAPI GetType(
        /* [out] */ String *type);

    CARAPI GetProvider(
        /* [out] */ IProvider **provider);

    CARAPI GetCertStoreParameters(
        /* [out] */ ICertStoreParameters **parameters);

    CARAPI GetCertificates(
        /* [in] */ ICertSelector *selector,
        /* [out] */ ICollection **certs);

    CARAPI GetCRLs(
        /* [in] */ ICRLSelector *selector,
        /* [out] */ ICollection **crls);

protected:
    /**
     * Creates a new {@code CertStore} instance.
     *
     * @param storeSpi
     *            the implementation delegate.
     * @param provider
     *            the security provider.
     * @param type
     *            the certificate store type.
     * @param params
     *            the certificate store parameters (may be {@code null}.
     */
    CertStore(
        /* [in] */ ICertStoreSpi* storeSpi,
        /* [in] */ IProvider* provider,
        /* [in] */ const String& type,
        /* [in] */ ICertStoreParameters* params);

private:
    // Store spi implementation service name
    static const String SERVICE;

    //Apache...Todo
    // Used to access common engine functionality
    //static const Engine ENGINE = new Engine(SERVICE);

    // Store default property name
    static const String PROPERTY_NAME;

    // Default value of CertStore type. It returns if certpathbuild.type
    // property is not defined in java.security file
    static const String DEFAULT_PROPERTY;

    // Store used provider
    const AutoPtr<IProvider> mProvider;

    // Store CertStoreSpi implementation
    const AutoPtr<ICertStoreSpi> mSpiImpl;

    // Store used type
    const String mType;

    // Store used parameters
    const AutoPtr<ICertStoreParameters> mCertStoreParams;
};

}
}
}

#endif // __ELASTOS_SECURITY_CERT_CERTSTORE_H__
