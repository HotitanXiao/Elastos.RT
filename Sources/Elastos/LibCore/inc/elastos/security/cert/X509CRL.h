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

#ifndef __ELASTOS_SECURITY_CERT_X509CRL_H__
#define __ELASTOS_SECURITY_CERT_X509CRL_H__

#include "elastos/security/cert/CRL.h"

using Elastos::Security::IPublicKey;
using Elastosx::Security::Auth::X500::IX500Principal;
using Elastos::Utility::IDate;
using Elastos::Math::IBigInteger;
using Elastos::Utility::ISet;

namespace Elastos {
namespace Security {
namespace Cert {

extern "C" const InterfaceID EIID_X509CRL;

class X509CRL
    : public CRL
    , public IX509Extension
{
public:
    CAR_INTERFACE_DECL()

    virtual CARAPI Equals(
        /* [in] */ IInterface *other,
        /* [out] */ Boolean *result);

    virtual CARAPI GetHashCode(
        /* [out] */ Int32 *hashCode);

    virtual CARAPI GetEncoded(
        /* [out, callee] */ ArrayOf<Byte> **encoded) = 0;

    virtual CARAPI Verify(
        /* [in] */ IPublicKey *key) = 0;

    virtual CARAPI VerifyEx(
        /* [in] */ IPublicKey *key,
        /* [in] */ const String& sigProvider) = 0;

    virtual CARAPI GetVersion(
        /* [out] */ Int32 *vs) = 0;

    virtual CARAPI GetIssuerDN(
        /* [out] */ IPrincipal **issuer) = 0;

    virtual CARAPI GetIssuerX500Principal(
        /* [out] */ IX500Principal **issuer);

    virtual CARAPI GetThisUpdate(
        /* [out] */ IDate **thisUpdate) = 0;

    virtual CARAPI GetNextUpdate(
        /* [out] */ IDate **nextUpdate) = 0;

    virtual CARAPI GetRevokedCertificate(
        /* [in] */ IBigInteger *serialNumber,
        /* [out] */ IX509CRLEntry **crlEntry) = 0;

    virtual CARAPI GetRevokedCertificateEx(
        /* [in] */ IX509Certificate *certificate,
        /* [out] */ IX509CRLEntry **crlEntry);

    virtual CARAPI GetRevokedCertificates(
        /* [out] */ ISet **ctrlEntrys) = 0;

    virtual CARAPI GetCriticalExtensionOIDs(
        /* [out] */ ISet **oids) = 0;

    virtual CARAPI GetExtensionValue(
        /* [in] */ const String& oid,
        /* [out, callee] */ ArrayOf<Byte> **extensionValue) = 0;

    virtual CARAPI GetNonCriticalExtensionOIDs(
        /* [out] */ ISet **oids) = 0;

    virtual CARAPI HasUnsupportedCriticalExtension(
        /* [out] */ Boolean *result) = 0;
protected:
    X509CRL();
};

}
}
}

#endif // __ELASTOS_SECURITY_CERT_X509CRL_H__
