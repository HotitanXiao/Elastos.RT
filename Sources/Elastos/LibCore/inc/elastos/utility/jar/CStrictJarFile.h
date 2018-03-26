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

#ifndef __ELASTOS_UTILITY_JAR_ELASTOS_UTILITY_CSTRICT_JAR_FILE_H__
#define __ELASTOS_UTILITY_JAR_ELASTOS_UTILITY_CSTRICT_JAR_FILE_H__

#include "Elastos.CoreLibrary.Utility.h"
#include "_Elastos_Utility_Jar_CStrictJarFile.h"
#include "elastos/core/Object.h"
#include "elastos/utility/jar/JarVerifier.h"

using Elastos::Utility::IIterator;
using Elastos::Utility::Jar::IManifest;
using Elastos::Utility::Zip::IZipEntry;
using Elastos::IO::IInputStream;
using Elastos::IO::IRandomAccessFile;
using Elastos::Core::IArrayOf;
using Elastos::Core::ICloseGuard;
using Elastos::Security::Cert::ICertificate;

namespace Elastos {
namespace Utility {
namespace Jar {

CarClass(CStrictJarFile)
    , public Object
    , public IStrictJarFile
{
public:
    class EntryIterator
        : public Object
        , public IIterator
    {
    public:
        CAR_INTERFACE_DECL()

        EntryIterator(
            /* [in] */ Int64 nativeHandle,
            /* [in] */ const String& prefix);

        CARAPI GetNext(
            /* [out] */ IInterface** obj);

        CARAPI HasNext(
            /* [out] */ Boolean* result);

        CARAPI Remove();
    private:
        Int64 mIterationHandle;
        AutoPtr<IZipEntry> mNextEntry;
    };

public:
    CAR_INTERFACE_DECL()

    CAR_OBJECT_DECL()

    CStrictJarFile();

    CARAPI constructor(
        /* [in] */ const String& filename);

    CARAPI GetManifest(
        /* [out] */ IManifest** manifest);

    CARAPI GetIterator(
        /* [out] */ IIterator** it);

    CARAPI FindEntry(
        /* [in] */ const String& name,
        /* [out] */ IZipEntry** ze);

    /**
     * Return all certificate chains for a given {@link ZipEntry} belonging to this jar.
     * This method MUST be called only after fully exhausting the InputStream belonging
     * to this entry.
     *
     * Returns {@code null} if this jar file isn't signed or if this method is
     * called before the stream is processed.
     */
    CARAPI GetCertificateChains(
        /* [in] */ IZipEntry* ze,
        /* [out, callee] */ ArrayOf<IArrayOf *> ** certificate);

    CARAPI GetCertificates(
        /* [in] */ IZipEntry* ze,
        /* [out, callee] */ ArrayOf<ICertificate *> ** certificate);

    CARAPI GetInputStream(
        /* [in] */ IZipEntry* ze,
        /* [out] */ IInputStream** is);

    CARAPI Close();

private:
    friend class EntryIterator;

    CARAPI GetZipInputStream(
        /* [in] */ IZipEntry* ze,
        /* [out] */ IInputStream** is);

    AutoPtr<HashMap<String, AutoPtr<ArrayOf<Byte> > > > GetMetaEntries();

    static CARAPI NativeOpenJarFile(
        /* [in] */ const String& fileName,
        /* [out] */ Int64* result);

    static CARAPI NativeStartIteration(
        /* [in] */ Int64 nativeHandle,
        /* [in] */ const String& prefix,
        /* [out] */ Int64* result);

    static CARAPI NativeNextEntry(
        /* [in] */ Int64 iterationHandle,
        /* [out] */ IZipEntry** ze);

    static CARAPI NativeFindEntry(
        /* [in] */ Int64 nativeHandle,
        /* [in] */ const String& entryName,
        /* [out] */ IZipEntry** ze);

    static CARAPI NativeClose(
        /* [in] */ Int64 nativeHandle);

private:
    Int64 mNativeHandle;

    // NOTE: It's possible to share a file descriptor with the native
    // code, at the cost of some additional complexity.
    AutoPtr<IRandomAccessFile> mRaf;

    AutoPtr<IManifest> mManifest;
    AutoPtr<JarVerifier> mVerifier;

    AutoPtr<ICloseGuard> mGuard;// = CloseGuard.get();
    Boolean mIsSigned;
    Boolean mClosed;
};

} // namespace Jar
} // namespace Utility
} // namespace Elastos

#endif // __ELASTOS_UTILITY_JAR_ELASTOS_UTILITY_CSTRICT_JAR_FILE_H__
