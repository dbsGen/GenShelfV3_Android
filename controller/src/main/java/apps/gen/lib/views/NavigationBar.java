package apps.gen.lib.views;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.content.Context;
import android.content.res.ColorStateList;
import android.content.res.TypedArray;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.graphics.Typeface;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.RippleDrawable;
import android.os.Build;
import android.support.design.widget.AppBarLayout;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.TranslateAnimation;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import apps.gen.lib.utils.Configs;
import apps.gen.lib.R;
import apps.gen.lib.utils.H;

import com.fichardu.interpolator.*;

import static apps.gen.lib.views.NavigationBar.AnimationType.*;

/**
 * Created by Gen on 2016/3/29.
 */
public class NavigationBar extends RelativeLayout implements View.OnClickListener {
    public interface OnClickListener {
        void onClick(View v, int index);
    }

    public enum AnimationType {
        NONE,
        PUSH,
        POP,
        FADE
    }

    private class ItemButton extends RelativeLayout {

        ImageView imageView;
        View contentView;

        public ItemButton(Context context) {
            super(context);
            initView(context);
        }

        public ItemButton(Context context, AttributeSet attrs) {
            super(context, attrs);
            initView(context);
        }

        public ItemButton(Context context, AttributeSet attrs, int defStyleAttr) {
            super(context, attrs, defStyleAttr);
            initView(context);
        }

        void initView(Context context) {
            imageView = initIconView();
            addView(imageView);
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                setBackground(context.getDrawable(R.drawable.ripple));
            }
        }

        ImageView initIconView() {
            ImageView iconView = new ImageView(getContext());
            RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(H.dip2px(getContext(), 24), H.dip2px(getContext(), 24));
            layoutParams.addRule(CENTER_HORIZONTAL, TRUE);
            layoutParams.addRule(CENTER_VERTICAL, TRUE);

            iconView.setLayoutParams(layoutParams);
            return iconView;
        }

        void changedView(Animation in, Animation out, View inView, View outView, final Runnable complete) {
            if (inView != null) {
                inView.setVisibility(VISIBLE);
                addView(inView);
                inView.startAnimation(in);
            }
            if (outView != null) {
                outView.clearAnimation();
                outView.startAnimation(out);
            }
            Animation.AnimationListener listener = new Animation.AnimationListener() {
                @Override
                public void onAnimationStart(Animation animation) {

                }

                @Override
                public void onAnimationEnd(Animation animation) {
                    NavigationBar.this.getHandler().postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            complete.run();
                        }
                    }, 0);
                }

                @Override
                public void onAnimationRepeat(Animation animation) {

                }
            };
            if (out != null) {
                out.setAnimationListener(listener);
            }else if (in != null) {
                in.setAnimationListener(listener);
            }
        }

        View getCurrentView() {
            if (contentView == null) {
                return imageView;
            }else {
                return contentView;
            }
        }

        boolean empty() {
            return  contentView == null && imageView.getVisibility() == GONE;
        }

        void setDrawable(Drawable drawable) {
            setDrawable(drawable, NONE);
        }
        void setDrawable(Drawable drawable, AnimationType type) {
            if (imageView.getVisibility() != View.GONE && drawable == imageView.getDrawable()) {
                return;
            }
            if (drawable != null) {
                drawable.mutate().setColorFilter(Color.WHITE, PorterDuff.Mode.SRC_IN);
            }
            switch (type) {
                case NONE: {
                    if (contentView != null && drawable != null) {
                        removeView(contentView);
                        contentView = null;
                    }
                    imageView.setVisibility(VISIBLE);
                    imageView.setImageDrawable(drawable);
                    break;
                }
                case FADE: {
                    final ImageView newButton = initIconView();
                    newButton.setImageDrawable(drawable);

                    AlphaAnimation in = new AlphaAnimation(0, 1);
                    in.setInterpolator(new EaseInOutCubicInterpolator());
                    in.setDuration(Configs.AnimationDuring);
                    in.setFillAfter(true);

                    AlphaAnimation out = new AlphaAnimation(1, 0);
                    out.setInterpolator(new EaseInOutCubicInterpolator());
                    out.setDuration(Configs.AnimationDuring);
                    out.setFillAfter(true);

                    final View willRemove = getCurrentView();
                    changedView(in, out, newButton, willRemove, new Runnable() {
                        @Override
                        public void run() {
                            if (willRemove != null)
                                removeView(willRemove);
                        }
                    });

                    imageView = newButton;
                    contentView = null;
                    break;
                }
                default: {
                    Context context = getContext();
                    final ImageView newButton = initIconView();
                    newButton.setImageDrawable(drawable);

                    AnimationSet in = new AnimationSet(true);
                    in.setInterpolator(new EaseInOutCubicInterpolator());
                    AlphaAnimation aa = new AlphaAnimation(0, 1);
                    TranslateAnimation ta = new TranslateAnimation(type== PUSH?H.dip2px(context, AnimationOffset):-H.dip2px(context, AnimationOffset), 0, 0, 0);
                    in.addAnimation(aa);
                    in.addAnimation(ta);
                    in.setDuration(Configs.AnimationDuring);
                    in.setFillAfter(true);

                    AnimationSet out = new AnimationSet(true);
                    out.setInterpolator(new EaseInOutCubicInterpolator());
                    aa = new AlphaAnimation(1, 0);
                    ta = new TranslateAnimation(mLeftItemButton.getTranslationX(), type== PUSH?-H.dip2px(context, AnimationOffset):H.dip2px(context, AnimationOffset),0, 0);
                    out.addAnimation(aa);
                    out.addAnimation(ta);
                    out.setDuration(Configs.AnimationDuring);
                    out.setFillAfter(true);

                    final View willRemove = getCurrentView();
                    changedView(in, out, newButton, willRemove, new Runnable() {
                        @Override
                        public void run() {
                            if (willRemove != null)
                                removeView(willRemove);
                        }
                    });

                    imageView = newButton;
                    contentView = null;
                    break;
                }
            }

        }

        void setContentView(View view) {
            setContentView(view, NONE);
        }
        void setContentView(View view, AnimationType type) {
            switch (type) {
                case NONE: {
                    imageView.setVisibility(View.GONE);
                    if (contentView != null) {
                        removeView(contentView);
                        contentView = null;
                    }
                    contentView = view;
                    RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
                    contentView.setLayoutParams(layoutParams);
                    addView(contentView);
                    break;
                }
                case FADE: {

                    AlphaAnimation in = new AlphaAnimation(0, 1);
                    in.setInterpolator(new EaseInOutCubicInterpolator());
                    in.setDuration(Configs.AnimationDuring);
                    in.setFillAfter(true);

                    AlphaAnimation out = new AlphaAnimation(1, 0);
                    out.setInterpolator(new EaseInOutCubicInterpolator());
                    out.setDuration(Configs.AnimationDuring);
                    out.setFillAfter(true);

                    final View willRemove = getCurrentView();
                    changedView(in, out, view, willRemove, new Runnable() {
                        @Override
                        public void run() {
                            if (willRemove != null)
                                removeView(willRemove);
                            imageView.setVisibility(GONE);
                        }
                    });

                    contentView = view;
                    break;
                }
                default: {
                    Context context = getContext();

                    AnimationSet in = new AnimationSet(true);
                    in.setInterpolator(new EaseInOutCubicInterpolator());
                    AlphaAnimation aa = new AlphaAnimation(0, 1);
                    TranslateAnimation ta = new TranslateAnimation(type== PUSH?H.dip2px(context, AnimationOffset):-H.dip2px(context, AnimationOffset), 0, 0, 0);
                    in.addAnimation(aa);
                    in.addAnimation(ta);
                    in.setDuration(Configs.AnimationDuring);
                    in.setFillAfter(true);

                    AnimationSet out = new AnimationSet(true);
                    out.setInterpolator(new EaseInOutCubicInterpolator());
                    aa = new AlphaAnimation(1, 0);
                    ta = new TranslateAnimation(mLeftItemButton.getTranslationX(), type== PUSH?-H.dip2px(context, AnimationOffset):H.dip2px(context, AnimationOffset),0, 0);
                    out.addAnimation(aa);
                    out.addAnimation(ta);
                    out.setDuration(Configs.AnimationDuring);
                    out.setFillAfter(true);

                    final View willRemove = getCurrentView();
                    changedView(in, out, view, willRemove, new Runnable() {
                        @Override
                        public void run() {
                            if (willRemove != null)
                                removeView(willRemove);
                            imageView.setVisibility(GONE);
                        }
                    });

                    contentView = view;
                    break;
                }
            }
        }

    }

    ItemButton mLeftItemButton;
    ItemButton mRightItemButton;
    TextView mTitleView;

    RelativeLayout mContentView;

    public NavigationBar(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView(context);
        if (attrs != null) {
            @SuppressLint("Recycle") TypedArray a = context.obtainStyledAttributes(attrs, R.styleable.NavigationBar);
            String title = a.getString(R.styleable.NavigationBar_title);
            if (title != null)
                mTitleView.setText(title);
            Drawable leftIcon = a.getDrawable(R.styleable.NavigationBar_leftIcon);
            if (leftIcon != null)
                mLeftItemButton.setDrawable(leftIcon);
            Drawable rightIcon = a.getDrawable(R.styleable.NavigationBar_rightIcon);
            if (rightIcon != null)
                mRightItemButton.setDrawable(rightIcon);
        }
    }
    public NavigationBar(Context context) {
        this(context, null);
    }

    void initView(Context context) {
        mContentView = new RelativeLayout(context);
        ViewGroup.LayoutParams layoutParams = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        mContentView.setLayoutParams(layoutParams);
        addView(mContentView);

        mTitleView = initTitle(context);
        mContentView.addView(mTitleView);

        mLeftItemButton = new ItemButton(context);
        RelativeLayout.LayoutParams rlp = new RelativeLayout.LayoutParams(H.dip2px(context, MARGIN_MAX), H.dip2px(context, MARGIN_MAX));
        rlp.addRule(CENTER_VERTICAL, TRUE);
        mLeftItemButton.setLayoutParams(rlp);
        rlp.addRule(RelativeLayout.ALIGN_PARENT_LEFT, RelativeLayout.TRUE);
        mLeftItemButton.setOnClickListener(this);
        mContentView.addView(mLeftItemButton);

        mRightItemButton = new ItemButton(context);
        rlp = new RelativeLayout.LayoutParams(H.dip2px(context, MARGIN_MAX), H.dip2px(context, MARGIN_MAX));
        mRightItemButton.setLayoutParams(rlp);
        rlp.addRule(CENTER_VERTICAL, TRUE);
        rlp.addRule(RelativeLayout.ALIGN_PARENT_RIGHT, RelativeLayout.TRUE);
        mRightItemButton.setOnClickListener(this);
        mContentView.addView(mRightItemButton);
    }

    void updateLayout() {
        if (!mLeftItemButton.empty()) {
            mLeftItemButton.setVisibility(VISIBLE);
        }else {
            mLeftItemButton.setVisibility(GONE);
        }
        if (!mRightItemButton.empty()) {
            mRightItemButton.setVisibility(VISIBLE);
        }else {
            mRightItemButton.setVisibility(GONE);
        }
    }

    public void setLeftIcon(Drawable leftIcon) {
        mLeftItemButton.setDrawable(leftIcon);
        updateLayout();
        checkLeftIcon();
    }

    public void setRightIcon(Drawable rightIcon) {
        mRightItemButton.setDrawable(rightIcon);
        updateLayout();
        checkRightIcon();
    }

    final float AnimationOffset = 100;
    public void setLeftIcon(Drawable leftIcon, AnimationType animationType) {
        mLeftItemButton.setDrawable(leftIcon, animationType);
        checkLeftIcon();
    }

    public void setRightIcon(Drawable rightIcon, AnimationType animationType) {
        mRightItemButton.setDrawable(rightIcon, animationType);
        checkRightIcon();
    }

    public TextView getTitleView() {
        return mTitleView;
    }

    public  void setTitle(String title, AnimationType animationType) {
        Context context = getContext();
        switch (animationType) {
            case NONE:
                mTitleView.setText(title);
                RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams)mTitleView.getLayoutParams();
                layoutParams.setMargins(H.dip2px(context, mTitleLeft), 0, H.dip2px(context, mTitleRight), 0);
                break;
            case FADE:
            {
                final TextView newTitleView = initTitle(context);
                newTitleView.setText(title);
                addView(newTitleView);

                AlphaAnimation aa = new AlphaAnimation(0, 1);
                aa.setInterpolator(new EaseInOutCubicInterpolator());
                aa.setDuration(Configs.AnimationDuring);
                aa.setFillAfter(true);
                newTitleView.startAnimation(aa);

                if (mTitleView != null) mTitleView.clearAnimation();
                aa = new AlphaAnimation(1, 0);
                aa.setInterpolator(new EaseInOutCubicInterpolator());
                aa.setDuration(Configs.AnimationDuring);
                aa.setFillAfter(true);
                mTitleView.startAnimation(aa);
                final View willRemove = mTitleView;
                aa.setAnimationListener(new Animation.AnimationListener() {
                    @Override
                    public void onAnimationStart(Animation animation) {

                    }

                    @Override
                    public void onAnimationEnd(Animation animation) {
                        NavigationBar.this.getHandler().postDelayed(new Runnable() {
                            @Override
                            public void run() {
                                removeView(willRemove);
                            }
                        }, 0);
                    }

                    @Override
                    public void onAnimationRepeat(Animation animation) {

                    }
                });
                mTitleView = newTitleView;
            }
            break;
            default: {
                final TextView newTitleView = initTitle(context);
                newTitleView.setText(title);
                addView(newTitleView);

                AnimationSet set = new AnimationSet(true);
                set.setInterpolator(new EaseInOutCubicInterpolator());
                AlphaAnimation aa = new AlphaAnimation(0, 1);
                TranslateAnimation ta = new TranslateAnimation(animationType == PUSH ? H.dip2px(context, AnimationOffset) : -H.dip2px(context, AnimationOffset), 0, 0, 0);
                set.addAnimation(aa);
                set.addAnimation(ta);
                set.setDuration(Configs.AnimationDuring);
                set.setFillAfter(true);
                newTitleView.startAnimation(set);

                if (mTitleView != null) mTitleView.clearAnimation();
                set = new AnimationSet(true);
                set.setInterpolator(new EaseInOutCubicInterpolator());
                aa = new AlphaAnimation(1, 0);
                ta = new TranslateAnimation(mTitleView.getTranslationX(), animationType == PUSH ? -H.dip2px(context, AnimationOffset) : H.dip2px(context, AnimationOffset),0, 0);
                set.addAnimation(aa);
                set.addAnimation(ta);
                set.setDuration(Configs.AnimationDuring);
                set.setFillAfter(true);
                mTitleView.startAnimation(set);
                final View willRemove = mTitleView;
                set.setAnimationListener(new Animation.AnimationListener() {
                    @Override
                    public void onAnimationStart(Animation animation) {

                    }

                    @Override
                    public void onAnimationEnd(Animation animation) {
                        NavigationBar.this.getHandler().postDelayed(new Runnable() {
                            @Override
                            public void run() {
                                removeView(willRemove);
                            }
                        }, 0);
                    }

                    @Override
                    public void onAnimationRepeat(Animation animation) {

                    }
                });
                mTitleView = newTitleView;
            }
        }
    }

    final int MARGIN_MAX = 44, MARGIN_MIN = 8;
    void checkLeftIcon() {
        mTitleLeft = mLeftItemButton.empty() ? MARGIN_MIN : MARGIN_MAX;
    }
    void checkRightIcon() {
        mTitleRight = mRightItemButton.empty() ? MARGIN_MIN : MARGIN_MAX;
    }
    int mTitleLeft = MARGIN_MIN;
    int mTitleRight = MARGIN_MIN;
    void setTitleLeft(int titleLeft) {
        mTitleLeft = titleLeft;
    }
    void setTitleRight(int titleRight) {
        mTitleRight = titleRight;
    }

    TextView initTitle(Context context) {
        TextView textView = new TextView(context);
        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.addRule(RelativeLayout.CENTER_VERTICAL, 1);
        layoutParams.setMargins(H.dip2px(context, mTitleLeft), 0, H.dip2px(context, mTitleRight), 0);
        textView.setLayoutParams(layoutParams);
        textView.setMaxLines(1);
        textView.setTextSize(16);
        textView.setTextColor(getResources().getColor(R.color.colorTitle));
        textView.setTypeface(Typeface.defaultFromStyle(Typeface.BOLD));
        textView.setEllipsize(TextUtils.TruncateAt.END);
        return textView;
    }

    OnClickListener mLeftListener;
    OnClickListener mRightListener;
    public void setLeftListener(OnClickListener leftListener) {
        mLeftListener = leftListener;
    }
    public OnClickListener getLeftListener() {
        return mLeftListener;
    }
    public void setRightListener(OnClickListener rightListener) {
        mRightListener = rightListener;
    }
    public OnClickListener getRightListener() {
        return mRightListener;
    }
    int count = 0;
    @Override
    public void onClick(View v) {
        if (v.equals(mLeftItemButton) && mLeftListener != null) {
            mLeftListener.onClick(v,0);
        }else if (v.equals(mRightItemButton) && mRightListener != null) {
            mRightListener.onClick(v,0);
        }
    }
}
