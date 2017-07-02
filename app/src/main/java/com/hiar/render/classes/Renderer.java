package com.hiar.render.classes;

import android.util.Log;
import android.util.SizeF;

import com.hiar.render.HiRender;
import com.hiar.render.NativeClass;

import java.util.ArrayList;

/**
 * Created by gen on 24/11/2016.
 */

@NativeClass("hirender::Renderer")
public class Renderer extends HiRender.HiInstance {
    private static HiRender.HiClass<Renderer> _class;
    public static void register() {
        HiRender.registerClass(Renderer.class);
    }

    public static HiRender.HiClass<Renderer> cls() {
        if (_class == null) {
            _class = HiRender.find(Renderer.class);
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
