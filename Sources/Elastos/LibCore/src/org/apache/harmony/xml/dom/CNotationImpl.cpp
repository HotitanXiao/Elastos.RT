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

#include "org/apache/harmony/xml/dom/CNotationImpl.h"
#include "org/apache/harmony/xml/dom/CDocumentImpl.h"
#include "org/apache/harmony/xml/dom/InnerNodeImpl.h"

using Org::W3c::Dom::EIID_INotation;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Xml {
namespace Dom {

CAR_OBJECT_IMPL(CNotationImpl);
CAR_INTERFACE_IMPL(CNotationImpl, LeafNodeImpl, INotation);

ECode CNotationImpl::constructor(
    /* [in] */ IDocument* document,
    /* [in] */ const String& notationName,
    /* [in] */ const String& publicID,
    /* [in] */ const String& systemID)
{
    LeafNodeImpl::constructor(document);
    return NOERROR;
}

ECode CNotationImpl::GetNodeName(
    /* [out] */ String * pStr)
{
    VALIDATE_NOT_NULL(pStr);
    *pStr = notationName;
    return NOERROR;
}

ECode CNotationImpl::GetNodeType(
    /* [out] */ Int16 * pValue)
{
    VALIDATE_NOT_NULL(pValue);
    *pValue = INode::NOTATION_NODE;
    return NOERROR;
}

ECode CNotationImpl::GetPublicId(
    /* [out] */ String * pStr)
{
    VALIDATE_NOT_NULL(pStr);
    *pStr = publicID;
    return NOERROR;
}

ECode CNotationImpl::GetSystemId(
    /* [out] */ String * pStr)
{
    VALIDATE_NOT_NULL(pStr);
    *pStr = systemID;
    return NOERROR;
}

//ECode CNotationImpl::GetNodeValue(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::SetNodeValue(
//    /* [in] */ const String& nodeValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetParentNode(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetChildNodes(
//    /* [out] */ Org::W3c::Dom::INodeList ** ppNodelist)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetFirstChild(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetLastChild(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetPreviousSibling(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetNextSibling(
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetAttributes(
//    /* [out] */ Org::W3c::Dom::INamedNodeMap ** ppNodemap)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetOwnerDocument(
//    /* [out] */ Org::W3c::Dom::IDocument ** ppDoc)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::InsertBefore(
//    /* [in] */ Org::W3c::Dom::INode * pNewChild,
//    /* [in] */ Org::W3c::Dom::INode * pRefChild,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::ReplaceChild(
//    /* [in] */ Org::W3c::Dom::INode * pNewChild,
//    /* [in] */ Org::W3c::Dom::INode * pOldChild,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::RemoveChild(
//    /* [in] */ Org::W3c::Dom::INode * pOldChild,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::AppendChild(
//    /* [in] */ Org::W3c::Dom::INode * pNewChild,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::HasChildNodes(
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::CloneNode(
//    /* [in] */ Boolean deep,
//    /* [out] */ Org::W3c::Dom::INode ** ppNode)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::Normalize()
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::IsSupported(
//    /* [in] */ const String& feature,
//    /* [in] */ const String& ver,
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetNamespaceURI(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetPrefix(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::SetPrefix(
//    /* [in] */ const String& prefix)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetLocalName(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::HasAttributes(
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetBaseURI(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::CompareDocumentPosition(
//    /* [in] */ Org::W3c::Dom::INode * pOther,
//    /* [out] */ Int16 * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetTextContent(
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::SetTextContent(
//    /* [in] */ const String& textContent)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::IsSameNode(
//    /* [in] */ Org::W3c::Dom::INode * pOther,
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::LookupPrefix(
//    /* [in] */ const String& namespaceURI,
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::IsDefaultNamespace(
//    /* [in] */ const String& namespaceURI,
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::LookupNamespaceURI(
//    /* [in] */ const String& prefix,
//    /* [out] */ String * pStr)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::IsEqualNode(
//    /* [in] */ Org::W3c::Dom::INode * pArg,
//    /* [out] */ Boolean * pValue)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetFeature(
//    /* [in] */ const String& feature,
//    /* [in] */ const String& ver,
//    /* [out] */ IObject ** ppObj)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::SetUserData(
//    /* [in] */ const String& key,
//    /* [in] */ IObject * pData,
//    /* [in] */ Org::W3c::Dom::IUserDataHandler * pHandler,
//    /* [out] */ IObject ** ppObj)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::GetUserData(
//    /* [in] */ const String& key,
//    /* [out] */ IObject ** ppObj)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}
//
//ECode CNotationImpl::IsParentOf(
//    /* [in] */ Org::W3c::Dom::INode * pNode,
//    /* [out] */ Boolean * pIsParentOf)
//{
//    // TODO: Add your code here
//    return E_NOT_IMPLEMENTED;
//}

}
}
}
}
}

