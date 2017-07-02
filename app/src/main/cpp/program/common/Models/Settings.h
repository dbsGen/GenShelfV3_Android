//
//  Settings.hpp
//  GenS
//
//  Created by mac on 2017/5/21.
//  Copyright © 2017年 gen. All rights reserved.
//

#ifndef Settings_hpp
#define Settings_hpp

#include <core/Ref.h>
#include <core/Array.h>
#include "../nl_define.h"

using namespace hicore;

namespace nl {
    CLASS_BEGIN_N(SettingItem, RefObject)
    public:
        enum _ItemType {
            Option = 1,
            Input,
            Mark,
            Switch,
            Password,
            Divider
        };
        typedef int ItemType;
    private:

        string name;
        ItemType type;
        Variant params;
        Variant default_value;
        Variant value;

    public:
        METHOD _FORCE_INLINE_ const string &getName() {
            return name;
        }
        METHOD _FORCE_INLINE_ void setName(const string &name) {
            this->name = name;
        }
        PROPERTY(name, getName, setName);

        METHOD _FORCE_INLINE_ ItemType getType() {
            return type;
        }
        METHOD _FORCE_INLINE_ void setType(ItemType type) {
            this->type = type;
        }
        PROPERTY(type, getType, setType);

        METHOD _FORCE_INLINE_ const Variant &getParams() {
            return params;
        }
        METHOD _FORCE_INLINE_ void setParams(const Variant &params) {
            this->params = params;
        }
        PROPERTY(params, getParams, setParams);

        METHOD _FORCE_INLINE_ const Variant &getDefaultValue() {
            return default_value;
        }
        METHOD _FORCE_INLINE_ void setDefaultValue(const Variant &default_value) {
            this->default_value = default_value;
        }
        PROPERTY(default_value, getDefaultValue, setDefaultValue);

        METHOD const Variant &getValue();
        METHOD _FORCE_INLINE_ void setValue(const Variant &value) {
            this->value = value;
        }
        PROPERTY(value, getValue, setValue);

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_PROPERTY(cls, "name", ADD_METHOD(cls, SettingItem, getName), ADD_METHOD(cls, SettingItem, setName));
            ADD_PROPERTY(cls, "type", ADD_METHOD(cls, SettingItem, getType), ADD_METHOD(cls, SettingItem, setType));
            ADD_PROPERTY(cls, "params", ADD_METHOD(cls, SettingItem, getParams), ADD_METHOD(cls, SettingItem, setParams));
            ADD_PROPERTY(cls, "default_value", ADD_METHOD(cls, SettingItem, getDefaultValue), ADD_METHOD(cls, SettingItem, setDefaultValue));
            ADD_PROPERTY(cls, "value", ADD_METHOD(cls, SettingItem, getValue), ADD_METHOD(cls, SettingItem, setValue));
        ON_LOADED_END
    CLASS_END

    CLASS_BEGIN_N(Settings, RefObject)

        string path;
        vector<Ref<SettingItem> > items;
        Variant parseJson(void *node);

    public:

        METHOD _FORCE_INLINE_ void addItem(const Ref<SettingItem> &item) {
            items.push_back(item);
        }
        METHOD void removeItem(const Ref<SettingItem> &item);
        METHOD _FORCE_INLINE_ int getItemsCount() {
            return items.size();
        }
        METHOD _FORCE_INLINE_ const Ref<SettingItem> &getItem(int idx) {
            return items.size() > idx ? items[idx] : Ref<SettingItem>::null();
        }
        _FORCE_INLINE_ const vector<Ref<SettingItem> > &getItems() {
            return items;
        }
        void load(const string &path);
        METHOD void parse(const char *path);
        METHOD void save() const;

        METHOD const Ref<SettingItem> &findItem(const string &name) const;
        METHOD _FORCE_INLINE_ const Variant &find(const string &name) const {
            return findItem(name)->getValue();
        }

        EVENT(void, process);

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_METHOD(cls, Settings, addItem);
            ADD_METHOD(cls, Settings, removeItem);
            ADD_METHOD(cls, Settings, getItemsCount);
            ADD_METHOD(cls, Settings, getItem);
            ADD_METHOD(cls, Settings, parse);
            ADD_METHOD(cls, Settings, save);
            ADD_METHOD(cls, Settings, findItem);
            ADD_METHOD(cls, Settings, find);
        ON_LOADED_END
    CLASS_END
}

#endif /* Settings_hpp */
