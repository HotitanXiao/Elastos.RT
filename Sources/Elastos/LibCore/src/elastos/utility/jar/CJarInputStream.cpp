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

#include "elastos/utility/jar/CJarInputStream.h"
#include "elastos/io/CByteArrayOutputStream.h"
#include "elastos/utility/jar/CManifest.h"
#include "elastos/utility/jar/CAttributes.h"
#include "elastos/core/CString.h"
#include "elastos/utility/jar/JarVerifier.h"
#include "elastos/utility/jar/CJarFile.h"
#include "libcore/io/CStreams.h"

using Elastos::IO::IByteArrayOutputStream;
using Elastos::IO::CByteArrayOutputStream;
using Elastos::IO::EIID_IInputStream;
using Libcore::IO::IStreams;
using Libcore::IO::CStreams;
using Elastos::Utility::Zip::IZipEntry;
using Elastos::Core::CString;

namespace Elastos {
namespace Utility {
namespace Jar {

CAR_INTERFACE_IMPL(CJarInputStream, ZipInputStream, IJarInputStream)

CAR_OBJECT_IMPL(CJarInputStream)

CJarInputStream::CJarInputStream()
    : mIsMeta(FALSE)
    , mVerified(FALSE)
{}

ECode CJarInputStream::constructor(
    /* [in] */ IInputStream* stream,
    /* [in] */ Boolean verify)
{
    FAIL_RETURN(ZipInputStream::constructor(stream))

    AutoPtr<IJarEntry> je;
    GetNextJarEntry((IJarEntry**)&je);
    if (je == NULL) {
        return NOERROR;
    }

    String name;
    IZipEntry::Probe(mCurrentJarEntry)->GetName(&name);
    if (name.EqualsIgnoreCase(CJarFile::META_DIR)) {
        CloseEntry();
        je = NULL;
        GetNextJarEntry((IJarEntry**)&je);
    }

    IZipEntry::Probe(mCurrentJarEntry)->GetName(&name);
    if (name.EqualsIgnoreCase(IJarFile::MANIFEST_NAME)) {
        AutoPtr<ArrayOf<Byte> > manifestBytes;
        AutoPtr<IStreams> streams;
        CStreams::AcquireSingleton((IStreams**)&streams);
        streams->ReadFullyNoClose(this, (ArrayOf<Byte>**)&manifestBytes);
        CManifest::New((IManifest**)&mManifest);
        ((CManifest*)mManifest.Get())->constructor(manifestBytes, verify);
        FAIL_RETURN(CloseEntry())

        if (verify) {
            AutoPtr<HashMap<String, AutoPtr<ArrayOf<Byte> > > > metaEntries;
            metaEntries = new HashMap<String, AutoPtr<ArrayOf<Byte> > >();
            (*metaEntries)[IJarFile::MANIFEST_NAME] = manifestBytes;
            mVerifier = new JarVerifier(
                String("JarInputStream"), mManifest, metaEntries);
        }
    }

    // There was no manifest available, so we should return the current
    // entry the next time getNextEntry is called.
    mPendingJarEntry = mCurrentJarEntry;
    mCurrentJarEntry = NULL;

    // If the manifest isn't the first entry, we will not have enough
    // information to perform verification on entries that precede it.
    //
    // TODO: Should we throw if verify == true in this case ?
    // TODO: We need all meta entries to be placed before the manifest
    // as well.
    return NOERROR;
}

ECode CJarInputStream::constructor(
    /* [in] */ IInputStream* stream)
{
    return constructor(stream, TRUE);
}

ECode CJarInputStream::GetManifest(
    /* [out] */ IManifest** manifest)
{
    VALIDATE_NOT_NULL(manifest)
    *manifest = mManifest;
    REFCOUNT_ADD(*manifest)
    return NOERROR;
}

ECode CJarInputStream::GetNextJarEntry(
    /* [out] */ IJarEntry** jarEntry)
{
    VALIDATE_NOT_NULL(jarEntry)
    *jarEntry = NULL;
    AutoPtr<IZipEntry> ze;
    FAIL_RETURN(GetNextEntry((IZipEntry**)&ze))
    *jarEntry = IJarEntry::Probe(ze);
    REFCOUNT_ADD(*jarEntry)
    return NOERROR;
}

ECode CJarInputStream::Read(
    /* [in] */ ArrayOf<Byte>* buffer,
    /* [in] */ Int32 byteOffset,
    /* [in] */ Int32 byteCount,
    /* [out] */ Int32* read)
{
    VALIDATE_NOT_NULL(read)
    *read = -1;

    if (mCurrentJarEntry == NULL) {
        return NOERROR;
    }

    Int32 r;
    FAIL_RETURN(ZipInputStream::Read(buffer, byteOffset, byteCount, &r))

    // verifier can be null if we've been asked not to verify or if
    // the manifest wasn't found.
    //
    // verStream will be null if we're reading the manifest or if we have
    // no signatures or if the digest for this entry isn't present in the
    // manifest.
    if (mVerifier != NULL && mVerStream != NULL && !mVerified) {
        if (r == -1) {
            // We've hit the end of this stream for the first time, so attempt
            // a verification.
            mVerified = TRUE;
            if (mIsMeta) {
                String name;
                IZipEntry::Probe(mCurrentJarEntry)->GetName(&name);
                AutoPtr<ArrayOf<Byte> > bytes;
                IByteArrayOutputStream::Probe(mVerStream)->ToByteArray((ArrayOf<Byte>**)&bytes);
                mVerifier->AddMetaEntry(name, bytes);
                // try {
                Boolean bval;
                ECode ec = mVerifier->ReadCertificates(&bval);
                if (ec == (ECode)E_SECURITY_EXCEPTION) {
                    mVerifier = NULL;
                    return ec;
                }
                // } catch (SecurityException e) {
                    // mVerifier = NULL;
                    // throw e;
                // }
            }
            else {
                JarVerifier::VerifierEntry * ve = (JarVerifier::VerifierEntry *)mVerStream.Get();
                FAIL_RETURN(ve->Verify())
            }
        }
        else {
            mVerStream->Write(buffer, byteOffset, r);
        }
    }

    *read = r;
    return NOERROR;
}

ECode CJarInputStream::GetNextEntry(
    /* [out] */ IZipEntry** entry)
{
    VALIDATE_NOT_NULL(entry)
    *entry = NULL;

    // NOTE: This function must update the value of currentJarEntry
    // as a side effect.
    if (mPendingJarEntry != NULL) {
        AutoPtr<IJarEntry> pending = mPendingJarEntry;
        mPendingJarEntry = NULL;
        mCurrentJarEntry = pending;
        *entry = IZipEntry::Probe(pending);
        REFCOUNT_ADD(*entry)
        return NOERROR;
    }

    AutoPtr<IZipEntry> ze;
    FAIL_RETURN(ZipInputStream::GetNextEntry((IZipEntry**)&ze))
    mCurrentJarEntry = IJarEntry::Probe(ze);
    if (mCurrentJarEntry == NULL) {
        return NOERROR;
    }

    if (mVerifier != NULL) {
        String name;
        IZipEntry::Probe(mCurrentJarEntry)->GetName(&name);
        String nameUc = name.ToUpperCase(/*Locale.US*/);
        mIsMeta = nameUc.StartWith(/*CJarFile::META_DIR*/String("META-INF/"));
        if (mIsMeta) {
            Int64 size;
            IZipEntry::Probe(mCurrentJarEntry)->GetSize(&size);
            Int32 entrySize = (Int32) size;
            mVerStream = NULL;
            CByteArrayOutputStream::New(entrySize > 0 ? entrySize : 8192, (IOutputStream**)&mVerStream);
        }
        else {
            AutoPtr<JarVerifier::VerifierEntry> ve;
            FAIL_RETURN(mVerifier->InitEntry(name, (JarVerifier::VerifierEntry**)&ve));
            mVerStream = ve.Get();
        }
    }

    mVerified = FALSE;
    *entry = IZipEntry::Probe(mCurrentJarEntry);
    REFCOUNT_ADD(*entry)
    return NOERROR;
}


} // namespace Jar
} // namespace Utility
} // namespace Elastos
