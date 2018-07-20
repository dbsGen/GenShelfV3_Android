//
// Created by mac on 2017/10/11.
//

#ifndef GSAV2_0_SEARCHTIP_H
#define GSAV2_0_SEARCHTIP_H

#include <utils/database/Model.h>
#include "../nl_define.h"

using namespace hirender;

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
        METHOD static RefArray search(const string &key);

    CLASS_END
}


#endif //GSAV2_0_SEARCHTIP_H
