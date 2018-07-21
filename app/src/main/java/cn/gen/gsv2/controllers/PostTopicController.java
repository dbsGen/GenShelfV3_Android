package cn.gen.gsv2.controllers;


import android.animation.ObjectAnimator;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v7.widget.PopupMenu;
import android.text.Editable;
import android.text.SpannableStringBuilder;
import android.text.Spanned;
import android.text.TextWatcher;
import android.text.method.Touch;
import android.text.style.ImageSpan;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.Toast;

import app.dinus.com.loadingdrawable.render.LoadingDrawable;
import app.dinus.com.loadingdrawable.render.circle.rotate.MaterialLoadingRenderer;
import apps.gen.lib.controllers.Controller;

import com.fichardu.interpolator.EaseOutCubicInterpolator;
import com.gr.Activity;
import com.gr.Request;
import com.gr.classes.Array;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.util.ArrayList;
import java.util.Date;
import java.util.Random;
import java.util.UUID;

import apps.gen.lib.utils.H;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.ArtBasket;
import cn.gen.gsv2.models.KeyValue;
import cn.gen.gsv2.utils.ArtSpan;
import cn.gen.gsv2.views.ArtCell;
import cn.gen.gsv2.views.TouchPanel;

/**
 * A simple {@link Fragment} subclass.
 */
public class PostTopicController extends Controller implements PopupMenu.OnMenuItemClickListener, Request.OnStatusListener {

    public interface OnPostListener {
        void onPost(PostTopicController c);
    }

    EditText titleView;
    EditText contentView;
    Button categoryButton;
    ImageButton booksButton;
    RelativeLayout drawer;
    ArrayList<SocialController.Category> categories;
    int selected = 0;
    TouchPanel drawerCover, loadingCover;
    ListView bookList;
    BaseAdapter bookAdapter;
    Array<ArtBasket.Art> arts;
    OnPostListener onPostListener;

    boolean edit = false;

    String uuid;

    SpannableStringBuilder stringBuilder = new SpannableStringBuilder();

    NavigationItem commitItem, loadingItem;
    LoadingDrawable loadingDrawable;

    public PostTopicController() {
        // Required empty public constructor
    }

    public void setSelected(int selected) {
        this.selected = selected;
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        commitItem = new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.done),
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        commit();
                    }
                });
        loadingDrawable = new LoadingDrawable(new MaterialLoadingRenderer.Builder(context).setWidth(72).setHeight(72).setColors(new int[]{Color.WHITE, Color.argb(150, 255, 255, 255)}).build());
        loadingItem = new NavigationItem(loadingDrawable);

        setRightItems(commitItem);

        setTitle(context.getString(R.string.post_topic));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_post_topic, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        MainActivity activity = (MainActivity) Activity.current();
        categories = activity.getSocialController().getCategories();

        titleView = (EditText)view.findViewById(R.id.title);
        contentView = (EditText)view.findViewById(R.id.content);

        drawer = (RelativeLayout)view.findViewById(R.id.drawer);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            drawer.setZ(4);
        }
        drawer.setTranslationX(H.dip2px(getContext(), 140));

        if (categories.size() > selected) {
            categoryButton = (Button)view.findViewById(R.id.category_button);
            categoryButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    PopupMenu menu = new PopupMenu(getContext(), v);
                    int count = 0;
                    for (SocialController.Category category : categories) {
                        menu.getMenu().add(0, 0, count++, category.name);
                    }
                    menu.setOnMenuItemClickListener(PostTopicController.this);
                    menu.show();
                }
            });

            categoryButton.setText(categories.get(selected).name);
        }

        drawerCover = (TouchPanel)view.findViewById(R.id.drawer_cover);
        drawerCover.setListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                missDrawer();
            }
        });
        drawerCover.setAlpha(0);

        booksButton = (ImageButton)view.findViewById(R.id.books_button);
        booksButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showDrawer();
            }
        });

        bookList = (ListView)view.findViewById(R.id.books_list);
        arts = ArtBasket.getArts();
        bookAdapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return arts.size();
            }

            @Override
            public Object getItem(int position) {
                return null;
            }

            @Override
            public long getItemId(int position) {
                return 0;
            }

            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                ArtCell cell = (ArtCell)convertView;
                if (cell == null) {
                    cell = new ArtCell(getContext());
                }
                cell.setArt(arts.get(position));
                return cell;
            }
        };
        bookList.setAdapter(bookAdapter);
        bookList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                ArtBasket.Art art = arts.get(position);
                insertArt(art);
            }
        });

        contentView.setText(stringBuilder);
        contentView.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                if (edit) return;
                stringBuilder.replace(start, start + before, s.subSequence(start, start + count));
            }

            @Override
            public void afterTextChanged(Editable s) {

            }
        });

        loadingCover = (TouchPanel)view.findViewById(R.id.loading_cover);
        loadingCover.setEnableListener(false);
    }

    @Override
    public boolean onMenuItemClick(MenuItem item) {
        selected = item.getOrder();
        categoryButton.setText(categories.get(selected).name);
        return false;
    }

    @Override
    protected void onViewWillDisappear() {
        super.onViewWillDisappear();
        closeInput();
        loadingDrawable.stop();
    }

    void closeInput() {
        InputMethodManager imm = (InputMethodManager)getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.hideSoftInputFromWindow(getView().getWindowToken(),0);
    }

    float animationP = 0;

    void setAnimationP(float p) {
        animationP = p;
        drawerCover.setAlpha(p);
        drawer.setTranslationX(drawer.getWidth() * (1-p));
    }

    public float getAnimationP() {
        return animationP;
    }

    public void setOnPostListener(OnPostListener onPostListener) {
        this.onPostListener = onPostListener;
    }

    boolean drawerOpen = false;
    ObjectAnimator animator;
    private void showDrawer() {
        if (drawerOpen) return;
        drawerOpen = true;

        if (animator != null) animator.cancel();
        animator = ObjectAnimator.ofFloat(this, "animationP", 0, 1);
        animator.setInterpolator(new EaseOutCubicInterpolator());
        animator.setDuration(300);
        animator.start();
        drawerCover.setEnableListener(true);
    }

    private void missDrawer() {
        if (!drawerOpen) return;
        drawerOpen = false;
        if (animator != null) animator.cancel();
        animator = ObjectAnimator.ofFloat(this, "animationP", 1, 0);
        animator.setInterpolator(new EaseOutCubicInterpolator());
        animator.setDuration(300);
        animator.start();
        drawerCover.setEnableListener(false);
    }

    void insertArt(ArtBasket.Art art) {
        String imgText = art.html();
        int start = contentView.getSelectionStart();
        stringBuilder.replace(start, contentView.getSelectionEnd(), imgText);
        ImageSpan artSpan = ArtSpan.from(getContext(), art);
        stringBuilder.setSpan(artSpan, start, start + imgText.length(),
                Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
        edit = true;
        contentView.setText(stringBuilder);
        edit = false;
        contentView.setSelection(start + imgText.length());
    }

    void commit() {
        if (categories.size() <= selected) {
            Toast.makeText(getContext(), getContext().getString(R.string.require_category), Toast.LENGTH_SHORT).show();
            return;
        }
        String title = titleView.getText().toString().trim();
        if (title.isEmpty()) {
            Toast.makeText(getContext(), getContext().getString(R.string.require_title), Toast.LENGTH_SHORT).show();
            titleView.requestFocus();
            return;
        }
        String content = contentView.getText().toString().trim();
        if (content.isEmpty()) {
            Toast.makeText(getContext(), getContext().getString(R.string.require_content), Toast.LENGTH_SHORT).show();
            contentView.requestFocus();
            return;
        }
        missDrawer();
        closeInput();

        setRightItems(loadingItem);
        loadingDrawable.start();

        ObjectAnimator ani = ObjectAnimator.ofFloat(loadingCover, "alpha", 1, 0);
        ani.setInterpolator(new EaseOutCubicInterpolator());
        ani.setDuration(300);
        ani.start();
        loadingCover.setEnableListener(true);

        Request request = Request.get("http://112.74.13.80:3000/topics");
        request.setTimeout(5000);
        request.method = "POST";
        if (uuid == null) {
            String str = new Date().toString() + new Random().nextLong();
            uuid = UUID.nameUUIDFromBytes(str.getBytes()).toString();
        }
        request.setReadCache(false);
        request.setReadCacheWhenError(false);
        request.addParams("title", title);
        request.addParams("content", content);
        request.addParams("udid", uuid);
        SocialController.Category c = categories.get(selected);
        request.addParams("category", "" + c.id);
        String name = KeyValue.get("author_name");
        if (name != null && !name.isEmpty()) {
            request.addParams("author", name);
        }
        request.setListener(this);
        request.start();
    }

    @Override
    public void onProgress(Request request, float percent) {

    }

    @Override
    public void onComplete(Request request) {
        String json = H.read(request.getPath());
        try {
            JSONObject jobj = new JSONObject(json);
            if (jobj.getInt("code") == 0) {
                Toast.makeText(getContext(), getContext().getString(R.string.complete), Toast.LENGTH_LONG).show();
                if (onPostListener == null) {
                    H.navC(this).pop(true);
                }else {
                    onPostListener.onPost(this);
                }
            }else {
                Toast.makeText(getContext(), getContext().getString(R.string.failed) + ":" + jobj.getString("msg"),
                        Toast.LENGTH_LONG).show();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        ObjectAnimator ani = ObjectAnimator.ofFloat(loadingCover, "alpha", 1, 0);
        ani.setInterpolator(new EaseOutCubicInterpolator());
        ani.setDuration(300);
        ani.start();
        loadingCover.setEnableListener(false);
        setRightItems(commitItem);
        loadingDrawable.stop();
    }

    @Override
    public void onFailed(Exception e) {
        Toast.makeText(getContext(), getContext().getString(R.string.failed) + ": network failed.", Toast.LENGTH_LONG).show();

        ObjectAnimator ani = ObjectAnimator.ofFloat(loadingCover, "alpha", 1, 0);
        ani.setInterpolator(new EaseOutCubicInterpolator());
        ani.setDuration(300);
        ani.start();
        loadingCover.setEnableListener(false);
        setRightItems(commitItem);
        loadingDrawable.stop();
    }

    @Override
    public void onCancel(Request request) {

    }
}
