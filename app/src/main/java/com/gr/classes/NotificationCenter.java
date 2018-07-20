package com.gr.classes;

import com.gr.Helper;
import com.gr.NativeClass;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by gen on 01/06/2017.
 */

@NativeClass("gr::NotificationCenter")
public class NotificationCenter extends Helper.GInstance {
    private static Helper.GClass<NotificationCenter> _class;

    public static Helper.GClass<NotificationCenter> cls() {
        if (_class == null) {
            _class = Helper.find(NotificationCenter.class);
        }
        return _class;
    }

    public void listen(String name, Callback callback) {
        call("listen", name, callback);
    }
    public void remove(String name, Callback callback) {
        call("remove", name, callback);
    }
    public static NotificationCenter getInstance() {
        return (NotificationCenter)cls().call("getInstance");
    }
}
