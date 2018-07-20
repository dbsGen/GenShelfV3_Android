//
// Created by gen on 26/07/2017.
//

#ifndef GSAV2_0_ARTBASKET_H
#define GSAV2_0_ARTBASKET_H

#include <core/Ref.h>
#include <core/Array.h>
#include <vector>
#include "Book.h"
#include "Chapter.h"
#include "../nl_define.h"

using namespace gcore;
using namespace std;

namespace nl {
    CLASS_BEGIN_N(Art, RefObject)
        int type;
        StringName shop_id;
        string url;
        string chapter_url;
        string name;
        string chapter_name;
        string thumb;
        string thumb_ref;

    public:
        METHOD _FORCE_INLINE_ void setType(int type) {
            this->type = type;
        }
        METHOD _FORCE_INLINE_ int getType() const {
            return type;
        }
        PROPERTY(type, getType, setType)

        METHOD _FORCE_INLINE_ void setShopId(const StringName &shop_id) {
            this->shop_id = shop_id;
        }
        METHOD _FORCE_INLINE_ const StringName &getShopId() const {
            return shop_id;
        }
        PROPERTY(shop_id, getShopId, setShopId)

        METHOD _FORCE_INLINE_ void setUrl(const string &url) {
            this->url = url;
        }
        METHOD _FORCE_INLINE_ const string &getUrl() const {
            return url;
        }
        PROPERTY(url, getUrl, setUrl)

        METHOD _FORCE_INLINE_ void setName(const string &name) {
            this->name = name;
        }
        METHOD _FORCE_INLINE_ const string &getName() const {
            return name;
        }
        PROPERTY(name, getName, setName)

        METHOD _FORCE_INLINE_ void setThumb(const string &thumb) {
            this->thumb = thumb;
        }
        METHOD _FORCE_INLINE_ const string &getThumb() const {
            return thumb;
        }
        PROPERTY(thumb, getThumb, setThumb)

        METHOD _FORCE_INLINE_ void setChapterUrl(const string &chapter_url) {
            this->chapter_url = chapter_url;
        }
        METHOD _FORCE_INLINE_ const string &getChapterUrl() {
            return chapter_url;
        }
        PROPERTY(chapter_url, getChapterUrl, setChapterUrl);

        METHOD _FORCE_INLINE_ void setChapterName(const string &chapter_name) {
            this->chapter_name = chapter_name;
        }
        METHOD _FORCE_INLINE_ const string &getChapterName() const {
            return chapter_name;
        }
        PROPERTY(chapter_name, getChapterName, setChapterName)

        METHOD _FORCE_INLINE_ void setThumbRef(const string &ref) {
            this->thumb_ref = ref;
        }
        METHOD _FORCE_INLINE_ const string &getThumbRef() {
            return thumb_ref;
        }
        PROPERTY(thumb_ref, getThumbRef, setThumbRef)

        METHOD string html();
        METHOD static Array parse(const string &content);

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_PROPERTY(cls, "type", ADD_METHOD(cls, Art, getType), ADD_METHOD(cls, Art, setType));
            ADD_PROPERTY(cls, "shop_id", ADD_METHOD(cls, Art, getShopId), ADD_METHOD(cls, Art, setShopId));
            ADD_PROPERTY(cls, "url", ADD_METHOD(cls, Art, getUrl), ADD_METHOD(cls, Art, setUrl));
            ADD_PROPERTY(cls, "name", ADD_METHOD(cls, Art, getName), ADD_METHOD(cls, Art, setName));
            ADD_PROPERTY(cls, "thumb", ADD_METHOD(cls, Art, getThumb), ADD_METHOD(cls, Art, setThumb));
            ADD_PROPERTY(cls, "chapter_url", ADD_METHOD(cls, Art, getChapterUrl), ADD_METHOD(cls, Art, setChapterUrl));
            ADD_PROPERTY(cls, "chapter_name", ADD_METHOD(cls, Art, getChapterName), ADD_METHOD(cls, Art, setChapterName));
            ADD_PROPERTY(cls, "thumb_ref", ADD_METHOD(cls, Art, getThumbRef), ADD_METHOD(cls, Art, setThumbRef));
            ADD_METHOD(cls, Art, html);
            ADD_METHOD(cls, Art, parse);
        ON_LOADED_END
    CLASS_END

    CLASS_BEGIN_N(ArtBasket, RefObject)

        static Array arts;

    public:

        METHOD static void addBook(const Ref<Book> &book);
        METHOD static void addChapter(const Ref<Book> &book, const Ref<Chapter> &chapter);

        METHOD _FORCE_INLINE_ static const Array &getArts() {
            return arts;
        }

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_METHOD(cls, ArtBasket, addBook);
            ADD_METHOD(cls, ArtBasket, addChapter);
            ADD_METHOD(cls, ArtBasket, getArts);
        ON_LOADED_END
    CLASS_END
}


#endif //GSAV2_0_ARTBASKET_H
