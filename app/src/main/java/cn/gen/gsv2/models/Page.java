package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Map;

import java.util.Dictionary;

/**
 * Created by mac on 2017/6/9.
 */

@NativeClass("nl::Page")
public class Page extends Helper.GInstance {

    private static Helper.GClass<Page> _class;
    static {
        _class = Helper.find(Page.class);
    }

    public static void register(){}

    public String getPicture() {
        return (String)call("getPicture");
    }
    public String getMethod() {
        return (String)call("getMethod");
    }
    public Map getHeaders() {
        return (Map)call("getHeaders");
    }
    public Map getParameters() {
        return (Map)call("getParameters");
    }
}
