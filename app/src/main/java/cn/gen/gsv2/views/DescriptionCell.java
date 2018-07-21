package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;

import static android.view.ViewGroup.LayoutParams.WRAP_CONTENT;

/**
 * Created by mac on 2017/6/6.
 */

public class DescriptionCell extends ListCell {
    RelativeLayout arrow;
    TextView labelView;
    boolean extended = false;

    public DescriptionCell(Context context) {
        super(context);
    }

    public DescriptionCell(Context context, String identifier) {
        super(context, identifier);
    }

    @Override
    protected void initialize(final Context context) {
        super.initialize(context);

        setContentView((RelativeLayout) inflate(context, R.layout.cell_description, this));

        getContentView().setBackgroundColor(Color.WHITE);

        labelView = (TextView) getContentView().findViewById(R.id.description);
        labelView.setText("niasdhoasbdhvxcasd阿斯顿卡卡就舍不得阿克苏第八科技手段卡带啊啊实力对比啊开展宣传\n苏第八科技手段卡带啊啊实力对比啊开展宣传\n苏第八科技手段卡带啊啊实力对比啊开展宣传\n苏第八科技手段卡带啊啊实力对比啊开展宣传");
        labelView.getLayoutParams().height = WRAP_CONTENT;
        labelView.setMaxHeight(H.dip2px(context, 80));
        arrow = (RelativeLayout)getContentView().findViewById(R.id.arrow);
        arrow.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                extended = !extended;
                if (extended) {
                    labelView.getLayoutParams().height = WRAP_CONTENT;
                    labelView.setMaxHeight(H.dip2px(context, 999));
                    RotateAnimation animation = new RotateAnimation(0, 180, Animation.RELATIVE_TO_SELF,0.5f, Animation.RELATIVE_TO_SELF, 0.5f);
                    animation.setDuration(300);
                    animation.setFillAfter(true);
                    animation.setFillEnabled(true);
                    arrow.startAnimation(animation);
                }else {
                    labelView.getLayoutParams().height = WRAP_CONTENT;
                    labelView.setMaxHeight(H.dip2px(context, 80));
                    RotateAnimation animation = new RotateAnimation(180, 0, Animation.RELATIVE_TO_SELF,0.5f, Animation.RELATIVE_TO_SELF, 0.5f);
                    animation.setDuration(300);
                    animation.setFillAfter(true);
                    animation.setFillEnabled(true);
                    arrow.startAnimation(animation);
                }
                labelView.setLayoutParams(labelView.getLayoutParams());
                arrow.requestLayout();
            }
        });
    }

    @Override
    public TextView getLabelView() {
        return labelView;
    }
}
