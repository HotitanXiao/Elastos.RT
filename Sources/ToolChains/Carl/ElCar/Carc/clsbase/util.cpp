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

#include <ctype.h>
#ifndef _apple
#ifdef _linux
#include <sys/io.h>
#else
#include <io.h>
#endif
#endif
#include <unistd.h>

#include "clsbase.h"

#ifndef _win32
#define _access access
#endif

void GetNakedFileName(const char *pszSource, char *pszDest)
{
    int n;

    while (isspace(*pszSource)) pszSource++;

    n = strlen(pszSource) - 1;
    while (n >= 0) {
        if (IS_PATH_SEPARATOR(*(pszSource + n)) || *(pszSource + n) == ':') break;
        n--;
    }
    pszSource += n + 1;

    strcpy(pszDest, pszSource);
    n = strlen(pszDest) - 1;
    while (n >= 0) {
        if ('.' == *(pszDest + n)) {
            *(pszDest + n) = '\0';
            return;
        }
        n--;
    }
}

void GetNakedFileType(const char *pszSource, char *pszDest)
{
    int n = strlen(pszSource) - 1;

    while (n >= 0) {
        if ('.' == *(pszSource + n)) {
            strcpy(pszDest, pszSource + n + 1);
            return;
        }
        n--;
    }
    *pszDest = 0;
}

int SearchFileFromPath(
    const char *pszPath, const char *pszFile, char *pszResult)
{
    int n;

    if (0 == _access(pszFile, 0)) {
        strcpy(pszResult, pszFile);
        _ReturnOK (CLS_NoError);
    }

    while (0 != *pszPath) {
        n = 0;
        while (':' != *pszPath && 0 != *pszPath) {
            pszResult[n++] = *pszPath++;
        }
        if (n > 0) {
            if (!IS_PATH_SEPARATOR(pszResult[n - 1])) pszResult[n++] = '/';
            strcpy(pszResult + n, pszFile);
            if (0 == _access(pszResult, 0)) _ReturnOK (CLS_NoError);
        }

        while (':' == *pszPath) pszPath++;
    }
    pszResult[0] = 0;

    ExtraMessage(pszFile);
    _ReturnError (CLSError_NotFound);
}
