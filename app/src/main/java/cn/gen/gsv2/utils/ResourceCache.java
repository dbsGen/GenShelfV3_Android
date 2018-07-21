package cn.gen.gsv2.utils;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.support.v4.app.ActivityCompat;

import java.util.HashMap;

/**
 * Created by mac on 2017/8/14.
 */

public class ResourceCache {
    static HashMap<Integer, Drawable> map = new HashMap<>();

    public static Drawable getDrawable(Context context, int resId) {
        if (map.containsKey(resId)) {
            return map.get(resId);
        }else {
            if (context != null) {
                Drawable d = ActivityCompat.getDrawable(context, resId);
                map.put(resId, d);
                return d;
            }
        }
        return null;
    }
}
