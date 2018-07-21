package cn.gen.gsv2.views;

import android.content.Context;
import android.support.annotation.Nullable;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.widget.RelativeLayout;

/**
 * Created by gen on 27/07/2017.
 */

public class TouchPanel extends RelativeLayout {

    OnClickListener listener;

    public TouchPanel(Context context) {
        super(context);
    }

    public TouchPanel(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public TouchPanel(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public void setListener(OnClickListener listener) {
        this.listener = listener;
    }

    boolean enableListener = false;

    public void setEnableListener(boolean enableListener) {
        this.enableListener = enableListener;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (enableListener) {
            if (event.getAction() == MotionEvent.ACTION_UP) {
                if (this.listener != null) {
                    listener.onClick(this);
                }
            }
        }
        return enableListener;
    }
}
