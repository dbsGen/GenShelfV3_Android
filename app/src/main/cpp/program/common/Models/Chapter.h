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

using namespace gcore;

namespace nl {
    class Book;

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

        Array pages;
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

        METHOD _FORCE_INLINE_ const Array &getPages() {
            return pages;
        }
        METHOD _FORCE_INLINE_ void setPages(const Array &pages) {
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
        METHOD int pageCount();
        METHOD int completeCount();
        METHOD void bringFirst(int index);

        METHOD Array cachedPages() const;
        METHOD void cachePages(const Array &pages) const;
        METHOD int lastIndex() const;
        METHOD void setLastIndex(int idx) const;
        METHOD void stopDownload();

        METHOD static void downloadingChapters(const Array &books, const Array &chapters);

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
            ADD_METHOD(cls, Chapter, pageCount);
            ADD_METHOD(cls, Chapter, completeCount);
            ADD_METHOD(cls, Chapter, bringFirst);
            ADD_METHOD(cls, Chapter, cachedPages);
            ADD_METHOD(cls, Chapter, cachePages);
            ADD_METHOD(cls, Chapter, lastIndex);
            ADD_METHOD(cls, Chapter, setLastIndex);
            ADD_METHOD(cls, Chapter, downloadingChapters);
            ADD_METHOD(cls, Chapter, stopDownload);
        ON_LOADED_END
    CLASS_END
}

#endif /* Chapter_hpp */
