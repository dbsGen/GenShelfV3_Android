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
#include "unistd.h"

using namespace nl;
using namespace hicore;

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
        JSONNODE_ITERATOR pit = json_begin(pages_node);
        for (auto it = pages->begin(), _e = pages->end(); it != _e; ++it) {
            JSONNODE *node = json_new(JSON_NODE);
            JSONNODE_ITERATOR jit = json_begin(node);

            jit = json_insert(node, jit, json_new_a("url", (*it).get<Page>()->getUrl().c_str()));
            jit = json_insert(node, jit, json_new_a("picture", (*it).get<Page>()->getPicture().c_str()));
            pit = json_insert(pages_node, pit, node);
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
                    str = json_as_string(json_get(page_node, "url"));
                    page->setUrl(str);
                    json_free(str);
                    str = json_as_string(json_get(page_node, "picture"));
                    page->setPicture(str);
                    json_free(str);
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

void Chapter::bringFirst(int index) {
    DownloadQueue::getInstance()->pageStatusAndBringFirst(this, index);
}