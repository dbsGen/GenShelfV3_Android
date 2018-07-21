package apps.gen.lib.utils;

import android.content.Context;
import android.util.Log;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.controllers.NavigationController;
import apps.gen.lib.controllers.TabController;

/**
 * Created by gen on 16/4/23.
 * Helper of Gen libraries.
 */
public final class H {
    public static boolean debug = false;

    public static NavigationController navC(Controller thiz) {
        return NavigationController.getNavigationController(thiz);
    }
    public static TabController tabC(Controller thiz) {
        return TabController.getTabController(thiz);
    }
    public static int dip2px(Context context, float dipValue){
        final float scale = context.getResources().getDisplayMetrics().density;
        return (int)(dipValue * scale + 0.5f);
    }

    public static int px2dip(Context context, float pxValue){
        final float scale = context.getResources().getDisplayMetrics().density;
        return (int)(pxValue / scale + 0.5f);
    }

    public static void i(String msg, Object ...args) {info(msg, args);}
    public static void info(String format, Object ...args) {
        if (!debug) return;
        if (args.length > 0) {
            Log.i(Configs.LogTag, String.format(format, args));
        }else {
            Log.i(Configs.LogTag, format);
        }
    }

    public static void e(String err, Object ...args) {error(err, args);}
    public static void error(String err, Object ...args) {
        if (!debug) return;
        if (args.length > 0) {
            Log.e(Configs.LogTag, String.format(err, args));
        }else {
            Log.e(Configs.LogTag, err);
        }
    }

    public interface BaseInterface<T> {
        void run(T p);
    }
    public interface BaseInterface2<T, E> {
        void run(T p, E e);
    }

    public static NotificationCenter NC() {
        return NotificationCenter.instance();
    }

    public static String read(String path)
    {
        StringBuilder str=new StringBuilder("");
        File file=new File(path);
        try {
            FileReader fr=new FileReader(file);
            char[] chs = new char[2048];
            int len = 0;
            while((len = fr.read(chs))!=-1 )
            {
                str.append(chs, 0, len);
            }
            fr.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return str.toString();
    }

    public static boolean copy(String from, String to) {
        File fromFile = new File(from);
        File toFile = new File(to);
        if (!fromFile.exists()) {
            return false;
        }
        toFile.deleteOnExit();
        try {
            FileInputStream is = new FileInputStream(fromFile);
            FileOutputStream os = new FileOutputStream(toFile);
            final int len = 2048;
            int readed = 0;
            byte[] buffer = new byte[len];
            while ((readed = is.read(buffer)) > 0) {
                os.write(buffer, 0, readed);
            }
            os.close();
            is.close();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }
}
