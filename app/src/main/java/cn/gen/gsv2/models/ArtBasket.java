package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Array;

/**
 * Created by mac on 2017/7/27.
 */

@NativeClass("nl::ArtBasket")
public class ArtBasket extends Helper.GInstance {

    @NativeClass("nl::Art")
    public static class Art extends Helper.GInstance {
        private static Helper.GClass<Art> _class;
        static {
            _class = Helper.find(Art.class);
        }

        public int getType() {
            return (int)call("getType");
        }

        public String getShopId() {
            return (String)call("getShopId");
        }

        public String getUrl() {
            return (String)call("getUrl");
        }
        public String getName() {
            return (String)call("getName");
        }
        public String getThumb() {
            return (String)call("getThumb");
        }
        public String getThumbRef() {
            return (String)call("getThumbRef");
        }
        public String getChapterUrl() {
            return (String)call("getChapterUrl");
        }
        public String getChapterName() {
            return (String)call("getChapterName");
        }

        public String html() {
            return (String)call("html");
        }

        public static Array parse(String content) {
            return (Array)_class.call("parse", content);
        }

        static void reg() {}
    }

    private static Helper.GClass<ArtBasket> _class;
    static {
        _class = Helper.find(ArtBasket.class);
        Art.reg();
    }

    public static void addBook(Book book) {
        _class.call("addBook", book);
    }

    public static void addChapter(Book book, Chapter chapter) {
        _class.call("addChapter", book, chapter);
    }

    public static Array<Art> getArts() {
        return (Array<Art>)_class.call("getArts");
    }
}
