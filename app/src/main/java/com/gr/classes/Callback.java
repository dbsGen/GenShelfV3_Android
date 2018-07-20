package com.gr.classes;

import com.gr.Helper;
import com.gr.NativeClass;

/**
 * Created by gen on 01/06/2017.
 */

@NativeClass("gcore::Callback")
public class Callback extends Helper.GInstance {
    private static Helper.GClass<Callback> _class;
    static {
        _class = Helper.find(Callback.class);
    }
    public static void register() {
    }

    public Callback() {}
    public Callback(boolean init) {
        if (init) initialize();
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
    }

    public Object _invoke(Array args) {
        Object ret = null;
        try {
            ret = run(args.toArray());
        }catch (Exception e) {
            e.printStackTrace();
        }
        return ret;
    }
    public Object run(Object... args) {
        return null;
    }
    public Object invoke(Object... args) {
        return call("invoke", new Object[]{args});
    }
}
