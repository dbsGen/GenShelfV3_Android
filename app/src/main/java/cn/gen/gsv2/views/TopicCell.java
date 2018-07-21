package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.os.Build;
import android.support.v4.content.ContextCompat;
import android.util.TypedValue;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.ArrayList;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;

/**
 * Created by mac on 2017/7/24.
 */

public class TopicCell extends ListCell {
    private TextView titleView;
    private TextView subtitleView;
    private TextView descriptionView;
    private ArrayList<cn.gen.gsv2.views.ImageView> imageViews = new ArrayList<>();
    private LinearLayout imagesLayout;

    public TopicCell(Context context) {
        super(context);
        init(context);
    }

    public TopicCell(Context context, String identifier) {
        super(context, identifier);
        init(context);
    }

    public TextView getTitleView() {
        return titleView;
    }

    public TextView getDescriptionView() {
        return descriptionView;
    }

    public TextView getSubtitleView() {
        return subtitleView;
    }

    void init(Context context) {
//        titleView = new TextView(context);
//        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, H.dip2px(context, 18));
        int m = H.dip2px(context, 10);
//        layoutParams.setMargins(m, m, m * 3, m);
//        titleView.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 16);
//        titleView.getPaint().setFakeBoldText(true);
//        titleView.setTextColor(Color.rgb(80, 80, 80));
//        titleView.setLayoutParams(layoutParams);
//        getContentView().addView(titleView);
//
//        subtitleView = new TextView(context);
//        layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, H.dip2px(context, 18));
//        layoutParams.setMargins(m, (int)(m * 3), m * 3, m);
//        subtitleView.setLayoutParams(layoutParams);
//        subtitleView.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 11);
//        getContentView().addView(subtitleView);
//
//        descriptionView = new TextView(context);
//        layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
//                ViewGroup.LayoutParams.WRAP_CONTENT);
//        layoutParams.setMargins(m, (int)(m * 4.6), m * 3, m);
//        descriptionView.setLayoutParams(layoutParams);
//        descriptionView.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 14);
//        descriptionView.setMaxHeight(H.dip2px(context, 50));
//        getContentView().addView(descriptionView);
//
        ImageView arrowView = new ImageView(context);
        arrowView.setImageDrawable(ContextCompat.getDrawable(context, R.drawable.arrow_right));
        LayoutParams layoutParams = new LayoutParams(m, (int) (m * 1.7));
        layoutParams.setMargins(m, (int)(m*1.5), m, (int)(m*1.5));
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(ALIGN_PARENT_RIGHT, TRUE);
        arrowView.setLayoutParams(layoutParams);
        getContentView().addView(arrowView);
        arrowView.setAlpha(0.6f);
//
//        imagesLayout = new LinearLayout(context);
//        layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
//                ViewGroup.LayoutParams.WRAP_CONTENT);
//        imagesLayout.setLayoutParams(layoutParams);
//        imagesLayout.setOrientation(LinearLayout.HORIZONTAL);
//
//        getContentView().addView(imagesLayout);
//

        View view = inflate(context, R.layout.cell_topic, getContentView());
        titleView = (TextView) view.findViewById(R.id.title);
        subtitleView = (TextView)view.findViewById(R.id.subtitle);
        descriptionView = (TextView)view.findViewById(R.id.content);
        imagesLayout = (LinearLayout)view.findViewById(R.id.images);

        getContentView().getLayoutParams().height = ViewGroup.LayoutParams.WRAP_CONTENT;
        try {
            getContentView().setBackgroundResource(R.drawable.white_repple);
        }catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void setThumbs(String[] thumbs) {
        int len = 0;
        if (thumbs != null) {
            len = thumbs.length;
        }
        int max = Math.min(len, 5);

        int icount = imageViews.size();
        for (int i = 0; i < max; ++i) {
            if (i < icount) {
                imageViews.get(i).setVisibility(VISIBLE);
                imageViews.get(i).setUrl(thumbs[i]);
            }else {
                cn.gen.gsv2.views.ImageView imageView = new cn.gen.gsv2.views.ImageView(getContext());
                int m = H.dip2px(getContext(), 10);
                LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(4*m, 4*m);
                params.setMargins(m/2,m/4,m/2,m/4);
                imageView.setLayoutParams(params);
                imageView.setBackgroundColor(Color.WHITE);
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                    imageView.setElevation(4);
                }
                imagesLayout.addView(imageView);
                imageViews.add(imageView);
                imageView.setUrl(thumbs[i]);
            }
        }
        for (int i = max, t = imageViews.size(); i < t; ++i) {
            imageViews.get(i).setVisibility(INVISIBLE);
        }
    }
}
