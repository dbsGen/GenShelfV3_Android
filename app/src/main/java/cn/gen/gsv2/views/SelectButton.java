package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.support.v4.app.ActivityCompat;
import android.util.AttributeSet;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import com.gr.Activity;

import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;

/**
 * Created by mac on 2017/6/12.
 */

public class SelectButton extends RelativeLayout {

    ImageView arrowView;

    public SelectButton(Context context) {
        super(context);
        init(context);
    }

    public SelectButton(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public SelectButton(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    void init(Context context) {
        arrowView = new ImageView(context);
        Drawable drawable = ActivityCompat.getDrawable(context, R.drawable.tri);
        drawable.mutate().setColorFilter(Color.WHITE, PorterDuff.Mode.SRC_IN);
        arrowView.setImageDrawable(drawable);
        int px = H.dip2px(context, 12);
        LayoutParams layoutParams = new LayoutParams(px, px);
        layoutParams.addRule(ALIGN_PARENT_END, TRUE);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        arrowView.setLayoutParams(layoutParams);
        addView(arrowView);

        setBackground(ActivityCompat.getDrawable(context, R.drawable.ripple));
    }

    public void extend(boolean e) {
        if (e) {
            RotateAnimation animation = new RotateAnimation(0, 180, Animation.RELATIVE_TO_SELF, 0.5f, Animation.RELATIVE_TO_SELF, 0.5f);
            animation.setFillAfter(true);
            animation.setDuration(300);
            arrowView.startAnimation(animation);
        }else {
            RotateAnimation animation = new RotateAnimation(180, 0, Animation.RELATIVE_TO_SELF, 0.5f, Animation.RELATIVE_TO_SELF, 0.5f);
            animation.setFillAfter(true);
            animation.setDuration(300);
            arrowView.startAnimation(animation);
        }
    }
}
