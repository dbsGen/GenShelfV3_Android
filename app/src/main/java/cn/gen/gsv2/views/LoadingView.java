package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.ViewGroup;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.RotateAnimation;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;

/**
 * Created by mac on 2017/6/9.
 */

public class LoadingView extends RelativeLayout {
    public static final int STATUS_LOADING = 0;
    public static final int STATUS_FAILED = 1;
    public static final int STATUS_MISSING = 2;

    int status;
    ImageView imageView;

    public int getStatus() {
        return status;
    }

    public LoadingView(Context context) {
        super(context);
        init(context);
    }

    public LoadingView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public LoadingView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private void init(Context context) {
        imageView = new ImageView(context);
        imageView.setImageResource(R.drawable.no_image);
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.addRule(CENTER_HORIZONTAL, TRUE);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        imageView.setLayoutParams(layoutParams);
        addView(imageView);

        setBackgroundColor(Color.WHITE);
    }

    public void startLoading() {
        imageView.setVisibility(VISIBLE);
        imageView.setImageResource(R.drawable.no_image);

        AnimationSet set = new AnimationSet(true);
        set.setDuration(100);

        RotateAnimation animation = new RotateAnimation(-3, 3,
                Animation.RELATIVE_TO_SELF, 0.5f,
                Animation.RELATIVE_TO_SELF, 0.5f);
        animation.setDuration(100);
        animation.setRepeatCount(Animation.INFINITE);
        animation.setRepeatMode(Animation.REVERSE);
        set.addAnimation(animation);

        int pix = H.dip2px(getContext(), 2);
        TranslateAnimation trans = new TranslateAnimation(-pix, pix, 0, 0);
        trans.setDuration(100);
        trans.setRepeatCount(Animation.INFINITE);
        trans.setRepeatMode(Animation.REVERSE);
        set.addAnimation(trans);

        imageView.startAnimation(set);

        status = STATUS_LOADING;
    }

    public void failed() {
        imageView.clearAnimation();
        imageView.setImageResource(R.drawable.failed);
        status = STATUS_FAILED;
    }

    public void miss() {
        AlphaAnimation animation = new AlphaAnimation(1, 0);
        animation.setDuration(300);
        animation.setAnimationListener(new Animation.AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {

            }

            @Override
            public void onAnimationEnd(Animation animation) {
                setVisibility(GONE);
            }

            @Override
            public void onAnimationRepeat(Animation animation) {

            }
        });
        startAnimation(animation);
        status = STATUS_MISSING;
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent ev) {
        return true;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return true;
    }
}
