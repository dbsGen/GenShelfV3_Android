package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.os.Build;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.gr.Request;
import com.gr.classes.Array;
import com.gr.classes.Map;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;

import static android.text.TextUtils.TruncateAt.END;
import static android.text.TextUtils.TruncateAt.MIDDLE;

/**
 * Created by Gen on 2016/5/2.
 */
public class BookCell extends ListCell {

    cn.gen.gsv2.views.ImageView imageView;
    TextView titleLabel;
    TextView descriptionLabel;
    ImageView newView;

    public BookCell(Context context) {
        super(context);
        init(context);
    }

    public BookCell(Context context, String identifier) {
        super(context, identifier);
        init(context);
    }

    int d(int r) {
        return H.dip2px(getContext(), r);
    }

    public ImageView getNewView() {
        return newView;
    }

    void init(Context context) {
        imageView = new cn.gen.gsv2.views.ImageView(context);
        imageView.setBackgroundColor(Color.WHITE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            imageView.setElevation(6);
        }
        LayoutParams layoutParams = new LayoutParams(d(60), d(60));
        layoutParams.setMargins(d(10), d(10), d(10), 0);
        imageView.setLayoutParams(layoutParams);
        getContentView().addView(imageView);

        titleLabel = new TextView(context);
        layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, d(18));
        layoutParams.setMargins(d(80), d(10), d(10), d(10));
        titleLabel.setGravity(Gravity.TOP);
        titleLabel.setLayoutParams(layoutParams);
        titleLabel.setEllipsize(MIDDLE);
        titleLabel.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 16);
        titleLabel.getPaint().setFakeBoldText(true);
        titleLabel.setTextColor(Color.rgb(80, 80, 80));
        getContentView().addView(titleLabel);

        descriptionLabel = new TextView(context);
        layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        layoutParams.setMargins(d(80), d(33), d(10), d(10));
        descriptionLabel.setGravity(Gravity.TOP);
        descriptionLabel.setLayoutParams(layoutParams);
        descriptionLabel.setLines(2);
        descriptionLabel.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 14);
        titleLabel.setEllipsize(END);
        getContentView().addView(descriptionLabel);

        newView = new ImageView(context);
        layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(d(80), d(10), d(10), d(10));
        layoutParams.addRule(ALIGN_PARENT_RIGHT);
        newView.setLayoutParams(layoutParams);
        getContentView().addView(newView);
    }

    public cn.gen.gsv2.views.ImageView getThumbView() {
        return imageView;
    }

    public TextView getTitleLabel() {
        return titleLabel;
    }

    public TextView getDescriptionLabel() {
        return descriptionLabel;
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        getContentView().getLayoutParams().height = H.dip2px(context, 80);
    }

    public void setImageUrl(String url) {
        imageView.setUrl(url);
    }

    public void setImageUrl(String url, Map headers) {
        imageView.setUrl(url, headers);
    }
}
