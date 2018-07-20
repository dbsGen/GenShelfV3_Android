//
// Created by mac on 2017/8/27.
//

#ifndef GSAV2_0_HISTORY_H
#define GSAV2_0_HISTORY_H


#include <utils/database/Model.h>
#include "Book.h"

#include "../nl_define.h"

using namespace gr;

namespace nl {
    CLASS_BEGIN_TN(History, Model, 1, History)

        DEFINE_STRING(content, Content)
        DEFINE_FIELD(long long, date, Date)
        DEFINE_STRING(url, Url)

    public:
        _FORCE_INLINE_ History() {}
        static void registerFields() {
            Model<History>::registerFields();
            ADD_FILED(History, content, Content, false);
            ADD_FILED(History, date, Date, true);
            ADD_FILED(History, url, Url, true);
        }

        Ref<Book> getBook() const;

        static void visit(const Ref<Book> &book);
        static Array histories(long long from);
        static void clear();

        ON_LOADED_BEGIN(cls, Model<History>)
            ADD_PROPERTY(cls, "date", ADD_METHOD(cls, History, getDate), ADD_METHOD(cls, History, setDate));
            ADD_PROPERTY(cls, "content", ADD_METHOD(cls, History, getContent), ADD_METHOD(cls, History, setContent));
            ADD_PROPERTY(cls, "url", ADD_METHOD(cls, History, getUrl), ADD_METHOD(cls, History, setUrl));
            ADD_METHOD(cls, History, visit);
            ADD_METHOD(cls, History, histories);
            ADD_METHOD(cls, History, clear);
            ADD_METHOD(cls, History, getBook);
        ON_LOADED_END

    CLASS_END
}


#endif //GSAV2_0_HISTORY_H
