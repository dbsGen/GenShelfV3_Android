//
// Created by mac on 2017/6/18.
//

#include <dirent.h>
#include <unistd.h>
#include <utils/NotificationCenter.h>
#include "DownloadQueue.h"

using namespace nl;
using namespace hirender;

const StringName &DownloadPage::NOTIFICATION_STATUS("PAGE_STATUS");
const StringName &DownloadChapter::NOTIFICATION_STATUS("CHAPTER_STATUS");
const StringName &DownloadChapter::NOTIFICATION_PERCENT("CHAPTER_PERCENT");
const StringName &DownloadChapter::NOTIFICATION_PAGE_COUNT("CHAPTER_PAGE_COUNT");

void DownloadPage::start() {
    if (status != DownloadQueue::StatusNone) return;
    const string &url = page->getPicture();
    client = new_t(HTTPClient, url);
    client->setDelay(0.5);
    client->setRetryCount(3);
    client->setMethod(page->getMethod());
    client->setReadCache(true);
    const RefMap &map = page->getHeaders();
    for (auto it = map->begin(), _e = map->end(); it != _e; ++it) {
        client->addHeader(it->first, it->second);
    }
    for (auto it = page->getParameters()->begin(), _e = page->getParameters()->end();
         it != _e; ++it) {
        client->addParameter(it->first, it->second);
    }
    client->setOnComplete(C([=](HTTPClient *c, const string &path){
        if (c->getError().empty()) {
            DownloadChapter *dc = this->chapter;
            string npath = dc->book->picturePath(*dc->chapter, this->index);
            FILE *old_file = fopen(path.c_str(), "r");
            FILE *new_file = fopen(npath.c_str(), "w");
            char buf[BUFSIZ];
            size_t size;
            while ((size = fread(buf, 1, BUFSIZ, old_file))) {
                fwrite(buf, 1, size, new_file);
            }
            fclose(old_file);
            fclose(new_file);

            this->setStatus(DownloadQueue::StatusComplete);
        }else {
            this->setStatus(DownloadQueue::StatusFailed);
        }
        this->chapter->pageRequestOver(this);
    }));
    setStatus(DownloadQueue::StatusLoading);
    client->start();
}

void DownloadPage::stop() {
    if (client) {
        client->cancel();
        client = nullptr;
    }
}

DownloadPage::DownloadPage() : client(NULL), status(DownloadQueue::StatusNone) {

}

void DownloadPage::setStatus(int status) {
    if (this->status != status) {
        this->status = status;
        variant_vector vs{page, chapter->chapter, index, status};
        NotificationCenter::getInstance()->trigger(NOTIFICATION_STATUS, &vs);
    }
}

DownloadChapter::DownloadChapter() : reader(NULL),
                                     complete_count(0),
                                     page_count(0),
                                     old_downloaded(0)
{
}

void DownloadChapter::pageRequestOver(DownloadPage *page) {
    checkStatus();
    queue->current_page = NULL;
    queue->checkPageQueue();
    if (status == DownloadQueue::StatusComplete ||
            status == DownloadQueue::StatusFailed) {
        queue->current_chapter = NULL;
        queue->checkChaptersQueue();
    }
}

void DownloadChapter::stop() {
    if (status == DownloadQueue::StatusLoading) {
        if (reader) {
            reader->apply("stop");
        }
        for (auto it = pages.begin(), _e = pages.end(); it != _e; ++it) {
            queue->pausePage(*it->second);
        }
        queue->checkPageQueue();
        setStatus(DownloadQueue::StatusNone);
    }
}

void DownloadChapter::start() {
    if (status != DownloadQueue::StatusNone)
        return;
    if (!reader) {
        reader = new_t(Reader);
        shop->setupReader(reader);
    }

    if (pages.size() == 0) {
        reader->setOnPageCount(C([=](bool success, int count){
            if (success) {
                page_count = count;
                if (page_count == complete_count) {
                    setStatus(DownloadQueue::StatusComplete);
                }
                if (page_count == pages.size()) {
                    saveChapterInfo();
                }
                variant_vector vs{chapter, count};
                NotificationCenter::getInstance()->trigger(NOTIFICATION_PAGE_COUNT, &vs);
            }else {
                setStatus(DownloadQueue::StatusFailed);
            }
        }));
        reader->setOnPageLoaded(C([=](bool success, int page_idx, const Ref<Page> &page){
            if (success) {
                DownloadPage *dp = new DownloadPage;
                dp->page = page;
                dp->index = page_idx;
                dp->chapter = this;
                dp->status = DownloadQueue::StatusNone;
                pages[page_idx] = dp;
                string pic_path = this->book->picturePath(*chapter, page_idx);
                if (access(pic_path.c_str(), F_OK) != 0) {
                    queue->pushPage(dp);
                }
            }else {
                DownloadPage *dp = new DownloadPage;
                dp->page = page;
                dp->index = page_idx;
                dp->chapter = this;
                dp->status = DownloadQueue::StatusFailed;
                pages[page_idx] = dp;
                checkStatus();
            }
            if (page_count != 0 && page_count == pages.size()) {
                saveChapterInfo();
            }
        }));
        setStatus(DownloadQueue::StatusLoading);
        Variant v(chapter);
        pointer_vector vs{&v};
        reader->apply("process", vs);
    }else {
        for (auto it = pages.begin(), _e = pages.end(); it != _e; ++it) {
            queue->pushPage(*it->second);
        }
    }
}

void DownloadChapter::setStatus(int status) {
    if (this->status != status) {
        this->status = status;
        variant_vector vs{chapter, status};
        NotificationCenter::getInstance()->trigger(NOTIFICATION_STATUS, &vs);
    }
}

void DownloadChapter::saveChapterInfo() {
    auto &pages = chapter->getPages();
    pages->clear();
    for (int i = 0; i < page_count; ++i) {
        pages->push_back(this->pages[i]->page);
    }
    chapter->saveConfig(book->chapterPath(*chapter) + Chapter::DATA_FILE);
}

void DownloadChapter::checkStatus() {
    if (page_count != 0) {
        bool complete = true;
        bool  has_failed = false;
        int count = 0;
        for (int i = 0; i < page_count; ++i) {
            auto it = pages.find(i);
            if (it == pages.end()) {
                complete = false;
            }else {
                auto &page = it->second;
                if (page->status == DownloadQueue::StatusFailed) {
                    has_failed = true;
                }else if (page->status == DownloadQueue::StatusComplete) {
                    count++;
                }
            }
        }
        if (complete_count != count) {
            complete_count = count;
            if (page_count) {
                variant_vector vs{chapter, complete_count/(float)page_count};
                NotificationCenter::getInstance()->trigger(NOTIFICATION_PERCENT, &vs);
            }
        }
        if (complete) {
            if (has_failed) {
                setStatus(DownloadQueue::StatusFailed);
            }else {
                setStatus(DownloadQueue::StatusComplete);
            }
        }
    }else {

        int i = 0;
        for (; i < 999; ++i) {
            auto it = pages.find(i);
            if (it == pages.end()) {
                break;
            }
        }
        old_downloaded = i;
    }
}

int DownloadQueue::pageCount(Chapter *chapter) {
    auto it = chapters.find(chapter->getUrl());
    if (it == chapters.end()) {
        return 0;
    }else {
        return it->second->page_count;
    }
}

int DownloadQueue::chapterOldDownloaded(Chapter *chapter) {
    auto it = chapters.find(chapter->getUrl());
    if (it == chapters.end()) {
        return 0;
    }else {
        return it->second->old_downloaded;
    }
}

float DownloadQueue::chapterPercent(Chapter *chapter) {
    auto it = chapters.find(chapter->getUrl());
    if (it == chapters.end()) {
        return 0;
    }else {
        return it->second->complete_count / (float)it->second->page_count;
    }
}

DownloadQueue::Status DownloadQueue::chapterStatus(Chapter *chapter) {
    auto it = chapters.find(chapter->getUrl());
    if (it == chapters.end()) {
        return StatusNone;
    }else {
        return it->second->status;
    }
}
DownloadQueue::Status DownloadQueue::pageStatus(Chapter *chapter, int idx) {
    auto it = chapters.find(chapter->getUrl());
    if (it == chapters.end()) {
        return StatusNone;
    }else {
        auto &pages = it->second->pages;
        auto pit = pages.find(idx);
        if (pit == pages.end()) {
            return StatusNone;
        }else {
            return pit->second->status;
        }
    }
}

DownloadQueue::Status DownloadQueue::pageStatusAndBringFirst(Chapter *chapter, int idx) {
    auto it = chapters.find(chapter->getUrl());
    if (it == chapters.end()) {
        return StatusNone;
    }else {
        auto &pages = it->second->pages;
        auto pit = pages.find(idx);
        if (pit == pages.end()) {
            return StatusNone;
        }else {
            pages_queue.remove(*pit->second);
            pages_queue.push_front(*pit->second);
            return pit->second->status;
        }
    }
}

DownloadQueue::Result DownloadQueue::startDownload(Book *book, Chapter *chapter) {
    auto &shops = Shop::getLocalShops();
    Ref<Shop> f_shop;
    for (int i = 0, t = shops.size(); i < t; ++i) {
        Ref<Shop> shop = shops.at(i);
        if (shop->getIdentifier() == book->getShopId()) {
            f_shop = shop;
            break;
        }
    }
    if (f_shop) {
        auto it = chapters.find(chapter->getUrl());
        if (it == chapters.end()) {
            DownloadChapter *dc = new DownloadChapter;
            dc->book = book;
            dc->chapter = chapter;
            dc->shop = f_shop;
            dc->queue = this;
            string path = book->chapterPath(chapter);
            DIR *dir = opendir(path.c_str());
            if (dir) {
                const RefArray &pages = chapter->getPages();
                int size = pages.size();
                if (size == 0) {
                    dc->status = StatusNone;
                    int i = 0;
                    for (; i < 999; ++i) {
                        string pic_path = book->picturePath(chapter, i);
                        if (access(pic_path.c_str(), F_OK) != 0) {
                            break;
                        }
                    }
                    dc->old_downloaded = i;
                }else {
                    bool complete = true;
                    int complete_count = 0;
                    for (int i = 0; i < size; ++i) {
                        string pic_path = book->picturePath(chapter, i);
                        DownloadPage *dp = new DownloadPage;
                        dp->page = pages->at(i).ref();
                        dp->chapter = dc;
                        dp->index = i;
                        if (access(pic_path.c_str(), F_OK) == 0) {
                            dp->status = StatusComplete;
                            ++complete_count;
                        }else {
                            dp->status = StatusNone;
                            complete = false;
                            pushPage(dp);
                        }
                        dc->pages[i] = dp;
                    }
                    if (complete) {
                        dc->status = StatusComplete;
                    }else {
                        dc->status = StatusNone;
                    }
                    dc->page_count = size;
                    dc->complete_count = complete_count;
                }
                closedir(dir);
            }else {
                dc->status = StatusNone;
            }
            chapters[chapter->getUrl()] = dc;
            if (dc->status != StatusComplete) {
                chapters_queue.push_back(dc);
                checkChaptersQueue();
            }
            return ResultStart;
        }else {
            if (it->second->status == StatusNone) {
                it->second->start();
                return ResultStart;
            }else {
                return ResultDownloading;
            }
        }
    }else {
        return ResultShopNotFound;
    }
}

void DownloadQueue::stopDownload(Chapter *chapter) {
    auto it = chapters.find(chapter->getUrl());
    if (it != chapters.end()) {
        it->second->stop();
    }
}

void DownloadQueue::pushPage(DownloadPage *page) {
    pages_queue.push_back(page);
    checkPageQueue();
}

void DownloadQueue::pausePage(DownloadPage *page) {
    if (current_page == page) {
        current_page->stop();
        current_page = NULL;
    }else {
        auto it = pages_queue.begin();
        while (it != pages_queue.end()) {
            if (*it == page) {
                it = pages_queue.erase(it);
            }else ++it;
        }
    }
}

void DownloadQueue::checkChaptersQueue() {
    if (!current_chapter && chapters_queue.size()) {
        current_chapter = (DownloadChapter*)chapters_queue.front();
        chapters_queue.pop_front();
        current_chapter->start();
    }
}

void DownloadQueue::checkPageQueue() {
    if (!current_page && pages_queue.size()) {
        current_page = (DownloadPage*)pages_queue.front();
        pages_queue.pop_front();
        current_page->start();
    }
}

DownloadQueue::DownloadQueue() : current_chapter(NULL), current_page(NULL) {
}
