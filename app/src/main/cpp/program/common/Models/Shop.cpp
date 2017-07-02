//
//  Shop.cpp
//  hirender_iOS
//
//  Created by mac on 2017/4/29.
//  Copyright © 2017年 gen. All rights reserved.
//

#include "Shop.h"
#include <utils/FileSystem.h>
#include "io_helper.h"
#include <utils/network/HTTPClient.h>
#include <unistd.h>
#include "../Utils/minizip/unzip.h"
#include <utils/NotificationCenter.h>
#include <thirdparties/mruby/mruby.h>
#include <thirdparties/mruby/mruby/class.h>
#include <thirdparties/mruby/mruby/variable.h>
#include <thirdparties/mruby/mruby/string.h>
#include "../GlobalsDefine.h"
#include <utils/json/libjson.h>
#include <set>
#include "DownloadQueue.h"
#include "../Utils/MD5/md5.h"

using namespace nl;
using namespace hirender;
using namespace hicore;
using namespace hiscript;

bool Shop::readed = false;
RefArray Shop::local_shops;
Ref<Shop> Shop::selected_shop;
pointer_map Shop::processing_readers;

string url_md5_string;

namespace nl {
    const char *md5(const char *str, size_t size) {
        md5_state_t state;
        md5_init(&state);
        md5_append(&state, (const unsigned char*)str, (int)size);
        md5_byte_t outPut[17];
        memset((void*)outPut, 0, sizeof(md5_byte_t) * 17);
        char outStr[33];
        md5_finish(&state, outPut);
        for (int di = 0; di < 16; ++di)
            sprintf(outStr + di * 2, "%02x", outPut[di]);
        outStr[32] = 0;
        url_md5_string = outStr;
        return url_md5_string.c_str();
    }
    
}

const Ref<Settings> & Library::settings() {
    if (shop)
        return shop->getSettings();
    return Ref<Settings>::null();
}

void Reader::loadedPage(int idx, bool success, const Ref<nl::Page> &page) {
    if (pages.size() <= idx) {
        pages.vec()->resize(idx+1);
    }
    pages.vec()->operator[](idx) = page;
    if (on_page_loaded) {
        on_page_loaded(success, idx, page);
    }
}

void Reader::collect(nl::Chapter *chapter, nl::Book *book) {
    string path = FileSystem::getInstance()->getStoragePath() + "/books/";
    path += identifier.str();
    path += '_';
    path += md5(book->getUrl().c_str(), book->getUrl().size());
    if (access(path.c_str(), F_OK) != 0) {
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    path.push_back('/');
    string book_config = path + "config.json";
    if (access(book_config.c_str(), F_OK) != 0) {
        JSONNODE *json = json_new(JSON_NODE);
        json_push_back(json, json_new_a("identifier", identifier.str()));
        json_push_back(json, json_new_a("url", book->getUrl().c_str()));
        
        char *chs = json_as_string(json);
        
        json_free(chs);
        
        json_delete(json);
    }
    
}
const Ref<Settings> &Reader::settings() {
    if (shop)
        return shop->getSettings();
    return Ref<Settings>::null();
}

const StringName Shop::NOTIFICATION_SHOP_CHANGED("SHOP_CHANGED");
const StringName Shop::NOTIFICATION_INSTALLED("SHOP_INSTALLED");
const StringName Shop::NOTIFICATION_REMOVED("SHOP_REMOVED");
const StringName Shop::NOTIFICATION_SCRIPT_READY("SHOP_SCRIPT_READY");
const StringName Shop::NOTIFICATION_COLLECTED("SHOP_COLLECTED");

const RefArray &Shop::getLocalShops() {
    if (!readed) {
        string path = FileSystem::getInstance()->getStoragePath() + "/shops/";
        DIR *dir = opendir(path.c_str());
        if (dir) {
            struct dirent* ent = NULL;
            while (NULL != (ent = readdir(dir))) {
                if (ent->d_type!=8 && ent->d_name[0] != '.') {
                    Shop *shop = parse(path + ent->d_name + '/');
                    if (shop) {
                        shop->is_localize = true;
                        local_shops.vec()->push_back(Ref<Shop>(shop));
                    }
                }
            }
            closedir(dir);
        }
        NotificationCenter::getInstance()->listen(NOTIFICATION_REMOVED,
                                                  &Shop::onShopRemoved,
                                                  "ShopSelect");
        readed = true;
    }
    return local_shops;
}

const Ref<Shop> &Shop::getCurrentShop() {
    if (!selected_shop) {
        string selected_id;
        FileSystem::getInstance()->configGet("selected_shop", selected_id);
        const RefArray &shops = getLocalShops();
        StringName id(selected_id.c_str());
        if (!selected_id.empty()) {
            for (int i = 0, t = local_shops.size(); i < t; ++i) {
                Ref<Shop> shop = local_shops.at(i);
                if (shop->getIdentifier() == id) {
                    selected_shop = shop;
                    selected_shop->setupScript();
                    break;
                }
            }
        }
        if (!selected_shop && shops.size()) {
            selected_shop = (Ref<Shop>)shops.at(0);
            selected_shop->setupScript();
        }
    }
    if (selected_shop && !selected_shop->isLocalize()) {
        selected_shop = NULL;
    }
    return selected_shop;
}

void Shop::setCurrentShop(const Ref<nl::Shop> &shop) {
    if (selected_shop != shop) {
        if (shop && shop->isLocalize()) {
            FileSystem::getInstance()->configSet("selected_shop", shop->getIdentifier().str());
        }
//        if (selected_shop) {
//            selected_shop->clearScript();
//        }
        selected_shop = shop;
        if (selected_shop) {
            selected_shop->setupScript();
        }
        variant_vector vs{shop};
        NotificationCenter::getInstance()->trigger(NOTIFICATION_SHOP_CHANGED, &vs);
    }
}

Ref<Shop> Shop::find(const hicore::StringName &identifier) {
    const RefArray &shops = getLocalShops();
    for (int i = 0, t = local_shops.size(); i < t; ++i) {
        Ref<Shop> shop = local_shops.at(i);
        if (shop->getIdentifier() == identifier) {
            return shop;
            break;
        }
    }
    return Ref<Shop>::null();
}

Shop::Shop() : is_doing(false),
               script(NULL),
               is_localize(false),
               version(0),
               package_version(0) {
}

Shop::~Shop() {
    clearScript();
}

void Shop::onShopRemoved(void *key, void *params, void *data) {
    if (selected_shop){
        vector<Variant> *vs = (vector<Variant>*)params;
        Shop *shop = vs->at(0).get<Shop>();
        if (*selected_shop == shop) {
            selected_shop->clearScript();
            setCurrentShop(Ref<Shop>::null());
        }
    }
}

Shop *Shop::parse(const string &path) {
    string file = path + "config.json";
    if (access(file.c_str(), F_OK) == 0) {
        Ref<Data> data = new FileData(file);
        JSONNODE *node = json_parse(data->text());
        Shop *shop = parseJson(node);
        json_delete(node);
        return shop;
    }
    return nullptr;
}

RefArray Shop::parseShops(const string &path) {
    FileData file(path.c_str());
    JSONNODE *node = json_parse(file.text());
    RefArray arr;
    for (int i = 0, t = json_size(node); i < t; ++i) {
        JSONNODE *child = json_at(node, i);
        JSONNODE *id_node = json_get(child, "id");
        if (id_node) {
            arr.vec()->push_back(Ref<Shop>(nl::Shop::parseJson(child)));
        }
    }
    json_delete(node);
    return arr;
}

Shop *Shop::parseJson(void *node) {
    Shop *shop = new Shop;
    JSONNODE *name_node = json_get(node, "name");
    char *str;
    if (name_node) {
        str = json_as_string(name_node);
        shop->setName(str);
        json_free(str);
    }
    JSONNODE *icon_node = json_get(node, "icon");
    if (icon_node) {
        str = json_as_string(icon_node);
        shop->setIcon(str);
        json_free(str);
    }
    JSONNODE *url_node = json_get(node, "url");
    if (url_node) {
        str = json_as_string(url_node);
        shop->package = str;
        json_free(str);
    }
    JSONNODE *des_node = json_get(node, "description");
    if (des_node) {
        str = json_as_string(des_node);
        shop->setDescription(str);
        json_free(str);
    }
    JSONNODE *id_node = json_get(node, "id");
    if (id_node) {
        str = json_as_string(id_node);
        shop->identifier = str;
        json_free(str);
    }
    JSONNODE *host_node = json_get(node, "host");
    if (host_node) {
        str = json_as_string(host_node);
        shop->host = str;
        json_free(str);
    }
    JSONNODE *version_node = json_get(node, "version");
    if (version_node) {
        shop->version = json_as_int(version_node);
    }
    JSONNODE *pv_node = json_get(node, "package_version");
    if (pv_node) {
        shop->package_version = json_as_int(pv_node);
    }
    
    return shop;
}

void Shop::onInstallComplete(void *_client, void *sd, void *data) {
    Ref<Shop> shop = (Shop *)data;
    HTTPClient *client = (HTTPClient *)_client;
    if (client->getError().empty()) {
        unzFile zipfile = unzOpen(client->getPath().c_str());
        if (!zipfile) {
            shop->is_localize = false;
            goto failed;
        }
        
        unz_global_info global_info;
        if ( unzGetGlobalInfo( zipfile, &global_info ) != UNZ_OK )
        {
            printf( "could not read file global info\n" );
            unzClose( zipfile );
            goto failed;
        }
        
#define READ_SIZE 8192
        char read_buffer[ READ_SIZE ];
        string path = FileSystem::getInstance()->getStoragePath() + "/shops/";
        if (access(path.c_str(), F_OK) != 0) {
            mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        path += shop->identifier.str();
        path += '/';
        if (access(path.c_str(), F_OK) != 0) {
            mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        for (int i = 0; i < global_info.number_entry; ++i) {
            unz_file_info file_info;
#define MAX_FILENAME 256
#define dir_delimter '/'
            char filename[ MAX_FILENAME ];
            if ( unzGetCurrentFileInfo(zipfile,
                                       &file_info,
                                       filename,
                                       MAX_FILENAME,
                                       NULL, 0, NULL, 0 ) != UNZ_OK )
            {  
                LOG(w, "could not read file info");
                unzClose( zipfile );
                goto failed;
            }
            
            const size_t filename_length = strlen( filename );
            if ( filename[ filename_length-1 ] == dir_delimter )
            {
                mkdir((path + filename).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            }else {
                if (unzOpenCurrentFile(zipfile) != UNZ_OK) {
                    LOG(w, "could not open file");
                    unzClose( zipfile );
                    goto failed;
                }
                
                FILE *out = fopen((path + filename).c_str(), "wb");
                if (out == NULL)
                {
                    LOG(w, "could not open destination file");
                    unzCloseCurrentFile( zipfile );
                    unzClose( zipfile );
                    goto failed;
                }
                
                int error = UNZ_OK;
                do
                {
                    error = unzReadCurrentFile( zipfile, read_buffer, READ_SIZE );
                    if ( error < 0 )
                    {
                        LOG(w, "error %d", error );
                        unzCloseCurrentFile( zipfile );
                        unzClose( zipfile );
                        return;
                    }
                    
                    // Write data to file.
                    if ( error > 0 )
                    {
                        fwrite( read_buffer, error, 1, out ); // You should check return of fwrite...
                    }
                } while ( error > 0 );  
                
                fclose( out );
            }
            
            unzCloseCurrentFile( zipfile );
            if ( ( i+1 ) < global_info.number_entry )
            {
                if ( unzGoToNextFile( zipfile ) != UNZ_OK )
                {
                    LOG(w, "cound not read next file");
                    unzClose( zipfile );
                    goto failed;
                }
            }
        }
        unzClose(zipfile);
        
        JSONNODE *node = json_new(JSON_NODE);
        JSONNODE_ITERATOR it = json_begin(node);
        it = json_insert(node, it, json_new_a("name", shop->name.c_str()));
        it = json_insert(node, it, json_new_i("version", shop->version));
        it = json_insert(node, it, json_new_a("id", shop->identifier.str()));
        it = json_insert(node, it, json_new_a("icon", shop->icon.c_str()));
        it = json_insert(node, it, json_new_a("host", shop->host.c_str()));
        it = json_insert(node, it, json_new_a("url", shop->package.c_str()));
        it = json_insert(node, it, json_new_a("description", shop->description.c_str()));
        it = json_insert(node, it, json_new_i("package_version", shop->package_version));
        
        FILE *file = fopen((path + "config.json").c_str(), "wb");
        json_char *chs = json_write(node);
        fwrite(chs, strlen(chs), 1, file);
        fclose(file);
        json_free(chs);
        json_delete(node);

        local_shops.vec()->push_back(shop);
        shop->is_localize = true;
        vector<Variant> vs{shop};
        NotificationCenter::getInstance()->trigger(NOTIFICATION_INSTALLED, &vs);
    }else {
        vector<Variant> vs{shop};
        NotificationCenter::getInstance()->trigger(NOTIFICATION_INSTALLED, &vs);
    }
    shop->is_doing = false;
    return;
failed:
    shop->is_doing = false;
    vector<Variant> vs{shop};
    NotificationCenter::getInstance()->trigger(NOTIFICATION_INSTALLED, &vs);
}

void Shop::clearScript() {
    if (script) {
        delete script;
        script = NULL;
    }
}

void Shop::setupScript() {
    if (isLocalize() && !script) {
        script = new RubyScript;
        script->setup((FileSystem::getInstance()->getResourcePath() + "/ruby").c_str());
        
        string path;
        if (IS_DEBUG) {
            path = FileSystem::getInstance()->getResourcePath() + "/ruby/t_root";
        }else {
            path = FileSystem::getInstance()->getStoragePath() + "/shops/" + identifier.str();
        }
        script->addEnvPath(path.c_str());
        path += "/config.rb";

        script->run(path.c_str());
        
        vector<Variant> vs{this};
        NotificationCenter::getInstance()->trigger(NOTIFICATION_SCRIPT_READY, &vs);
    }
}

bool Shop::setupLibrary(Library *lib) {
    if (!script) {
        setupScript();
    }
    lib->shop = this;
    mrb_value val = script->runScript("$config[:library]");
    if (mrb_bool(val)) {
        struct RClass *scls = mrb_class_ptr(val);
        RubyInstance *sins = script->newBuff(scls, lib, NULL, 0);
        
        mrb_gv_set(script->getMRB(),
                   mrb_intern_cstr(script->getMRB(), "library_instance"),
                   mrb_obj_value(sins->getScriptInstance()));
        
        return true;
    }
    return false;
}

bool Shop::setupReader(Reader *reader) {
    if (!script) {
        setupScript();
    }
    reader->shop = this;
    reader->setIdentifier(getIdentifier());
    mrb_value val = script->runScript("$config[:reader]");
    if (mrb_bool(val)) {
        struct RClass *scls = mrb_class_ptr(val);
        RubyInstance *sins = script->newBuff(scls, reader, NULL, 0);
        
        char str[40];
        sprintf(str, "reader_%ld", (long)reader);
        
        mrb_gv_set(script->getMRB(),
                   mrb_intern_cstr(script->getMRB(), str),
                   mrb_obj_value(sins->getScriptInstance()));
        
        return true;
    }
    return false;
}

bool Shop::unbindReader(nl::Reader *reader) {
    if (!script) {
        setupScript();
    }
    
    char str[40];
    sprintf(str, "reader_%ld", (long)reader);
    
    mrb_gv_remove(script->getMRB(),
                  mrb_intern_cstr(script->getMRB(), str));
    
    return true;
}

void Shop::install() {
    if (is_doing)
        return;
    is_doing = true;
    client = new_t(HTTPClient, package);
    client->setOnComplete(C([=](Ref<HTTPClient> client, const string &res){
        onInstallComplete(client, NULL, this);
        if (!selected_shop) {
            setCurrentShop(this);
        }
        this->client = NULL;
    }));
    client->start();
}

void Shop::remove() {
    clearScript();
    auto it = local_shops->begin();
    while (it != local_shops->end()) {
        Ref<Shop> shop = *it;
        if (shop->getIdentifier() == getIdentifier()) {
            it = local_shops.vec()->erase(it);
        }else {
            ++it;
        }
    }
    string path = FileSystem::getInstance()->getStoragePath() + "/shops/" + identifier.str();
    removeDir(path.c_str());
    is_localize = false;
    vector<Variant> vs{this};
    NotificationCenter::getInstance()->trigger(NOTIFICATION_REMOVED, &vs);
}

int Shop::collect(Book *book, nl::Chapter *chapter) {
    if (isLocalize()) {
        
        const map<string, Ref<Book> > &local_books = Book::getLocalBooks();
        Ref<Book> current_book;
        auto it = local_books.find(book->getUrl());
        if (it == local_books.end()) {
            book->convertLocal();
            current_book = book;
        }else {
            current_book = it->second;
        }
        auto &chapters = current_book->getChapters();
        auto cit = chapters->find(chapter->getUrl());
        if (cit == chapters->end()) {
            if (current_book->insertLocalChapter(chapter)) {
                download(book, chapter);
            }
            
            variant_vector vs {book, chapter};
            NotificationCenter::getInstance()->trigger(NOTIFICATION_COLLECTED, &vs);
            
            return 0;
        }else {
            return 1;
        }
    }else {
        return 2;
    }
    
}

int Shop::download(nl::Book *book, nl::Chapter *chapter) {
    return DownloadQueue::getInstance()->startDownload(book, chapter);
}

void Shop::cancelDownload(Chapter *chapter) {
    DownloadQueue::getInstance()->stopDownload(chapter);
}

const Ref<Settings> &Shop::getSettings() {
    if (isLocalize() && !settings) {
        
        settings = new Settings;
        
        if (!script) {
            setupScript();
        }
        
        string path;
        if (IS_DEBUG) {
            path = FileSystem::getInstance()->getResourcePath() + "/ruby/t_root";
        }else {
            path = FileSystem::getInstance()->getStoragePath() + "/shops/" + identifier.str();
        }
        mrb_value val = script->runScript("$config[:settings]");
        if (val.tt == MRB_TT_STRING) {
            char* string_path = mrb_str_to_cstr(script->getMRB(), val);
            string spath = path + '/' + string_path;
            if (access(spath.c_str(), F_OK) == 0) {
                settings->parse(spath.c_str());
            }else {
                LOG(w, "Setting file not found %s", string_path);
            }
        }else if (val.tt == MRB_TT_CLASS || val.tt == MRB_TT_ICLASS || val.tt == MRB_TT_SCLASS){
            struct RClass *scls = mrb_class_ptr(val);
            RubyInstance *sins = script->newBuff(scls, *settings, NULL, 0);
            
            mrb_gv_set(script->getMRB(),
                       mrb_intern_cstr(script->getMRB(), "settings"),
                       mrb_obj_value(sins->getScriptInstance()));
            sins->apply("process", NULL, 0);
        }
        if (IS_DEBUG) {
            string val_path = FileSystem::getInstance()->getStoragePath() + "/.setting_values";
            settings->load(val_path);
        }else {
            string val_path = path + "/.setting_values";
            settings->load(val_path);
        }
    }
    return settings;
}

Ref<Data> Shop::file(const char *filename) {
    string path;
    if (IS_DEBUG) {
        path = FileSystem::getInstance()->getResourcePath() + "/ruby/t_root";
    }else {
        path = FileSystem::getInstance()->getStoragePath() + "/shops/" + identifier.str();
    }
    path += '/';
    path += filename;
    return new FileData(path.c_str());
}

