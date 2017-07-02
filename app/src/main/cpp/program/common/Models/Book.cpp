//
//  Book.cpp
//  hirender_iOS
//
//  Created by mac on 2017/4/13.
//  Copyright © 2017年 gen. All rights reserved.
//

#include "Book.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utils/FileSystem.h>
#include "../Utils/minizip/unzip.h"
#include "../GlobalsDefine.h"
#include <utils/json/libjson.h>
#ifdef __ANDROID__
#include <bits/stl_algo.h>
#endif
#include "Shop.h"
#include "io_helper.h"

using namespace nl;
using namespace hirender;

map<string, Ref<Book> > Book::local_books;
bool Book::local_books_inited = false;

Book *Book::parse(const string &path) {
    string file = path + "/data.json";
    
    if (access(file.c_str(), F_OK) == 0) {
        Ref<Data> data(new FileData(file));
        JSONNODE *node = json_parse(data->text());
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
            str = json_as_string(shop_node);
            book->setShopId(str);
            json_free(str);
            
            json_delete(node);

            DIR *dir = opendir(path.c_str());
            if (dir) {
                struct dirent* ent = NULL;
                while (NULL != (ent = readdir(dir))) {
                    if (ent->d_type!=8 && ent->d_name[0] != '.') {
                        Ref<Chapter> chapter = Chapter::parse(path + '/' + ent->d_name);
                        if (chapter) {
                            chapter->setShopId(book->getShopId());
                            book->chapters->at(chapter->getUrl()) = chapter;
                        }
                    }
                }
                closedir(dir);
            }
            
            return book;
        }
        json_delete(node);
    }
    return NULL;
}

RefArray Book::localBooks() {
    variant_vector vs;
    const map<string, Ref<Book> > &local_books = Book::getLocalBooks();
    for (auto it = local_books.begin(), _e = local_books.end(); it != _e; ++it) {
        vs.push_back(it->second);
    }
    struct BookCompare {
        bool operator ()(const Ref<Book> &b1, const Ref<Book> &b2) {
            return b1->getIndex() < b2->getIndex();
        }
    };
    sort(vs.begin(), vs.end(), BookCompare());
    return vs;
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
    }
    return local_books;
}

void Book::removeBook() {
    Ref<Shop> shop = Shop::find(getShopId());
    if (shop) {
        for (map<string, Variant>::iterator it = chapters->begin(), _e = chapters->end(); it != _e; ++it) {
            shop->cancelDownload(it->second.get<Chapter>());
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

void Book::convertLocal() {
    getLocalBooks();
    if (local_books.find(url) == local_books.end()) {
        string path = FileSystem::getInstance()->getStoragePath() + "/local_books";
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
        it = json_insert(node, it, json_new_i("index", local_books.size()));
        
        FILE *file = fopen(path.c_str(), "wb");
        json_char *chs = json_write(node);
        fwrite(chs, strlen(chs), 1, file);
        fclose(file);
        json_free(chs);
        json_delete(node);
        
        local_books[url] = this;
    }
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
