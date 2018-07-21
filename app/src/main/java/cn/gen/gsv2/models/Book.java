package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Array;
import com.gr.classes.Map;

import java.util.Dictionary;

/**
 * Created by mac on 2017/6/3.
 */

@NativeClass("nl::Book")
public class Book extends Helper.GInstance {

    private static Helper.GClass<Book> _class;
    static {
        _class = Helper.find(Book.class);
    }

    public Book(){}

    public Book(boolean init) {
        if (init) {
            initialize();
        }
    }

    public static Array localBooks() {
        return (Array) _class.call("localBooks");
    }
    public static Array likedBooks() {
        return (Array)_class.call("likedBooks");
    }

    public String getName() {
        return (String)call("getName");
    }
    public void setName(String name) {
        call("setName", name);
    }
    public void setThumb(String thumb) {
        call("setThumb", thumb);
    }

    public String getThumb() {
        return (String)call("getThumb");
    }
    public Map getThumbHeaders() {
        return (Map)call("getThumbHeaders");
    }
    public String getSubtitle() {
        return (String)call("getSubtitle");
    }
    public void setSubtitle(String subtitle) {
        call("setSubtitle", subtitle);
    }
    public String getDes() {
        return (String)call("getDes");
    }
    public String getUrl() {
        return (String)call("getUrl");
    }
    public void setUrl(String url) {
        call("setUrl", url);
    }
    public String getShopId() {
        return (String)call("getShopId");
    }
    public void setShopId(String shopId) {
        call("setShopId", shopId);
    }
    public Map getChapters() {
        return (Map) call("getChapters");
    }
    public String picturePath(Chapter chapter, int index) {
        return (String) call("picturePath", chapter, index);
    }
    public void removeBook() {
        call("removeBook");
    }
    public void unlikeBook() {
        call("unlikeBook");
    }
    public void removeChapter(Chapter chapter) {
        call("removeChapter", chapter);
    }

    public boolean isLiked() {
        return (boolean)call("isLiked");
    }

    public Chapter lastChapter() {
        return (Chapter)call("lastChapter");
    }
    public void setLastChapter(Chapter chapter) {
        call("setLastChapter", chapter);
    }
}
