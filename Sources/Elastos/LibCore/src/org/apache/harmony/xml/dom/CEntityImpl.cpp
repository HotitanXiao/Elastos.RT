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

#include "org/apache/harmony/xml/dom/CEntityImpl.h"
#include "org/apache/harmony/xml/dom/CDocumentImpl.h"
#include <elastos/utility/logging/Logger.h>

using Org::W3c::Dom::EIID_IEntity;
using Org::W3c::Dom::INode;
using Elastos::Utility::Logging::Logger;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Xml {
namespace Dom {

CAR_OBJECT_IMPL(CEntityImpl)
CAR_INTERFACE_IMPL(CEntityImpl, NodeImpl, IEntity);

ECode CEntityImpl::constructor(
    /* [in] */ IDocument* document,
    /* [in] */ const String& notationName,
    /* [in] */ const String& publicID,
    /* [in] */ const String& systemID)
{
    NodeImpl::constructor(document);
    this->notationName = notationName;
    this->publicID = publicID;
    this->systemID = systemID;
    return NOERROR;
}

ECode CEntityImpl::GetNodeName(
    /* [out] */ String * pStr)
{
    return GetNotationName(pStr);
}

ECode CEntityImpl::GetNodeType(
    /* [out] */ Int16 * pValue)
{
    VALIDATE_NOT_NULL(pValue);
    *pValue = INode::ENTITY_NODE;
    return NOERROR;
}

ECode CEntityImpl::GetNotationName(
    /* [out] */ String * pStr)
{
    VALIDATE_NOT_NULL(pStr);
    *pStr = notationName;
    return NOERROR;
}

ECode CEntityImpl::GetPublicId(
    /* [out] */ String * pStr)
{
    VALIDATE_NOT_NULL(pStr);
    *pStr = publicID;
    return NOERROR;
}

ECode CEntityImpl::GetSystemId(
    /* [out] */ String * pStr)
{
    VALIDATE_NOT_NULL(pStr);
    *pStr = systemID;
    return NOERROR;
}

ECode CEntityImpl::GetInputEncoding(
    /* [out] */ String * pStr)
{
    Logger::E("CEntityImpl", "GetInputEncoding");
    assert(0);
    return E_UNSUPPORTED_OPERATION_EXCEPTION;
}

ECode CEntityImpl::GetXmlEncoding(
    /* [out] */ String * pStr)
{
    Logger::E("CEntityImpl", "GetXmlEncoding");
    assert(0);
    return E_UNSUPPORTED_OPERATION_EXCEPTION;
}

ECode CEntityImpl::GetXmlVersion(
    /* [out] */ String * pStr)
{
    Logger::E("CEntityImpl", "GetXmlVersion");
    assert(0);
    return E_UNSUPPORTED_OPERATION_EXCEPTION;
}

//ECode CEntityImpl::GetNodeValue(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::SetNodeValue(
//    /* [in] */ const String& nodeValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetParentNode(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetChildNodes(
//    /* [out] */ Org::W3c::Dom::INodeList ** ppNodelist)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetFirstChild(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetLastChild(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetPreviousSibling(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetNextSibling(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetAttributes(
//    /* [out] */ Org::W3c::Dom::INamedNodeMap ** ppNodemap)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetOwnerDocument(
//    /* [out] */ Org::W3c::Dom::IDocument ** ppDoc)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::InsertBefore(
//    /* [in] */ Org::W3c::Dom::INode * pNewChild,
//    /* [in] */ Org::W3c::Dom::INode * pRefChild,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::ReplaceChild(
//    /* [in] */ Org::W3c::Dom::INode * pNewChild,
//    /* [in] */ Org::W3c::Dom::INode * pOldChild,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::RemoveChild(
//    /* [in] */ Org::W3c::Dom::INode * pOldChild,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::AppendChild(
//    /* [in] */ Org::W3c::Dom::INode * pNewChild,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::HasChildNodes(
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::CloneNode(
//    /* [in] */ Boolean deep,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::Normalize()
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::IsSupported(
//    /* [in] */ const String& feature,
//    /* [in] */ const String& ver,
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetNamespaceURI(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetPrefix(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::SetPrefix(
//    /* [in] */ const String& prefix)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetLocalName(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::HasAttributes(
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetBaseURI(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::CompareDocumentPosition(
//    /* [in] */ Org::W3c::Dom::INode * pOther,
//    /* [out] */ Int16 * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetTextContent(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::SetTextContent(
//    /* [in] */ const String& textContent)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::IsSameNode(
//    /* [in] */ Org::W3c::Dom::INode * pOther,
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::LookupPrefix(
//    /* [in] */ const String& namespaceURI,
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::IsDefaultNamespace(
//    /* [in] */ const String& namespaceURI,
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::LookupNamespaceURI(
//    /* [in] */ const String& prefix,
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::IsEqualNode(
//    /* [in] */ Org::W3c::Dom::INode * pArg,
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetFeature(
//    /* [in] */ const String& feature,
//    /* [in] */ const String& ver,
//    /* [out] */ IObject ** ppObj)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::SetUserData(
//    /* [in] */ const String& key,
//    /* [in] */ IObject * pData,
//    /* [in] */ Org::W3c::Dom::IUserDataHandler * pHandler,
//    /* [out] */ IObject ** ppObj)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CEntityImpl::GetUserData(
//    /* [in] */ const String& key,
//    /* [out] */ IObject ** ppObj)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}

}
}
}
}
}

