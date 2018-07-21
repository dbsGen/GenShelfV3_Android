package cn.gen.gsv2.views;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.support.v4.app.ActivityCompat;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

import java.util.ArrayList;

import apps.gen.lib.Activity;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Chapter;

/**
 * Created by mac on 2017/6/7.
 */

public class ChapterCell extends ListCell implements View.OnClickListener, View.OnLongClickListener {
    Button[] buttons;
    ArrayList<Chapter> chapters;
    String checkUrl;
    int offset;
    Drawable selected;
    Drawable noselected;

    public interface OnClickListener {
        void click(int index);
        boolean longClick(int index);
    }
    OnClickListener buttonClicked;

    public ChapterCell(Context context) {
        super(context);
    }

    public ChapterCell(Context context, String identifier) {
        super(context, identifier);
    }

    public void setCheckUrl(String checkUrl) {
        this.checkUrl = checkUrl;
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
        RelativeLayout layout = (RelativeLayout)inflate(context, R.layout.cell_chapters, this);
        setContentView(layout);

        buttons = new Button[3];
        buttons[0] = (Button)layout.findViewById(R.id.button1);
        buttons[1] = (Button)layout.findViewById(R.id.button2);
        buttons[2] = (Button)layout.findViewById(R.id.button3);
        buttons[0].setOnClickListener(this);
        buttons[1].setOnClickListener(this);
        buttons[2].setOnClickListener(this);
        buttons[0].setOnLongClickListener(this);
        buttons[1].setOnLongClickListener(this);
        buttons[2].setOnLongClickListener(this);
    }

    public void setChapters(ArrayList<Chapter> chapters, int offset) {
        this.chapters = chapters;
        this.offset = offset;

        int total = Math.min(chapters.size() - offset, 3);
        for (int i = 0; i < 3; ++i) {
            int idx = i + offset;
            if (i < total) {
                Button button = buttons[i];
                button.setVisibility(View.VISIBLE);
                Chapter chapter = chapters.get(idx);
                button.setText(chapter.getName());
                if (chapter.getUrl().equals(checkUrl)) {
                    button.setBackground(ActivityCompat.getDrawable(getContext(), R.drawable.background));
                    button.setTextColor(Color.WHITE);
                }else {
                    button.setBackground(ActivityCompat.getDrawable(getContext(), R.drawable.chapter));

                    button.setTextColor(ActivityCompat.getColorStateList(getContext(), R.drawable.chaptet_text));
                }
            }else {
                buttons[i].setVisibility(View.INVISIBLE);
            }
        }
    }

    public Button[] getButtons() {
        return buttons;
    }

    public void setButtonClicked(OnClickListener buttonClicked) {
        this.buttonClicked = buttonClicked;
    }

    @Override
    public void onClick(View v) {
        if (buttonClicked != null) {
            if (buttons[0] == v) {
                buttonClicked.click(offset);
            }else if (buttons[1] == v) {
                buttonClicked.click(offset + 1);
            }else if (buttons[2] == v) {
                buttonClicked.click(offset + 2);
            }
        }
    }

    @Override
    public boolean onLongClick(View v) {
        if (buttonClicked != null) {
            if (buttons[0] == v) {
                return buttonClicked.longClick(offset);
            }else if (buttons[1] == v) {
                return buttonClicked.longClick(offset + 1);
            }else if (buttons[2] == v) {
                return buttonClicked.longClick(offset + 2);
            }
        }
        return false;
    }
}
