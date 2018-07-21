package cn.gen.gsv2.views;

import android.content.Context;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.util.AttributeSet;
import android.util.Log;
import android.util.TypedValue;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.gr.Activity;
import com.gr.classes.Callback;
import com.gr.classes.NotificationCenter;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Chapter;
import cn.gen.gsv2.models.Shop;

/**
 * Created by mac on 2017/7/16.
 */

public class ProcessCell extends ListCell {
    TextView titleView;
    TextView subtitleView;
    TextView statusView;
    LinearLayout processView;
    ImageButton actionButton;
    View barView;

    Book book;
    Chapter chapter;
    int total;
    int completed;
    int status;

    Callback percentListener;
    Callback statusListener;
    Callback totalListener;

    public ProcessCell(Context context) {
        super(context);
    }

    public ProcessCell(Context context, String identifier) {
        super(context, identifier);
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        titleView = new TextView(context);
        LayoutParams params = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, H.dip2px(context, 16));
        int m = H.dip2px(context, 10);
        int m2 = H.dip2px(context, 5);
        params.setMargins(m, m2, m, m2);
        titleView.setLayoutParams(params);
        titleView.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 14);
        titleView.getPaint().setFakeBoldText(true);
        titleView.setTextColor(Color.rgb(80, 80, 80));
        getContentView().addView(titleView);

        subtitleView = new TextView(context);
        params = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, H.dip2px(context, 14));
        params.setMargins(m, H.dip2px(context, 23), m, m2);
        subtitleView.setLayoutParams(params);
        subtitleView.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 12);
        getContentView().addView(subtitleView);

        processView = new LinearLayout(context);
        RelativeLayout.LayoutParams layout = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                H.dip2px(context, 5));
        layout.setMargins(m, m2, m, m2);
        layout.addRule(ALIGN_PARENT_BOTTOM, TRUE);
        processView.setWeightSum(1);
        processView.setLayoutParams(layout);
        getContentView().addView(processView);

        barView = new View(context);
        LinearLayout.LayoutParams layoutParams2 = new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.MATCH_PARENT);
        layoutParams2.weight = 0.6f;
        barView.setLayoutParams(layoutParams2);
        barView.setBackgroundColor(ActivityCompat.getColor(context, R.color.blue));
        processView.addView(barView);

        statusView = new TextView(context);
        statusView.setVisibility(GONE);
        layout = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layout.setMargins(m, m2, H.dip2px(context, 60), m2);
        statusView.setLayoutParams(layout);
        layout.addRule(ALIGN_PARENT_RIGHT, TRUE);
        getContentView().addView(statusView);

        actionButton = new ImageButton(context);
        layout = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layout.addRule(CENTER_VERTICAL, TRUE);
        layout.addRule(ALIGN_PARENT_RIGHT, TRUE);
        layout.setMargins(m, m, m, m);
        actionButton.setLayoutParams(layout);
        actionButton.setImageResource(R.drawable.play);
        actionButton.setBackgroundColor(Color.TRANSPARENT);
        actionButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                int status = chapter.downloadStatus();
                if (status == Chapter.STATUS_LOADING || status == Chapter.STATUS_WAITING) {
                    chapter.stopDownload();
                }else {
                    Shop.download(book, chapter);
                }
            }
        });
        getContentView().addView(actionButton);

        percentListener = new Callback(true) {
            @Override
            public Object run(Object... args) {
                Chapter cha = (Chapter) args[0];
                float per = (float)args[1];
                if (chapter != null && chapter.equals(cha)) {
                    updatePercent(per);
                }
                return null;
            }
        };
        NotificationCenter.getInstance().listen("CHAPTER_PERCENT", percentListener);

        statusListener = new Callback(true) {
            @Override
            public Object run(Object... args) {
                Chapter cha = (Chapter)args[0];
                int _s = (int)args[1];
                if (chapter != null && chapter.equals(cha)) {
                    status = _s;
                    updateStatus(status);
                }
                return null;
            }
        };
        NotificationCenter.getInstance().listen("CHAPTER_STATUS", statusListener);

        totalListener = new Callback(true) {
            @Override
            public Object run(Object... args) {
                Chapter cha = (Chapter)args[0];
                int count = (int)args[1];
                int c2 = (int)args[2];
                if (chapter != null && chapter.equals(cha)) {
                    total = count;
                    completed = c2;
                    updateStatus(status);
                }
                return null;
            }
        };
        NotificationCenter.getInstance().listen("CHAPTER_PAGE_COUNT", totalListener);

        LayoutParams layoutParams = (LayoutParams) getContentView().getLayoutParams();
        layoutParams.height = H.dip2px(context, 56);
    }

    @Override
    protected void finalize() throws Throwable {
        NotificationCenter.getInstance().remove("CHAPTER_PERCENT", percentListener);
        NotificationCenter.getInstance().remove("CHAPTER_STATUS", statusListener);
        NotificationCenter.getInstance().remove("CHAPTER_PAGE_COUNT", totalListener);
        super.finalize();
    }

    public void setData(Book book, Chapter chapter) {
        this.book = book;
        this.chapter = chapter;

        total = chapter.pageCount();
        completed = chapter.completeCount();

        titleView.setText(book.getName());
        subtitleView.setText(chapter.getName());
        status = chapter.downloadStatus();

        updatePercent();
        updateStatus(status);
    }

    void updatePercent() {
        updatePercent(chapter.downloadPercent());
    }
    void updatePercent(float per) {
        LinearLayout.LayoutParams layoutParams = (LinearLayout.LayoutParams)barView.getLayoutParams();
        layoutParams.weight = per;
        barView.setLayoutParams(layoutParams);
    }

    void updateStatus(int status) {
        String title = chapter.getName() + " (";
        switch (status) {
            case 5: {
                title += getContext().getString(R.string.waiting);
                actionButton.setImageResource(R.drawable.pause);
                actionButton.setVisibility(VISIBLE);
                break;
            }
            case 1: {
                title += getContext().getString(R.string.loading);
                actionButton.setImageResource(R.drawable.pause);
                actionButton.setVisibility(VISIBLE);
                break;
            }
            case 2: {
                title += getContext().getString(R.string.complete);
                actionButton.setVisibility(GONE);
                break;
            }
            case 3: {
                title += getContext().getString(R.string.paused);
                actionButton.setImageResource(R.drawable.play);
                actionButton.setVisibility(VISIBLE);
                break;
            }
            case 4: {
                title += getContext().getString(R.string.failed);
                actionButton.setImageResource(R.drawable.play);
                actionButton.setVisibility(VISIBLE);
                break;
            }
            default: {
                title += getContext().getString(R.string.unkown);
                actionButton.setImageResource(R.drawable.play);
                actionButton.setVisibility(VISIBLE);
            }
        }
        if (total > 0) {
            title += " ";
            title += completed + "/" + total;
        }
        title += ')';
        subtitleView.setText(title);
    }


}
