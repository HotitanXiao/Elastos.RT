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

#include "elastos/utility/concurrent/CCopyOnWriteArrayListHelper.h"
#include "elastos/utility/concurrent/CopyOnWriteArrayList.h"

namespace Elastos {
namespace Utility {
namespace Concurrent {

CAR_INTERFACE_IMPL(CCopyOnWriteArrayListHelper, Singleton, ICopyOnWriteArrayListHelper)

CAR_SINGLETON_IMPL(CCopyOnWriteArrayListHelper)

ECode CCopyOnWriteArrayListHelper::ContainsAll(
    /* [in] */ ICollection* collection,
    /* [in] */ ArrayOf<IInterface*>* snapshot,
    /* [in] */ Int32 from,
    /* [in] */ Int32 to,
    /* [out] */ Boolean* value)
{
    return CopyOnWriteArrayList::ContainsAll(collection, snapshot, from, to, value);
}

ECode CCopyOnWriteArrayListHelper::LastIndexOf(
    /* [in] */ IInterface* o,
    /* [in] */ ArrayOf<IInterface*>* data,
    /* [in] */ Int32 from,
    /* [in] */ Int32 to,
    /* [out] */ Int32* value)
{
    return CopyOnWriteArrayList::LastIndexOf(o, data, from, to, value);
}

ECode CCopyOnWriteArrayListHelper::IndexOf(
    /* [in] */ IInterface* o,
    /* [in] */ ArrayOf<IInterface*>* data,
    /* [in] */ Int32 from,
    /* [in] */ Int32 to,
    /* [out] */ Int32* value)
{
    return CopyOnWriteArrayList::IndexOf(o, data, from, to, value);
}

} // namespace Concurrent
} // namespace Utility
} // namespace Elastos
