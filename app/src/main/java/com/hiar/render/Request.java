package com.hiar.render;

import android.content.Context;
import android.content.res.Resources;
import android.os.Handler;

import org.apache.http.entity.mime.Header;
import org.apache.http.entity.mime.HttpMultipartMode;
import org.apache.http.entity.mime.MultipartEntity;
import org.apache.http.entity.mime.content.ContentBody;
import org.apache.http.entity.mime.content.StringBody;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.StringBufferInputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Dictionary;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Locale;
import java.util.Map;
import java.util.TimeZone;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Created by mac on 2017/5/28.
 */

public class Request {

    private static final String CACHE_DIR = "caches";

    private static String file_dir;
    String key;
    long date;
    long length;
    NetworkRunnable threadHandler;
    static Handler handler = new Handler();
    boolean readCacheWhenError = true;
    boolean readCache;

    static Dictionary<String, Request> requests = new Hashtable<>();

    public interface OnStatusListener {
        void onProgress(Request request, float percent);

        void onComplete(Request request);

        void onFailed(Exception e);
        void onCancel(Request request);
    }

    public String method = "GET";
    public String url;
    public Map<String, String> headers;
    public Map<String, Object> params;
    public byte[] body;
    private String path;

    private Request() {
    }

    public void setParams(Map<String, Object> params) {
        this.params = params;
    }

    public Map<String, Object> getParams() {
        return params;
    }

    public String getCachePath() {
        Activity context = Activity.current();
        if (context == null) return "no";
        if (file_dir == null)
            file_dir = context.getFilesDir().toString();
        return file_dir + "/" + CACHE_DIR;
    }

    String  getCachePath(String file) {
        return getCachePath() + '/' + file;
    }

    public String getPath() {
        if (path == null) {
            try {
                MessageDigest md5 = MessageDigest.getInstance("MD5");
                md5.update(key.getBytes());
                byte[] b = md5.digest();
                StringBuffer sb = new StringBuffer();
                for (int i = 0; i < b.length; i++) {
                    sb.append(b[i]);
                }
                path = getCachePath(sb.toString());
            } catch (NoSuchAlgorithmException e) {
                e.printStackTrace();
            }
        }
        return path;
    }

    public void setReadCache(boolean readCache) {
        this.readCache = readCache;
    }

    public boolean isReadCache() {
        return readCache;
    }

    class NetworkRunnable implements Runnable {

        private Handler handler;
        private Request request;
        FileOutputStream fileStream;
        public AtomicBoolean cancel = new AtomicBoolean(false);

        @Override
        public void run() {
            if (fileStream == null) {
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        onFailed(new Resources.NotFoundException());
                    }
                });
                return;
            }
            try {
                File file = new File(getCachePath(request.getPath()));
                URL _url = new URL(request.url);
                HttpURLConnection connection = (HttpURLConnection) _url.openConnection();
                connection.setConnectTimeout(10 * 1000);
                connection.setRequestMethod(request.method);
                connection.setInstanceFollowRedirects(true);
                connection.setRequestProperty("User-Agent","Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/534.24 (KHTML, like Gecko) Chrome/11.0.696.34 Safari/534.24");
                boolean fileExists = file.exists();
                if (fileExists && request.date != 0) {
                    Date date = new Date(request.date);
                    SimpleDateFormat simple1 = new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss ", Locale.UK);
                    //设置 DateFormat的时间区域为GMT
                    simple1.setTimeZone(TimeZone.getTimeZone("GMT"));
                    connection.setRequestProperty("If-Modified-Since", simple1.format(date) + "GMT");
                }
                if (request.headers != null) {
                    for (String key : request.headers.keySet()) {
                        connection.setRequestProperty(key, request.headers.get(key));
                    }
                }
                if (request.body != null) {
                    connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
                    connection.setRequestProperty("Content-Length", "" + Integer.toString(request.body.length));
                    OutputStream os = connection.getOutputStream();
                    os.write(request.body);
                    os.close();
                }else if (request.params != null) {
                    Iterator<String> it = request.params.keySet().iterator();
                    MultipartEntity entity = new MultipartEntity(HttpMultipartMode.BROWSER_COMPATIBLE);
                    while (it.hasNext()) {
                        String key = it.next();
                        Object obj = request.params.get(key);
                        if (obj instanceof String) {
                            entity.addPart(key, new StringBody((String) obj, StandardCharsets.UTF_8));
                        }else if (obj instanceof ContentBody) {
                            entity.addPart(key, (ContentBody) obj);
                        }
                    }
                    connection.setDoInput(true);
                    connection.setDoOutput(true);
                    connection.setRequestProperty("Content-length", "" + entity.getContentLength());
                    org.apache.http.Header header = entity.getContentType();
                    connection.setRequestProperty(header.getName(), header.getValue());
                    ByteArrayOutputStream out = new ByteArrayOutputStream();
                    OutputStream os = connection.getOutputStream();
                    entity.writeTo(out);
                    byte[] bytes = out.toByteArray();
                    os.write(bytes);
                    os.close();
                    connection.connect();
                }

                int length = connection.getContentLength();
                int responseCode = connection.getResponseCode();
                while (responseCode == HttpURLConnection.HTTP_MOVED_TEMP ||
                        responseCode == HttpURLConnection.HTTP_MOVED_PERM) {
                    _url = new URL(connection.getHeaderField("Location"));
                    connection = (HttpURLConnection) _url.openConnection();
                    connection.setConnectTimeout(10 * 1000);
                    connection.setRequestMethod(request.method);
                    if (request.headers != null) {

                        for (String key : request.headers.keySet()) {
                            connection.setRequestProperty(key, request.headers.get(key));
                        }
                    }
                    if (request.body != null) {
                        connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
                        connection.setRequestProperty("Content-Length", "" + Integer.toString(request.body.length));
                        OutputStream os = connection.getOutputStream();
                        os.write(request.body);
                        os.close();
                    }
                    connection.setInstanceFollowRedirects(true);
                    responseCode = connection.getResponseCode();
                }
                if (responseCode == HttpURLConnection.HTTP_NOT_MODIFIED) {
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            request.onComplete();
                        }
                    });
                } else if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
                    InputStream ins = connection.getInputStream();
                    try {

                        byte[] buffer;
                        if (length > 1024 * 1024) {
                            buffer = new byte[10 * 1024];
                        } else {
                            buffer = new byte[1024];
                        }
                        request.length = length;
                        int len = 0;
                        int total_readed = 0;
                        while ((len = ins.read(buffer)) != -1) {
                            fileStream.write(buffer, 0, len);
                            total_readed += len;
                            if (length > 0) {
                                if (cancel.get()) {
                                    onCancel();
                                    fileStream.close();
                                    ins.close();
                                    return;
                                }
                                final float p = ((float) total_readed) / length;
                                handler.post(new Runnable() {
                                    @Override
                                    public void run() {
                                        request.onProgress(p);
                                    }
                                });
                            }
                        }
                        fileStream.close();
                        fileStream = null;
                        ins.close();
                        ins = null;
                        request.date = connection.getHeaderFieldDate("Last-Modified", 0);
                        (new File(request.getPath() + ".tmp")).renameTo(new File(request.getPath()));
                        handler.post(new Runnable() {
                            @Override
                            public void run() {
                                request.onComplete();
                            }
                        });
                    }catch (Exception e) {
                        if (ins != null) ins.close();
                    }
                } else {
                    if (fileExists) {
                        handler.post(new Runnable() {
                            @Override
                            public void run() {
                                request.onComplete();
                            }
                        });
                    } else {
                        handler.post(new Runnable() {
                            @Override
                            public void run() {
                                request.onFailed(new Exception("Error"));
                            }
                        });
                    }
                }
            } catch (final MalformedURLException e) {
                e.printStackTrace();
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        request.onFailed(e);
                    }
                });
            } catch (final Exception e) {
                e.printStackTrace();
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        request.onFailed(e);
                    }
                });
            }
        }

        public NetworkRunnable(Handler handler,
                               Request request) {
            this.handler = handler;
            this.request = request;
            File dir = new File(getCachePath());
            if (!dir.exists()) {
                dir.mkdir();
            }
            File _file = new File(request.getPath() + ".tmp");
            _file.deleteOnExit();
            try {
                fileStream = new FileOutputStream(_file);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public void cancel() {
            if (fileStream != null) {
                try {
                    fileStream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                fileStream = null;
            }
            cancel.set(true);
        }
    }

    OnStatusListener listener;

    public void setListener(OnStatusListener listener) {
        this.listener = listener;
    }

    public OnStatusListener getListener() {
        return listener;
    }

    void onComplete() {
        threadHandler = null;
        if (listener != null) {
            listener.onComplete(this);
        }
    }
    void onFailed(Exception e) {
        threadHandler = null;
        if (readCacheWhenError) {
            File file = new File(getPath());
            if (file.exists()) {
                onComplete();
                return;
            }
        }
        if (listener != null) {
            listener.onFailed(e);
        }
    }

    void onProgress(float p) {
        if (listener != null) {
            listener.onProgress(this, p);
        }
    }

    void onCancel() {
        if (listener != null) {
            listener.onCancel(this);
        }
        threadHandler = null;
    }

    Runnable startHandler = new Runnable() {
        @Override
        public void run() {
            start();
        }
    };

    public void cancel() {
        if (threadHandler != null) {
            threadHandler.cancel();
            threadHandler = null;
        }
        handler.removeCallbacks(startHandler);
    }

    public void start() {
        File file = new File(getPath());
        if (file.exists() && readCache) {
            if (listener != null) {
                listener.onComplete(this);
            }
        }else {
            if (threadHandler == null) {
                threadHandler = new NetworkRunnable(handler, this);
                new Thread(threadHandler).start();
            }
        }
    }

    public void start(float delay) {
        handler.postDelayed(startHandler, (long)(delay * 1000));
    }

    public static Request get(String url) {
        return get(url, url);
    }

    public static Request get(String url, String key) {
        Request request = requests.get(key);
        if (request == null) {
            request = new Request();
            request.url = url;
            request.key = key;
            requests.put(key, request);
        }
        return request;
    }
}
