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

#include "CStringEncoderHelper.h"
#include "StringEncoder.h"

namespace Elastos {
namespace Sql {
namespace SQLite {
CAR_INTERFACE_IMPL(CStringEncoderHelper, Object, IStringEncoderHelper)

CAR_SINGLETON_IMPL(CStringEncoderHelper)

ECode CStringEncoderHelper::Encode(
    /* [in] */ ArrayOf<Byte> * a,
    /* [out] */ String * str)
{
    VALIDATE_NOT_NULL(str);
    *str = StringEncoder::Encode(a);
    return NOERROR;
}

ECode CStringEncoderHelper::Decode(
    /* [in] */ const String& s,
    /* [out, callee] */ ArrayOf<Byte> ** outarray)
{
    VALIDATE_NOT_NULL(outarray);
    AutoPtr<ArrayOf<Byte> > result = StringEncoder::Decode(s);
    *outarray = result;
    REFCOUNT_ADD(*outarray);
    return NOERROR;
}

ECode CStringEncoderHelper::EncodeX(
    /* [in] */ ArrayOf<Byte> * a,
    /* [out] */ String * str)
{
    VALIDATE_NOT_NULL(str);
    *str = StringEncoder::EncodeX(a);
    return NOERROR;
}

} // namespace SQLite
} // namespace Sql
} // namespace Elastos
