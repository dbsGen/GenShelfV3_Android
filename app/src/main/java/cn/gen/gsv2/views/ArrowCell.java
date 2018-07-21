package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v4.content.ContextCompat;
import android.view.ContextThemeWrapper;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.bigkoo.pickerview.OptionsPickerView;

import java.util.ArrayList;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;

import static android.text.TextUtils.TruncateAt.END;

/**
 * Created by mac on 2017/6/3.
 */

public class ArrowCell extends ListCell {

    TextView titleView;
    TextView labelView;
    ArrayList<String> options;
    int selected;
    OptionsPickerView optionsView;
    Button button;
    OnClickListener onClickListener;
    Object data;

    public void setData(Object data) {
        this.data = data;
    }

    public Object getData() {
        return data;
    }

    public void setOptionsView(OptionsPickerView optionsView) {
        this.optionsView = optionsView;
    }

    public TextView getTitleView() {
        return titleView;
    }

    @Override
    public TextView getLabelView() {
        return labelView;
    }

    public ArrayList<String> getOptions() {
        return options;
    }

    public void setOptions(ArrayList<String> options) {
        this.options = options;
    }

    public int getSelected() {
        return selected;
    }

    public void setSelected(int selected) {
        this.selected = selected;
        labelView.setText(options.get(selected));
    }

    int d(int r) {
        return H.dip2px(getContext(), r);
    }

    public ArrowCell(Context context) {
        super(context);
    }

    public ArrowCell(Context context, String identifier) {
        super(context, identifier);
    }

    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
    @Override
    protected void initialize(Context context) {
        super.initialize(context);

//        setBackgroundColor(Color.WHITE);

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

        ImageView arrowView = new ImageView(context);
        arrowView.setImageDrawable(ContextCompat.getDrawable(context, R.drawable.arrow_right));
        layoutParams = new LayoutParams(d(10), d(17));
        layoutParams.setMargins(d(10), d(15), d(10), d(15));
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(ALIGN_PARENT_RIGHT, TRUE);
        arrowView.setLayoutParams(layoutParams);
        getContentView().addView(arrowView);
        arrowView.setAlpha(0.6f);

        labelView = new TextView(context);
        labelView.setText("测试");
        labelView.setEllipsize(END);
        layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(d(10), d(15), d(37), d(15));
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(ALIGN_PARENT_RIGHT, TRUE);
        labelView.setTextSize(16);
        labelView.setLayoutParams(layoutParams);
        getContentView().addView(labelView);

        setBackground(ContextCompat.getDrawable(context, R.drawable.white_repple));
    }

    public void setClicked(OnClickListener onClickListener) {
        this.onClickListener = onClickListener;
    }
}
