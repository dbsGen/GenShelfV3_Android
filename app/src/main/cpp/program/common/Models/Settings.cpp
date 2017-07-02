//
//  Settings.cpp
//  GenS
//
//  Created by mac on 2017/5/21.
//  Copyright © 2017年 gen. All rights reserved.
//

#include "Settings.h"
#include <core/Data.h>
#include <core/String.h>
#include <utils/json/libjson.h>

using namespace nl;
using namespace hicore;

const Variant &SettingItem::getValue() {
    if (!value.empty()) {
        return value;
    }
    return default_value;
}

void Settings::removeItem(const Ref<nl::SettingItem> &item) {
    auto it = items.begin();
    while (it != items.end()) {
        if (*it == item) {
            it = items.erase(it);
        }else ++it;
    }
}

Variant Settings::parseJson(void *node) {
    Variant ret;
    switch (json_type(node)) {
        case JSON_ARRAY:{
            variant_vector vs;
            for (int i = 0, t = json_size(node); i < t; ++i) {
                vs.push_back(parseJson(json_at(node, i)));
            }
            ret = RefArray(vs);
            break;
        }
        case JSON_STRING: {
            char *str = json_as_string(node);
            ret = str;
            json_free(str);
            break;
        }
        case JSON_NUMBER: {
            ret = json_as_float(node);
            break;
        }
        case JSON_BOOL: {
            ret = json_as_bool(node);
            break;
        }
            
        default:
            break;
    }
    return ret;
}

void Settings::parse(const char *path) {
    Ref<Data> data(new FileData(path));
    JSONNODE *json = json_parse(data->text());
    if (json) {
        items.clear();
        size_t size = json_size(json);
        for (int i = 0; i < size; ++i) {
            JSONNODE *node = json_at(json, i);
            JSONNODE *name_node = json_get(node, "name");
            if (name_node) {
                Ref<SettingItem> item(new SettingItem);
                char *str = json_as_string(name_node);
                item->setName(str);
                json_free(str);
                
                JSONNODE *type_node = json_get(node, "type");
                if (type_node) {
                    char *str = json_as_string(type_node);
                    if (strcmp(str, "option") == 0) {
                        item->setType(SettingItem::Option);
                    }else if (strcmp(str, "input") == 0) {
                        item->setType(SettingItem::Input);
                    }else if (strcmp(str, "mark") == 0) {
                        item->setType(SettingItem::Mark);
                    }else if (strcmp(str, "password") == 0) {
                        item->setType(SettingItem::Password);
                    }else if (strcmp(str, "divider") == 0) {
                        item->setType(SettingItem::Divider);
                    }
                    json_free(str);
                }
                
                JSONNODE *param_node = json_get(node, "param");
                if (param_node) {
                    item->setParams(parseJson(param_node));
                }
                
                JSONNODE *default_node = json_get(node, "default");
                if (default_node) {
                    item->setDefaultValue(parseJson(default_node));
                }
                items.push_back(item);
            }
        }
        json_delete(json);
    }
}

const Ref<SettingItem> &Settings::findItem(const string &name) const {
    for (auto it = items.begin(), _e = items.end(); it != _e; ++it) {
        if ((*it)->getName() == name) {
            return *it;
        }
    }
    return Ref<SettingItem>::null();
}

void Settings::save() const {
    if (!path.empty()) {
        JSONNODE *node = json_new(JSON_NODE);
        JSONNODE_ITERATOR _it = json_begin(node);
        for (auto it = items.begin(), _e = items.end(); it != _e; ++it) {
            const Ref<SettingItem> &item = (*it);
            const Variant &var = item->getValue();
            if (!var.empty()) {
                switch (item->getType()) {
                    case SettingItem::Mark:
                    case SettingItem::Switch:
                        _it = json_insert(node, _it, json_new_b(item->getName().c_str(), var));
                        break;
                    case SettingItem::Input:
                        if (var.getType() == String::getClass())
                            _it = json_insert(node, _it, json_new_a(item->getName().c_str(), var));
                        break;
                    case SettingItem::Password:
                        if (var.getType() == String::getClass()) {
                            const char *content = var;
                            char *str = json_encode64(content, strlen(content));
                            _it = json_insert(node, _it, json_new_a(item->getName().c_str(), str));
                            json_free(str);
                        }
                        break;
                    case SettingItem::Option:
                        _it = json_insert(node, _it, json_new_i(item->getName().c_str(), var));
                        break;
                    default:
                        break;
                }
            }
        }
        char *str = json_write(node);
        FILE *f = fopen(path.c_str(), "wb");
        fwrite(str, strlen(str), 1, f);
        fclose(f);
        json_free(str);
        json_delete(node);
    }else {
        LOG(w, "Path is empty, save failed!");
    }
}

void Settings::load(const string &path) {
    this->path = path;
    Ref<Data> data(new FileData(path));
    if (data) {
        JSONNODE *node = json_parse(data->text());
        if (node) {
            for (JSONNODE_ITERATOR it = json_begin(node), end = json_end(node); it != end; ++it) {
                JSONNODE *child = *it;
                char *name = json_name(child);
                const Ref<SettingItem> &item = findItem(name);
                if (item) {
                    switch (item->getType()) {
                        case SettingItem::Mark:
                        case SettingItem::Switch:
                        {
                            item->setValue(json_as_bool(child));
                            break;
                        }
                        case SettingItem::Input:
                        {
                            char *str = json_as_string(child);
                            item->setValue(str);
                            json_free(str);
                            break;
                        }
                        case SettingItem::Password:
                        {
                            char *str = json_as_string(child);
                            unsigned long size = strlen(str);
                            char *_decode = (char *)json_decode64(str, &size);
                            string str1;
                            str1.resize(size);
                            memcpy(&str1[0], _decode, size);
                            item->setValue(str1);
                            json_free(_decode);
                            json_free(str);
                            break;
                        }
                        case SettingItem::Option:
                        {
                            item->setValue(json_as_int(child));
                            break;
                        }
                            
                        default:
                            break;
                    }
                }
                json_free(name);
            }
            json_delete(node);
        }
        
    }
}

