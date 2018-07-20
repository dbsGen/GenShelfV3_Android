//
// Created by mac on 2017/7/10.
//

#ifndef GSAV2_0_KEYVALUE_H
#define GSAV2_0_KEYVALUE_H

#include <utils/database/Model.h>
#include "../nl_define.h"

using namespace gr;

namespace nl {
    CLASS_BEGIN_TN(KeyValue, Model, 1, KeyValue)

        static map<string, Ref<KeyValue> > caches;

        static void pushCache(const string &key, const Ref<KeyValue> &kv);

        DEFINE_STRING(key, Key);
        DEFINE_STRING(value, Value);

    public:

        METHOD static string get(const string &key);
        METHOD static void set(const string &key, const string &value);
        METHOD static Array search(const string &key);

        static void registerFields() {
            Model<KeyValue>::registerFields();
            ADD_FILED(KeyValue, key, Key, true);
            ADD_FILED(KeyValue, value, Value, true);
        }

    protected:

        ON_LOADED_BEGIN(cls, Model<KeyValue>)
            ADD_PROPERTY(cls, "key", ADD_METHOD(cls, KeyValue, getKey), ADD_METHOD(cls, KeyValue, setKey));
            ADD_METHOD(cls, KeyValue, get);
            ADD_METHOD(cls, KeyValue, set);
            ADD_METHOD(cls, KeyValue, search);
        ON_LOADED_END

    CLASS_END
}


#endif //GSAV2_0_KEYVALUE_H
