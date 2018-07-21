package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.support.annotation.Nullable;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.gr.classes.Array;

import java.util.ArrayList;

import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.ArtBasket;

/**
 * Created by gen on 28/07/2017.
 */

public class TopicDisplayView extends LinearLayout implements View.OnClickListener {

    TextView titleView;
    TextView subtitleView;

    public interface OnArtListener {
        void onPress(ArtBasket.Art art);
    }

    Array datas;
    ArrayList<View> subviews = new ArrayList<>();

    OnArtListener onArtListener;

    public void setOnArtListener(OnArtListener onArtListener) {
        this.onArtListener = onArtListener;
    }

    public TopicDisplayView(Context context) {
        super(context);
        init(context);
    }

    public TopicDisplayView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public TopicDisplayView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    public TextView getTitleView() {
        return titleView;
    }

    public TextView getSubtitleView() {
        return subtitleView;
    }

    void init(Context context) {
        setOrientation(VERTICAL);
        setBackgroundColor(Color.WHITE);

        View titleLayout = inflate(context, R.layout.view_topic_title, this);
        RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        titleLayout.setLayoutParams(params);

        titleView = (TextView) titleLayout.findViewById(R.id.title);
        subtitleView = (TextView)titleLayout.findViewById(R.id.subtitle);
    }


    public void setDatas(Array datas) {
        this.datas = datas;
        for (View view : subviews) {
            removeView(view);
        }
        subviews.clear();
        if (datas != null) {
            for (Object data : datas) {
                if (data instanceof String) {
                    TextView textView = new TextView(getContext());
                    LayoutParams params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                    int m = H.dip2px(getContext(), 10);
                    params.setMargins(m, m/2, m, m/2);
                    textView.setLayoutParams(params);
                    textView.setText((String)data);
                    addView(textView);
                    subviews.add(textView);
                }else if (data instanceof ArtBasket.Art) {
                    ArtView artView = new ArtView(getContext());
                    LayoutParams params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                    artView.setLayoutParams(params);
                    artView.setArt((ArtBasket.Art) data);
                    artView.setOnClickListener(this);
                    addView(artView);
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
