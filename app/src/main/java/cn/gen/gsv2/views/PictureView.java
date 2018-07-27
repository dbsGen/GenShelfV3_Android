package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.graphics.RectF;
import android.os.Debug;
import android.support.annotation.DrawableRes;
import android.util.AttributeSet;
import android.util.Log;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.HorizontalScrollView;
import android.widget.ImageView;
import android.widget.ScrollView;

import com.boycy815.pinchimageview.PinchImageView;
import com.gr.Request;
import com.gr.classes.Array;
import com.gr.classes.Map;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Dictionary;
import java.util.Enumeration;
import java.util.HashMap;

import apps.gen.lib.utils.H;
import apps.gen.lib.utils.ResourcePool;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Chapter;
import cn.gen.gsv2.models.Page;
import cn.gen.gsv2.utils.ResourceCache;

/**
 * Created by gen on 09/06/2017.
 */

public class PictureView extends PinchImageView implements ResourcePool.OnReleaseListener {

    Request currentRequest;
    float width, height;
    Bitmap bitmap;
    String path;

    public PictureView(Context context) {
        super(context);
        init(context);
    }

    public PictureView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public PictureView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private void init(Context context) {
        ResourcePool.current().addRelease(this);
    }

    public void clear() {
        if (bitmap != null) {
            bitmap.recycle();
            bitmap = null;
            setImageBitmap(null);
        }
        this.path = null;
    }

    @Override
    protected void finalize() throws Throwable {
        clear();
        super.finalize();
    }

    @Override
    public void setImageBitmap(Bitmap bm) {
        super.setImageBitmap(bm);
        if (bm != null) {
            width = bm.getWidth();
            height = bm.getHeight();
            int w = getWidth();
            int h = getHeight();
            if (w != 0 && h != 0) {
                updateSize(w, h);
            }
        }
    }

    void updateSize(int w, int h) {
        if (height/width > 16/9.0f) {
            Matrix mat = MathUtils.matrixTake();
            getOuterMatrix(mat);
            float scale = w/(width*h/height);
            mat.setTranslate((width*h/height-w)/2, 0);
            mat.postScale(scale, scale);
            outerMatrixTo(mat, 300);
        }else if (height/width < 1.0f) {
            Matrix mat = MathUtils.matrixTake();
            getOuterMatrix(mat);
            int h2 = (int) (h * 0.9);
            float scale = h2/(height*w/width);
            mat.setTranslate(0, (height*w/width-h*0.975f)/2);
            mat.postScale(scale, scale);
            outerMatrixTo(mat, 300);
        }else {
            Matrix mat = MathUtils.matrixTake();
            outerMatrixTo(mat, 300);
        }
    }

    int doubleTapStatus = 0;

    @Override
    protected void doubleTap(float x, float y) {
        if (isReady()) {
            if (doubleTapStatus == 0 ||
                    doubleTapStatus == 1) {
                super.doubleTap(x, y);
            }else {
                int w = getWidth();
                int h = getHeight();
                updateSize(w, h);
            }
            doubleTapStatus += 1;
            if (doubleTapStatus == 3) {
                doubleTapStatus = 0;
            }
        }
//        super.doubleTap(x, y);
    }

    boolean eq(String p1, String p2) {
        if (p1 == null && p2 == null) {
            return true;
        }else if (p1 == null || p2 == null) {
            return false;
        }else {
            return p1.equals(p2);
        }
    }

    public void setImagePath(String path) {
        if (!eq(this.path, path)) {
            if (bitmap != null) {
                bitmap.recycle();
            }
            bitmap = BitmapFactory.decodeFile(path);
            setImageBitmap(bitmap);
            this.path = path;
        }else {
            setImageBitmap(bitmap);
        }
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);

        updateSize(w, h);
    }

    public static Request requestPage(Page page) {
        Request request = Request.get(page.getPicture());
        request.setReadCache(true);
        request.method = page.getMethod();
        Map headers = page.getHeaders();
        Array keys = headers.keys();
        request.headers = new HashMap<>();
        for (Object key : keys) {
            request.headers.put(key.toString(), headers.get(key).toString());
        }
        return request;
    }

    public void setPage(final Page page) {
        if (currentRequest != null) {
            currentRequest.setListener(null);
            currentRequest = null;
        }
        setImageDrawable(ResourceCache.getDrawable(getContext(), R.drawable.no_image));
        Matrix mat = MathUtils.matrixTake();
        outerMatrixTo(mat, 300);
        Request request = Request.get(page.getPicture());
        request.setReadCache(true);
        request.method = page.getMethod();
        Map headers = page.getHeaders();
        Array keys = headers.keys();
        request.headers = new HashMap<>();
        for (Object key : keys) {
            request.headers.put(key.toString(), headers.get(key).toString());
        }
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                setImagePath(request.getPath());
                currentRequest.setListener(null);
                currentRequest = null;
            }

            @Override
            public void onFailed(Exception e) {
                setImageDrawable(ResourceCache.getDrawable(getContext(), R.drawable.failed));
                currentRequest.setListener(null);
                currentRequest = null;
            }

            @Override
            public void onCancel(Request request) {
                currentRequest = null;
            }
        });
        currentRequest = request;
        request.start();
    }

    public void reset() {
        setImageDrawable(ResourceCache.getDrawable(getContext(), R.drawable.no_image));
    }

    @Override
    public void onRelease() {
        clear();
        if (currentRequest != null) {
            currentRequest.setListener(null);
            currentRequest = null;
        }
    }
}
