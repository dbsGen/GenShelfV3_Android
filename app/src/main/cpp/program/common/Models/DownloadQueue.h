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

using namespace hicore;

namespace nl {

    class DownloadChapter;
    class DownloadQueue;

    CLASS_BEGIN_N(DownloadPage, RefObject)

        int status;
        Ref<Page> page;
        DownloadChapter *chapter;
        Ref<hirender::HTTPClient> client;
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

        _FORCE_INLINE_ int getStatus() {
            return status;
        }
        void setStatus(int status);

        void start();
        void stop();

    CLASS_END

    CLASS_BEGIN_N(DownloadChapter, RefObject)

        map<int, Ref<DownloadPage> >  pages;
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
         */
        static const StringName &NOTIFICATION_PAGE_COUNT;

        DownloadChapter();

        _FORCE_INLINE_ int getStatus() {
            return status;
        }
        void setStatus(int status);

        void start();
        void stop();

    CLASS_END

    CLASS_BEGIN_TN(DownloadQueue, Singleton, 1, DownloadQueue)

        map<string, Ref<DownloadChapter> > chapters;
        pointer_list chapters_queue;
        pointer_list pages_queue;

        DownloadChapter *current_chapter;
        DownloadPage *current_page;

        void checkChaptersQueue();
        void checkPageQueue();

        void pushPage(DownloadPage *page);
        void pausePage(DownloadPage *page);

        friend class DownloadPage;
        friend class DownloadChapter;

    public:
        enum _Status {
            StatusNone = 0,
            StatusLoading = 1,
            StatusComplete = 2,
            StatusPause = 3,
            StatusFailed
        };
        enum _Result {
            ResultStart = 0,
            ResultDownloading = 1,
            ResultShopNotFound = 2
        };
        typedef int Status;
        typedef int Result;

        DownloadQueue();

        METHOD int pageCount(Chapter *chapter);
        METHOD int chapterOldDownloaded(Chapter *chapter);
        METHOD float chapterPercent(Chapter *chapter);
        METHOD Status chapterStatus(Chapter *chapter);
        METHOD Status pageStatus(Chapter *chapter, int idx);
        METHOD Status pageStatusAndBringFirst(Chapter *chapter, int idx);

        METHOD Result startDownload(Book *book, Chapter *chapter);
        METHOD void stopDownload(Chapter *chapter);

    protected:
        ON_LOADED_BEGIN(cls, Singleton<DownloadQueue>)
            ADD_METHOD(cls, DownloadQueue, pageCount);
            ADD_METHOD(cls, DownloadQueue, chapterOldDownloaded);
            ADD_METHOD(cls, DownloadQueue, chapterPercent);
            ADD_METHOD(cls, DownloadQueue, chapterStatus);
            ADD_METHOD(cls, DownloadQueue, pageStatus);
            ADD_METHOD(cls, DownloadQueue, pageStatusAndBringFirst);
            ADD_METHOD(cls, DownloadQueue, startDownload);
            ADD_METHOD(cls, DownloadQueue, stopDownload);
        ON_LOADED_END
    CLASS_END
}


#endif //GSAV2_0_DOWNLOADQUEUE_H
