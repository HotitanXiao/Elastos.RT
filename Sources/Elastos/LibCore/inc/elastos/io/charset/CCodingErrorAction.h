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

#ifndef __ELASTOS_IO_CHARSET_ELASTOS_IO_CCODINGERRORACTION_H__
#define __ELASTOS_IO_CHARSET_ELASTOS_IO_CCODINGERRORACTION_H__

#include "_Elastos_IO_Charset_CCodingErrorAction.h"
#include "elastos/core/Object.h"

using Elastos::Core::Object;

namespace Elastos {
namespace IO {
namespace Charset {

CarClass(CCodingErrorAction)
    , public Object
    , public ICodingErrorAction
{
public:
    CAR_INTERFACE_DECL()

    CAR_OBJECT_DECL()

    CARAPI constructor();

    static CARAPI GetIGNORE(
        /* [out] */ ICodingErrorAction** ignore);

    static CARAPI GetREPLACE(
        /* [out] */ ICodingErrorAction** replace);

    static CARAPI GetREPORT(
        /* [out] */ ICodingErrorAction** report);

    CARAPI ToString(
        /* [out] */ String* toString);

private:
    friend AutoPtr<ICodingErrorAction> CreateAction(
        /* [in] */ const String& action);

private:
    static const AutoPtr<ICodingErrorAction> IGNORE;
    static const AutoPtr<ICodingErrorAction> REPLACE;
    static const AutoPtr<ICodingErrorAction> REPORT;

    String mAction;
};

} // namespace Charset
} // namespace IO
} // namespace Elastos

#endif // __ELASTOS_IO_CHARSET_ELASTOS_IO_CCODINGERRORACTION_H__
