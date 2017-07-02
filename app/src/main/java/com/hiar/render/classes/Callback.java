package com.hiar.render.classes;

import com.hiar.render.HiRender;
import com.hiar.render.NativeClass;

/**
 * Created by gen on 01/06/2017.
 */

@NativeClass("hicore::Callback")
public class Callback extends HiRender.HiInstance {
    private static HiRender.HiClass<Callback> _class;
    static {
        _class = HiRender.find(Callback.class);
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
        return run(args.toArray());
    }
    public Object run(Object... args) {
        return null;
    }
    public Object invoke(Object... args) {
        return call("invoke", args);
    }
}
