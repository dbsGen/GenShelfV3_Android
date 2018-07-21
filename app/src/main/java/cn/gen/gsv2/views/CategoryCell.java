package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.support.v4.content.ContextCompat;
import android.util.TypedValue;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;

/**
 * Created by mac on 2017/7/23.
 */

public class CategoryCell extends ListCell {
    private TextView titleView;
    private TextView descriptionView;

    public CategoryCell(Context context) {
        super(context);
        init(context);
    }
    public CategoryCell(Context context, String identifier) {
        super(context, identifier);
        init(context);
    }

    public TextView getTitleView() {
        return titleView;
    }

    public TextView getDescriptionView() {
        return descriptionView;
    }

    void init(Context context) {
        titleView = new TextView(context);
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, H.dip2px(context, 18));
        int m = H.dip2px(context, 10);
        layoutParams.setMargins(m, m, m * 3, m);
        titleView.setLayoutParams(layoutParams);
        titleView.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 16);
        titleView.getPaint().setFakeBoldText(true);
        titleView.setTextColor(Color.rgb(80, 80, 80));
        getContentView().addView(titleView);

        descriptionView = new TextView(context);
        layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, H.dip2px(context, 18));
        layoutParams.setMargins(m, (int)(m * 3.2), m * 3, m);
        descriptionView.setLayoutParams(layoutParams);
        descriptionView.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 14);
        getContentView().addView(descriptionView);

        ImageView arrowView = new ImageView(context);
        arrowView.setImageDrawable(ContextCompat.getDrawable(context, R.drawable.arrow_right));
        layoutParams = new LayoutParams(m, (int) (m * 1.7));
        layoutParams.setMargins(m, (int)(m*1.5), m, (int)(m*1.5));
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(ALIGN_PARENT_RIGHT, TRUE);
        arrowView.setLayoutParams(layoutParams);
        getContentView().addView(arrowView);
        arrowView.setAlpha(0.6f);

        getContentView().getLayoutParams().height = H.dip2px(context, 64);
        try {
            getContentView().setBackgroundResource(R.drawable.white_repple);
        }catch (Exception e) {
            e.printStackTrace();
        }
    }
}
