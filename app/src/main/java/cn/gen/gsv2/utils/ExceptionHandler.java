package cn.gen.gsv2.utils;

import android.app.Application;
import android.content.Context;
import android.os.Build;
import android.util.Log;

import com.gr.Activity;
import com.gr.Request;

import org.apache.http.entity.mime.content.FileBody;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Date;

import apps.gen.lib.utils.H;

/**
 * Created by gen on 16/06/2017.
 */

public class ExceptionHandler implements Thread.UncaughtExceptionHandler {

    private Thread.UncaughtExceptionHandler originalHandler;
    static ExceptionHandler handler;
    String filePath;

    public static void setup(String path) {
        if (handler != null) return;
        Thread.UncaughtExceptionHandler original = Thread.getDefaultUncaughtExceptionHandler();
        if (!(original instanceof ExceptionHandler)) {
            handler = new ExceptionHandler();
            handler.originalHandler = original;
            handler.filePath = path;
            Log.i("path", path);
            Thread.setDefaultUncaughtExceptionHandler(handler);
        }
    }

    private void writeLine(FileOutputStream os, String line) throws IOException {
        os.write(line.getBytes());
        os.write("\n".getBytes());
    }

    public static void post(Context context) {
        final File file = new File(handler.filePath);
        if (file.exists()) {
            Request request = Request.get("http://112.74.13.80:3000/crash");
            request.method = "POST";
            request.addParams("file", H.read(handler.filePath));
            request.addParams("os_version", Build.VERSION.RELEASE + "|" + Analysis.getVersion(context));
            request.addParams("device", Build.MODEL);
            request.setReadCache(false);
            request.setListener(new Request.OnStatusListener() {
                @Override
                public void onProgress(Request request, float percent) {

                }

                @Override
                public void onComplete(Request request) {
                    file.delete();
                }

                @Override
                public void onFailed(Exception e) {

                }

                @Override
                public void onCancel(Request request) {

                }
            });
            request.start();
        }
    }

    @Override
    public void uncaughtException(Thread t, Throwable e) {
        StackTraceElement[] es = e.getStackTrace();
        File file = new File(filePath);
        try {
            file.deleteOnExit();
            FileOutputStream os = new FileOutputStream(file);
            writeLine(os, new Date().toString());
            writeLine(os, e.getMessage());
            for (StackTraceElement stack :
                    es) {
                writeLine(os, String.format("%s %s(%s:%d)", stack.getFileName(), stack.getClassName(), stack.getMethodName(), stack.getLineNumber()));
            }
            os.close();
        } catch (Exception e1) {
            e1.printStackTrace();
        }


        if (originalHandler != null) {
            originalHandler.uncaughtException(t, e);
        }
    }
}
