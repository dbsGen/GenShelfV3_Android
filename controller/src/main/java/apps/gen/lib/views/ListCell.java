package apps.gen.lib.views;

import android.content.Context;
import android.graphics.Color;
import android.media.Image;
import android.util.AttributeSet;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import apps.gen.lib.utils.H;

/**
 * Created by gen on 16/4/30.
 */
public class ListCell extends RelativeLayout {
    int d(int s) {return H.dip2px(getContext(), s);}

    RelativeLayout mContentView;

    final int DEFAULT_HEIGHT = 44, CELL_PADDING = 0;

    ImageView mImageView;
    private ImageView getImageView() {
        if (mImageView == null) {
            Context context = getContext();
            mImageView = new ImageView(context);
            mImageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
            LayoutParams layoutParams = new LayoutParams(d(DEFAULT_HEIGHT - CELL_PADDING * 2), ViewGroup.LayoutParams.MATCH_PARENT);
            mImageView.setLayoutParams(layoutParams);
            getContentView().addView(mImageView);
        }
        return mImageView;
    }

    TextView mLabelView;
    public TextView getLabelView() {
        if (mLabelView == null) {
            Context context = getContext();
            mLabelView = new TextView(context);
            mLabelView.setTextColor(Color.BLACK);
            LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            layoutParams.setMargins(d(DEFAULT_HEIGHT - CELL_PADDING), 0, 0, 0);
            mLabelView.setGravity(Gravity.CENTER_VERTICAL);
            mLabelView.setLayoutParams(layoutParams);
            getContentView().addView(mLabelView);
        }
        return mLabelView;
    }

    public ListCell(Context context) {
        super(context);
        mContentView = new RelativeLayout(context);
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, d(DEFAULT_HEIGHT));
        mContentView.setLayoutParams(layoutParams);
        super.addView(mContentView);

        initialize(context);
    }
    public ListCell(Context context, String identifier) {
        super(context);
        mContentView = new RelativeLayout(context);
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, d(DEFAULT_HEIGHT));
        mContentView.setLayoutParams(layoutParams);
        int p = d(CELL_PADDING);
        mContentView.setPadding(p, p, p, p);
        super.addView(mContentView);

        mIdentifier = identifier;
        initialize(context);
    }

    protected void initialize(Context context) {}

    public void setContentView(RelativeLayout contentView) {
        if (mContentView != null) {
            removeView(mContentView);
        }
        this.mContentView = contentView;

    }

    public RelativeLayout getContentView() {
        return mContentView;
    }

    String mIdentifier = "cellIdentifier";

    public String getIdentifier() {
        return mIdentifier;
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        if (mImageView != null) {
            mImageView.getLayoutParams().width = h - (CELL_PADDING)* 2;
        }
        if (mLabelView != null) {
            LayoutParams layoutParams = (LayoutParams)mLabelView.getLayoutParams();
            layoutParams.setMargins(h - mContentView.getPaddingLeft(), 0, 0, 0);
            mLabelView.setLayoutParams(layoutParams);
        }
    }
}
