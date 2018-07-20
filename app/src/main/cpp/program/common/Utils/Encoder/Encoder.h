//
//  URLCoder.hpp
//  GenS
//
//  Created by gen on 29/06/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#ifndef URLCoder_hpp
#define URLCoder_hpp

#include <core/Object.h>
#include <core/Data.h>
#include "../../nl_define.h"

using namespace gcore;
namespace nl {
    CLASS_BEGIN_0_NV(Encoder)
    
    public:
        // url 编码默认用utf-8编码，urlEncodeWithEncoding来选择编码例如:"gbk"
        METHOD static string urlEncode(const char *);
        METHOD static string urlEncodeWithEncoding(const char *, const char *encoding);
    
        // 字符串编码(encoding -> utf-8)
        METHOD static Ref<Data> decode(const Ref<Data> &data, const char *encoding);
    
    protected:
        ON_LOADED_BEGIN(cls, HObject)
            ADD_METHOD(cls, Encoder, urlEncode);
            ADD_METHOD(cls, Encoder, urlEncodeWithEncoding);
            ADD_METHOD(cls, Encoder, decode);
        ON_LOADED_END
    CLASS_END
}

#endif /* URLCoder_hpp */
