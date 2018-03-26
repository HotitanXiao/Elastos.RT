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

#ifndef __ELASTOS_UTILITY_CONCURRENT_TIMEUNIT_H__
#define __ELASTOS_UTILITY_CONCURRENT_TIMEUNIT_H__

#include "Elastos.CoreLibrary.Utility.Concurrent.h"
#include "elastos/core/Object.h"
#include "elastos/core/Math.h"

using Elastos::Core::ISynchronize;
using Elastos::Core::IThread;
using Elastos::Core::Object;

#define ITIMEUNIT_METHODS_DECL()                                        \
    CARAPI Convert(                                                     \
        /* [in] */ Int64 sourceDuration,                                \
        /* [in] */ ITimeUnit* sourceUnit,                               \
        /* [out] */ Int64* result);                                     \
                                                                        \
    CARAPI ToNanos(                                                     \
        /* [in] */ Int64 duration,                                      \
        /* [out] */ Int64* result);                                     \
                                                                        \
    CARAPI ToMicros(                                                    \
        /* [in] */ Int64 duration,                                      \
        /* [out] */ Int64* result);                                     \
                                                                        \
    CARAPI ToMillis(                                                    \
        /* [in] */ Int64 duration,                                      \
        /* [out] */ Int64* result);                                     \
                                                                        \
    CARAPI ToSeconds(                                                   \
        /* [in] */ Int64 duration,                                      \
        /* [out] */ Int64* result);                                     \
                                                                        \
    CARAPI ToMinutes(                                                   \
        /* [in] */ Int64 duration,                                      \
        /* [out] */ Int64* result);                                     \
                                                                        \
    CARAPI ToHours(                                                     \
        /* [in] */ Int64 duration,                                      \
        /* [out] */ Int64* result);                                     \
                                                                        \
    CARAPI ToDays(                                                      \
        /* [in] */ Int64 duration,                                      \
        /* [out] */ Int64* result);                                     \
                                                                        \
    CARAPI ExcessNanos(                                                 \
        /* [in] */ Int64 d,                                             \
        /* [in] */ Int64 m,                                             \
        /* [out] */ Int32* result);                                     \


namespace Elastos {
namespace Utility {
namespace Concurrent {

class TimeUnit
    : public Object
    , public ITimeUnit
{
public:
    CAR_INTERFACE_DECL()

    /**
     * Scale d by m, checking for overflow.
     * This has a short name to make above code more readable.
     */
    static CARAPI_(Int64) X(
        /* [in] */ Int64 d,
        /* [in] */ Int64 m,
        /* [in] */ Int64 over);

    virtual CARAPI TimedWait(
        /* [in] */ ISynchronize* obj,
        /* [in] */ Int64 timeout);

    virtual CARAPI TimedJoin(
        /* [in] */ IThread* thread,
        /* [in] */ Int64 timeout);

    virtual CARAPI Sleep(
        /* [in] */ Int64 timeout);

    static CARAPI_(AutoPtr<ITimeUnit>) GetNANOSECONDS();

    static CARAPI_(AutoPtr<ITimeUnit>) GetMICROSECONDS();

    static CARAPI_(AutoPtr<ITimeUnit>) GetMILLISECONDS();

    static CARAPI_(AutoPtr<ITimeUnit>) GetSECONDS();

    static CARAPI_(AutoPtr<ITimeUnit>) GetMINUTES();

    static CARAPI_(AutoPtr<ITimeUnit>) GetHOURS();

    static CARAPI_(AutoPtr<ITimeUnit>) GetDAYS();

public:
    // Handy constants for conversion methods
    static const Int64 C0 = 1LL;
    static const Int64 C1 = C0 * 1000LL;
    static const Int64 C2 = C1 * 1000LL;
    static const Int64 C3 = C2 * 1000LL;
    static const Int64 C4 = C3 * 60LL;
    static const Int64 C5 = C4 * 60LL;
    static const Int64 C6 = C5 * 24LL;

    static const Int64 MAX;
};

class NANOSECONDS
    : public TimeUnit
{
public:
//    CAR_INTERFACE_DECL()

    ITIMEUNIT_METHODS_DECL();
};

class MICROSECONDS
    : public TimeUnit
{
public:
//    CAR_INTERFACE_DECL()

    ITIMEUNIT_METHODS_DECL();
};

class MILLISECONDS
    : public TimeUnit
{
public:
//    CAR_INTERFACE_DECL()

    ITIMEUNIT_METHODS_DECL();
};

class SECONDS
    : public TimeUnit
{
public:
//    CAR_INTERFACE_DECL()

    ITIMEUNIT_METHODS_DECL();
};

class MINUTES
    : public TimeUnit
{
public:
//    CAR_INTERFACE_DECL()

    ITIMEUNIT_METHODS_DECL();
};

class HOURS
    : public TimeUnit
{
public:
//    CAR_INTERFACE_DECL()

    ITIMEUNIT_METHODS_DECL();
};

class DAYS
    : public TimeUnit
{
public:
//    CAR_INTERFACE_DECL()

    ITIMEUNIT_METHODS_DECL();
};

} // namespace Concurrent
} // namespace Utility
} // namespace Elastos

#endif //__ELASTOS_UTILITY_CONCURRENT_TIMEUNIT_H__
