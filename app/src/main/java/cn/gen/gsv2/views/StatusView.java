package cn.gen.gsv2.views;

import android.content.Context;
import android.support.annotation.Nullable;
import android.util.AttributeSet;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;

import cn.gen.gsv2.R;

/**
 * Created by mac on 2017/6/13.
 */

public class StatusView extends RelativeLayout {
    TextView labelView;
    Button checkButton;

    public StatusView(Context context) {
        super(context);
        init(context);
    }

    public StatusView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public StatusView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    void init(Context context) {
        View view = inflate(context, R.layout.view_status, this);
        labelView = (TextView)view.findViewById(R.id.label);
        checkButton = (Button)view.findViewById(R.id.check_button);

    }

    public Button getCheckButton() {
        return checkButton;
    }

    public TextView getLabelView() {
        return labelView;
    }
}
