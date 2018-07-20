//
// Created by mac on 2018/7/18.
//

#ifndef GSAV2_0_GUMBOPARSER_H
#define GSAV2_0_GUMBOPARSER_H

#include <gumbo-query/Document.h>
#include <gumbo-query/Node.h>
#include <core/Data.h>
#include <core/Ref.h>
#include <core/Array.h>

#include "../nl_define.h"

using namespace hicore;

namespace nl {

    CLASS_BEGIN_N(GBNode, RefObject)
        CNode node;

    public:

        _FORCE_INLINE_ GBNode() {}
        _FORCE_INLINE_ GBNode(CNode node) {
            this->node = node;
        }

        METHOD RefArray css(const char *str);

        METHOD string getAttribute(const char *name);

        METHOD string getContent();
        METHOD string text();
        METHOD long getChildrenCount();
        METHOD Ref<GBNode> getChild(int i);

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_METHOD(cls, GBNode, css);
            ADD_METHOD(cls, GBNode, getAttribute);
            ADD_METHOD(cls, GBNode, getContent);
            ADD_METHOD(cls, GBNode, text);
            ADD_METHOD(cls, GBNode, getChildrenCount);
            ADD_METHOD(cls, GBNode, getChild);
        ON_LOADED_END
    CLASS_END

    CLASS_BEGIN_N(GBDocument, RefObject)

        CDocument doc;

    public:

        METHOD void initialize(const Ref<Data> &data);

        METHOD RefArray css(const char *str);

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_METHOD(cls, GBDocument, css);
        ON_LOADED_END
    CLASS_END
}


#endif //GSAV2_0_GUMBOPARSER_H
