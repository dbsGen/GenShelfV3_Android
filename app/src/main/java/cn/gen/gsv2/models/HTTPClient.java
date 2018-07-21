package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;

/**
 * Created by gen on 13/06/2017.
 */

@NativeClass("gr::HTTPClient")
public class HTTPClient extends Helper.GInstance {
    private static Helper.GClass<HTTPClient> _class;
    static {
        _class = Helper.find(HTTPClient.class);
    }
    public static void register() {
    }

    public void start() {
        call("start");
    }
    public void cancel() {
        call("cancel");
    }
}
