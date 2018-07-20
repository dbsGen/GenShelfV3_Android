//
//  Chapter.cpp
//  GenS
//
//  Created by mac on 2017/5/17.
//  Copyright © 2017年 gen. All rights reserved.
//

#include "Chapter.h"
#include "DownloadQueue.h"
#include <utils/json/libjson.h>
#include <core/Data.h>
#include <cstring>
#include "KeyValue.h"
#include "unistd.h"

using namespace nl;
using namespace gcore;

const char *Chapter::DATA_FILE = "data.json";

void Chapter::saveConfig(const string &path) {

    if (access(path.c_str(), F_OK) == 0) {
        remove(path.c_str());
    }
    JSONNODE *node = json_new(JSON_NODE);
    JSONNODE_ITERATOR it = json_begin(node);
    it = json_insert(node, it, json_new_a("url", getUrl().c_str()));
    if (name.size()) {
        it = json_insert(node, it, json_new_a("name", getName().c_str()));
    }
//    it = json_insert(node, it, json_new_i("index", getIndex()));

    if (pages.size()) {
        JSONNODE *pages_node = json_new(JSON_ARRAY);
        json_set_name(pages_node, "pages");
        for (auto it = pages->begin(), _e = pages->end(); it != _e; ++it) {
            Ref<Page> page = *it;
            JSONNODE *node = page->unparse();
            json_push_back(pages_node, node);
        }
        it = json_insert(node, it, pages_node);
    }

    FILE *file = fopen(path.c_str(), "wb");
    json_char *chs = json_write(node);
    fwrite(chs, strlen(chs), 1, file);
    fclose(file);
    json_free(chs);
    json_delete(node);
}

Chapter *Chapter::parse(const string &path) {
    string file = path + "/" + DATA_FILE;
    Chapter *chapter = NULL;

    if (access(file.c_str(), F_OK) == 0) {
        Ref<Data> data(new FileData(file));
        JSONNODE *node = json_parse(data->text());
        JSONNODE *url_node = json_get(node, "url");
        if (url_node) {
            chapter = new_t(Chapter);
            char *str = json_as_string(url_node);
            chapter->setUrl(str);
            json_free(str);

            JSONNODE *name_node = json_get(node, "name");
            if (name_node) {
                str = json_as_string(name_node);
                chapter->setName(str);
                json_free(str);
            }

            JSONNODE *pages_node = json_get(node, "pages");
            if (pages_node) {
                json_index_t size = json_size(pages_node);
                for (json_index_t i = 0; i < size; ++i) {
                    JSONNODE *page_node = json_at(pages_node, i);
                    Ref<Page> page = new_t(Page);
                    page->parse(page_node);
                    chapter->pages->push_back(page);
                }
                chapter->status = Pause;

            }else
                chapter->status = None;
        }
        json_delete(node);
    }
    return chapter;
}

float Chapter::downloadPercent() {
    return DownloadQueue::getInstance()->chapterPercent(this);
}

int Chapter::downloadStatus() {
    return DownloadQueue::getInstance()->chapterStatus(this);
}

int Chapter::pageStatus(int index) {
    return DownloadQueue::getInstance()->pageStatus(this, index);
}

int Chapter::oldDownloaded() {
    return DownloadQueue::getInstance()->chapterOldDownloaded(this);
}

int Chapter::pageCount() {
    return DownloadQueue::getInstance()->pageCount(this);
}

int Chapter::completeCount() {
    return DownloadQueue::getInstance()->completeCount(this);
}

void Chapter::bringFirst(int index) {
    DownloadQueue::getInstance()->pageStatusAndBringFirst(this, index);
}

Array Chapter::cachedPages() const {
    string key = "chapter:";
    key += url;
    string val = KeyValue::get(key);
    Array pages;
    if (!val.empty()) {
        JSONNODE *pages_node = json_parse(val.c_str());
        if (pages_node) {
            json_index_t size = json_size(pages_node);
            for (json_index_t i = 0; i < size; ++i) {
                JSONNODE *page_node = json_at(pages_node, i);
                if (page_node) {
                    Ref<Page> page = new_t(Page);
                    page->parse(page_node);
                    pages->push_back(page);
                }
            }
            json_delete(pages_node);
        }
    }
    return pages;
}

void Chapter::cachePages(const Array &pages) const {
    string key = "chapter:";
    key += url;
    JSONNODE *pages_node = json_new(JSON_ARRAY);
    for (auto it = pages->begin(), _e = pages->end(); it != _e; ++it) {
        Ref<Page> page = *it;
        JSONNODE *node = page->unparse();
        json_push_back(pages_node, node);
    }
    char *text = json_write(pages_node);
    KeyValue::set(key, text);
    json_free(text);
}

int Chapter::lastIndex() const {
    string key = "page_index:";
    key += url;
    string val = KeyValue::get(key);
    if (!val.empty()) {
        return atoi(val.c_str());
    }
    return 0;
}

void Chapter::setLastIndex(int idx) const {
    string key = "page_index:";
    key += url;
    char index_str[20];
    sprintf(index_str, "%d", idx);
    KeyValue::set(key, index_str);
}

void Chapter::stopDownload() {
    DownloadQueue::getInstance()->stopDownload(this);
}

void Chapter::downloadingChapters(const Array &books, const Array &chapters) {
    const map<string, Ref<DownloadChapter> > &chs = DownloadQueue::getInstance()->getChapters();
    for (auto it = chs.begin(), _e = chs.end(); it != _e; ++it) {
        if (it->second->getStatus() != DownloadQueue::StatusComplete) {
            books->push_back(it->second->getBook());
            chapters->push_back(it->second->getChapter());
        }
    }
}
