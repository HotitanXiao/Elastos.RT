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

#include "org/conscrypt/OpenSSLContextImpl.h"
#include "org/conscrypt/CClientSessionContext.h"
#include "org/conscrypt/COpenSSLEngineImpl.h"
#include "org/conscrypt/COpenSSLServerSocketFactoryImpl.h"
#include "org/conscrypt/COpenSSLSocketFactoryImpl.h"
#include "org/conscrypt/CServerSessionContext.h"
#include "org/conscrypt/CSSLParametersImpl.h"
#include "elastos/core/AutoLock.h"

namespace Org {
namespace Conscrypt {

CAR_INTERFACE_IMPL(OpenSSLContextImpl, SSLContextSpi, IOpenSSLContextImpl)

AutoPtr<IDefaultSSLContextImpl> OpenSSLContextImpl::DEFAULT_SSL_CONTEXT_IMPL;

ECode OpenSSLContextImpl::constructor()
{
    CClientSessionContext::New((IClientSessionContext**)&clientSessionContext);
    CServerSessionContext::New((IServerSessionContext**)&serverSessionContext);
    return NOERROR;
}

ECode OpenSSLContextImpl::constructor(
    /* [in] */ IDefaultSSLContextImpl* dummy)
{
    AutoLock lock(DEFAULT_SSL_CONTEXT_IMPL);    // synchronized (DefaultSSLContextImpl.class);
    if (DEFAULT_SSL_CONTEXT_IMPL == NULL) {
        CClientSessionContext::New((IClientSessionContext**)&clientSessionContext);
        CServerSessionContext::New((IServerSessionContext**)&serverSessionContext);
        DEFAULT_SSL_CONTEXT_IMPL = IDefaultSSLContextImpl::Probe(this);
    }
    else {
        AutoPtr<ISSLSessionContext> clientCtx;
        ISSLContextSpi::Probe(DEFAULT_SSL_CONTEXT_IMPL)->EngineGetClientSessionContext(
            (ISSLSessionContext**)&clientCtx);
        clientSessionContext = IClientSessionContext::Probe(clientCtx);
        AutoPtr<ISSLSessionContext> serverCtx;
        ISSLContextSpi::Probe(DEFAULT_SSL_CONTEXT_IMPL)->EngineGetServerSessionContext(
            (ISSLSessionContext**)&serverCtx);
        serverSessionContext = IServerSessionContext::Probe(serverCtx);
    }

    AutoPtr<ArrayOf<IKeyManager*> > keyManager;
    DEFAULT_SSL_CONTEXT_IMPL->GetKeyManagers(
            (ArrayOf<IKeyManager*>**)&keyManager);
    AutoPtr<ArrayOf<ITrustManager*> > trustManager;
    DEFAULT_SSL_CONTEXT_IMPL->GetTrustManagers(
            (ArrayOf<ITrustManager*>**)&trustManager);

    CSSLParametersImpl::New(
            keyManager,
            trustManager,
            NULL,
            clientSessionContext,
            serverSessionContext,
            (ISSLParametersImpl**)&sslParameters);
    return NOERROR;
}

ECode OpenSSLContextImpl::EngineInit(
    /* [in] */ ArrayOf<IKeyManager*>* kms,
    /* [in] */ ArrayOf<ITrustManager*>* tms,
    /* [in] */ ISecureRandom* sr)
{
    return CSSLParametersImpl::New(
            kms, tms, sr, clientSessionContext, serverSessionContext,
            (ISSLParametersImpl**)&sslParameters);
    return NOERROR;
}

ECode OpenSSLContextImpl::EngineGetSocketFactory(
    /* [out] */ ISSLSocketFactory** result)
{
    VALIDATE_NOT_NULL(result)
    *result = NULL;
    if (sslParameters == NULL) {
        // throw new IllegalStateException("SSLContext is not initialized.");
        return E_ILLEGAL_STATE_EXCEPTION;
    }
    return COpenSSLSocketFactoryImpl::New(sslParameters, result);
}

ECode OpenSSLContextImpl::EngineGetServerSocketFactory(
    /* [out] */ ISSLServerSocketFactory** result)
{
    VALIDATE_NOT_NULL(result)
    *result = NULL;
    if (sslParameters == NULL) {
        // throw new IllegalStateException("SSLContext is not initialized.");
        return E_ILLEGAL_STATE_EXCEPTION;
    }
    return COpenSSLServerSocketFactoryImpl::New(sslParameters, result);
}

ECode OpenSSLContextImpl::EngineCreateSSLEngine(
    /* [in] */ const String& host,
    /* [in] */ Int32 port,
    /* [out] */ ISSLEngine** result)
{
    VALIDATE_NOT_NULL(result)
    if (sslParameters == NULL) {
        // throw new IllegalStateException("SSLContext is not initialized.");
        return E_ILLEGAL_STATE_EXCEPTION;
    }
    // AutoPtr<ISSLParametersImpl> p = (SSLParametersImpl) sslParameters.clone();
    AutoPtr<ISSLParametersImpl> p = ISSLParametersImpl::Probe(sslParameters);
    p->SetUseClientMode(FALSE);
    COpenSSLEngineImpl::New(host, port, p, result);
    return NOERROR;
}

ECode OpenSSLContextImpl::EngineCreateSSLEngine(
    /* [out] */ ISSLEngine** result)
{
    VALIDATE_NOT_NULL(result)
    if (sslParameters == NULL) {
        // throw new IllegalStateException("SSLContext is not initialized.");
        return E_ILLEGAL_STATE_EXCEPTION;
    }
    // AutoPtr<ISSLParametersImpl> p = (SSLParametersImpl) sslParameters.clone();
    AutoPtr<ISSLParametersImpl> p = ISSLParametersImpl::Probe(sslParameters);
    p->SetUseClientMode(FALSE);
    COpenSSLEngineImpl::New(p, result);
    return NOERROR;
}

ECode OpenSSLContextImpl::EngineGetServerSessionContext(
    /* [out] */ ISSLSessionContext** result)
{
    VALIDATE_NOT_NULL(result)
    *result = ISSLSessionContext::Probe(serverSessionContext);
    REFCOUNT_ADD(*result)
    return NOERROR;
}

ECode OpenSSLContextImpl::EngineGetClientSessionContext(
    /* [out] */ ISSLSessionContext** result)
{
    VALIDATE_NOT_NULL(result)
    *result = ISSLSessionContext::Probe(clientSessionContext);
    REFCOUNT_ADD(*result)
    return NOERROR;
}

} // namespace Conscrypt
} // namespace Org
