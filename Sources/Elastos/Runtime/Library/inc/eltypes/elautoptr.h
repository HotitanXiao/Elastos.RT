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

#ifndef __ELASTOS_RUNTIME_ELAUTOPTR_H__
#define __ELASTOS_RUNTIME_ELAUTOPTR_H__

#include <eladef.h>

_ELASTOS_NAMESPACE_BEGIN

//------------------------- IsSpecializedAutoPtr ------------------------------

template <typename T>
class AutoPtr;

template<typename T>
struct IsSpecializedAutoPtr
{
    static const Boolean Value = FALSE;
    typedef void InnerType;
};

template<typename T>
struct IsSpecializedAutoPtr<AutoPtr<T> >
{
    static const Boolean Value = TRUE;
    typedef T InnerType;
};

//--------------------------------- AutoPtr ------------------------------------

#define AUTOPTR_COMPARE(_op_)                                   \
inline Boolean operator _op_ (const AutoPtr<T>& o) const {      \
    return mPtr _op_ o.mPtr;                                    \
}                                                               \
inline Boolean operator _op_ (const T* o) const {               \
    return mPtr _op_ o;                                         \
}                                                               \
template<typename U>                                            \
inline Boolean operator _op_ (const AutoPtr<U>& o) const {      \
    return mPtr _op_ o.mPtr;                                    \
}                                                               \
template<typename U>                                            \
inline Boolean operator _op_ (const U* o) const {               \
    return mPtr _op_ o;                                         \
}

template <typename T>
class AutoPtr
{
public:
    inline AutoPtr() : mPtr(0) {}

    AutoPtr(T* other);
    AutoPtr(const AutoPtr<T>& other);
    template<typename U> AutoPtr(U* other);
    template<typename U> AutoPtr(const AutoPtr<U>& other);

    ~AutoPtr();

    // Assignment

    AutoPtr& operator = (T* other);
    AutoPtr& operator = (const AutoPtr<T>& other);

    template<typename U> AutoPtr& operator = (const AutoPtr<U>& other);
    template<typename U> AutoPtr& operator = (U* other);

    // Accessors

    inline  T& operator* () const  { return *mPtr; }
    inline  T* operator-> () const { return mPtr;  }
    inline  T* Get() const         { return mPtr; }
    inline  operator T*() const { return mPtr; }

    // Operators

    AUTOPTR_COMPARE(==)
    AUTOPTR_COMPARE(!=)
    AUTOPTR_COMPARE(>)
    AUTOPTR_COMPARE(<)
    AUTOPTR_COMPARE(<=)
    AUTOPTR_COMPARE(>=)

private:
    template<typename Y> friend class AutoPtr;

    T*              mPtr;
};

// ---------------------------------------------------------------------------
// No user serviceable parts below here.

template<typename T>
AutoPtr<T>::AutoPtr(T* other) : mPtr(other)
{
    if (other) other->AddRef();
}

template<typename T>
AutoPtr<T>::AutoPtr(const AutoPtr<T>& other) : mPtr(other.mPtr)
{
    if (mPtr) mPtr->AddRef();
}

template<typename T> template<typename U>
AutoPtr<T>::AutoPtr(U* other) : mPtr(other)
{
    if (other) other->AddRef();
}

template<typename T> template<typename U>
AutoPtr<T>::AutoPtr(const AutoPtr<U>& other) : mPtr(other.mPtr)
{
    if (mPtr) mPtr->AddRef();
}

template<typename T>
AutoPtr<T>::~AutoPtr()
{
    if (mPtr) mPtr->Release();
}

template<typename T>
AutoPtr<T>& AutoPtr<T>::operator = (const AutoPtr<T>& other)
{
    if (other.mPtr) other.mPtr->AddRef();
    if (mPtr) mPtr->Release();
    mPtr = other.mPtr;
    return *this;
}

template<typename T>
AutoPtr<T>& AutoPtr<T>::operator = (T* other)
{
    if (other) other->AddRef();
    if (mPtr) mPtr->Release();
    mPtr = other;
    return *this;
}

template<typename T> template<typename U>
AutoPtr<T>& AutoPtr<T>::operator = (const AutoPtr<U>& other)
{
    if (other.mPtr) other.mPtr->AddRef();
    if (mPtr) mPtr->Release();
    mPtr = other.mPtr;
    return *this;
}

template<typename T> template<typename U>
AutoPtr<T>& AutoPtr<T>::operator = (U* other)
{
    if (other) other->AddRef();
    if (mPtr) mPtr->Release();
    mPtr = other;
    return *this;
}

_ELASTOS_NAMESPACE_END

#endif //__ELASTOS_RUNTIME_ELAUTOPTR_H__
