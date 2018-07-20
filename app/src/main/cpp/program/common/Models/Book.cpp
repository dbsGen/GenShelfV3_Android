//
//  Book.cpp
//  hirender_iOS
//
//  Created by mac on 2017/4/13.
//  Copyright © 2017年 gen. All rights reserved.
//

#include "Book.h"
#include "KeyValue.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utils/FileSystem.h>
#include "../Utils/minizip/unzip.h"
#include "../GlobalsDefine.h"
#include <utils/json/libjson.h>
#ifdef __ANDROID__
#include <bits/stl_algo.h>
#include <cstring>

#endif
#include "Shop.h"
#include "io_helper.h"

using namespace nl;
using namespace gr;

map<string, Ref<Book> > Book::local_books;
map<string, Ref<Book> > Book::liked_books;
bool Book::local_books_inited = false;

map<string, Ref<BookData> > BookData::caches;

void BookData::pushCache(const string &key, const Ref<BookData> &kv) {
    while (caches.size() > 100) {
        caches.erase(caches.begin());
    }
    caches[key] = kv;
}

Ref<BookData> BookData::get(const string &url) {
    auto it = caches.find(url);
    if (it != caches.end()) {
        return it->second;
    }
    Array arr = BookData::query()->equal("url", url)->results();
    if (arr.size() > 0) {
        Ref<BookData> bd = arr.at(0).ref();
        pushCache(url, bd);
        return bd;
    }else {
        Ref<BookData> bd = new BookData;
        bd->setUrl(url);
        pushCache(url, bd);
        return bd;
    }
}

Book *Book::parse(const string &path) {
    string file = path + "/data.json";

    if (access(file.c_str(), F_OK) == 0) {
        Ref<Data> data(new FileData(file));
        JSONNODE *node = json_parse(data->text());
        Book *book = parse(node);
        if (book) {
            DIR *dir = opendir(path.c_str());
            if (dir) {
                struct dirent *ent = NULL;
                while (NULL != (ent = readdir(dir))) {
                    if (ent->d_type != 8 && ent->d_name[0] != '.') {
                        Ref<Chapter> chapter = Chapter::parse(path + '/' + ent->d_name);
                        if (chapter) {
                            chapter->setShopId(book->getShopId());
                            book->chapters->at(chapter->getUrl()) = chapter;
                        }
                    }
                }
                closedir(dir);
            }
        }
        json_delete(node);
        return book;

    }
    return NULL;
}

Book* Book::parse(JSONNODE *node) {
    JSONNODE *url_node = json_get(node, "url");
    JSONNODE *shop_node = json_get(node, "shop");
    if (url_node && shop_node) {
        Book *book = new_t(Book);
        char *str = json_as_string(url_node);
        book->setUrl(str);
        json_free(str);
        JSONNODE *name_node = json_get(node, "name");
        if (name_node) {
            str = json_as_string(name_node);
            book->setName(str);
            json_free(str);
        }
        JSONNODE *thumb_node = json_get(node, "thumb");
        if (thumb_node) {
            str = json_as_string(thumb_node);
            book->setThumb(str);
            json_free(str);
        }
        JSONNODE *subtitle_node = json_get(node, "subtitle");
        if (subtitle_node) {
            str = json_as_string(subtitle_node);
            book->setSubtitle(str);
            json_free(str);
        }
        JSONNODE *des_node = json_get(node, "des");
        if (des_node) {
            str = json_as_string(des_node);
            book->setDes(str);
            json_free(str);
        }
        JSONNODE *idx_node = json_get(node, "index");
        if (idx_node) {
            book->index = (int)json_as_int(idx_node);
        }

        JSONNODE_ITERATOR header_it = json_find(node, "thumb_headers");
        if (header_it != json_end(node)) {
            JSONNODE_ITERATOR it = json_begin(*header_it), _e = json_end(*header_it);
            while (it != _e) {
                const Map &map = book->thumb_headers;
                char *name = json_name(*it);
                char *val = json_as_string(*it);
                map->set(name, Variant(val));
                json_free(name);
                json_free(val);
                ++it;
            }
        }

        str = json_as_string(shop_node);
        book->setShopId(str);
        json_free(str);

        return book;
    }
    return NULL;
}

struct BookCompare {
    bool operator ()(const Ref<Book> &b1, const Ref<Book> &b2) {
        return b1->getIndex() > b2->getIndex();
    }
};

Array Book::localBooks() {
    variant_vector vs;
    const map<string, Ref<Book> > &local_books = Book::getLocalBooks();
    for (auto it = local_books.begin(), _e = local_books.end(); it != _e; ++it) {
        vs.push_back(it->second);
    }
    sort(vs.begin(), vs.end(), BookCompare());
    return vs;
}

Array Book::likedBooks() {
    variant_vector vs;
    Book::getLocalBooks();
    for (auto it = liked_books.begin(), _e = liked_books.end(); it != _e; ++it) {
        vs.push_back(it->second);
    }
    sort(vs.begin(), vs.end(), BookCompare());
    return vs;
}

bool Book::isLiked() {
    return liked_books.find(url) != liked_books.end();
}

const map<string, Ref<Book> > &Book::getLocalBooks() {
    if (!local_books_inited) {
        local_books_inited = true;
        string path = FileSystem::getInstance()->getStoragePath() + "/local_books";

        DIR *dir = opendir(path.c_str());
        if (dir) {
            struct dirent* ent = NULL;
            while (NULL != (ent = readdir(dir))) {
                if (ent->d_type!=8 && ent->d_name[0] != '.') {
                    Book *book = parse(path + '/' + ent->d_name);
                    if (book) {
                        local_books[book->getUrl()] = book;
                    }
                }
            }
            closedir(dir);
        }

        path = FileSystem::getInstance()->getStoragePath() + "/liked_books";
        dir = opendir(path.c_str());
        if (dir) {
            struct dirent* ent = NULL;
            while (NULL != (ent = readdir(dir))) {
                if (ent->d_type!=8 && ent->d_name[0] != '.') {
                    Book *book = parse(path + '/' + ent->d_name);
                    if (book) {
                        liked_books[book->getUrl()] = book;
                    }
                }
            }
            closedir(dir);
        }
    }
    return local_books;
}

void Book::removeBook() {
    Ref<Shop> shop = Shop::find(getShopId());
    if (shop) {
        for (map<string, Variant>::iterator it = chapters->begin(), _e = chapters->end(); it != _e; ++it) {
            shop->cancelDownload(it->second.get<Chapter>());
            shop->removeDownload(it->second.get<Chapter>());
        }
    }
    string path = FileSystem::getInstance()->getStoragePath() + "/local_books/" + md5(url.c_str(), url.size());
    removeDir(path.c_str());
    local_books.erase(url);
}

void Book::removeChapter(nl::Chapter *chapter) {
    Ref<Shop> shop = Shop::find(getShopId());
    if (shop) shop->cancelDownload(chapter);
    string path = FileSystem::getInstance()->getStoragePath() + "/local_books/" + md5(url.c_str(), url.size());
    path.push_back('/');
    path += md5(chapter->getUrl().c_str(), chapter->getUrl().size());
    removeDir(path.c_str());
    chapters->erase(chapter->getUrl());
}

void Book::convertLocal(bool just_like) {
    getLocalBooks();
    if (just_like || local_books.find(url) == local_books.end()) {
        string path;
        if (just_like) {
            path = FileSystem::getInstance()->getStoragePath() + "/liked_books";
        }else {
            path = FileSystem::getInstance()->getStoragePath() + "/local_books";
        }
        if (access(path.c_str(), F_OK) != 0) {
            mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        path.push_back('/');
        path += md5(url.c_str(), url.size());
        if (access(path.c_str(), F_OK) != 0) {
            mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        path.push_back('/');
        path += "data.json";
        if (access(path.c_str(), F_OK) == 0) {
            remove(path.c_str());
        }
        JSONNODE *node = unparse();
        if (just_like) {
            static const string lc_string = "like_count";
            int like_count = atoi(KeyValue::get(lc_string).c_str());
            if (like_count == 0) {
                like_count = liked_books.size();
            }
            json_push_back(node, json_new_i("index", like_count));
            ++like_count;
            char str[20];
            sprintf(str, "%d", like_count);
            KeyValue::set(lc_string, str);
        }else {
            static const string lc_string = "local_count";
            int local_count = atoi(KeyValue::get(lc_string).c_str());
            if (local_count == 0) {
                local_count = local_books.size();
            }
            json_push_back(node, json_new_i("index", local_count));
            ++local_count;
            char str[20];
            sprintf(str, "%d", local_count);
            KeyValue::set(lc_string, str);
        }

        FILE *file = fopen(path.c_str(), "wb");
        json_char *chs = json_write(node);
        fwrite(chs, strlen(chs), 1, file);
        fclose(file);
        json_free(chs);
        json_delete(node);

        if (just_like) {
            liked_books[url] = this;
        }else {
            local_books[url] = this;
        }
    }
}

JSONNODE* Book::unparse() const {
    JSONNODE *node = json_new(JSON_NODE);
    JSONNODE_ITERATOR it = json_begin(node);
    it = json_insert(node, it, json_new_a("url", getUrl().c_str()));
    it = json_insert(node, it, json_new_a("shop", getShopId().str()));
    if (name.size()) {
        it = json_insert(node, it, json_new_a("name", name.c_str()));
    }
    if (thumb.size()) {
        it = json_insert(node, it, json_new_a("thumb", thumb.c_str()));
    }
    if (subtitle.size()) {
        it = json_insert(node, it, json_new_a("subtitle", subtitle.c_str()));
    }
    if (des.size()) {
        it = json_insert(node, it, json_new_a("des", des.c_str()));
    }
    const Map &map = thumb_headers;
    JSONNODE *headers_node = json_new(JSON_NODE);
    for (auto hit = map->begin(), _e = map->end(); hit != _e; ++hit) {
        json_push_back(headers_node, json_new_a(hit->first.c_str(), hit->second));
    }
    it = json_insert(node, it, headers_node);
    return node;
}

void Book::unlikeBook() {
    Ref<Shop> shop = Shop::find(getShopId());
    string path = FileSystem::getInstance()->getStoragePath() + "/liked_books/" + md5(url.c_str(), url.size());
    path.push_back('/');
    removeDir(path.c_str());
    liked_books.erase(url);
}

bool Book::insertLocalChapter(nl::Chapter *chapter) {
    getLocalBooks();
    if (local_books.find(url) != local_books.end() && chapters->find(chapter->getUrl()) == chapters->end()) {
        string path = FileSystem::getInstance()->getStoragePath() + "/local_books/" + md5(url.c_str(), url.size());
        if (access(path.c_str(), F_OK) == 0) {
            path.push_back('/');
            path += md5(chapter->getUrl().c_str(), chapter->getUrl().size());
            if (access(path.c_str(), F_OK) != 0) {
                mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            }
            path.push_back('/');
            path += Chapter::DATA_FILE;

            chapter->saveConfig(path);
            chapters->at(chapter->getUrl()) = Ref<Chapter>(chapter);

            return true;
        }
    }
    return false;
}

void Book::saveChapterConfig(nl::Chapter *chapter) {
    string path = FileSystem::getInstance()->getStoragePath() + "/local_books/" + md5(url.c_str(), url.size());
    if (access(path.c_str(), F_OK) == 0) {
        path.push_back('/');
        path += md5(chapter->getUrl().c_str(), chapter->getUrl().size());
        if (access(path.c_str(), F_OK) == 0) {
            path.push_back('/');
            path += "data.json";
            chapter->saveConfig(path);
        }
    }
}

void file_copy(const char *src, const char *dst)
{
    FILE *fp1, *fp2;
    int c;
    fp1 = fopen(src, "rb");
    fp2 = fopen(dst, "wb");
    if(fp1 == NULL || fp2 == NULL)
    {
        printf("open file failed\n");
        if(fp1) fclose(fp1);
        if(fp2) fclose(fp2);
    }

    while((c = fgetc(fp1)) != EOF)
        fputc(c, fp2);
    fclose(fp1);
    fclose(fp2);

}

bool Book::movePicture(nl::Chapter *chapter, const string &pic_path, int idx) {
    getLocalBooks();
    string path = FileSystem::getInstance()->getStoragePath() + "/local_books/" + md5(url.c_str(), url.size());
    if (access(path.c_str(), F_OK) != 0) {
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    path.push_back('/');
    path += md5(chapter->getUrl().c_str(), chapter->getUrl().size());
    if (access(path.c_str(), F_OK) != 0) {
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    path.push_back('/');
    char p_str[14];
    sprintf(p_str, "%04d.pic", idx);
    path += p_str;
    file_copy(pic_path.c_str(), path.c_str());

    return true;
}

string Book::picturePath(nl::Chapter *chapter, int idx) {
    string path = FileSystem::getInstance()->getStoragePath() + "/local_books/" + md5(url.c_str(), url.size());
    path.push_back('/');
    path += md5(chapter->getUrl().c_str(), chapter->getUrl().size());
    path.push_back('/');
    char p_str[14];
    sprintf(p_str, "%04d.pic", idx);
    path += p_str;
    return path;
}

string Book::chapterPath(Chapter *chapter) {
    string path = FileSystem::getInstance()->getStoragePath() + "/local_books/" + md5(url.c_str(), url.size());
    path.push_back('/');
    path += md5(chapter->getUrl().c_str(), chapter->getUrl().size());
    path.push_back('/');
    return path;
}

void Book::checkData() {
    if (!book_data) {
        book_data = BookData::get(url);
    }
}

Ref<Chapter> Book::lastChapter() {
    checkData();
    if (!book_data->getUrl().empty()) {
        Ref<Chapter> chapter = new Chapter;
        chapter->setName(book_data->getName());
        chapter->setUrl(book_data->getChapterUrl());
        chapter->setShopId(getShopId());
        return chapter;
    }
    return Ref<Chapter>::null();
}

void Book::setLastChapter(const Ref<Chapter> &chapter) {
    checkData();
    if (book_data->getChapterUrl() != chapter->getUrl()) {
        book_data->setName(chapter->getName());
        book_data->setChapterUrl(chapter->getUrl());
        book_data->setUrl(url);
        book_data->setPageIndex(0);
        book_data->save();
    }
}
