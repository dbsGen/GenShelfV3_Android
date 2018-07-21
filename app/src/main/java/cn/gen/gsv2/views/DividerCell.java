package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.TextView;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;

import static android.text.TextUtils.TruncateAt.END;

/**
 * Created by mac on 2017/6/3.
 */

public class DividerCell extends ListCell {

    TextView titleView;

    int d(int r) {
        return H.dip2px(getContext(), r);
    }

    public DividerCell(Context context) {
        super(context);
    }

    public DividerCell(Context context, String identifier) {
        super(context, identifier);
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        titleView = new TextView(context);
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(d(10), 0, d(10), 0);
        titleView.setGravity(Gravity.CENTER_VERTICAL);
        titleView.setLayoutParams(layoutParams);
        titleView.setEllipsize(END);
        titleView.setTextSize(16);
        titleView.getPaint().setFakeBoldText(true);
        titleView.setTextColor(Color.rgb(80, 80, 80));
        titleView.setMaxWidth(d(130));
        getContentView().addView(titleView);

    }

    public void setTitle(String title) {
        if (title == null) {
            titleView.setText("");
        }else {
            titleView.setText(title);
        }
        if (titleView.getText().length() == 0)
            getContentView().getLayoutParams().height = d(14);
        else
            getContentView().getLayoutParams().height = ViewGroup.LayoutParams.WRAP_CONTENT;
    }
}
