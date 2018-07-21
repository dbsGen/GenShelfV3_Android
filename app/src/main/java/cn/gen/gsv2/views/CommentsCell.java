package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Rect;
import android.support.v4.app.ActivityCompat;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.gr.classes.Array;

import java.util.ArrayList;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.ArtBasket;

import static android.util.TypedValue.COMPLEX_UNIT_DIP;

/**
 * Created by mac on 2017/7/30.
 */

public class CommentsCell extends ListCell implements View.OnClickListener {
    TextView authorView;
    LinearLayout container;
    Array datas;
    ArrayList<View> subviews = new ArrayList<>();

    public interface OnArtListener {
        void onPress(ArtBasket.Art art);
    }
    OnArtListener onArtListener;

    public void setOnArtListener(OnArtListener onArtListener) {
        this.onArtListener = onArtListener;
    }

    public CommentsCell(Context context) {
        super(context);
    }

    public CommentsCell(Context context, String identifier) {
        super(context, identifier);
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
        authorView = new TextView(context);
        int m = H.dip2px(context, 10);
        LayoutParams params = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
                m * 18 / 10);
        params.setMargins(m,m/2,m,m/2);
        authorView.setLayoutParams(params);
        authorView.setTextSize(COMPLEX_UNIT_DIP, 12);
        getContentView().addView(authorView);

        container = new LinearLayout(context);
        params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        params.setMargins(m, m * 3, m, m/2);
        container.setOrientation(LinearLayout.VERTICAL);
        container.setLayoutParams(params);
        getContentView().addView(container);

        getContentView().getLayoutParams().height = ViewGroup.LayoutParams.WRAP_CONTENT;

        try {
            getContentView().setBackgroundResource(R.drawable.white_repple);
        }catch (Exception e) {
        }
    }

    public void setAuthor(String author) {
        Rect bounds = new Rect();
        int m = H.dip2px(getContext(), 10);
        authorView.getPaint().getTextBounds(author, 0, author.length(), bounds);
        LayoutParams params = (LayoutParams)container.getLayoutParams();
        params.setMargins(m, bounds.height() + m, m, m/2);
        container.setLayoutParams(params);
        authorView.setText(author);
    }

    public void setDatas(Array datas) {
        this.datas = datas;
        for (View view : subviews) {
            container.removeView(view);
        }
        subviews.clear();
        if (datas != null) {
            for (Object data : datas) {
                if (data instanceof String) {
                    TextView textView = new TextView(getContext());
                    LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                    int m = H.dip2px(getContext(), 10);
                    params.setMargins(m, m/2, m, m/2);
                    textView.setLayoutParams(params);
                    textView.setText((String)data);
                    container.addView(textView);
                    subviews.add(textView);
                }else if (data instanceof ArtBasket.Art) {
                    ArtView artView = new ArtView(getContext());
                    LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                    artView.setLayoutParams(params);
                    artView.setArt((ArtBasket.Art) data);
                    artView.setOnClickListener(this);
                    container.addView(artView);
                    subviews.add(artView);
                }
            }
        }
    }

    @Override
    public void onClick(View v) {
        ArtView artView = (ArtView)v;
        if (onArtListener != null) {
            onArtListener.onPress(artView.getArt());
        }
    }
}
