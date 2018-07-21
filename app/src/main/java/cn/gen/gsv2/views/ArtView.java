package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.util.AttributeSet;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.gr.classes.Map;

import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.ArtBasket;

/**
 * Created by gen on 28/07/2017.
 */

public class ArtView extends RelativeLayout {

    RelativeLayout container;
    ImageView imageView;
    TextView titleLabel;
    TextView subtitleLabel;

    ArtBasket.Art art;

    public ArtView(Context context) {
        super(context);
        init(context);
    }

    public ArtView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public ArtView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    void init(Context context) {
        container = (RelativeLayout) inflate(context, R.layout.view_art, this);

        imageView = (ImageView)container.findViewById(R.id.image_view);
        titleLabel = (TextView)container.findViewById(R.id.title);
        subtitleLabel = (TextView)container.findViewById(R.id.subtitle);
    }

    public void setArt(ArtBasket.Art art) {
        this.art = art;
        if (art != null) {
            String ref = art.getThumbRef();
            if (ref != null && !ref.isEmpty()) {
                Map headers = new Map(true);
                headers.put("Referer", ref);
                imageView.setUrl(art.getThumb(), headers);
            }else
                imageView.setUrl(art.getThumb());
            titleLabel.setText(art.getName());
            if (art.getType() == 0) {
                subtitleLabel.setText(art.getChapterName());
            }
        }
    }

    public ArtBasket.Art getArt() {
        return art;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        super.onTouchEvent(event);
        return true;
    }
}
