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

#include "elastos/net/CResponseCacheHelper.h"
#include "elastos/net/ResponseCache.h"

namespace Elastos {
namespace Net {

CAR_INTERFACE_IMPL(CResponseCacheHelper, Singleton, IResponseCacheHelper)

CAR_SINGLETON_IMPL(CResponseCacheHelper)

ECode CResponseCacheHelper::GetDefault(
    /* [out] */ IResponseCache** responseCache)
{
    return ResponseCache::GetDefault(responseCache);
}

ECode CResponseCacheHelper::SetDefault(
    /* [in] */ IResponseCache* responseCache)
{
    return ResponseCache::SetDefault(responseCache);
}

} // namespace Net
} // namespace Elastos