package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Callback;

/**
 * Created by mac on 2017/6/3.
 */

@NativeClass("nl::Library")
public class Library extends Helper.GInstance {
    private static Helper.GClass<Library> _class;
    static {
        _class = Helper.find(Library.class);
    }

    public Library(){}
    public Library(boolean init) {
        if (init) {
            initialize();
        }
    }

    public void applyLoad(int page, Callback callback) {
        call("applyLoad", page, callback);
    }
}
