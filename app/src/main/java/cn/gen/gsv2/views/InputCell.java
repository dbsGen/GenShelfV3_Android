package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextWatcher;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;

import static android.text.TextUtils.TruncateAt.END;

/**
 * Created by mac on 2017/6/2.
 */

public class InputCell extends ListCell {

    TextView titleView;
    EditText editText;
    public interface OnTextChanged {
        void textChanged(InputCell cell, String newText);
    }
    OnTextChanged onTextChanged;
    Object data;

    public void setData(Object data) {
        this.data = data;
    }

    public Object getData() {
        return data;
    }

    public void setOnTextChanged(OnTextChanged onTextChanged) {
        this.onTextChanged = onTextChanged;
    }

    int d(int r) {
        return H.dip2px(getContext(), r);
    }

    public InputCell(Context context) {
        super(context);
        init(context);
    }

    public InputCell(Context context, String identifier) {
        super(context, identifier);
        init(context);
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        setBackgroundColor(Color.WHITE);
        getContentView().getLayoutParams().height = ViewGroup.LayoutParams.WRAP_CONTENT;
    }

    private void init(Context context) {
        titleView = new TextView(context);
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(d(15), d(15), d(10), d(15));
        titleView.setGravity(Gravity.CENTER_VERTICAL);
        titleView.setLayoutParams(layoutParams);
        titleView.setEllipsize(END);
        titleView.setTextSize(16);
        titleView.getPaint().setFakeBoldText(true);
        titleView.setTextColor(Color.rgb(80, 80, 80));
        titleView.setMaxWidth(d(130));
        getContentView().addView(titleView);

        editText = new EditText(context);
        layoutParams = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        layoutParams.setMargins(d(145), d(0), d(10), d(0));
        layoutParams.addRule(CENTER_VERTICAL, TRUE);
        editText.setGravity(Gravity.END);
        editText.setLayoutParams(layoutParams);
        editText.setTextSize(16);
        editText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                if (onTextChanged != null) {
                    onTextChanged.textChanged(InputCell.this, s.toString());
                }
            }
        });
        getContentView().addView(editText);
    }

    public TextView getTitleView() {
        return titleView;
    }

    public EditText getEditText() {
        return editText;
    }
}
