package cn.gen.gsv2.utils;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.provider.Settings;
import android.util.Log;

import com.gr.Request;

import org.apache.http.entity.mime.MultipartEntity;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URLEncoder;
import java.util.HashMap;

/**
 * Created by mac on 2017/6/30.
 */

public class Analysis {
    static final String AnalysisURL = "http://112.74.13.80:3000/analysis";

    public static String getVersion(Context context) {
        try {
            PackageManager manager = context.getPackageManager();
            PackageInfo info = manager.getPackageInfo(context.getPackageName(), 0);
            String version = info.versionName;
            return version;
        } catch (Exception e) {
            e.printStackTrace();
            return "0.0";
        }
    }

    public static void run(final Context context) {
        Request request = Request.get("http://ip.chinaz.com/getip.aspx");
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                try {
                    File file = new File(request.getPath());
                    FileInputStream is = new FileInputStream(file);
                    BufferedReader reader = new BufferedReader(new InputStreamReader(is));
                    StringBuilder sb = new StringBuilder();
                    String line = null;
                    while ((line = reader.readLine()) != null) {
                        sb.append(line).append("\n");
                    }
                    reader.close();
                    is.close();
                    JSONObject json = new JSONObject(sb.toString());
                    Request req = Request.get(AnalysisURL);
                    req.method = "POST";
                    HashMap<String, Object> params = new HashMap<String, Object>();
                    params.put("ip", json.get("ip"));
                    params.put("address", json.get("address"));
                    String android_id = Settings.Secure.getString(context.getContentResolver(),
                            Settings.Secure.ANDROID_ID);
                    params.put("udid", android_id);
                    params.put("os", "android");
                    params.put("os_version", Build.VERSION.RELEASE);
                    params.put("device", Build.MODEL);
                    params.put("version", getVersion(context));
                    req.setParams(params);
                    req.setListener(new Request.OnStatusListener() {
                        @Override
                        public void onProgress(Request request, float percent) {

                        }

                        @Override
                        public void onComplete(Request request) {
                            Log.i("complete", "Analysis complete");
                        }

                        @Override
                        public void onFailed(Exception e) {

                        }

                        @Override
                        public void onCancel(Request request) {

                        }
                    });
                    req.start();
                } catch (Exception e) {
                    e.printStackTrace();
                }

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
