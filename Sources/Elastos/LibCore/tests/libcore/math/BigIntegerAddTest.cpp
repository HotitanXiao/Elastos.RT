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

#include <elautoptr.h>
#include "elastos/coredef.h"
#include "elastos/core/StringUtils.h"
#include "elastos/core/StringBuilder.h"
#include "elastos/utility/etl/List.h"
#include "elastos/utility/Arrays.h"

using namespace Elastos;
using Elastos::Core::StringUtils;
using Elastos::Core::Math;
using Elastos::Math::IBigInteger;
using Elastos::Math::CBigInteger;
using Elastos::Math::IBigDecimal;
using Elastos::Math::CBigDecimal;
using Elastos::Math::IBigDecimalHelper;
using Elastos::Math::CBigDecimalHelper;

#define ARRAY_SIZE(a)   (sizeof (a) / sizeof ((a)[0]))

#if 0
static void assertEquals(const String& expecting, const String& toVerify)
{
    printf("expecting: [%s], toVerify: [%s]\n", expecting.string(), toVerify.string());
    assert(expecting.Equals(toVerify) && "result not equals expecting!");
}

static void assertEquals(Double expecting, Double toVerify)
{
    printf("expecting: %f, toVerify: %f\n", expecting, toVerify);
    assert(expecting == toVerify);
}

static void assertEquals(Float expecting, Float toVerify)
{
    printf("expecting: %f, toVerify: %f\n", expecting, toVerify);
    assert(expecting == toVerify);
}

static void assertEquals(Int64 expecting, Int64 toVerify)
{
    printf("expecting: %lld, toVerify: %lld\n", expecting, toVerify);
    assert(expecting == toVerify);
}
#endif

static void assertEquals(const char *hintMessage, Int32 expecting, Int32 toVerify)
{
    printf("expecting: %d, toVerify: %d. %s\n", expecting, toVerify, hintMessage);
    assert(expecting == toVerify);
}

#if 0
static void assertEquals(const char* hintMessage, Int64 toVerify, Int64 expecting)
{
    printf("expecting: %lld, toVerify: %lld. %s\n", expecting, toVerify, hintMessage);
    assert(expecting == toVerify);
}
#endif

static void assertEquals(const char* hintMessage, Byte toVerify, Byte expecting)
{
    printf("expecting: %x, toVerify: %x. %s\n", expecting, toVerify, hintMessage);
    assert(expecting == toVerify);
}

#if 0
static void printArray(ArrayOf<IBigInteger *> *v, const char* hintMessage)
{
    printf("  >------Start print %s ------<\n", hintMessage);
    Int32 len = v->GetLength();
    for (Int32 i = 0; i < len; ++i) {
        if ((*v)[i]) {
            IBigInteger* bi = (*v)[i];
            Int32 sign = 0;
            bi->GetSignum(&sign);
            printf("    > %d: %p, sign %d\n", i, bi, sign);
        }
        else {
            printf("    > %d: NULL\n", i);
        }
    }
    printf("  >------End print %s ------<\n", hintMessage);
}
#endif


/**
 * Add two positive numbers of the same length
 */
 #if 0
    public void testCase1() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = 1;
        int bSign = 1;
        byte rBytes[] = {11, 22, 33, 44, 55, 66, 77, 11, 22, 33};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif

void testCase1()
{
    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(10);
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(10);
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(10);

    unsigned char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3};
    unsigned char _bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _rBytes[] = {11, 22, 33, 44, 55, 66, 77, 11, 22, 33};
    memcpy(aBytes->GetPayload(), _aBytes, 10);
    memcpy(bBytes->GetPayload(), _bBytes, 10);
    memcpy(rBytes->GetPayload(), _rBytes, 10);

    int aSign = 1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase1() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase1() incorrect sign", 1, sign);
}

    /**
     * Add two negative numbers of the same length
     */
#if 0
    public void testCase2() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = -1;
        int bSign = -1;
        byte rBytes[] = {-12, -23, -34, -45, -56, -67, -78, -12, -23, -33};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif

void testCase2()
{
    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(10);
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(10);
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(10);

    unsigned char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3};
    unsigned char _bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _rBytes[] = {-12, -23, -34, -45, -56, -67, -78, -12, -23, -33};
    memcpy(aBytes->GetPayload(), _aBytes, 10);
    memcpy(bBytes->GetPayload(), _bBytes, 10);
    memcpy(rBytes->GetPayload(), _rBytes, 10);

    int aSign = -1;
    int bSign = -1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase2() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase2() incorrect sign", -1, sign);
}

    /**
     * Add two numbers of the same length.
     * The first one is positive and the second is negative.
     * The first one is greater in absolute value.
     */
#if 0
    public void testCase3() {
        byte aBytes[] = {3, 4, 5, 6, 7, 8, 9};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte rBytes[] = {2, 2, 2, 2, 2, 2, 2};
        int aSign = 1;
        int bSign = -1;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif

void testCase3()
{
    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(7);
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(7);
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(7);

    unsigned char _aBytes[] = {3, 4, 5, 6, 7, 8, 9};
    unsigned char _bBytes[] = {1, 2, 3, 4, 5, 6, 7};
    signed char _rBytes[] = {2, 2, 2, 2, 2, 2, 2};
    memcpy(aBytes->GetPayload(), _aBytes, 7);
    memcpy(bBytes->GetPayload(), _bBytes, 7);
    memcpy(rBytes->GetPayload(), _rBytes, 7);

    int aSign = 1;
    int bSign = -1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase3() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase3() incorrect sign", 1, sign);
}


    /**
     * Add two numbers of the same length.
     * The first one is negative and the second is positive.
     * The first one is greater in absolute value.
     */
#if 0
    public void testCase4() {
        byte aBytes[] = {3, 4, 5, 6, 7, 8, 9};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte rBytes[] = {-3, -3, -3, -3, -3, -3, -2};
        int aSign = -1;
        int bSign = 1;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
void testCase4()
{
    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(7);
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(7);
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(7);

    unsigned char _aBytes[] = {3, 4, 5, 6, 7, 8, 9};
    unsigned char _bBytes[] = {1, 2, 3, 4, 5, 6, 7};
    signed char _rBytes[] = {-3, -3, -3, -3, -3, -3, -2};
    memcpy(aBytes->GetPayload(), _aBytes, 7);
    memcpy(bBytes->GetPayload(), _bBytes, 7);
    memcpy(rBytes->GetPayload(), _rBytes, 7);

    int aSign = -1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase4() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase4() incorrect sign", -1, sign);
}

#if 0
    /**
     * Add two numbers of the same length.
     * The first is positive and the second is negative.
     * The first is less in absolute value.
     */
    public void testCase5() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte bBytes[] = {3, 4, 5, 6, 7, 8, 9};
        byte rBytes[] = {-3, -3, -3, -3, -3, -3, -2};
        int aSign = 1;
        int bSign = -1;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
void testCase5()
{
    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(7);
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(7);
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(7);

    unsigned char _aBytes[] = {1, 2, 3, 4, 5, 6, 7};
    unsigned char _bBytes[] = {3, 4, 5, 6, 7, 8, 9};
    signed char _rBytes[] = {-3, -3, -3, -3, -3, -3, -2};
    memcpy(aBytes->GetPayload(), _aBytes, 7);
    memcpy(bBytes->GetPayload(), _bBytes, 7);
    memcpy(rBytes->GetPayload(), _rBytes, 7);

    int aSign = 1;
    int bSign = -1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase5() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase5() incorrect sign", -1, sign);
}

    /**
     * Add two numbers of the same length.
     * The first one is negative and the second is positive.
     * The first one is less in absolute value.
     */
#if 0
    public void testCase6() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte bBytes[] = {3, 4, 5, 6, 7, 8, 9};
        byte rBytes[] = {2, 2, 2, 2, 2, 2, 2};
        int aSign = -1;
        int bSign = 1;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
void testCase6()
{
    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(7);
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(7);
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(7);

    unsigned char _aBytes[] = {1, 2, 3, 4, 5, 6, 7};
    unsigned char _bBytes[] = {3, 4, 5, 6, 7, 8, 9};
    signed char _rBytes[] = {2, 2, 2, 2, 2, 2, 2};
    memcpy(aBytes->GetPayload(), _aBytes, 7);
    memcpy(bBytes->GetPayload(), _bBytes, 7);
    memcpy(rBytes->GetPayload(), _rBytes, 7);

    int aSign = -1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase6() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase6() incorrect sign", 1, sign);
}

    /**
     * Add two positive numbers of different length.
     * The first is longer.
     */
#if 0
    public void testCase7() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = 1;
        int bSign = 1;
        byte rBytes[] = {1, 2, 3, 4, 15, 26, 37, 41, 52, 63, 74, 15, 26, 37};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
void testCase7()
{
    unsigned char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
    unsigned char _bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _rBytes[] = {1, 2, 3, 4, 15, 26, 37, 41, 52, 63, 74, 15, 26, 37};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(ARRAY_SIZE(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(ARRAY_SIZE(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(ARRAY_SIZE(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, ARRAY_SIZE(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, ARRAY_SIZE(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, ARRAY_SIZE(_rBytes));

    int aSign = 1;
    int bSign = 1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase7() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase7() incorrect sign", 1, sign);
}

    /**
     * Add two positive numbers of different length.
     * The second is longer.
     */
#if 0
    public void testCase8() {
        byte aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
        byte rBytes[] = {1, 2, 3, 4, 15, 26, 37, 41, 52, 63, 74, 15, 26, 37};
        BigInteger aNumber = new BigInteger(aBytes);
        BigInteger bNumber = new BigInteger(bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif
void testCase8()
{
    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(10);
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(14);
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(14);

    unsigned char _aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    unsigned char _bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
    signed char _rBytes[] = {1, 2, 3, 4, 15, 26, 37, 41, 52, 63, 74, 15, 26, 37};
    memcpy(aBytes->GetPayload(), _aBytes, 10);
    memcpy(bBytes->GetPayload(), _bBytes, 14);
    memcpy(rBytes->GetPayload(), _rBytes, 14);

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(*aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(*bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase8() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase8() incorrect sign", 1, sign);
}

    /**
     * Add two negative numbers of different length.
     * The first is longer.
     */
#if 0
    public void testCase9() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = -1;
        int bSign = -1;
        byte rBytes[] = {-2, -3, -4, -5, -16, -27, -38, -42, -53, -64, -75, -16, -27, -37};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
void testCase9()
{
    unsigned char _aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
    unsigned char _bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    signed char _rBytes[] = {-2, -3, -4, -5, -16, -27, -38, -42, -53, -64, -75, -16, -27, -37};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(ARRAY_SIZE(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(ARRAY_SIZE(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(ARRAY_SIZE(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, ARRAY_SIZE(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, ARRAY_SIZE(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, ARRAY_SIZE(_rBytes));

    int aSign = -1;
    int bSign = -1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
        return;
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase9() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase9() incorrect sign", -1, sign);
}

    /**
     * Add two negative numbers of different length.
     * The second is longer.
     */
#if 0
    public void testCase10() {
        byte aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
        int aSign = -1;
        int bSign = -1;
        byte rBytes[] = {-2, -3, -4, -5, -16, -27, -38, -42, -53, -64, -75, -16, -27, -37};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif
void testCase10()
{
    unsigned char _aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
    unsigned char _bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
    signed char _rBytes[] = {-2, -3, -4, -5, -16, -27, -38, -42, -53, -64, -75, -16, -27, -37};

    AutoPtr<ArrayOf<Byte> > aBytes = ArrayOf<Byte>::Alloc(ARRAY_SIZE(_aBytes));
    AutoPtr<ArrayOf<Byte> > bBytes = ArrayOf<Byte>::Alloc(ARRAY_SIZE(_bBytes));
    AutoPtr<ArrayOf<Byte> > rBytes = ArrayOf<Byte>::Alloc(ARRAY_SIZE(_rBytes));

    memcpy(aBytes->GetPayload(), _aBytes, ARRAY_SIZE(_aBytes));
    memcpy(bBytes->GetPayload(), _bBytes, ARRAY_SIZE(_bBytes));
    memcpy(rBytes->GetPayload(), _rBytes, ARRAY_SIZE(_rBytes));

    int aSign = -1;
    int bSign = -1;

    AutoPtr<IBigInteger> aNumber;
    ECode ec = CBigInteger::New(aSign, *aBytes, (IBigInteger**)&aNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> bNumber;
    ec = CBigInteger::New(bSign, *bBytes, (IBigInteger**)&bNumber);
    if (FAILED(ec)) {
        printf(" Failed to create CBigInteger. Error %08X\n", ec);
    }

    AutoPtr<IBigInteger> result;
    AutoPtr<ArrayOf<Byte> > resBytes;

    aNumber->Add(bNumber, (IBigInteger**)&result);
    result->ToByteArray((ArrayOf<Byte> **)&resBytes);

    for(int i = 0; i < resBytes->GetLength(); i++) {
        assertEquals("testCase10() data error", (*resBytes)[i], (*rBytes)[i]);
    }

    Int32 sign;
    result->GetSignum(&sign);
    assertEquals("testCase10() incorrect sign", -1, sign);
}

    /**
     * Add two numbers of different length and sign.
     * The first is positive.
     * The first is longer.
     */
#if 0
    public void testCase11() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = 1;
        int bSign = -1;
        byte rBytes[] = {1, 2, 3, 3, -6, -15, -24, -40, -49, -58, -67, -6, -15, -23};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif

    /**
     * Add two numbers of different length and sign.
     * The first is positive.
     * The second is longer.
     */
#if 0
    public void testCase12() {
        byte aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
        int aSign = 1;
        int bSign = -1;
        byte rBytes[] = {-2, -3, -4, -4, 5, 14, 23, 39, 48, 57, 66, 5, 14, 23};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif

    /**
     * Add two numbers of different length and sign.
     * The first is negative.
     * The first is longer.
     */
#if 0
    public void testCase13() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
        byte bBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        int aSign = -1;
        int bSign = 1;
        byte rBytes[] = {-2, -3, -4, -4, 5, 14, 23, 39, 48, 57, 66, 5, 14, 23};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", -1, result.signum());
    }
#endif

    /**
     * Add two numbers of different length and sign.
     * The first is negative.
     * The second is longer.
     */
#if 0
    public void testCase14() {
        byte aBytes[] = {10, 20, 30, 40, 50, 60, 70, 10, 20, 30};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7};
        int aSign = -1;
        int bSign = 1;
        byte rBytes[] = {1, 2, 3, 3, -6, -15, -24, -40, -49, -58, -67, -6, -15, -23};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif

    /**
     * Add two equal numbers of different signs
     */
#if 0
    public void testCase15() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte rBytes[] = {0};
        int aSign = -1;
        int bSign = 1;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 0, result.signum());
    }
#endif

    /**
     * Add zero to a number
     */
#if 0
    public void testCase16() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte bBytes[] = {0};
        byte rBytes[] = {1, 2, 3, 4, 5, 6, 7};
        int aSign = 1;
        int bSign = 1;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif

    /**
     * Add a number to zero
     */
#if 0
    public void testCase17() {
        byte aBytes[] = {0};
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte rBytes[] = {1, 2, 3, 4, 5, 6, 7};
        int aSign = 1;
        int bSign = 1;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif

    /**
     * Add zero to zero
     */
#if 0
    public void testCase18() {
        byte aBytes[] = {0};
        byte bBytes[] = {0};
        byte rBytes[] = {0};
        int aSign = 1;
        int bSign = 1;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 0, result.signum());
    }
#endif

    /**
     * Add ZERO to a number
     */
#if 0
    public void testCase19() {
        byte aBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte rBytes[] = {1, 2, 3, 4, 5, 6, 7};
        int aSign = 1;
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = BigInteger.ZERO;
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif

    /**
     * Add a number to zero
     */
#if 0
    public void testCase20() {
        byte bBytes[] = {1, 2, 3, 4, 5, 6, 7};
        byte rBytes[] = {1, 2, 3, 4, 5, 6, 7};
        int bSign = 1;
        BigInteger aNumber = BigInteger.ZERO;
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif

    /**
     * Add ZERO to ZERO
     */
#if 0
    public void testCase21() {
        byte rBytes[] = {0};
        BigInteger aNumber = BigInteger.ZERO;
        BigInteger bNumber = BigInteger.ZERO;
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 0, result.signum());
    }
#endif

    /**
     * Add ONE to ONE
     */
#if 0
    public void testCase22() {
        byte rBytes[] = {2};
        BigInteger aNumber = BigInteger.ONE;
        BigInteger bNumber = BigInteger.ONE;
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
#endif

    /**
     * Add two numbers so that carry is 1
     */
#if 0
    public void testCase23() {
        byte aBytes[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        byte bBytes[] = {-1, -1, -1, -1, -1, -1, -1, -1};
        int aSign = 1;
        int bSign = 1;
        byte rBytes[] = {1, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -2};
        BigInteger aNumber = new BigInteger(aSign, aBytes);
        BigInteger bNumber = new BigInteger(bSign, bBytes);
        BigInteger result = aNumber.add(bNumber);
        byte resBytes[] = new byte[rBytes.length];
        resBytes = result.toByteArray();
        for(int i = 0; i < resBytes.length; i++) {
            assertTrue(resBytes[i] == rBytes[i]);
        }
        assertEquals("incorrect sign", 1, result.signum());
    }
}
#endif


//==============================================================================

EXTERN_C int mainBigIntegerAddTest(int argc, char *argv[])
{
	printf("\n==== libcore/math/BigIntegerAddTest ====\n");
	testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();
    testCase6();
    testCase7();
    testCase8();
    testCase9();
    testCase10();
	printf("\n==== end of libcore/math/BigIntegerAddTest ====\n");

	return 0;
}


