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

#include "CXPathConstants.h"
#include "CQName.h"
#include "coredef.h"

using Elastosx::Xml::Namespace::CQName;

namespace Elastosx {
namespace Xml {
namespace XPath {

static AutoPtr<IQName> initNUMBER()
{
    AutoPtr<IQName> cq;
    CQName::New(String("http://www.w3.org/1999/XSL/Transform"), String("NUMBER"), (IQName**)&cq);
    return cq;
}

static AutoPtr<IQName> initSTRING()
{
    AutoPtr<IQName> cq;
    CQName::New(String("http://www.w3.org/1999/XSL/Transform"), String("STRING"), (IQName**)&cq);
    return cq;
}

static AutoPtr<IQName> initBOOLEAN()
{
    AutoPtr<IQName> cq;
    CQName::New(String("http://www.w3.org/1999/XSL/Transform"), String("BOOLEAN"), (IQName**)&cq);
    return cq;
}

static AutoPtr<IQName> initNODESET()
{
    AutoPtr<IQName> cq;
    CQName::New(String("http://www.w3.org/1999/XSL/Transform"), String("NODESET"), (IQName**)&cq);
    return cq;
}

static AutoPtr<IQName> initNODE()
{
    AutoPtr<IQName> cq;
    CQName::New(String("http://www.w3.org/1999/XSL/Transform"), String("NODE"), (IQName**)&cq);
    return cq;
}

const AutoPtr<IQName> CXPathConstants::NUMBER = initNUMBER();
const AutoPtr<IQName> CXPathConstants::STRING = initSTRING();
const AutoPtr<IQName> CXPathConstants::BOOLEAN = initBOOLEAN();
const AutoPtr<IQName> CXPathConstants::NODESET = initNODESET();
const AutoPtr<IQName> CXPathConstants::NODE = initNODE();

CAR_INTERFACE_IMPL(CXPathConstants, Object, IXPathConstants)

CAR_OBJECT_IMPL(CXPathConstants)

ECode CXPathConstants::GetQNameNUMBER(
    /* [out] */ IQName** qName)
{
    VALIDATE_NOT_NULL(qName)
    *qName = NUMBER;
    REFCOUNT_ADD(*qName);
    return NOERROR;
}

ECode CXPathConstants::GetQNameSTRING(
    /* [out] */ IQName** qName)
{
    VALIDATE_NOT_NULL(qName)
    *qName = STRING;
    REFCOUNT_ADD(*qName);
    return NOERROR;
}

ECode CXPathConstants::GetQNameBOOLEAN(
    /* [out] */ IQName** qName)
{
    VALIDATE_NOT_NULL(qName)
    *qName = BOOLEAN;
    REFCOUNT_ADD(*qName);
    return NOERROR;
}

ECode CXPathConstants::GetQNameNODESET(
    /* [out] */ IQName** qName)
{
    VALIDATE_NOT_NULL(qName)
    *qName = NODESET;
    REFCOUNT_ADD(*qName);
    return NOERROR;
}

ECode CXPathConstants::GetQNameNODE(
    /* [out] */ IQName** qName)
{
    VALIDATE_NOT_NULL(qName)
    *qName = NODE;
    REFCOUNT_ADD(*qName);
    return NOERROR;
}

}// namespace XPath
}// namespace Xml
}// namespace Elastosx

