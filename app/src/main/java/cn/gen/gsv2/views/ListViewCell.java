package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.RelativeLayout;

/**
 * Created by gen on 31/07/2017.
 */

public class ListViewCell extends RelativeLayout {
    View contentView;

    public ListViewCell(Context context) {
        super(context);
        init(context);
    }

    public ListViewCell(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public ListViewCell(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    public void setContentView(View view) {
        if (view == contentView) {
            return;
        }
        if (contentView != null) {
            removeView(contentView);
        }
        if (view.getParent() != null) {
            ((ViewGroup)view.getParent()).removeView(view);
        }
        addView(view);
        contentView = view;
    }

    public View getContentView() {
        return contentView;
    }
    void init(Context context) {
        setBackgroundColor(Color.WHITE);
    }
}
