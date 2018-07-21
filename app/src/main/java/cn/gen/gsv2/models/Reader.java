package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Callback;

/**
 * Created by gen on 09/06/2017.
 */

@NativeClass("nl::Reader")
public class Reader extends Helper.GInstance {
    private static Helper.GClass<Reader> _class;
    static {
        _class = Helper.find(Reader.class);
    }

    public Reader(boolean init) {
        if (init) {
            initialize();
        }
    }

    Callback onPageCount;
    Callback onPageLoaded;

    public void setOnPageCount(Callback onPageCount) {
        this.onPageCount = onPageCount;
        call("setOnPageCount", onPageCount);
    }

    public Callback getOnPageCount() {
        return onPageCount;
    }

    public void setOnPageLoaded(Callback onPageLoaded) {
        this.onPageLoaded = onPageLoaded;
        call("setOnPageLoaded", onPageLoaded);
    }

    public Callback getOnPageLoaded() {
        return onPageLoaded;
    }
}
