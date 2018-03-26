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

#include "elastos/security/cert/CertPathBuilder.h"
#include "elastos/security/CSecurity.h"

using Elastos::Security::ISecurity;
using Elastos::Security::CSecurity;

namespace Elastos {
namespace Security {
namespace Cert {

const String CertPathBuilder::sSERVICE = String("CertPathBuilder");

//apache...todo
// Used to access common engine functionality
//static const Engine ENGINE = new Engine(SERVICE);

// Store default property name
const String CertPathBuilder::sPROPERTY_NAME = String("certpathbuilder.type");

// Default value of CertPathBuilder type. It returns if certpathbuild.type
// property is not defined in java.security file
const String CertPathBuilder::sDEFAULT_PROPERTY = String("PKIX");

CAR_INTERFACE_IMPL(CertPathBuilder, Object, ICertPathBuilder)
ECode CertPathBuilder::GetAlgorithm(
    /* [out] */ String *algorithm)
{
    VALIDATE_NOT_NULL(algorithm)
    *algorithm = mAlgorithm;
    return NOERROR;
}

ECode CertPathBuilder::GetProvider(
    /* [out] */ IProvider **provider)
{
    VALIDATE_NOT_NULL(provider)
    *provider = mProvider;
    REFCOUNT_ADD(*provider)
    return NOERROR;
}

ECode CertPathBuilder::GetInstance(
/* [in] */ const String& algorithm,
/* [out] */ ICertPathBuilder **builder)
{
    VALIDATE_NOT_NULL(builder)
    if (algorithm.IsNull()) {
        return E_NULL_POINTER_EXCEPTION;
    }
    assert(0 && "TODO");
    //APACHE...Todo
/*
    Engine.SpiAndProvider sap = ENGINE.getInstance(algorithm, null);
    return new CertPathBuilder((CertPathBuilderSpi) sap.spi, sap.provider, algorithm);
*/
    return E_NOT_IMPLEMENTED;
}

ECode CertPathBuilder::GetInstance(
    /* [in] */ const String& algorithm,
    /* [in] */ const String& provider,
    /* [out] */ ICertPathBuilder **builder)
{
    VALIDATE_NOT_NULL(builder)
    if (provider.IsNullOrEmpty()) {
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }
    AutoPtr<IProvider> impProvider;
    AutoPtr<ISecurity> security;
    CSecurity::AcquireSingleton((ISecurity**)&security);
    security->GetProvider(provider, (IProvider**)&impProvider);
    if (impProvider == NULL) {
        return E_NO_SUCH_PROVIDER_EXCEPTION;
    }
    return GetInstance(algorithm, impProvider, builder);
}

ECode CertPathBuilder::GetInstance(
    /* [in] */ const String& algorithm,
    /* [in] */ IProvider *provider,
    /* [out] */ ICertPathBuilder **builder)
{
    VALIDATE_NOT_NULL(builder)
    if (!provider) {
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }
    if (algorithm.IsNull()) {
        return E_NULL_POINTER_EXCEPTION;
    }
    //Apache...Todo
    /*
    Object spi = ENGINE.getInstance(algorithm, provider, null);
    return new CertPathBuilder((CertPathBuilderSpi) spi, provider, algorithm);
    */
    return E_NOT_IMPLEMENTED;
}

ECode CertPathBuilder::Build(
    /* [in] */ ICertPathParameters* params,
    /* [out] */ ICertPathBuilderResult** result)
{
    return mSpiImpl->EngineBuild(params, result);
}

ECode CertPathBuilder::GetDefaultType(
    /* [out] */ String *type)
{
    VALIDATE_NOT_NULL(type)
    String defaultType;
    AutoPtr<ISecurity> security;
    CSecurity::AcquireSingleton((ISecurity**)&security);
    security->GetProperty(sPROPERTY_NAME, &defaultType);
    *type = !defaultType.IsNull() ? defaultType : sDEFAULT_PROPERTY;
    return NOERROR;
}

CertPathBuilder::CertPathBuilder(
    /* [in] */ ICertPathBuilderSpi *builderSpi,
    /* [in] */ IProvider *provider,
    /* [in] */ const String& algorithm)
    : mProvider(provider)
    , mSpiImpl(builderSpi)
    , mAlgorithm(algorithm)
{}

}
}
}
