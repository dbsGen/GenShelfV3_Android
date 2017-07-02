//
//  XMLNode.hpp
//  hirender_iOS
//
//  Created by gen on 10/05/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#ifndef XMLNode_hpp
#define XMLNode_hpp

#include <core/Ref.h>
#include <core/Array.h>
#include "../../render_define.h"

using namespace hicore;

struct _xmlNode;
typedef struct _xmlNode xmlNode;
typedef xmlNode *xmlNodePtr;

namespace hirender {
    class XMLDocument;

    typedef int XMLType;

    CLASS_BEGIN_N(XMLNode, RefObject)

        xmlNodePtr c_node;
        XMLDocument *doc;
        RefArray children;

        friend class XMLDocument;

    public:
        XMLNode() : c_node(NULL) {
        }
        ~XMLNode();

        METHOD _FORCE_INLINE_ XMLDocument *getDocument() {
            return doc;
        }
        METHOD long getChildrenCount() const;
        METHOD const RefArray &getChildren();
        METHOD Ref<XMLNode> getChild(int i);
        METHOD Ref<XMLNode> findChild(const char *name, const char *value = NULL);

        METHOD string getAttribute(const char *name) const;
        METHOD void setAttribute(const char *name, const char *value) const;
        METHOD bool hasAttribute(const char *name) const;

        METHOD const char *getName() const;

        METHOD string getContent();
        METHOD RefArray xpath(const char *str) const;
        METHOD XMLType getType() const;
        METHOD string text();

    protected:
        ON_LOADED_BEGIN(cls, HObject)
            ADD_METHOD(cls, XMLNode, getDocument);
            ADD_METHOD(cls, XMLNode, getChildrenCount);
            ADD_METHOD(cls, XMLNode, getChildren);
            ADD_METHOD(cls, XMLNode, getChild);
            ADD_METHOD(cls, XMLNode, findChild);
            ADD_METHOD(cls, XMLNode, getAttribute);
            ADD_METHOD(cls, XMLNode, setAttribute);
            ADD_METHOD(cls, XMLNode, hasAttribute);
            ADD_METHOD(cls, XMLNode, getName);
            ADD_METHOD(cls, XMLNode, getContent);
            ADD_METHOD(cls, XMLNode, getType);
            ADD_METHOD(cls, XMLNode, xpath);
            ADD_METHOD(cls, XMLNode, text);
        ON_LOADED_END
    CLASS_END
}

#endif /* XMLNode_hpp */
