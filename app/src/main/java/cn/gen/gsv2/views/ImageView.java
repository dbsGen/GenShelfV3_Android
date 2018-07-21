package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;

import com.gr.Request;
import com.gr.classes.Array;
import com.gr.classes.Map;

import apps.gen.lib.utils.ResourcePool;
import cn.gen.gsv2.R;
import cn.gen.gsv2.utils.ResourceCache;

/**
 * Created by gen on 27/07/2017.
 */

public class ImageView extends RelativeLayout implements ResourcePool.OnReleaseListener {

    public android.widget.ImageView imageView;
    Bitmap bitmap;
    Request currentRequest;
    ResourcePool pool;

    public ImageView(Context context) {
        super(context);
        init(context);
    }

    public ImageView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public ImageView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    @Override
    protected void finalize() throws Throwable {
        if (bitmap != null) {
            bitmap.recycle();
        }
        super.finalize();
    }

    void init(Context context) {
        pool = ResourcePool.current();
        pool.addRelease(this);

        imageView = new android.widget.ImageView(context);
        LayoutParams params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT);
        imageView.setScaleType(android.widget.ImageView.ScaleType.CENTER_CROP);
        imageView.setLayoutParams(params);
        addView(imageView);
    }

    public void setUrl(String url) {
        setUrl(url, null);
    }

    public void setUrl(String url, Map headers) {
        if (bitmap != null) {
            bitmap.recycle();
            bitmap = null;
        }
        if (currentRequest != null) {
            currentRequest.setListener(null);
            currentRequest = null;
        }
        imageView.setImageDrawable(ResourceCache.getDrawable(getContext(), R.drawable.no_image));
        Request request = Request.get(url);
        request.setReadCache(true);
        if (headers != null) {
            Array<String> keys = headers.keys();
            for (String key : keys) {
                request.addHeader(key, (String)headers.get(key));
            }
        }
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                request.setListener(null);
                currentRequest = null;
                try {
                    bitmap = BitmapFactory.decodeFile(request.getPath());
                    imageView.setImageBitmap(bitmap);
                }catch (Exception e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onFailed(Exception e) {
                currentRequest.setListener(null);
                currentRequest = null;
            }

            @Override
            public void onCancel(Request request) {

            }
        });
        currentRequest = request;
        request.start();
    }

    @Override
    public void onRelease() {
        if (bitmap != null) {
            bitmap.recycle();
            bitmap = null;
            imageView.setImageBitmap(null);
        }
        if (currentRequest != null) {
            currentRequest.setListener(null);
            currentRequest = null;
        }
    }
}
