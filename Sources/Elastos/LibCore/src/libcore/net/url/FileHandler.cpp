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

#include "libcore/net/url/FileHandler.h"
#include "elastos/net/CURL.h"
#include "libcore/net/url/CFileURLConnection.h"

using Elastos::Net::CURL;

namespace Libcore {
namespace Net {
namespace Url {

CAR_INTERFACE_IMPL(FileHandler, URLStreamHandler, IFileHandler)

ECode FileHandler::constructor()
{
    return NOERROR;
}

ECode FileHandler::OpenConnection(
    /* [in] */ IURL* u,
    /* [out] */ IURLConnection** urlConnection)
{
    return OpenConnection(u, NULL, urlConnection);
}

ECode FileHandler::OpenConnection(
    /* [in] */ IURL* u,
    /* [in] */ Elastos::Net::IProxy* proxy,
    /* [out] */ IURLConnection** urlConnection)
{
    VALIDATE_NOT_NULL(urlConnection)

    if (u == NULL) {
        // throw new IllegalArgumentException("url == null");
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }

    String host;
    u->GetHost(&host);
    if (host.IsNull() || host.IsEmpty() || host.EqualsIgnoreCase("localhost")) {
        AutoPtr<IFileURLConnection> furl;
        CFileURLConnection::New(u, (IFileURLConnection**)&furl);
        *urlConnection = IURLConnection::Probe(furl);
        REFCOUNT_ADD(*urlConnection)
        return NOERROR;
    }

    // If a hostname is specified try to get the resource using FTP
    String filename;
    AutoPtr<IURL> ftpURL;
    FAIL_RETURN(CURL::New(String("ftp"), host, (u->GetFile(&filename), filename), (IURL**)&ftpURL));
    AutoPtr<IURLConnection> outurl;
    *urlConnection = (proxy == NULL)
                    ? (ftpURL->OpenConnection((IURLConnection**)&outurl), outurl)
                    : (ftpURL->OpenConnection(proxy, (IURLConnection**)&outurl), outurl);
    REFCOUNT_ADD(*urlConnection)

    return NOERROR;
}

ECode FileHandler::ParseURL(
    /* [in] */ IURL* url,
    /* [in] */ const String& spec,
    /* [in] */ Int32 start,
    /* [in] */ Int32 end)
{
    if (end < start) {
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }
    String parseString = String("");
    if (start < end) {
        parseString = spec.Substring(start, end).Replace('\\', '/');
    }
    return URLStreamHandler::ParseURL(url, parseString, 0, parseString.GetLength());
}

} // namespace Url
} // namespace Net
} // namespace Libcore
