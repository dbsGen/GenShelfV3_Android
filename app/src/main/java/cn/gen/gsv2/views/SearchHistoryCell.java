package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.graphics.ColorFilter;
import android.graphics.PorterDuff;
import android.support.v4.app.ActivityCompat;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;
import android.widget.ImageView;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.SearchTip;

/**
 * Created by mac on 2017/10/11.
 */

public class SearchHistoryCell extends ListCell implements View.OnClickListener {

    public interface OnRemoveListener {
        void onRemove(SearchHistoryCell cell);
    }

    TextView labelView;
    OnRemoveListener onRemoveListener;

    public void setOnRemoveListener(OnRemoveListener onRemoveListener) {
        this.onRemoveListener = onRemoveListener;
    }

    public SearchHistoryCell(Context context) {
        super(context);
        initView(context);
    }

    public SearchHistoryCell(Context context, String identifier) {
        super(context, identifier);
        initView(context);
    }

    @Override
    public TextView getLabelView() {
        return labelView;
    }

    int d(int r) {
        return H.dip2px(getContext(), r);
    }

    void initView(Context context) {

        labelView = new TextView(context);
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(d(60), d(14), d(10), d(14));
        labelView.setGravity(Gravity.TOP);
        labelView.setLayoutParams(layoutParams);
        labelView.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 16);
        labelView.setTextColor(Color.rgb(130, 130, 130));
        labelView.setText("test");

        getContentView().addView(labelView);

        View view = new View(context);
        view.setBackgroundColor(Color.rgb(243, 243, 243));
        layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, d(1));
        layoutParams.setMargins(0, 0, 0, 0);
        layoutParams.addRule(ALIGN_PARENT_BOTTOM, TRUE);
        view.setLayoutParams(layoutParams);
        getContentView().addView(view);

        android.widget.ImageView clock = new android.widget.ImageView(context);
        clock.setImageResource(R.drawable.clock);
        clock.setColorFilter(Color.rgb(170, 170, 170), PorterDuff.Mode.SRC_IN);
        layoutParams = new LayoutParams(d(24), d(24));
        layoutParams.setMargins(d(20), 0, 0, 0);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        clock.setLayoutParams(layoutParams);
        getContentView().addView(clock);

        RelativeLayout close = new RelativeLayout(context);
        layoutParams = new LayoutParams(d(36), d(36));
        layoutParams.setMargins(0, 0, d(8), 0);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(ALIGN_PARENT_RIGHT, TRUE);
        close.setLayoutParams(layoutParams);
        close.setBackgroundResource(R.drawable.ripple);
        close.setOnClickListener(this);
        getContentView().addView(close);

        android.widget.ImageView closeImage = new ImageView(context);
        layoutParams = new LayoutParams(d(16), d(16));
        layoutParams.setMargins(0, 0, 0, 0);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(CENTER_HORIZONTAL, TRUE);
        closeImage.setImageResource(R.drawable.cancel2);
        closeImage.setLayoutParams(layoutParams);
        closeImage.setColorFilter(Color.rgb(130, 130, 130), PorterDuff.Mode.SRC_IN);
        close.addView(closeImage);

        getContentView().getLayoutParams().height = ViewGroup.LayoutParams.WRAP_CONTENT;
    }

    @Override
    public void onClick(View v) {
        if (onRemoveListener != null) {
            onRemoveListener.onRemove(this);
        }
    }
}
