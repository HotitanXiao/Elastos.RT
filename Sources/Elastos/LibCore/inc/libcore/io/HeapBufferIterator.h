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

#ifndef __LIBCORE_IO_HEAPBUFFERITERATOR_H__
#define __LIBCORE_IO_HEAPBUFFERITERATOR_H__

#include "Elastos.CoreLibrary.Libcore.h"
#include "elastos/core/Object.h"

using Elastos::Core::Object;
using Elastos::IO::ByteOrder;

namespace Libcore {
namespace IO {

class HeapBufferIterator
    : public Object
    , public IBufferIterator
{
public:
    CAR_INTERFACE_DECL()

    /**
     * Seeks to the absolute position {offset}, measured in bytes from the start.
     */
    CARAPI Seek(
        /* [in] */ Int32 offset);

    /**
     * Skips forwards or backwards {byteCount} bytes from the current position.
     */
    CARAPI Skip(
        /* [in] */ Int32 byteCount);

    /**
     * Copies {byteCount} bytes from the current position into {dst}, starting at
     * {dstOffset}, and advances the current position {byteCount} bytes.
     */
    CARAPI ReadByteArray(
        /* [in] */ ArrayOf<Byte>* dst,
        /* [in] */ Int32 dstOffset,
        /* [in] */ Int32 byteCount);

    /**
     * Returns the byte at the current position, and advances the current position one byte.
     */
    CARAPI ReadByte(
        /* [out] */ Byte* result);

    /**
     * Returns the 32-bit int at the current position, and advances the current position four bytes.
     */
    CARAPI ReadInt32(
        /* [out] */ Int32* result);

    /**
     * Copies {intCount} 32-bit ints from the current position into {dst}, starting at
     * {dstOffset}, and advances the current position {4 * intCount} bytes.
     */
    CARAPI ReadInt32Array(
        /* [in] */ ArrayOf<Int32>* dst,
        /* [in] */ Int32 dstOffset,
        /* [in] */ Int32 intCount);

    /**
     * Returns the 16-bit short at the current position, and advances the current position two bytes.
     */
    CARAPI ReadInt16(
        /* [out] */ Int16* result);

    static AutoPtr<IBufferIterator> Iterator(
        /* [in] */ ArrayOf<Byte>* buffer,
        /* [in] */ Int32 offset,
        /* [in] */ Int32 byteCount,
        /* [in] */ ByteOrder order);

private:
    HeapBufferIterator(
        /* [in] */ ArrayOf<Byte>* buffer,
        /* [in] */ Int32 offset,
        /* [in] */ Int32 byteCount,
        /* [in] */ ByteOrder order);

    AutoPtr<ArrayOf<Byte> > mBuffer;
    Int32 mOffset;
    Int32 mByteCount;
    ByteOrder mOrder;

    Int32 mPosition;
};

} // namespace IO
} // namespace Libcore
#endif
