package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.view.ContextThemeWrapper;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.gr.Request;
import com.gr.classes.Array;
import com.gr.classes.Map;

import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;

/**
 * Created by mac on 2017/6/6.
 */

public class BookHeaderCell extends ListCell {

    cn.gen.gsv2.views.ImageView imageView;
    TextView titleLabel;
    TextView descriptionLabel;
    Button  hostButton;

    public BookHeaderCell(Context context) {
        super(context);
    }

    public BookHeaderCell(Context context, String identifier) {
        super(context, identifier);
    }

    public TextView getTitleLabel() {
        return titleLabel;
    }

    public TextView getDescriptionLabel() {
        return descriptionLabel;
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        RelativeLayout layout = (RelativeLayout)inflate(context, R.layout.cell_book_header, this);

        setContentView(layout);
        imageView = (cn.gen.gsv2.views.ImageView) layout.findViewById(R.id.image);
        titleLabel = (TextView) layout.findViewById(R.id.title);
        descriptionLabel = (TextView) layout.findViewById(R.id.description);
        hostButton = (Button) layout.findViewById(R.id.host_button);

        hostButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i("clicked", "CLicked!");
            }
        });
    }

    public void setImageUrl(String url) {
        setImageUrl(url, null);
    }

    public void setImageUrl(String url, Map headers) {
        imageView.setUrl(url, headers);
    }

    public Button getHostButton() {
        return hostButton;
    }
}
