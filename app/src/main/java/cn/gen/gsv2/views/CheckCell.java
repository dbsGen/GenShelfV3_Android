package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;

import static android.text.TextUtils.TruncateAt.END;

/**
 * Created by mac on 2017/6/3.
 */

public class CheckCell extends ListCell {

    TextView titleView;
    CheckBox checkBox;
    public interface OnChecked {
        void checked(CheckCell cell, boolean checked);
    }
    Object data;

    OnChecked onChecked;

    public OnChecked getOnChecked() {
        return onChecked;
    }

    public void setOnChecked(OnChecked onChecked) {
        this.onChecked = onChecked;
    }

    public void setData(Object data) {
        this.data = data;
    }

    public Object getData() {
        return data;
    }

    int d(int r) {
        return H.dip2px(getContext(), r);
    }

    public TextView getTitleView() {
        return titleView;
    }

    public CheckBox getCheckBox() {
        return checkBox;
    }

    public CheckCell(Context context) {
        super(context);
    }

    public CheckCell(Context context, String identifier) {
        super(context, identifier);
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        setBackgroundColor(Color.WHITE);
        getContentView().getLayoutParams().height = ViewGroup.LayoutParams.WRAP_CONTENT;

        titleView = new TextView(context);
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(d(15), d(15), d(10), d(15));
        titleView.setGravity(Gravity.CENTER_VERTICAL);
        titleView.setLayoutParams(layoutParams);
        titleView.setEllipsize(END);
        titleView.setTextSize(16);
        titleView.getPaint().setFakeBoldText(true);
        titleView.setTextColor(Color.rgb(80, 80, 80));
        titleView.setMaxWidth(d(130));
        getContentView().addView(titleView);

        checkBox = new CheckBox(context);
        layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(d(145), d(0), d(10), d(0));
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(ALIGN_PARENT_RIGHT, 1);
        checkBox.setLayoutParams(layoutParams);
        checkBox.setGravity(Gravity.CENTER);
        checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (onChecked != null) {
                    onChecked.checked(CheckCell.this, isChecked);
                }
            }
        });
        getContentView().addView(checkBox);
    }
}
