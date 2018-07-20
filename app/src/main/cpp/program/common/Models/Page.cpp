//
//  Page.cpp
//  GenS
//
//  Created by gen on 18/05/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#include "Page.h"
#include <utils/json/libjson.h>

using namespace nl;

Ref<gr::HTTPClient> Page::makeClient() const {
    gr::HTTPClient *client = new_t(gr::HTTPClient, getPicture());
    client->setMethod(getMethod());
    const Map &headers = getHeaders();
    for (auto it = headers->begin(), _e = headers->end(); it != _e; ++it) {
        client->addHeader(it->first, it->second);
    }
    auto &params = getParameters();
    for (auto it = params->begin(), _e = params->end(); it != _e; ++it) {
        client->addParameter(it->first, it->second);
    }
    return client;
}


JSONNODE *Page::unparse() const {
    JSONNODE *node = json_new(JSON_NODE);
    json_push_back(node, json_new_a("url", url.c_str()));
    json_push_back(node, json_new_a("picture", picture.c_str()));
    if (headers->size() > 0) {
        JSONNODE  *hn = json_new(JSON_NODE);
        json_set_name(hn, "headers");
        for (auto it = headers->begin(), _e = headers->end(); it != _e; ++it) {
            json_push_back(hn, json_new_a(it->first.c_str(), (const char*)it->second));
        }
        json_push_back(node, hn);
    }
    return node;
}

void Page::parse(JSONNODE *node) {
    char *str = json_as_string(json_get(node, "url"));
    url = str;
    json_free(str);
    str = json_as_string(json_get(node, "picture"));
    picture = str;
    json_free(str);

    if (json_find(node, "headers") != json_end(node)) {
        JSONNODE *hn = json_get(node, "headers");
        for (JSONNODE_ITERATOR it = json_begin(hn), _e = json_end(hn); it != _e; ++it) {
            char  *name = json_name(*it);
            char *content = json_as_string(*it);
            addHeader(name, content);
            json_free(name);
            json_free(content);
        }
    }
}