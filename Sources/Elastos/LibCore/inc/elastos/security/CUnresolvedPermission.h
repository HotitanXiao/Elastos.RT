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

#ifndef __ELASTOS_SECURITY_CUNRESOLVEDPERMISSION_H__
#define __ELASTOS_SECURITY_CUNRESOLVEDPERMISSION_H__

#include "_Elastos_Security_CUnresolvedPermission.h"
#include "elastos/security/Permission.h"

namespace Elastos {
namespace Security {

/**
 * Legacy security code; do not use.
 */
CarClass(CUnresolvedPermission)
    , public Permission
    , public IUnresolvedPermission
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    CARAPI constructor(
        /* [in] */ const String& type,
        /* [in] */ const String& name,
        /* [in] */ const String& actions,
        /* [in] */ ArrayOf<Elastos::Security::Cert::ICertificate*>* certs);

    CARAPI GetUnresolvedName(
        /* [out] */ String* result);

    CARAPI GetUnresolvedActions(
        /* [out] */ String* result);

    CARAPI GetUnresolvedType(
        /* [out] */ String* result);

    CARAPI GetUnresolvedCerts(
        /* [out] */ ArrayOf<Elastos::Security::Cert::ICertificate*>** result);

    // @Override
    CARAPI GetActions(
        /* [out] */ String* result);

    // @Override
    CARAPI Implies(
        /* [in] */ IPermission* permission,
        /* [out] */ Boolean* result);
};

}
}

#endif // __ELASTOS_SECURITY_CUNRESOLVEDPERMISSION_H__
