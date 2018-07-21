package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Array;

/**
 * Created by mac on 2017/6/7.
 */

@NativeClass("nl::Chapter")
public class Chapter extends Helper.GInstance {
    private static Helper.GClass<Chapter> _class;
    static {
        _class = Helper.find(Chapter.class);
    }

    public static final int STATUS_NONE = 0,
            STATUS_LOADING = 1,
            STATUS_COMPLETE = 2,
            STATUS_PAUSE = 3,
            STATUS_FAILED = 4,
            STATUS_WAITING = 5;

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Chapter) {
            return getUrl().equals(((Chapter)obj).getUrl());
        }
        return false;
    }

    public Chapter() {}
    public Chapter(boolean init) {
        if (init) initialize();
    }

    public String getName() {
        return (String) call("getName");
    }
    public void setName(String name) {
        call("setName", name);
    }

    public String getUrl() {
        return (String) call("getUrl");
    }
    public void setUrl(String url) {
        call("setUrl", url);
    }

    public Array getPages() {
        return (Array)call("getPages");
    }
    public String getShopId() {
        return (String)call("getShopId");
    }
    public void setShopId(String shopId) {
        call("setShopId", shopId);
    }

    public float downloadPercent() {
        return (float)call("downloadPercent");
    }
    public int downloadStatus() {
        return (int)call("downloadStatus");
    }
    public int pageStatus(int idx) {
        return (int)call("pageStatus");
    }
    public int oldDownloaded() {
        return (int)call("oldDownloaded");
    }
    public void bringFirst(int index) {
        call("bringFirst", index);
    }

    public Array<Page> cachedPages() {
        return (Array<Page>)call("cachedPages");
    }
    public void cachePages(Array<Page> pages) {
        call("cachePages", pages);
    }
    public int lastIndex() {
        return (int)call("lastIndex");
    }
    public void setLastIndex(int idx) {
        call("setLastIndex", idx);
    }

    public void stopDownload() {
        call("stopDownload");
    }

    public static void downloadingChapters(Array<Book> books, Array<Chapter> chapters) {
        _class.call("downloadingChapters", books, chapters);
    }

    public int pageCount() {
        return (int)call("pageCount");
    }
    public int completeCount() {
        return (int)call("completeCount");
    }
}
