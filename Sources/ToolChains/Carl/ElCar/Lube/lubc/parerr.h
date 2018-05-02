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

#ifndef __PARERR_H__
#define __PARERR_H__

typedef enum LubeErrorNo {
    Lube_NoError = 0,

    // Warnings
    Lube_WarningStart        = 0x0001,

    // Errors
    Lube_ErrorStart          = 0x0100,
    Lube_E_UnexpectEOF,
    Lube_E_UnexpectSymbol,
    Lube_E_SymbolTooLong,
    Lube_E_BufOverflow,
    Lube_E_ExpectSymbol,
    Lube_E_OutOfMemory,
    Lube_E_NotFound,
    Lube_E_UndefinedSymbol,
    Lube_E_OpenFile,
    Lube_E_InvalidInput,
    Lube_E_InvalidWithObj,
    Lube_E_NoValidObject,
    Lube_E_IllegalAll,
    Lube_E_InvalidMember,
    Lube_E_UndefFunc,
    Lube_E_InvalidFuncArg,
    Lube_E_MultiElse,
    Lube_E_HasNoOrder,
    Lube_E_InvalidCondMem,
    Lube_E_HasNoAttrib,
    Lube_E_HasNoType,
    Lube_E_InvalidEmbed,
} LubeErrorNo;

extern void ErrorReport(/* LubeErrorNo */ int, ...);
extern void ErrorReporterInit(const char *);
extern void ErrorStringFix(const char *, const char *);
extern void * SaveErrorContext();
extern void RestoreErrorContext(void *);

extern int g_nErrorNumber;
extern int g_nWarningNumber;

#endif // __PARERR_H__
