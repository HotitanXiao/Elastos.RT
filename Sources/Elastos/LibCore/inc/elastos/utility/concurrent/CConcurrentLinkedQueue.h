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

#ifndef __ELASTOS_UTILITY_CONCURRENT_ELASTOS_UTILITY_CCONCURRENTLINKEDQUEUE_H__
#define __ELASTOS_UTILITY_CONCURRENT_ELASTOS_UTILITY_CCONCURRENTLINKEDQUEUE_H__

#include "_Elastos_Utility_Concurrent_CConcurrentLinkedQueue.h"
#include "elastos/utility/AbstractQueue.h"
#include "elastos/core/Object.h"

using Elastos::IO::IObjectOutputStream;
using Elastos::IO::IObjectInputStream;
using Elastos::IO::ISerializable;

namespace Elastos {
namespace Utility {
namespace Concurrent {

CarClass(CConcurrentLinkedQueue)
    , public AbstractQueue
    , public IConcurrentLinkedQueue
    , public ISerializable
{
private:
    class Node
        : public Object
    {
    public:
        Node(
            /* [in] */ IInterface* item);

        CARAPI_(Boolean) CasItem(
            /* [in] */ IInterface* cmp,
            /* [in] */ IInterface* val);

        CARAPI_(void) LazySetNext(
            /* [in] */ Node* val);

        CARAPI_(Boolean) CasNext(
            /* [in] */ Node* cmp,
            /* [in] */ Node* val);

    public:
        AutoPtr<IInterface> mItem;
        AutoPtr<Node> mNext;
    };

    class Itr
        : public IIterator
        , public Object
    {
    public:
        CAR_INTERFACE_DECL()

        Itr(
            /* [in] */ CConcurrentLinkedQueue* owner);

        CARAPI HasNext(
            /* [out] */ Boolean* result);

        CARAPI GetNext(
            /* [out] */ IInterface** object);

        CARAPI Remove();

    private:
        /**
         * Moves to next valid node and returns item to return for
         * next(), or null if no such.
         */
        AutoPtr<IInterface> Advance();

    public:
        CConcurrentLinkedQueue* mOwner;

    private:
        /**
         * Next node to return item for.
         */
        AutoPtr<Node> mNextNode;

        /**
         * nextItem holds on to item fields because once we claim
         * that an element exists in hasNext(), we must return it in
         * the following next() call even if it was in the process of
         * being removed when hasNext() was called.
         */
        AutoPtr<IInterface> mNextItem;

        /**
         * Node of the last returned item, to support remove.
         */
        AutoPtr<Node> mLastRet;
    };

public:
    CAR_INTERFACE_DECL()

    CAR_OBJECT_DECL()

    CARAPI constructor();

    CARAPI constructor(
        /* [in] */ ICollection* c);

    CARAPI Add(
        /* [in] */ IInterface* object,
        /* [out] */ Boolean* modified);

    CARAPI Offer(
        /* [in] */ IInterface* e,
        /* [out] */ Boolean* result);

    CARAPI Poll(
        /* [out] */ IInterface** e);

    CARAPI Peek(
        /* [out] */ IInterface** e);

    CARAPI IsEmpty(
        /* [out] */ Boolean* result);

    CARAPI GetSize(
        /* [out] */ Int32* size);

    CARAPI Contains(
        /* [in] */ IInterface* object,
        /* [out] */ Boolean* result);

    CARAPI Remove(
        /* [in] */ IInterface* object,
        /* [out] */ Boolean* modified);

    CARAPI AddAll(
        /* [in] */ ICollection* collection,
        /* [out] */ Boolean* modified);

    CARAPI ToArray(
        /* [out, callee] */ ArrayOf<IInterface*>** array);

    CARAPI ToArray(
        /* [in] */ ArrayOf<IInterface*>* inArray,
        /* [out, callee] */ ArrayOf<IInterface*>** outArray);

    CARAPI GetIterator(
        /* [out] */ IIterator** iterator);

    CARAPI Equals(
        /* [in] */ IInterface* object,
        /* [out] */ Boolean* result);

    CARAPI GetHashCode(
        /* [out] */ Int32* hashCode);

protected:
    CARAPI_(void) UpdateHead(
        /* [in] */ Node* h,
        /* [in] */ Node* p);

    CARAPI_(AutoPtr<Node>) Succ(
        /* [in] */ Node* p);

    CARAPI_(AutoPtr<Node>) First();

    CARAPI_(String) GetClassName() { return String("CConcurrentLinkedQueue"); }

private:
    CARAPI_(void) WriteObject(
        /* [in] */ IObjectOutputStream* s);

    CARAPI_(void) ReadObject(
        /* [in] */ IObjectInputStream* s);

    static CARAPI CheckNotNull(
        /* [in] */ IInterface* v);

    CARAPI_(Boolean) CasTail(
        /* [in] */ Node* cmp,
        /* [in] */ Node* val);

    CARAPI_(Boolean) CasHead(
        /* [in] */ Node* cmp,
        /* [in] */ Node* val);

private:
    AutoPtr<Node> mHead;
    AutoPtr<Node> mTail;
};

} // namespace Concurrent
} // namespace Utility
} // namespace Elastos

#endif //__ELASTOS_UTILITY_CONCURRENT_ELASTOS_UTILITY_CCONCURRENTLINKEDQUEUE_H__
