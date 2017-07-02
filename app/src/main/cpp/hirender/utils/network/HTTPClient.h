//
//  HTTPClient.hpp
//  hirender_iOS
//
//  Created by mac on 2017/4/11.
//  Copyright © 2017年 gen. All rights reserved.
//

#ifndef HTTPClient_hpp
#define HTTPClient_hpp

#include <core/Object.h>
#include <core/Action.h>
#include <core/Callback.h>
#include "../../render_define.h"

using namespace hicore;

namespace hirender {
    CLASS_BEGIN_N(HTTPClient, RefObject)

        string url;
        string path;
        StringName method;
        string error;
        pointer_map properties;
        float percent;
        bool read_cache;
        float delay;
        int retry_count;
        int retry_num;
        map<string, string> headers;
        map<string, Variant> parameters;

        RefCallback on_complete;
        RefCallback on_progress;

        void _initialize();
        void _finalize();

    public:
        static const StringName METHOD_GET;
        static const StringName METHOD_POST;
        static const StringName METHOD_PUT;
        static const StringName METHOD_DELETE;

        void event(const StringName &name, void *data);

        HTTPClient();
        ~HTTPClient();
        METHOD _FORCE_INLINE_ void initialize(const string &url) {
            this->url = url;
            _initialize();
        }
        METHOD _FORCE_INLINE_ const string &getError() {
            return error;
        }

        METHOD _FORCE_INLINE_ float getPercent() const {
            return percent;
        }

        /**
         * @params (HTTPClient *c, const string &path)  
         * @return NULL;
         */
        METHOD _FORCE_INLINE_ void setOnComplete(const RefCallback &callback) {
            on_complete = callback;
        }
        METHOD _FORCE_INLINE_ const RefCallback &getOnComplete() const {
            return on_complete;
        }
        PROPERTY(on_complete, getOnComplete, setOnComplete);
        METHOD _FORCE_INLINE_ void setOnProgress(const RefCallback &callback) {
            on_progress = callback;
        }
        METHOD _FORCE_INLINE_ const RefCallback &getOnProgress() const {
            return on_progress;
        }
        PROPERTY(on_progress, getOnProgress, setOnProgress)
        METHOD _FORCE_INLINE_ const string &getPath() const {
            return path;
        }
        PROPERTY(path, getPath, NULL);
        METHOD _FORCE_INLINE_ void setReadCache(bool read_cache) {
            this->read_cache = read_cache;
        }
        METHOD _FORCE_INLINE_ bool getReadCache() const {
            return read_cache;
        }
        PROPERTY(read_cache, getReadCache, setReadCache);
        METHOD _FORCE_INLINE_ void setDelay(float delay) {
            this->delay = delay;
        }
        METHOD _FORCE_INLINE_ float getDelay() const {
            return delay;
        }
        PROPERTY(delay, getDelay, setDelay);

        METHOD _FORCE_INLINE_ void setRetryCount(int count) {
            retry_count = count;
        }
        METHOD _FORCE_INLINE_ int getRetryCount() const {
            return retry_count;
        }
        PROPERTY(retry_count, getRetryCount, setRetryCount);

        METHOD _FORCE_INLINE_ void setMethod(const StringName &method) {
            this->method = method;
        }
        METHOD _FORCE_INLINE_ const StringName &getMethod() const {
            return method;
        }
        PROPERTY(method, getMethod, setMethod);

        METHOD _FORCE_INLINE_ void addHeader(const string &name, const string &val) {
            headers[name] = val;
        }
        METHOD _FORCE_INLINE_ void removeHeader(const string &name) {
            headers.erase(name);
        }

        METHOD _FORCE_INLINE_ void addParameter(const string &name, const Variant &val) {
            parameters[name] = val;
        }
        METHOD _FORCE_INLINE_ void removeParameter(const string &name) {
            parameters.erase(name);
        }

        METHOD void start();
        METHOD void cancel();

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_PROPERTY(cls, "on_complete", ADD_METHOD(cls, HTTPClient, getOnComplete), ADD_METHOD(cls, HTTPClient, setOnComplete));
            ADD_PROPERTY(cls, "on_progress", ADD_METHOD(cls, HTTPClient, getOnProgress), ADD_METHOD(cls, HTTPClient, setOnProgress));
            ADD_PROPERTY(cls, "path", ADD_METHOD(cls, HTTPClient, getPath), NULL);
            ADD_PROPERTY(cls, "read_cache", ADD_METHOD(cls, HTTPClient, getReadCache), ADD_METHOD(cls, HTTPClient, setReadCache));
            ADD_PROPERTY(cls, "delay", ADD_METHOD(cls, HTTPClient, getDelay), ADD_METHOD(cls, HTTPClient, setDelay));
            ADD_PROPERTY(cls, "retry_count", ADD_METHOD(cls, HTTPClient, getRetryCount), ADD_METHOD(cls, HTTPClient, setRetryCount));
            ADD_PROPERTY(cls, "method", ADD_METHOD(cls, HTTPClient, getMethod), ADD_METHOD(cls, HTTPClient, setMethod));
            ADD_METHOD(cls, HTTPClient, initialize);
            ADD_METHOD(cls, HTTPClient, getError);
            ADD_METHOD(cls, HTTPClient, getPercent);
            ADD_METHOD(cls, HTTPClient, addHeader);
            ADD_METHOD(cls, HTTPClient, removeHeader);
            ADD_METHOD(cls, HTTPClient, addParameter);
            ADD_METHOD(cls, HTTPClient, removeParameter);
            ADD_METHOD(cls, HTTPClient, start);
            ADD_METHOD(cls, HTTPClient, cancel);
        ON_LOADED_END
    CLASS_END
}

#endif /* HTTPClient_hpp */
