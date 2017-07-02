package com.hiar.render.classes;

import com.hiar.render.HiRender;
import com.hiar.render.NativeClass;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by gen on 01/06/2017.
 */

@NativeClass("hirender::NotificationCenter")
public class NotificationCenter extends HiRender.HiInstance {
    private static HiRender.HiClass<NotificationCenter> _class;

    public static HiRender.HiClass<NotificationCenter> cls() {
        if (_class == null) {
            _class = HiRender.find(NotificationCenter.class);
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
