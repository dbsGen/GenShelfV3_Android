//
//  Page.cpp
//  GenS
//
//  Created by gen on 18/05/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#include "Page.h"

using namespace nl;

Ref<hirender::HTTPClient> Page::makeClient() const {
    hirender::HTTPClient *client = new_t(hirender::HTTPClient, getPicture());
    client->setMethod(getMethod());
    const RefMap &headers = getHeaders();
    for (auto it = headers->begin(), _e = headers->end(); it != _e; ++it) {
        client->addHeader(it->first, it->second);
    }
    auto &params = getParameters();
    for (auto it = params->begin(), _e = params->end(); it != _e; ++it) {
        client->addParameter(it->first, it->second);
    }
    return client;
}
