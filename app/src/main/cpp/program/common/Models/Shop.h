//
//  Shop.hpp
//  hirender_iOS
//
//  Created by mac on 2017/4/29.
//  Copyright © 2017年 gen. All rights reserved.
//

#ifndef Shop_hpp
#define Shop_hpp

#include <core/Ref.h>
#include <utils/json/libjson.h>
#include <script/ruby/RubyScript.h>
#include <core/Callback.h>
#include <core/Data.h>
#include <utils/network/HTTPClient.h>
#include "Book.h"
#include "Chapter.h"
#include "Page.h"
#include "Settings.h"
#include "../nl_define.h"

using namespace gcore;

namespace nl {
    class Shop;
    const char *md5(const char *str, size_t size);

    CLASS_BEGIN_N(Library, RefObject)

        Shop *shop;
        friend class Shop;


    public:
        _FORCE_INLINE_ Shop *getShop() {
            return shop;
        }
        EVENT(Ref<HTTPClient>, load, int page, const Ref<Callback> &on_complete);

        EVENT(Ref<HTTPClient>, loadBook, const Ref<Book> &book, int page, const Ref<Callback> &on_complete);

        EVENT(Ref<HTTPClient>, search, const char *key, int page, const Ref<Callback> &on_complete);
        METHOD const Ref<Settings> &settings();

        METHOD void applyLoad(int page, const RefCallback &call) {
            Variant idx(page);
            Variant _call(call);
            pointer_vector vs{&idx, &_call};
            apply("load", vs);
        }
        METHOD Ref<Data> file(const char *filename);
        METHOD void message(const string &msg) const;

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_METHOD(cls, Library, settings);
            ADD_METHOD(cls, Library, applyLoad);
            ADD_METHOD(cls, Library, file);
            ADD_METHOD(cls, Library, message);
        ON_LOADED_END
    CLASS_END

    CLASS_BEGIN_N(Reader, RefObject)

        RefCallback on_page_count;
        RefCallback on_page_loaded;
        Array pages;
        StringName identifier;
        Shop *shop;
        friend class Shop;

    public:
        _FORCE_INLINE_ Shop *getShop() {
            return shop;
        }

        METHOD void loadedPage(int idx, bool success, const Ref<Page> &page);

        /**
         * @callback params [bool success, int count]
         */
        METHOD void setOnPageCount(const RefCallback &callback) {
            on_page_count = callback;
        }
        METHOD const RefCallback &getOnPageCount() {
            return on_page_count;
        }
        PROPERTY(on_page_count, getOnPageCount, setOnPageCount);

        /**
         * @callback params [bool success, int page_idx, const Ref<Page> &page]
         */
        METHOD void setOnPageLoaded(const RefCallback &callback) {
            on_page_loaded = callback;
        }
        METHOD const RefCallback &getOnPageLoaded() {
            return on_page_loaded;
        }

        METHOD const Array &getPages() {
            return pages;
        }

        METHOD _FORCE_INLINE_ void setIdentifier(const StringName &identifier) {
            this->identifier = identifier;
        }
        METHOD _FORCE_INLINE_ const StringName &getIdentidier() {
            return identifier;
        }
        PROPERTY(identifier, getIdentidier, setIdentifier);

        METHOD const Ref<Settings> &settings();
        METHOD void collect(Chapter *chapter, Book *book);
    
        METHOD Ref<Data> file(const char *filename);
        METHOD void message(const string &msg) const;

        EVENT(void, process, const Ref<Chapter> &chapter);
        EVENT(void, reloadPage, const Ref<Page> &page, int idx);
        EVENT(void, stop);

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_PROPERTY(cls, "on_page_count", ADD_METHOD(cls, Reader, getOnPageCount), ADD_METHOD(cls, Reader, setOnPageCount));
            ADD_PROPERTY(cls, "identifier", ADD_METHOD(cls, Reader, getIdentidier), ADD_METHOD(cls, Reader, setIdentifier));
            ADD_METHOD(cls, Reader, loadedPage);
            ADD_METHOD(cls, Reader, setOnPageLoaded);
            ADD_METHOD(cls, Reader, getOnPageLoaded);
            ADD_METHOD(cls, Reader, getPages);
            ADD_METHOD(cls, Reader, settings);
            ADD_METHOD(cls, Reader, collect);
            ADD_METHOD(cls, Reader, file);
            ADD_METHOD(cls, Reader, message);
        ON_LOADED_END
    CLASS_END

    CLASS_BEGIN_N(Shop, RefObject)

        static Array local_shops;
        static Ref<Shop> selected_shop;
        static bool readed;
        gscript::RubyScript *script;

        bool is_doing;

        StringName identifier;
        string package;
        string name;
        string host;
        string icon;
        string description;
        Ref<Settings> settings;
        Ref<gr::HTTPClient> client;
        int version;
        int package_version;

        bool is_localize;

        static pointer_map processing_readers;

        static void onShopRemoved(void *key, void *params, void *data);
        static void onInstallComplete(void *client, void *sd, void *data);

    public:
        Shop();
        ~Shop();

        METHOD static const Array &getLocalShops();
        METHOD static Shop *parse(const string &path);
        METHOD static Array parseShops(const string &);
        static Shop *parseJson(JSONNODE *node);

        static const StringName NOTIFICATION_SHOP_CHANGED;

        static const StringName NOTIFICATION_INSTALLED;
        static const StringName NOTIFICATION_REMOVED;
        static const StringName NOTIFICATION_SCRIPT_READY;

        static const StringName NOTIFICATION_COLLECTED;

        METHOD _FORCE_INLINE_ const string &getName() {
            return name;
        }
        METHOD _FORCE_INLINE_ void setName(const string &name) {
            this->name = name;
        }
        PROPERTY(name, getName, setName);

        METHOD _FORCE_INLINE_ const string &getHost() {
            return host;
        }
        METHOD _FORCE_INLINE_ void setHost(const string &host) {
            this->host = host;
        }
        PROPERTY(host, getHost, setHost);

        METHOD _FORCE_INLINE_ const string &getIcon() {
            return icon;
        }
        METHOD _FORCE_INLINE_ void setIcon(const string &icon) {
            this->icon = icon;
        }
        PROPERTY(icon, getIcon, setIcon);

        METHOD _FORCE_INLINE_ const string &getDescription() {
            return description;
        }
        METHOD _FORCE_INLINE_ void setDescription(const string &description) {
            this->description = description;
        }
        PROPERTY(description, getDescription, setDescription);

        METHOD _FORCE_INLINE_ const StringName &getIdentifier() {
            return identifier;
        }
        METHOD _FORCE_INLINE_ bool isLocalize() {
            return is_localize;
        }

        METHOD _FORCE_INLINE_ int getVersion() const {
            return version;
        }
        METHOD _FORCE_INLINE_ void setVersion(int version) {
            this->version = version;
        }
        PROPERTY(version, getVersion, setVersion);
    
        METHOD _FORCE_INLINE_ int getPackageVersion() const {
            return package_version;
        }
        METHOD _FORCE_INLINE_ void setPackageVersion(int package_version) {
            this->package_version = package_version;
        }
        PROPERTY(package_version, getPackageVersion, setPackageVersion);

        METHOD const Ref<Settings> &getSettings();

        METHOD static const Ref<Shop> &getCurrentShop();
        METHOD static void setCurrentShop(const Ref<Shop> &shop);
        METHOD static Ref<Shop> find(const StringName &identifier);

        METHOD void clearScript();
        METHOD void setupScript();

        METHOD bool setupLibrary(Library *lib);
        METHOD bool setupReader(Reader *reader);
        METHOD bool unbindReader(Reader *reader);

        /**
         * @return 0 : ok , 1 : collected , 2 : not installed
         */
        METHOD int collect(Book *book, Chapter *chapter);
        METHOD static int download(Book *book, Chapter *chapter);
        METHOD static void cancelDownload(Chapter *chapter);
        METHOD static void removeDownload(Chapter *chapter);

        METHOD int like(Book *book);

        METHOD void install();
        METHOD void remove();
        METHOD Ref<Data> file(const char *filename);
        METHOD void message(const string &msg) const;

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_PROPERTY(cls, "name", ADD_METHOD(cls, Shop, getName), ADD_METHOD(cls, Shop, setName));
            ADD_PROPERTY(cls, "host", ADD_METHOD(cls, Shop, getHost), ADD_METHOD(cls, Shop, setHost));
            ADD_PROPERTY(cls, "icon", ADD_METHOD(cls, Shop, getIcon), ADD_METHOD(cls, Shop, setIcon));
            ADD_PROPERTY(cls, "description", ADD_METHOD(cls, Shop, getDescription), ADD_METHOD(cls, Shop, setDescription));
            ADD_PROPERTY(cls, "version", ADD_METHOD(cls, Shop, getVersion), ADD_METHOD(cls, Shop, setVersion));
            ADD_PROPERTY(cls, "package_version", ADD_METHOD(cls, Shop, getPackageVersion), ADD_METHOD(cls, Shop, setPackageVersion));
            ADD_METHOD(cls, Shop, getLocalShops);
            ADD_METHOD(cls, Shop, parse);
            ADD_METHOD(cls, Shop, parseShops);
            ADD_METHOD(cls, Shop, getIdentifier);
            ADD_METHOD(cls, Shop, isLocalize);
            ADD_METHOD(cls, Shop, getSettings);
            ADD_METHOD(cls, Shop, getCurrentShop);
            ADD_METHOD(cls, Shop, setCurrentShop);
            ADD_METHOD(cls, Shop, find);
            ADD_METHOD(cls, Shop, clearScript);
            ADD_METHOD(cls, Shop, setupScript);
            ADD_METHOD(cls, Shop, setupLibrary);
            ADD_METHOD(cls, Shop, setupReader);
            ADD_METHOD(cls, Shop, unbindReader);
            ADD_METHOD(cls, Shop, like);
            ADD_METHOD(cls, Shop, collect);
            ADD_METHOD(cls, Shop, download);
            ADD_METHOD(cls, Shop, cancelDownload);
            ADD_METHOD(cls, Shop, install);
            ADD_METHOD(cls, Shop, remove);
            ADD_METHOD(cls, Shop, file);
            ADD_METHOD(cls, Shop, message);
        ON_LOADED_END
    CLASS_END
    
    _FORCE_INLINE_ Ref<Data> Library::file(const char *filename) {
        return shop ? shop->file(filename) : Ref<Data>::null();
    }
    _FORCE_INLINE_ Ref<Data> Reader::file(const char *filename) {
        return shop ? shop->file(filename) : Ref<Data>::null();
    }
    _FORCE_INLINE_ void Library::message(const string &msg) const {
        if (shop) shop->message(msg);
    }
    _FORCE_INLINE_ void Reader::message(const string &msg) const {
        if (shop) shop->message(msg);
    }
}

#endif /* Shop_hpp */
