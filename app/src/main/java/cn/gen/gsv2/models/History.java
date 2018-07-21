package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Array;

/**
 * Created by mac on 2017/8/27.
 */


@NativeClass("nl::History")
public class History extends Helper.GInstance {
    private static Helper.GClass<History> _class;
    static {
        _class = Helper.find(History.class);
    }

    public static void visit(Book book) {
        _class.call("visit", book);
    }

    public static Array<History> histories(long from) {
        return (Array<History>)_class.call("histories", from);
    }

    public static void clear() {
        _class.call("clear");
    }

    public Book getBook() {
        return (Book) call("getBook");
    }

    public long getDate() {
        return (long) call("getDate");
    }
}
