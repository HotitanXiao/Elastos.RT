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

#include "elastos/security/spec/CX509EncodedKeySpec.h"

namespace Elastos {
namespace Security {
namespace Spec {

CAR_OBJECT_IMPL(CX509EncodedKeySpec)
CAR_INTERFACE_IMPL(CX509EncodedKeySpec, EncodedKeySpec, IX509EncodedKeySpec)
ECode CX509EncodedKeySpec::GetEncoded(
    /* [out, callee] */ ArrayOf<Byte> **encoded)
{
    return EncodedKeySpec::GetEncoded(encoded);
}

ECode CX509EncodedKeySpec::GetFormat(
    /* [out] */ String *format)
{
    VALIDATE_NOT_NULL(format)
    *format = String("X.509");
    return NOERROR;
}

ECode CX509EncodedKeySpec::constructor(
    /* [in] */ ArrayOf<Byte> *encodedKey)
{
    return EncodedKeySpec::constructor(encodedKey);
}

}
}
}
