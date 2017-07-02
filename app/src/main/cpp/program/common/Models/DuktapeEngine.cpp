//
//  DuktapeEngine.cpp
//  GenS
//
//  Created by mac on 2017/6/25.
//  Copyright © 2017年 gen. All rights reserved.
//

#include "DuktapeEngine.h"
#include <core/Array.h>
#include <duktape/duktape.h>

using namespace nl;

DuktapeEngine::DuktapeEngine() {
    context = duk_create_heap(NULL, NULL, NULL, NULL,
                              &DuktapeEngine::fatal_handler);
}

DuktapeEngine::~DuktapeEngine() {
    duk_destroy_heap((duk_context*)context);
}

void DuktapeEngine::fatal_handler(void *udata, const char *msg) {
    LOG(w, "error: %s", msg);
}

Variant DuktapeEngine::process(void *context) {
    duk_context *ctx = (duk_context*)context;
    
    Variant ret;
    if (duk_is_string(ctx, -1)) {
        ret = duk_get_string(ctx, -1);
    }else if (duk_is_number(ctx, -1)) {
        ret = duk_get_number(ctx, -1);
    }else if (duk_is_boolean(ctx, -1)) {
        ret = duk_get_boolean(ctx, -1);
    }else if (duk_is_array(ctx, -1)) {
        if (duk_get_prop_string(ctx, -1, "length")) {
            duk_int_t len = duk_get_int(ctx, -1);
            duk_pop(ctx);
            RefArray arr;
            
            for (int i = 0; i < len; ++i) {
                if (duk_get_prop_index(ctx, -1, i)) {
                    arr->push_back(process(context));
                    duk_pop(ctx);
                }
            }
            ret = arr;
        }
    }
    return ret;
}

Variant DuktapeEngine::eval(const char *script) {
    duk_context *ctx = (duk_context*)context;
    duk_eval_string(ctx, script);
    
    Variant ret = process(ctx);
    
    duk_pop(ctx);
    
    return ret;
}

