//
// Created by mac on 2017/10/11.
//

#ifndef GSAV2_0_SEARCHTIP_H
#define GSAV2_0_SEARCHTIP_H

#include <utils/database/Model.h>
#include "../nl_define.h"

using namespace gr;

namespace nl {
    CLASS_BEGIN_TN(SearchTip, Model, 1, SearchTip)

    DEFINE_STRING(key, Key);
    DEFINE_FIELD(long long, date, Date);

    public:
        _FORCE_INLINE_ SearchTip() {}
        static void registerFields() {
            Model<SearchTip>::registerFields();
            ADD_FILED(SearchTip, key, Key, true);
            ADD_FILED(SearchTip, date, Date, true);
        }

        METHOD static void insert(const string &key);
        METHOD static Array search(const string &key);
        METHOD static void removeKey(const string &key);

    protected:
        ON_LOADED_BEGIN(cls, Model<SearchTip>)
            ADD_METHOD(cls, SearchTip, insert);
            ADD_METHOD(cls, SearchTip, search);
            ADD_METHOD(cls, SearchTip, removeKey);
        ON_LOADED_END
    CLASS_END
}


#endif //GSAV2_0_SEARCHTIP_H
