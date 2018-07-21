package cn.gen.gsv2.utils;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.support.v4.app.ActivityCompat;
import android.text.style.ImageSpan;

import com.gr.Request;

import java.io.File;

import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.ArtBasket;

import static android.graphics.Bitmap.Config.ARGB_4444;
import static android.graphics.Bitmap.Config.RGB_565;

/**
 * Created by mac on 2017/7/28.
 */

public class ArtSpan extends ImageSpan {

    Bitmap bitmap;
    static Rect bounds = new Rect();

    public ArtSpan(Drawable d, Bitmap bitmap) {
        super(d);
        this.bitmap = bitmap;
    }

    @Override
    protected void finalize() throws Throwable {
        if (bitmap != null)
            bitmap.recycle();
        super.finalize();
    }

    public static ImageSpan from(Context context, ArtBasket.Art art) {
        int m = H.dip2px(context, 10);

        Paint paint = new Paint();
        paint.setTextSize(m * 16/10);
        paint.getTextBounds(art.getName(), 0, art.getName().length(), bounds);

        Bitmap bitmap = Bitmap.createBitmap(m * 5 + bounds.width(), m * 4, ARGB_4444);
        Canvas canvas = new Canvas(bitmap);
        canvas.drawColor(Color.TRANSPARENT);
        Request request = Request.get(art.getThumb());
        File file = new File(request.getPath());
        if (file.exists()) {
            Bitmap bm = BitmapFactory.decodeFile(request.getPath());
            canvas.drawBitmap(bm,
                    new Rect(0, 0, bm.getWidth(), bm.getHeight())
                    , new Rect(m/2, m/2, m*3, m*3), paint);
            bm.recycle();
        }else {
            Drawable d = ActivityCompat.getDrawable(context, R.drawable.no_image);
            d.setBounds(m/2, m/2, m*3, m*3);
            d.draw(canvas);
        }

        BitmapDrawable drawable = new BitmapDrawable(bitmap);
        drawable.setBounds(0, 0, bitmap.getWidth(), bitmap.getHeight());
        ArtSpan span = new ArtSpan(drawable, bitmap);

        canvas.drawText(art.getName(), m*4, m + bounds.height(), paint);

        return span;
    }
}
