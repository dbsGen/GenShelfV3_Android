//
//  Page.hpp
//  GenS
//
//  Created by gen on 18/05/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#ifndef Page_hpp
#define Page_hpp

#include <core/Ref.h>
#include <utils/network/HTTPClient.h>
#include <core/Map.h>
#include <utils/json/libjson.h>
#include "../nl_define.h"

using namespace gcore;

namespace nl {
    CLASS_BEGIN_N(Page, RefObject)

        string picture;
        string url;
        StringName method;
        Map headers;
        Map parameters;
        int status;

    public:
        Page() : status(0), method(gr::HTTPClient::METHOD_GET) {}

        METHOD _FORCE_INLINE_ void setPicture(const string &url) {
            picture = url;
        }
        METHOD _FORCE_INLINE_ const string &getPicture() const {
            return picture;
        }
        PROPERTY(picture, getPicture, setPicture);

        METHOD _FORCE_INLINE_ void setUrl(const string &url) {
            this->url = url;
        }
        METHOD _FORCE_INLINE_ const string &getUrl() const {
            return url;
        }
        PROPERTY(url, getUrl, setUrl);

        METHOD _FORCE_INLINE_ void setMethod(const StringName &method) {
            this->method = method;
        }
        METHOD _FORCE_INLINE_ const StringName &getMethod() const {
            return method;
        }
        PROPERTY(method, getMethod, setMethod);

        METHOD _FORCE_INLINE_ void addHeader(const string &name, const string &val) {
            headers->set(name, val);
        }
        METHOD _FORCE_INLINE_ void removeHeader(const string &name) {
            headers->erase(name);
        }
        METHOD const Map &getHeaders() const {
            return headers;
        }

        METHOD _FORCE_INLINE_ void addParameter(const string &name, const Variant &val) {
            parameters->set(name, val);
        }
        METHOD _FORCE_INLINE_ void removeParameter(const string &name) {
            parameters->erase(name);
        }
        METHOD const Map &getParameters() const {
            return parameters;
        }

        /**
         * 0: processing
         * 1: complete
         * -1: error
         */
        METHOD _FORCE_INLINE_ void setStatus(int s) {
            status = s;
        }
        METHOD _FORCE_INLINE_ int getStatus() {
            return status;
        }
        PROPERTY(status, getStatus, setStatus);

        METHOD Ref<gr::HTTPClient> makeClient() const;

        JSONNODE *unparse() const;
        void parse(JSONNODE *node);

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_PROPERTY(cls, "picture", ADD_METHOD(cls, Page, getPicture), ADD_METHOD(cls, Page, setPicture));
            ADD_PROPERTY(cls, "url", ADD_METHOD(cls, Page, getUrl), ADD_METHOD(cls, Page, setUrl));
            ADD_PROPERTY(cls, "method", ADD_METHOD(cls, Page, getMethod), ADD_METHOD(cls, Page, setMethod));
            ADD_PROPERTY(cls, "status", ADD_METHOD(cls, Page, getStatus), ADD_METHOD(cls, Page, setStatus));
            ADD_METHOD(cls, Page, addHeader);
            ADD_METHOD(cls, Page, removeHeader);
            ADD_METHOD(cls, Page, addParameter);
            ADD_METHOD(cls, Page, removeParameter);
            ADD_METHOD(cls, Page, getHeaders);
            ADD_METHOD(cls, Page, getParameters);
        ON_LOADED_END
    CLASS_END
}

#endif /* Page_hpp */
