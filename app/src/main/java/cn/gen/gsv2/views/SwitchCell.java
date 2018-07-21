package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;

import static android.text.TextUtils.TruncateAt.END;

/**
 * Created by mac on 2017/6/3.
 */

public class SwitchCell extends ListCell {
    TextView titleView;
    Switch _switch;

    public interface OnSwitchChanged {
        void onSwitch(SwitchCell cell, boolean on);
    }
    OnSwitchChanged onSwitchChanged;
    Object data;

    public void setOnSwitchChanged(OnSwitchChanged onSwitchChanged) {
        this.onSwitchChanged = onSwitchChanged;
    }

    public OnSwitchChanged getOnSwitchChanged() {
        return onSwitchChanged;
    }

    public void setData(Object data) {
        this.data = data;
    }

    public Object getData() {
        return data;
    }

    public SwitchCell(Context context) {
        super(context);
    }

    public SwitchCell(Context context, String identifier) {
        super(context, identifier);
    }

    public TextView getTitleView() {
        return titleView;
    }

    public Switch getSwitch() {
        return _switch;
    }

    int d(int r) {
        return H.dip2px(getContext(), r);
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

        _switch = new Switch(context);
        layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(d(145), d(0), d(10), d(0));
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(ALIGN_PARENT_RIGHT, 1);
        _switch.setLayoutParams(layoutParams);
        _switch.setGravity(Gravity.CENTER);
        _switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (onSwitchChanged != null) {
                    onSwitchChanged.onSwitch(SwitchCell.this, isChecked);
                }
            }
        });
        getContentView().addView(_switch);
    }
}
