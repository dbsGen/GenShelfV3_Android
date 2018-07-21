package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Array;

/**
 * Created by mac on 2017/10/12.
 */

@NativeClass("nl::SearchTip")
public class SearchTip extends Helper.GInstance {
    private static Helper.GClass<SearchTip> _class;
    static {
        _class = Helper.find(SearchTip.class);
    }
    public static void insert(String key) {
        _class.call("insert", key);
    }

    public static Array<String> search(String key) {
        return (Array<String>)_class.call("search", key);
    }
    public static void removeKey(String key) {
        _class.call("removeKey", key);
    }
}
