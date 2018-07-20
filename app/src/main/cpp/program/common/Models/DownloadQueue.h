//
// Created by mac on 2017/6/18.
//

#ifndef GSAV2_0_DOWNLOADQUEUE_H
#define GSAV2_0_DOWNLOADQUEUE_H

#include <core/Singleton.h>
#include <core/Map.h>
#include "Chapter.h"
#include "Book.h"
#include "Shop.h"
#include <utils/network/HTTPClient.h>
#include "../nl_define.h"

using namespace gcore;

namespace nl {

    class DownloadChapter;
    class DownloadQueue;

    CLASS_BEGIN_N(DownloadPage, RefObject)

        int status;
        Ref<Page> page;
        DownloadChapter *chapter;
        Ref<gr::HTTPClient> client;
        int index;

        friend class DownloadChapter;
        friend class DownloadQueue;

    public:
        /**
         * PAGE_STATUS
         * @param page Page*
         * @param chapter Chapter*
         * @param index int
         * @param status int
         */
        static const StringName &NOTIFICATION_STATUS;

        DownloadPage();
        ~DownloadPage();

        _FORCE_INLINE_ int getStatus() {
            return status;
        }
        void setStatus(int status);

        void start();
        void stop();

    CLASS_END

    CLASS_BEGIN_N(DownloadChapter, RefObject)

        unordered_map<int, Ref<DownloadPage> >  pages;
        vector<Ref<DownloadPage> > cache_pages;
        int status;
        Ref<Book> book;
        Ref<Chapter> chapter;
        Ref<Shop> shop;
        Reader *reader;
        int complete_count;
        int page_count;
        int old_downloaded;
        DownloadQueue *queue;

        friend class DownloadPage;
        friend class DownloadQueue;

        void saveChapterInfo();
        void pageRequestOver(DownloadPage *page);
        void checkStatus();

    public:
        /**
         * CHAPTER_STATUS
         * @param chapter Chapter*,
         * @param status int
         */
        static const StringName &NOTIFICATION_STATUS;
        /**
         * CHAPTER_PERCENT
         * @param chapter Chapter*,
         * @param percent float
         */
        static const StringName &NOTIFICATION_PERCENT;
        /**
         * CHAPTER_PAGE_COUNT
         * @param chapter Chapter*,
         * @param count int
         * @param completed int
         */
        static const StringName &NOTIFICATION_PAGE_COUNT;

        DownloadChapter();

        _FORCE_INLINE_ int getStatus() {
            return status;
        }
        void setStatus(int status);

        _FORCE_INLINE_ const Ref<Book> &getBook() {
            return book;
        }

        _FORCE_INLINE_ const Ref<Chapter> &getChapter() {
            return chapter;
        }

        void start();
        void stop();

    CLASS_END

    CLASS_BEGIN_TN(DownloadQueue, Singleton, 1, DownloadQueue)

        Ref<DownloadChapter> cache_chapter;
        map<string, Ref<DownloadChapter> > chapters;
        list<Ref<DownloadChapter> > chapters_queue;
        list<Ref<DownloadPage> > pages_queue;

        Ref<DownloadChapter> current_chapter;
        Ref<DownloadPage> current_page;

        void checkChaptersQueue();
        void checkPageQueue();

        void pushPage(DownloadPage *page);
        void pausePage(DownloadPage *page);

        void loadAll();

        friend class DownloadPage;
        friend class DownloadChapter;

    public:
        enum _Status {
            StatusNone = 0,
            StatusLoading = 1,
            StatusComplete = 2,
            StatusPause = 3,
            StatusFailed,
            StatusWaiting
        };
        enum _Result {
            ResultStart = 0,
            ResultDownloading = 1,
            ResultShopNotFound = 2
        };
        typedef int Status;
        typedef int Result;

        DownloadQueue();

        const map<string, Ref<DownloadChapter> > &getChapters();

        METHOD int pageCount(Chapter *chapter);
        METHOD int completeCount(Chapter *chapter);
        METHOD int chapterOldDownloaded(Chapter *chapter);
        METHOD float chapterPercent(Chapter *chapter);
        METHOD Status chapterStatus(Chapter *chapter);
        METHOD Status pageStatus(Chapter *chapter, int idx);
        METHOD Status pageStatusAndBringFirst(Chapter *chapter, int idx);

        METHOD Result startDownload(Book *book, Chapter *chapter);
        METHOD void stopDownload(const Ref<Chapter> &chapter);
        METHOD void removeDownload(Chapter *chapter);

        METHOD void save();
        METHOD void restore();

    protected:
        ON_LOADED_BEGIN(cls, Singleton<DownloadQueue>)
            ADD_METHOD(cls, DownloadQueue, pageCount);
            ADD_METHOD(cls, DownloadQueue, completeCount);
            ADD_METHOD(cls, DownloadQueue, chapterOldDownloaded);
            ADD_METHOD(cls, DownloadQueue, chapterPercent);
            ADD_METHOD(cls, DownloadQueue, chapterStatus);
            ADD_METHOD(cls, DownloadQueue, pageStatus);
            ADD_METHOD(cls, DownloadQueue, pageStatusAndBringFirst);
            ADD_METHOD(cls, DownloadQueue, startDownload);
            ADD_METHOD(cls, DownloadQueue, stopDownload);
            ADD_METHOD(cls, DownloadQueue, save);
            ADD_METHOD(cls, DownloadQueue, restore);
        ON_LOADED_END
    CLASS_END
}


#endif //GSAV2_0_DOWNLOADQUEUE_H
