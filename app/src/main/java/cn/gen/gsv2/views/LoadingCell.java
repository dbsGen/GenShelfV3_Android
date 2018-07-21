package cn.gen.gsv2.views;

import android.content.Context;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;

import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;

/**
 * Created by mac on 2017/6/4.
 */

public class LoadingCell extends ListCell {
    TextView labelView;
    int status;

    public LoadingCell(Context context) {
        super(context);
    }

    public LoadingCell(Context context, String identifier) {
        super(context, identifier);
    }

    public void setStatus(int status) {
        this.status = status;
        checkStatus();
    }

    public int getStatus() {
        return status;
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
        labelView = new TextView(context);
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        layoutParams.addRule(CENTER_HORIZONTAL, TRUE);
        labelView.setLayoutParams(layoutParams);
        labelView.setTextSize(12);
        getContentView().addView(labelView);
        checkStatus();
    }

    public static final int STATUS_NORMAL = 0;
    public static final int STATUS_LOADING = 1;
    public static final int STATUS_NO_MORE = 2;

    private void checkStatus() {
        if (getContext() == null) return;
        switch (status) {
            case 0: {
                labelView.setText(getContext().getText(R.string.loading));
                break;
            }
            case 1: {
                labelView.setText(getContext().getText(R.string.loading));
                break;
            }
            case 2: {
                labelView.setText(getContext().getText(R.string.no_more));
                break;
            }
        }
    }
}
