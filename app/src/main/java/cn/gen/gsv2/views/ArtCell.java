package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.os.Build;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.TextView;

import com.gr.classes.Map;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.models.ArtBasket;

/**
 * Created by gen on 27/07/2017.
 */

public class ArtCell extends ListCell {
    ImageView imageView;
    TextView titleLabel;
    TextView subtitleLabel;

    public ArtCell(Context context) {
        super(context);
        init(context);
    }

    public ArtCell(Context context, String identifier) {
        super(context, identifier);
        init(context);
    }

    void init(Context context) {
        imageView = new ImageView(context);
        int m = H.dip2px(context, 10);
        LayoutParams params = new LayoutParams(10*m,10*m);
        params.addRule(CENTER_HORIZONTAL, TRUE);
        params.setMargins(0, m, 0, 0);
        imageView.setLayoutParams(params);
        imageView.setBackgroundColor(Color.WHITE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            imageView.setZ(6);
        }
        getContentView().addView(imageView);

        titleLabel = new TextView(context);
        titleLabel.setGravity(Gravity.CENTER_HORIZONTAL);
        params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        params.setMargins(0, 11 * m, 0, 0);
        titleLabel.setLayoutParams(params);
        getContentView().addView(titleLabel);

        subtitleLabel = new TextView(context);
        subtitleLabel.setGravity(Gravity.CENTER_HORIZONTAL);
        params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        params.setMargins(0, 13*m, 0, 0);
        subtitleLabel.setLayoutParams(params);
        getContentView().addView(subtitleLabel);

        getContentView().getLayoutParams().height = 16 * m;
    }

    ArtBasket.Art art;

    public void setArt(ArtBasket.Art art) {
        this.art = art;
        String ref = art.getThumbRef();
        if (ref != null && !ref.isEmpty()) {
            Map headers = new Map();
            headers.put("Referer", ref);
            imageView.setUrl(art.getThumb(), headers);
        }else
            imageView.setUrl(art.getThumb());
        titleLabel.setText(art.getName());
        if (art.getType() == 1) {
            subtitleLabel.setVisibility(INVISIBLE);
            getContentView().getLayoutParams().height = H.dip2px(getContext(), 140);
        }else {
            subtitleLabel.setVisibility(VISIBLE);
            subtitleLabel.setText(art.getChapterName());
            getContentView().getLayoutParams().height = H.dip2px(getContext(), 160);
        }
    }

    public ArtBasket.Art getArt() {
        return art;
    }
}
