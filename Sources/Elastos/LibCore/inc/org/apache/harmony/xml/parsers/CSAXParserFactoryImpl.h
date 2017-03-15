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

#ifndef __ORG_APACHE_HARMONY_XML_PARSERS_CSAXPARSERFACTORYIMPL_H__
#define __ORG_APACHE_HARMONY_XML_PARSERS_CSAXPARSERFACTORYIMPL_H__

#include "Elastos.CoreLibrary.Utility.h"
#include "_Org_Apache_Harmony_Xml_Parsers_CSAXParserFactoryImpl.h"
#include "elastosx/xml/parsers/SAXParserFactory.h"

using Elastosx::Xml::Parsers::SAXParserFactory;
using Elastos::Utility::IMap;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Xml {
namespace Parsers {

CarClass(CSAXParserFactoryImpl)
    , public SAXParserFactory
{
public:

    CSAXParserFactoryImpl();

    CARAPI NewSAXParser(
        /* [out] */ Elastosx::Xml::Parsers::ISAXParser ** ppParser);

    CARAPI IsNamespaceAware(
        /* [out] */ Boolean * pIsAware);

    CARAPI IsValidating(
        /* [out] */ Boolean * pIsValidating);

    CARAPI SetFeature(
        /* [in] */ const String& name,
        /* [in] */ Boolean value);

    CARAPI GetFeature(
        /* [in] */ const String& name,
        /* [out] */ Boolean * pFeature);

    CARAPI SetNamespaceAware(
        /* [in] */ Boolean awareness);

    CARAPI SetValidating(
        /* [in] */ Boolean validating);

private:
    static const String NAMESPACES;// = "http://xml.org/sax/features/namespaces";
    static const String VALIDATION;// = "http://xml.org/sax/features/validation";
    //Map<String, Boolean> features = new HashMap<String, Boolean>();
    AutoPtr<IMap> features;
};

}
}
}
}
}

#endif // __ORG_APACHE_HARMONY_XML_PARSERS_CSAXPARSERFACTORYIMPL_H__
