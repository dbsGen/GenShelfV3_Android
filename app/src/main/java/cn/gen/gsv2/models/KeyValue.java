package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Array;

/**
 * Created by gen on 10/07/2017.
 */

@NativeClass("nl::KeyValue")
public class KeyValue extends Helper.GInstance {
    private static Helper.GClass<KeyValue> _class;
    static {
        _class = Helper.find(KeyValue.class);
    }

    public String getKey() {
        return (String)call("getKey");
    }

    public void setKey(String key) {
        call("setKey", key);
    }

    public String getValue() {
        return (String)call("getValue");
    }
    public void setValue(String value) {
        call("setValue", value);
    }

    public static String get(String key) {
        return (String)_class.call("get", key);
    }

    public static void set(String key, String value) {
        _class.call("set", key, value);
    }

    public static Array<String> search(String key) { return (Array<String>) _class.call("search", key); }
}
