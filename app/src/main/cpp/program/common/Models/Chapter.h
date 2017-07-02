//
//  Chapter.hpp
//  GenS
//
//  Created by mac on 2017/5/17.
//  Copyright © 2017年 gen. All rights reserved.
//

#ifndef Chapter_hpp
#define Chapter_hpp

#include <core/Ref.h>
#include "Page.h"
#include "../nl_define.h"

using namespace hicore;

namespace nl {
    CLASS_BEGIN_N(Chapter, RefObject)
    public:
        enum Status {
            None,
            Downloading,
            Pause,
            Complete
        };
        static const char *DATA_FILE;

    private:

        string name;
        string url;
        int index;
        Status status;
        StringName shop_id;

        RefArray pages;
        int picture_loaded;

    public:
        Chapter() : status(None) {}

        METHOD _FORCE_INLINE_ void setName(const string &name) {
            this->name = name;
        }
        METHOD _FORCE_INLINE_ const string &getName() {
            return name;
        }
        PROPERTY(name, getName, setName)
        METHOD _FORCE_INLINE_ void setUrl(const string &url) {
            this->url = url;
        }
        METHOD _FORCE_INLINE_ const string &getUrl() {
            return url;
        }
        PROPERTY(url, getUrl, setUrl)

        METHOD _FORCE_INLINE_ const RefArray &getPages() {
            return pages;
        }
        METHOD _FORCE_INLINE_ void setPages(const RefArray &pages) {
            this->pages = pages;
        }
        PROPERTY(pages, getPages, setPages);

        METHOD _FORCE_INLINE_ const StringName &getShopId() {
            return shop_id;
        }

        METHOD _FORCE_INLINE_ void setShopId(const StringName &shop_id) {
            this->shop_id = shop_id;
        }
        PROPERTY(shop_id, getShopId, setShopId);

        _FORCE_INLINE_ void setStatus(Status status) {
            this->status = status;
        }
        _FORCE_INLINE_ Status getStatus() {
            return status;
        }

        METHOD float downloadPercent();
        METHOD int downloadStatus();
        METHOD int pageStatus(int index);
        METHOD int oldDownloaded();
        METHOD void bringFirst(int index);

        void saveConfig(const string &path);

        static Chapter *parse(const string &path);

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_PROPERTY(cls, "name", ADD_METHOD(cls, Chapter, getName), ADD_METHOD(cls, Chapter, setName));
            ADD_PROPERTY(cls, "url", ADD_METHOD(cls, Chapter, getUrl), ADD_METHOD(cls, Chapter, setUrl));
            ADD_PROPERTY(cls, "pages", ADD_METHOD(cls, Chapter, getPages), ADD_METHOD(cls, Chapter, setPages));
            ADD_PROPERTY(cls, "shop_id", ADD_METHOD(cls, Chapter, getShopId), ADD_METHOD(cls, Chapter, setShopId));
            ADD_METHOD(cls, Chapter, downloadPercent);
            ADD_METHOD(cls, Chapter, downloadStatus);
            ADD_METHOD(cls, Chapter, pageStatus);
            ADD_METHOD(cls, Chapter, oldDownloaded);
            ADD_METHOD(cls, Chapter, bringFirst);
        ON_LOADED_END
    CLASS_END
}

#endif /* Chapter_hpp */
