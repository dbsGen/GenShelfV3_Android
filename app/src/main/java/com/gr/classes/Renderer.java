package com.gr.classes;

import android.util.Log;
import android.util.SizeF;

import com.gr.Helper;
import com.gr.NativeClass;

import java.util.ArrayList;

/**
 * Created by gen on 24/11/2016.
 */

@NativeClass("gr::Renderer")
public class Renderer extends Helper.GInstance {
    private static Helper.GClass<Renderer> _class;
    public static void register() {
        Helper.registerClass(Renderer.class);
    }

    public static Helper.GClass<Renderer> cls() {
        if (_class == null) {
            _class = Helper.find(Renderer.class);
        }
        return _class;
    }

    public void setSize(SizeF size) {
        call("setSize", size);
    }

    public void render() {
        call("render");
    }

}
