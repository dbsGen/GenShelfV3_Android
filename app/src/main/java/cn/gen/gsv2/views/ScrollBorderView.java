package cn.gen.gsv2.views;

import android.animation.ObjectAnimator;
import android.content.Context;
import android.os.Build;
import android.support.v4.app.ActivityCompat;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.Interpolator;
import android.view.animation.ScaleAnimation;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import java.util.Date;

import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;

/**
 * Created by gen on 08/06/2017.
 */

public class ScrollBorderView extends RelativeLayout implements ViewPager.OnDragBorderListener {
    ViewPager viewPager;
    float offsetX;
    float offsetY;
    int dragDownStatus = 0;
    RelativeLayout prevView;
    RelativeLayout nextView;
    int buttonWidth;
    boolean single;
    boolean bording = false;

    @Override
    public void border() {
        bording = true;
    }

    public interface OnChapterListener {
        void onChapter(boolean chapter);
    }
    OnChapterListener onChapterListener;

    public void setOnChapterListener(OnChapterListener onChapterListener) {
        this.onChapterListener = onChapterListener;
    }

    public OnChapterListener getOnChapterListener() {
        return onChapterListener;
    }

    public ScrollBorderView(Context context) {
        super(context);
        init(context);
    }

    public ScrollBorderView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public ScrollBorderView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private void init(Context context) {
        prevView = new RelativeLayout(context);
        int dp36 = H.dip2px(context, 42);
        buttonWidth = dp36 + H.dip2px(context, 6);
        LayoutParams layoutParams = new LayoutParams(dp36, dp36);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        prevView.setLayoutParams(layoutParams);
        prevView.setBackground(ActivityCompat.getDrawable(context, R.drawable.circle));
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            prevView.setZ(H.dip2px(context, 2));
        }

        ImageView arrow = new ImageView(context);
        int dp18 = H.dip2px(context, 18);
        layoutParams = new LayoutParams(dp18, dp18);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(CENTER_HORIZONTAL, TRUE);
        arrow.setLayoutParams(layoutParams);
        arrow.setImageResource(R.drawable.arrow_right);
        prevView.addView(arrow);
        addView(prevView);
        prevView.setX(-buttonWidth);

        nextView = new RelativeLayout(context);
        layoutParams = new LayoutParams(dp36, dp36);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(ALIGN_PARENT_RIGHT, TRUE);
        nextView.setLayoutParams(layoutParams);
        nextView.setBackground(ActivityCompat.getDrawable(context, R.drawable.circle));
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            nextView.setZ(H.dip2px(context, 2));
        }

        arrow = new ImageView(context);
        layoutParams = new LayoutParams(dp18, dp18);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(CENTER_HORIZONTAL, TRUE);
        arrow.setLayoutParams(layoutParams);
        arrow.setImageResource(R.drawable.arrow_right);
        arrow.setRotation(180);
        nextView.addView(arrow);
        addView(nextView);
        nextView.setX(buttonWidth);
    }

    @Override
    public void onViewAdded(View child) {
        super.onViewAdded(child);
        if (child instanceof ViewPager) {
            viewPager = (ViewPager)child;
            viewPager.setOnDragBorderListener(this);
        }
    }

    @Override
    public boolean canScrollVertically(int direction) {
        return dragDownStatus == 2 || viewPager.canScrollVertically(direction);
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent ev) {
        if (ev.getPointerCount() != 1 || viewPager == null) return false;
//        if (bording) {
//            offsetX = 0;
//            return true;
//        }
        return true;
    }

    @Override
    public boolean onTouchEvent(MotionEvent ev) {
        if (viewPager == null) return false;
        if (offsetX == 0) {
            single = ev.getPointerCount() == 1;
            offsetX = ev.getX();
            offsetY = ev.getY();
        }
        boolean send = true;
        if (single) {
            switch (ev.getAction()) {
                case MotionEvent.ACTION_UP: {
                    bording = false;
                    dragDownStatus = 0;
                    offsetY = 0;
                    offsetX = 0;
                    int count = viewPager.getAdapter().getCount(), idx = viewPager.getCurrentItem();
                    if (idx == 0) {
                        if (prevView.getTranslationX() >= H.dip2px(getContext(), 10)) {
                            if (onChapterListener != null)
                                onChapterListener.onChapter(false);
                            ScaleAnimation animation = new ScaleAnimation(1, 0, 1, 0,
                                    Animation.RELATIVE_TO_SELF, 0.5f,
                                    Animation.RELATIVE_TO_SELF, 0.5f);
                            animation.setDuration(400);
                            animation.setInterpolator(new Interpolator() {
                                @Override
                                public float getInterpolation(float input) {
                                    float s = 1.70158f;
                                    return input * input * ((s + 1) * input - s);
                                }
                            });
                            animation.setAnimationListener(new Animation.AnimationListener() {
                                @Override
                                public void onAnimationStart(Animation animation) {

                                }

                                @Override
                                public void onAnimationEnd(Animation animation) {
                                    prevView.setTranslationX(-buttonWidth);
                                }

                                @Override
                                public void onAnimationRepeat(Animation animation) {

                                }
                            });
                            prevView.startAnimation(animation);
                            send = false;
                        }else {
                            ObjectAnimator animator = ObjectAnimator.ofFloat(prevView, "translationX", prevView.getTranslationX(), -buttonWidth);
                            animator.setDuration(400);
                            animator.start();
                        }
                    }
                    if (idx == count - 1) {
                        if (nextView.getTranslationX() <= H.dip2px(getContext(), -10)) {
                            if (onChapterListener != null)
                                onChapterListener.onChapter(true);
                            ScaleAnimation animation = new ScaleAnimation(1, 0, 1, 0,
                                    Animation.RELATIVE_TO_SELF, 0.5f,
                                    Animation.RELATIVE_TO_SELF, 0.5f);
                            animation.setInterpolator(new Interpolator() {
                                @Override
                                public float getInterpolation(float input) {
                                    float s = 1.70158f;
                                    return input * input * ((s + 1) * input - s);
                                }
                            });
                            animation.setDuration(400);
                            animation.setAnimationListener(new Animation.AnimationListener() {
                                @Override
                                public void onAnimationStart(Animation animation) {

                                }

                                @Override
                                public void onAnimationEnd(Animation animation) {
                                    nextView.setTranslationX(buttonWidth);
                                }

                                @Override
                                public void onAnimationRepeat(Animation animation) {

                                }
                            });
                            nextView.startAnimation(animation);
                            send = false;
                        }else {
                            ObjectAnimator animator = ObjectAnimator.ofFloat(nextView, "translationX", nextView.getTranslationX(), buttonWidth);
                            animator.setDuration(400);
                            animator.start();
                        }
                    }
                    break;
                }
                case MotionEvent.ACTION_CANCEL: {
                    bording = false;
                    dragDownStatus = 0;
                    offsetY = 0;
                    offsetX = 0;
                    break;
                }
                case MotionEvent.ACTION_MOVE: {
                    int count = viewPager.getAdapter().getCount(), idx = viewPager.getCurrentItem();
                    if (ev.getPointerCount() != 1) {
                        single = false;
                        if (idx == 0) {
                            ObjectAnimator animator = ObjectAnimator.ofFloat(prevView, "translationX", prevView.getTranslationX(), -buttonWidth);
                            animator.setDuration(400);
                            animator.start();
                        }else if (idx == count - 1) {
                            ObjectAnimator animator = ObjectAnimator.ofFloat(nextView, "translationX", nextView.getTranslationX(), buttonWidth);
                            animator.setDuration(400);
                            animator.start();
                        }
                    }else {
                        float off = ev.getX() - offsetX;
                        if (ev.getY() - offsetY == 0 && off == 0) {

                        }else if (dragDownStatus == 0 && ev.getY() - offsetY > Math.abs(off)) {
                            dragDownStatus = 1;
                        }else if (dragDownStatus == 0) {
                            dragDownStatus = 2;
                        }
                        if (idx == 0 && bording) {
                            float tranx = prevView.getTranslationX();
                            if (tranx < -buttonWidth) {
                                tranx = -buttonWidth;
                            }
                            prevView.setTranslationX(Math.min(tranx + (int)off, H.dip2px(getContext(), 10)));
                            float width = H.dip2px(getContext(), 10) + buttonWidth;
                            prevView.setAlpha(Math.min(1f, (tranx + buttonWidth)/width));
                            if (tranx > -buttonWidth && bording) {
                                send = false;
                            }
                        }
                        if (idx == count - 1 && bording) {
                            float tranx = nextView.getTranslationX();
                            if (tranx > buttonWidth) {
                                tranx = buttonWidth;
                            }
                            nextView.setTranslationX(Math.max(tranx + (int)off, -H.dip2px(getContext(), 10)));
                            float width = H.dip2px(getContext(), 10) + buttonWidth;
                            nextView.setAlpha(Math.min(1f, (buttonWidth-tranx)/width));
                            if (tranx < buttonWidth) {
                                send = false;
                            }
                        }
                        offsetX = ev.getX();
                        offsetY = ev.getY();
                    }
                    break;
                }
            }
        }else {
            dragDownStatus = 0;
            offsetY = 0;
            offsetX = 0;
        }
        if (send) {
            viewPager.dispatchTouchEvent(ev);
        }
        return true;
    }
}
