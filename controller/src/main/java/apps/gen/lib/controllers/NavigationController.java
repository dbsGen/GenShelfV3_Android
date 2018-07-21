package apps.gen.lib.controllers;

import android.animation.Animator;
import android.animation.ObjectAnimator;
import android.os.Build;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.v4.app.FragmentTransaction;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;

import com.fichardu.interpolator.EaseInCubicInterpolator;
import com.fichardu.interpolator.EaseOutCubicInterpolator;

import java.util.Collections;
import java.util.Stack;

import apps.gen.lib.R;
import apps.gen.lib.utils.Configs;
import apps.gen.lib.utils.H;
import apps.gen.lib.views.NavigationBar;

/**
 * Created by Gen on 2016/4/13.
 */
public class NavigationController extends Controller {
    public static class NavigationControllerView extends android.support.design.widget.CoordinatorLayout {
        NavigationBar mNavigationBar;
        NavigationBar getNavigationBar() {
            return mNavigationBar;
        }

        RelativeLayout mContentView;
        RelativeLayout getContentView() {
            return mContentView;
        }

        float navHeight;
        boolean isInitView = false;
        public NavigationControllerView(Context context, AttributeSet attrs, int defStyleAttr) {
            super(context, attrs, defStyleAttr);

            navHeight = H.dip2px(getContext(), DefaultHeight);
            isInitView = true;
            initView(context);
            isInitView = false;
        }
        public NavigationControllerView(Context context, AttributeSet attrs) {
            this(context, attrs, 0);
        }
        public  NavigationControllerView(Context context) {
            this(context, null);
        }

        final float DefaultHeight = 52;
        void initView(Context context) {
            mContentView = new RelativeLayout(context);
            LayoutParams params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            mContentView.setLayoutParams(params);
            mContentView.setPadding(0, H.dip2px(context, DefaultHeight), 0, 0);
            addView(mContentView);

            RelativeLayout view = new RelativeLayout(context);
            params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            view.setLayoutParams(params);
            view.setId(R.id.navigation_content);
            mContentView.addView(view);

            mNavigationBar = new NavigationBar(context);
            params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, H.dip2px(context, DefaultHeight));
            mNavigationBar.setLayoutParams(params);
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                mNavigationBar.setBackgroundColor(getResources().getColor(R.color.colorPrimary, null));
            }else {
                mNavigationBar.setBackgroundColor(getResources().getColor(R.color.colorPrimary));
            }
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                mNavigationBar.setTranslationZ(10);
            }
            addView(mNavigationBar);
        }

        float mPushAnimatorValue;
        public float getPushAnimatorValue() {
            return mPushAnimatorValue;
        }
        public void getPushAnimatorValue(float pushAnimatorValue) {
            if (mPushAnimatorValue != pushAnimatorValue) {
                mPushAnimatorValue = pushAnimatorValue;
            }
        }

//        @Override
//        public void addView(View child) {
//            if (isInitView) {
//                super.addView(child);
//            }else {
//                mContentView.addView(child);
//            }
//        }

        void setNavHeight(float height) {
            navHeight = height;
            mNavigationBar.setY(navHeight-H.dip2px(getContext(), DefaultHeight));
            mContentView.setPadding(0, (int)navHeight, 0, 0);
        }
        float getNavHeight() {
            return navHeight;
        }

        boolean hidden;
        ObjectAnimator hiddenAnimator;
        public void setNavBarHidden(boolean hidden, boolean animated) {
            if (this.hidden == hidden) return;
            this.hidden = hidden;
            if (hiddenAnimator != null) hiddenAnimator.cancel();
            if (hidden) {
                if (animated) {
                    hiddenAnimator = ObjectAnimator.ofFloat(this, "navHeight", getNavHeight(), 0);
                    hiddenAnimator.setDuration(400);
                    hiddenAnimator.addListener(new Animator.AnimatorListener() {
                        @Override
                        public void onAnimationStart(Animator animator) {

                        }

                        @Override
                        public void onAnimationEnd(Animator animator) {
                            mNavigationBar.setVisibility(View.GONE);
                            hiddenAnimator = null;
                        }

                        @Override
                        public void onAnimationCancel(Animator animator) {

                        }

                        @Override
                        public void onAnimationRepeat(Animator animator) {

                        }
                    });
                    hiddenAnimator.start();
                }else {
                    mNavigationBar.setVisibility(View.GONE);
                    mContentView.setPadding(0, 0, 0, 0);
                }
            }else {
                if (animated) {
                    mNavigationBar.setVisibility(View.VISIBLE);
                    hiddenAnimator = ObjectAnimator.ofFloat(this, "navHeight", getNavHeight(), H.dip2px(getContext(), DefaultHeight));
                    hiddenAnimator.setDuration(400);
                    hiddenAnimator.addListener(new Animator.AnimatorListener() {
                        @Override
                        public void onAnimationStart(Animator animator) {

                        }

                        @Override
                        public void onAnimationEnd(Animator animator) {
                            hiddenAnimator = null;
                        }

                        @Override
                        public void onAnimationCancel(Animator animator) {

                        }

                        @Override
                        public void onAnimationRepeat(Animator animator) {

                        }
                    });
                    hiddenAnimator.start();
                } else {
                    mNavigationBar.setVisibility(View.VISIBLE);
                    mNavigationBar.setY(0);
                    mContentView.setPadding(0, H.dip2px(getContext(), DefaultHeight), 0, 0);
                }
            }
        }
    }

    NavigationControllerView navView;

    public NavigationBar getNavigationBar() {
        if (navView != null) {
            return navView.getNavigationBar();
        }
        return null;
    }

    public RelativeLayout getContentView() {
        if (navView != null) {
            return navView.getContentView();
        }
        return null;
    }

    public NavigationControllerView getView() {
        return navView;
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        navView = new NavigationControllerView(getContext());
        navView.getNavigationBar().setLeftListener(new NavigationBar.OnClickListener() {
            @Override
            public void onClick(View v, int index) {
                if (currentLeftItem != null) {
                    ButtonItem item = currentLeftItem.getItems()[index];
                    if (item.getOnClickListener() != null)
                        item.getOnClickListener().onClick(v);
                }
            }
        });
        navView.getNavigationBar().setRightListener(new NavigationBar.OnClickListener() {
            @Override
            public void onClick(View v, int index) {
                if (currentRightItem != null) {
                    ButtonItem item = currentRightItem.getItems()[index];
                    if (item.getOnClickListener() != null)
                        item.getOnClickListener().onClick(v);
                }
            }
        });
        if (controllersStack.size() > 0) {
            Controller nc = controllersStack.lastElement();
            nc.enterStart(this);
            getFragmentManager().beginTransaction().replace(R.id.navigation_content, nc).commit();
            nc.enterEnd();
            pushNavAnim(nc, NavigationBar.AnimationType.NONE);
        }
        return navView;
    }

    boolean animating = false;
    Stack<Controller> controllersStack = new Stack<Controller>();
    public void push(Controller controller) {push(controller, false);}
    public void push(Controller controller, boolean animated) {
        if (animating)
            return;
        if (animated)
            animating = true;
        Controller base = null;
        if (controllersStack.size() > 0)
            base = controllersStack.lastElement();
        controllersStack.push(controller);
        if (navView == null) return;
        if (animated) {
            if (base != null) {
                ObjectAnimator animator1 = ObjectAnimator.ofFloat(base, "pushAnimatorValue", 0, -1);
                animator1.setInterpolator(new EaseInCubicInterpolator());
                animator1.setDuration(Configs.AnimationDuring);
                base.exitStart();
                final Controller willDisappear = base;
                animator1.addListener(new Animator.AnimatorListener() {
                    @Override
                    public void onAnimationStart(Animator animation) {
                    }

                    @Override
                    public void onAnimationEnd(Animator animation) {
                        willDisappear.exitEnd(NavigationController.this);
                        getFragmentManager().beginTransaction().remove(willDisappear).commit();
                    }

                    @Override
                    public void onAnimationCancel(Animator animation) {
                    }

                    @Override
                    public void onAnimationRepeat(Animator animation) {
                    }
                });
                animator1.start();
            }

            controller.enterStart(this);
            FragmentManager fragmentManager = getFragmentManager();
            FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
            fragmentTransaction.add(R.id.navigation_content, controller).commit();
            ObjectAnimator animator = ObjectAnimator.ofFloat(controller, "pushAnimatorValue", 1, 0);
            animator.setInterpolator(new EaseOutCubicInterpolator());
            animator.setDuration(Configs.AnimationDuring);
            final Controller willAppear = controller;
            animator.addListener(new Animator.AnimatorListener() {
                @Override
                public void onAnimationStart(Animator animation) { }

                @Override
                public void onAnimationEnd(Animator animation) {
                    getView().getHandler().postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            animating = false;
                            willAppear.enterEnd();
                        }
                    }, 0);
                }

                @Override
                public void onAnimationCancel(Animator animation) { }

                @Override
                public void onAnimationRepeat(Animator animation) { }
            });
            animator.start();
        }else {
            if (base != null) base.exitStart();
            controller.enterStart(this);
            getFragmentManager().beginTransaction().replace(R.id.navigation_content, controller).commit();
            if (base != null) base.exitEnd(this);
            controller.enterEnd();
        }
        pushNavAnim(controller, animated? NavigationBar.AnimationType.PUSH:NavigationBar.AnimationType.NONE);
    }

    public Controller pop() { return pop(false); }

    public Controller pop(boolean animated) {
        if (animating) return null;
        if (controllersStack.size() <= 1) {
            Log.w(Configs.LogTag, "Can not pop controller because the controllers stack is empty.");
        }
        if (animated) animating = true;

        Controller top = controllersStack.pop();
        Controller last = controllersStack.lastElement();
        if (navView == null) return top;
        if (animated) {
            ObjectAnimator animator1 = ObjectAnimator.ofFloat(top, "pushAnimatorValue", 0, 1);
            animator1.setDuration(Configs.AnimationDuring);
            animator1.setInterpolator(new EaseInCubicInterpolator());
            top.exitStart();
            final Controller willDisappear = top;
            animator1.addListener(new Animator.AnimatorListener() {
                @Override
                public void onAnimationStart(Animator animation) { }

                @Override
                public void onAnimationEnd(Animator animation) {
                    try {
                        willDisappear.exitEnd(NavigationController.this);
                        getFragmentManager().beginTransaction().remove(willDisappear).commit();
                    }catch (Exception e) {
                        e.printStackTrace();
                    }
                }

                @Override
                public void onAnimationCancel(Animator animation) { }

                @Override
                public void onAnimationRepeat(Animator animation) { }
            });
            animator1.start();

            last.enterStart(this);
            FragmentManager fragmentManager = getFragmentManager();
            FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
            fragmentTransaction.add(R.id.navigation_content, last).commit();
            ObjectAnimator animator = ObjectAnimator.ofFloat(last, "pushAnimatorValue", -1, 0);
            animator.setDuration(Configs.AnimationDuring);
            animator.setInterpolator(new EaseOutCubicInterpolator());
            final Controller willAppear = last;
            animator.addListener(new Animator.AnimatorListener() {
                @Override
                public void onAnimationStart(Animator animation) {
                }

                @Override
                public void onAnimationEnd(Animator animation) {
                    getView().getHandler().postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            animating = false;
                            willAppear.enterEnd();
                        }
                    }, 0);
                }

                @Override
                public void onAnimationCancel(Animator animation) {
                }

                @Override
                public void onAnimationRepeat(Animator animation) {
                }
            });
            animator.start();
        }else {
            top.exitStart();
            last.enterStart(this);
            getFragmentManager().beginTransaction().replace(R.id.navigation_content, last).commit();
            top.exitEnd(this);
            last.enterEnd();
        }
        popNavAnim(last, animated? NavigationBar.AnimationType.POP: NavigationBar.AnimationType.NONE);
        return top;
    }

    public Controller[] getControllers() {
        Controller[] cs = new Controller[controllersStack.size()];
        controllersStack.toArray(cs);
        return cs;
    }
    public void setControllers(Controller[] controllers) {setControllers(controllers, false);}
    public void setControllers(Controller[] controllers, boolean animated) {
        Controller oc = null;
        if (controllersStack.size() > 0) {
            oc = controllersStack.lastElement();
        }
        for (Controller c : controllersStack) {
            if (c != oc)
                c.setParent(null);
        }
        for (Controller c : controllers) {
            c.setParent(this);
        }
        controllersStack.clear();
        Collections.addAll(controllersStack, controllers);
        Controller nc = controllers.length == 0 ? null:controllers[controllers.length - 1];
        if (animated) {
            if (oc != null) {
                ObjectAnimator animator = ObjectAnimator.ofFloat(oc, "changeAnimatorValue", 0, -1);
                animator.setDuration(Configs.AnimationDuring);
                animator.setInterpolator(new EaseOutCubicInterpolator());
                oc.exitStart();
                final Controller willDisappear = oc;
                animator.addListener(new Animator.AnimatorListener() {
                    @Override
                    public void onAnimationStart(Animator animation) {

                    }

                    @Override
                    public void onAnimationEnd(Animator animation) {
                        willDisappear.exitEnd(NavigationController.this);
                        getFragmentManager().beginTransaction().remove(willDisappear).commit();
                    }

                    @Override
                    public void onAnimationCancel(Animator animation) {

                    }

                    @Override
                    public void onAnimationRepeat(Animator animation) {

                    }
                });
                animator.start();
            }

            nc.enterStart(this);
            getFragmentManager().beginTransaction().add(R.id.navigation_content, nc).commit();
            ObjectAnimator animator = ObjectAnimator.ofFloat(nc, "changeAnimatorValue", 1, 0);
            animator.setDuration(Configs.AnimationDuring);
            animator.setInterpolator(new EaseOutCubicInterpolator());
            final Controller willAppear = nc;
            animator.addListener(new Animator.AnimatorListener() {
                @Override
                public void onAnimationStart(Animator animation) {

                }

                @Override
                public void onAnimationEnd(Animator animation) {
                    getView().getHandler().postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            animating = false;
                            willAppear.enterEnd();
                        }
                    }, 0);
                }

                @Override
                public void onAnimationCancel(Animator animation) {

                }

                @Override
                public void onAnimationRepeat(Animator animation) {

                }
            });
            animator.start();
        }else {
            if (oc != null) oc.exitStart();
            if (nc != null) nc.enterStart(this);
            if (nc != null) {
                getFragmentManager().beginTransaction().replace(R.id.navigation_content, nc).commit();
            }else if (oc != null){
                getFragmentManager().beginTransaction().remove(oc).commit();
            }
            if (oc != null) oc.exitEnd(this);
            if (nc != null) nc.enterEnd();
        }
        pushNavAnim(nc, animated ? NavigationBar.AnimationType.FADE : NavigationBar.AnimationType.NONE);
    }

    @Override
    protected void onSubControllerChangeTitle(Controller sender, String title, NavigationBar.AnimationType type) {
        if (navView != null && sender.equals(controllersStack.lastElement())) {
            navView.getNavigationBar().setTitle(title, type);
        }
    }

    NavigationItem defaultBackItem;
    NavigationItem getDefaultBackItem() {
        if (defaultBackItem == null) {
            defaultBackItem = new NavigationItem(getResources().getDrawable(R.drawable.ic_action_back), new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    pop(true);
                }
            });
        }
        return defaultBackItem;
    }
    NavigationItem currentLeftItem = null;
    NavigationItem currentRightItem = null;

    public void setLeftNavItem(NavigationItem leftItem, NavigationBar.AnimationType animationType) {
        currentLeftItem = leftItem;
        if (currentLeftItem == null && controllersStack.size() > 1) {
            currentLeftItem = getDefaultBackItem();
        }
        Drawable icon = null;
        if (currentLeftItem != null && currentLeftItem.getItems().length > 0) {
            icon = currentLeftItem.getItems()[0].getIcon();
        }
        if (navView != null)
            navView.getNavigationBar().setLeftIcon(icon, animationType);
    }
    public void setRightNavItem(NavigationItem rightItem, NavigationBar.AnimationType animationType) {
        currentRightItem = rightItem;
        Drawable icon = null;
        if (currentRightItem != null && currentRightItem.getItems().length > 0) {
            icon = currentRightItem.getItems()[0].getIcon();
        }
        if (navView != null)
            navView.getNavigationBar().setRightIcon(icon, animationType);
    }

    public void pushNavAnim(Controller controller, NavigationBar.AnimationType type) {
        if (navView != null && controller != null) {
            final Controller tController = controller;
            final NavigationBar.AnimationType tAnimation = type;
            getHandler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    setLeftNavItem(tController.getLeftItems(), tAnimation);
                    setRightNavItem(tController.getRightItems(), tAnimation);
                    navView.getNavigationBar().setTitle(tController.getTitle(), tAnimation);
                }
            }, 0);
        }
    }

    public void popNavAnim(Controller controller, NavigationBar.AnimationType type) {
        if (navView != null) {
            final NavigationBar.AnimationType tAnimation = type;
            setLeftNavItem(controller.getLeftItems(), tAnimation);
            setRightNavItem(controller.getRightItems(), tAnimation);
            navView.getNavigationBar().setTitle(controller.getTitle(), tAnimation);
        }
    }

    public static NavigationController getNavigationController(Controller thiz) {
        Controller parent = thiz.getParent();
        while (parent != null) {
            if (parent instanceof NavigationController) {
                return (NavigationController)parent;
            }
            parent = parent.getParent();
        }
        return null;
    }

    @Override
    public boolean onBackPressed() {
        if (controllersStack.size() > 1) {
            Controller top = controllersStack.lastElement();
            if (!top.onBackPressed()) {
                pop(true);
            }
            return true;
        }else {
            return super.onBackPressed();
        }
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (controllersStack.size() > 1) {
            Controller top = controllersStack.lastElement();
            return top.onKeyDown(keyCode, event);
        }else {
            return false;
        }
    }

    public void setNavBarHidden(boolean hidden){
        setNavBarHidden(hidden, false);
    }
    public void setNavBarHidden(boolean hidden, boolean animated) {
        if (navView != null) {
            navView.setNavBarHidden(hidden, animated);
        }
    }
    public boolean getNavHidden() {
        return navView.hidden;
    }
}
