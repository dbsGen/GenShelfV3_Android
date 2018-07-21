package cn.gen.gsv2.views;

import android.animation.Animator;
import android.animation.ObjectAnimator;
import android.content.Context;
import android.graphics.Color;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.RelativeLayout;

import com.gr.classes.Array;

import apps.gen.lib.utils.H;
import cn.gen.gsv2.models.ArtBasket;

/**
 * Created by mac on 2017/7/30.
 */

public class BooksCover extends RelativeLayout {
    public interface OnCheckedListener {
        void onChecked(ArtBasket.Art art);
    }

    TouchPanel backgroundView;
    ListView booksView;
    BaseAdapter adapter;

    Array<ArtBasket.Art> arts;
    OnCheckedListener onCheckedListener;

    public BooksCover(Context context) {
        super(context);
        init(context);
    }

    public BooksCover(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public BooksCover(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    public void setOnCheckedListener(OnCheckedListener onCheckedListener) {
        this.onCheckedListener = onCheckedListener;
    }

    public void setArts(Array<ArtBasket.Art> arts) {
        this.arts = arts;
        adapter.notifyDataSetChanged();
    }

    void init(Context context) {
        backgroundView = new TouchPanel(context);
        backgroundView.setBackgroundColor(Color.argb(133, 0, 0, 0));
        LayoutParams params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        backgroundView.setLayoutParams(params);
        addView(backgroundView);
        backgroundView.setAlpha(0);
        backgroundView.setListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                miss();
            }
        });


        booksView = new ListView(context);
        params = new LayoutParams(H.dip2px(context, 140), ViewGroup.LayoutParams.MATCH_PARENT);
        params.addRule(ALIGN_PARENT_RIGHT, TRUE);
        booksView.setLayoutParams(params);
        booksView.setBackgroundColor(Color.WHITE);
        booksView.setTranslationX(H.dip2px(context, 140));
        addView(booksView);

        adapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return arts == null ? 0 : arts.size();
            }

            @Override
            public Object getItem(int position) {
                return null;
            }

            @Override
            public long getItemId(int position) {
                return 0;
            }

            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                ArtCell cell = (ArtCell)convertView;
                if (cell == null) {
                    cell = new ArtCell(getContext());
                }
                cell.setArt(arts.get(position));
                return cell;
            }
        };
        booksView.setAdapter(adapter);
        booksView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if (onCheckedListener != null)
                    onCheckedListener.onChecked(arts.get(position));
            }
        });
    }


    float animationP = 0;

    void setAnimationP(float p) {
        animationP = p;
        backgroundView.setAlpha(p);
        booksView.setTranslationX(booksView.getWidth() * (1-p));
    }

    boolean showing = false;

    ObjectAnimator animator;
    public void show() {
        if (showing) return;
        showing = true;
        if (animator != null) {
            animator.cancel();
        }
        backgroundView.setEnableListener(true);
        animator = ObjectAnimator.ofFloat(this, "animationP", 0, 1);
        animator.addListener(new Animator.AnimatorListener() {
            @Override
            public void onAnimationStart(Animator animation) {

            }

            @Override
            public void onAnimationEnd(Animator animation) {
                animator = null;
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

    public void miss() {
        if (!showing) return;
        showing =false;
        if (animator != null) {
            animator.cancel();
        }
        backgroundView.setEnableListener(false);
        animator = ObjectAnimator.ofFloat(this, "animationP", 1, 0);
        animator.addListener(new Animator.AnimatorListener() {
            @Override
            public void onAnimationStart(Animator animation) {

            }

            @Override
            public void onAnimationEnd(Animator animation) {
                animator = null;
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
}
