package cn.gen.gsv2.controllers;


import android.content.Context;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.PointF;
import android.graphics.Rect;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceScreen;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;

import apps.gen.lib.views.NavigationBar;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.models.ArtBasket;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.KeyValue;
import cn.gen.gsv2.models.Page;
import cn.gen.gsv2.models.Reader;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.views.LoadingView;
import cn.gen.gsv2.views.PagerAdapter;
import cn.gen.gsv2.views.SelectButton;
import cn.gen.gsv2.views.ViewPager;

import android.support.v4.widget.DrawerLayout;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.widget.PopupMenu;
import android.text.TextPaint;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.bigkoo.pickerview.OptionsPickerView;
import com.bigkoo.pickerview.listener.OnDismissListener;
import com.boycy815.pinchimageview.PinchImageView;
import com.gr.Activity;
import com.gr.Request;
import com.gr.classes.Array;
import com.gr.classes.Callback;
import com.gr.classes.Map;
import com.gr.classes.NotificationCenter;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.Dictionary;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Chapter;
import cn.gen.gsv2.views.PictureView;
import cn.gen.gsv2.views.ScrollBorderView;

import static android.os.Environment.DIRECTORY_ALARMS;
import static android.os.Environment.DIRECTORY_DOCUMENTS;
import static android.os.Environment.DIRECTORY_PICTURES;
import static android.os.Environment.getExternalStoragePublicDirectory;

/**
 * A simple {@link Fragment} subclass.
 */
public class ViewController extends Controller implements PinchImageView.OnClickListener,
        PopupMenu.OnMenuItemClickListener, apps.gen.lib.utils.NotificationCenter.Runnable {

    Chapter chapter;
    Shop shop;
    Reader reader;
    Book book;
    ArrayList<Page> pages = new ArrayList<>();

    int prev_status, next_status;
    boolean localBook;

    ViewPager viewPager;
    PagerAdapter adapter;
    ArrayList<View> cacheViews = new ArrayList<>();
    HashMap<Integer, PictureView> displayViews = new HashMap<Integer, PictureView>();

    ScrollBorderView borderView;
    LoadingView loadingView;
    SwipeRefreshLayout refreshLayout;

    Callback onPageStatus;
    Callback onChapterPercent;
    Callback onChapterPageCount;
    Callback reloadComplete;

    SelectButton selectButton;
    NavigationBar navigationBar;

    OptionsPickerView optionsView;

    boolean canHidden = true;

    String titleString;
    int currentIndex;

    int total_page;
    boolean reloading = false;

    boolean added_share = false;

    static final String KEY_IS_PORTRAIT = "is_portrait";

    public interface OnChapterChangedListener {
        Chapter prevChapter(Chapter chapter);
        Chapter nextChapter(Chapter chapter);
    }

    OnChapterChangedListener onChapterChangedListener;

    public ViewController() {
        // Required empty public constructor
    }

    boolean isPortrait() {
        String isPortrait = KeyValue.get(KEY_IS_PORTRAIT);
        int isP = 1;
        try {
            isP = Integer.parseInt(isPortrait);
        }catch (Exception e) {

        }
        return isP == 1;
    }

    @Override
    protected void initialize(final Context context) {
        super.initialize(context);
        setRightItems(new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.menu_2), new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                PopupMenu menu = new PopupMenu(getContext(), v);
                if (localBook) {
                    menu.inflate(R.menu.book_local);
                }else {
                    menu.inflate(R.menu.book_online);
                }
                menu.getMenu().findItem(R.id.swap).setTitle(isPortrait() ? context.getString(R.string.landscape) :
                        context.getString(R.string.portrait));
                menu.setOnMenuItemClickListener(ViewController.this);
                menu.show();
            }
        }));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_view, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        final Window window = Activity.current().getWindow();

        viewPager = (ViewPager)view.findViewById(R.id.view_pager);
        borderView = (ScrollBorderView)view.findViewById(R.id.border);
        loadingView = (LoadingView)view.findViewById(R.id.loading_view);

        adapter = new PagerAdapter() {
            @Override
            public int getCount() {
                return pages.size();
            }

            @Override
            public boolean isViewFromObject(View view, Object object) {
                return view == object;
            }

            @Override
            public Object instantiateItem(ViewGroup container, int position) {
                PictureView pictureView;
                if (cacheViews.size() > 0) {
                    Object obj = cacheViews.get(0);
                    cacheViews.remove(0);
                    pictureView = (PictureView)obj;
                }else {
                    pictureView = new PictureView(getContext());
                    pictureView.setLayoutParams(new ViewPager.LayoutParams());
                    pictureView.setImageResource(R.drawable.no_image);
                    pictureView.setOnClickListener(ViewController.this);
                }
                displayViews.put(position, pictureView);
                container.addView(pictureView);
                if (localBook) {
                    String path = book.picturePath(chapter, position);
                    File file = new File(path);
                    if (file.exists()) {
                        pictureView.setImagePath(path);
                    }else {
                        pictureView.reset();
                        chapter.bringFirst(position);
                    }
                }else {
                    Page page = pages.get(position);
                    if (page != null) {
                        pictureView.setPage(page);
                    }else {
                        pictureView.reset();
                    }
                }
                return pictureView;
            }

            @Override
            public void destroyItem(ViewGroup container, int position, Object object) {
                cacheViews.add((View)object);
                container.removeView((View)object);
                displayViews.remove(position);
            }

            @Override
            public int getItemPosition(Object object) {
                if (displayViews.containsValue(object)) {
                    return POSITION_UNCHANGED;
                }else {
                    return POSITION_NONE;
                }
            }
        };
        viewPager.setAdapter(adapter);

        borderView.setOnChapterListener(new ScrollBorderView.OnChapterListener() {
            @Override
            public void onChapter(boolean next) {
                if (onChapterChangedListener != null) {
                    Chapter c;
                    if (next) {
                        c = onChapterChangedListener.nextChapter(chapter);
                    }else {
                        c = onChapterChangedListener.prevChapter(chapter);
                    }
                    if (c == null) {
                        Toast.makeText(getContext(), getContext().getString(R.string.no_more), Toast.LENGTH_SHORT).show();
                    }else {
                        reloadChapter(c);
                    }
                }
            }
        });
        viewPager.addOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {

            }

            @Override
            public void onPageSelected(int position) {
                currentIndex = position;
                if (!reloading)
                    chapter.setLastIndex(currentIndex);
                updateTitle();
            }

            @Override
            public void onPageScrollStateChanged(int state) {

            }
        });

        refreshLayout = (SwipeRefreshLayout)view.findViewById(R.id.refresh);
        refreshLayout.setColorSchemeResources(R.color.blue);
        refreshLayout.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                reloadPage(viewPager.getCurrentItem());
                getHandler().postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        refreshLayout.setRefreshing(false);
                    }
                }, 800);
            }
        });

        selectButton = new SelectButton(getContext());
        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(H.dip2px(getContext(), 40), ViewGroup.LayoutParams.MATCH_PARENT);
        layoutParams.setMargins(H.dip2px(getContext(), 44), 0, 0, 0);
        selectButton.setLayoutParams(layoutParams);
        selectButton.setVisibility(View.GONE);
        selectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ArrayList<String> sps = new ArrayList<>();
                for (int i = 0, t = pages.size(); i < t; ++i) {
                    sps.add("" + (i+1));
                }
                optionsView.setPicker(sps);
                optionsView.setSelectOptions(currentIndex);
                selectButton.extend(true);
                optionsView.show();
            }
        });

        optionsView = new OptionsPickerView.Builder(getContext(), new OptionsPickerView.OnOptionsSelectListener(){

            @Override
            public void onOptionsSelect(int options1, int options2, int options3, View v) {
                viewPager.setCurrentItem(options1);
            }
        }).build();
        optionsView.setOnDismissListener(new OnDismissListener() {
            @Override
            public void onDismiss(Object o) {
                selectButton.extend(false);
            }
        });

        if (localBook) {
            setupLocalBook();
        }else {
            setupReader();
        }

        H.NC().addListener(Request.REQUEST_COMPLETE, this);
        H.NC().addListener(Request.REQUEST_FAILED, this);
    }

    @Override
    public void onDestroyView() {
        for (View view : cacheViews) {
            ((PictureView)view).clear();
        }
        Collection<PictureView> pics = displayViews.values();
        for (PictureView view : pics) {
            view.clear();
        }
        H.NC().removeListener(Request.REQUEST_COMPLETE, this);
        H.NC().removeListener(Request.REQUEST_FAILED, this);
        Log.i("view controller", "destroy");
        super.onDestroyView();
    }

    public void setOnChapterChangedListener(OnChapterChangedListener onChapterChangedListener) {
        this.onChapterChangedListener = onChapterChangedListener;
    }

    public void setChapter(Chapter chapter) {
        this.chapter = chapter;
        String name = chapter.getName();
        titleString = chapter.getName().substring(0, Math.min(name.length(), 10));
        setTitle(titleString);
    }

    public void setLocalBook(boolean localBook) {
        this.localBook = localBook;
    }

    public void setBook(Book book) {
        this.book = book;
    }

    public void setShop(Shop shop) {
        this.shop = shop;
    }

    boolean extend = true;

    @Override
    public void onClick(View v, MotionEvent event) {
        DisplayMetrics dm = new DisplayMetrics();
        MainActivity mainActivity = (MainActivity)Activity.current();
        mainActivity.getWindowManager().getDefaultDisplay().getMetrics(dm);
        if (event.getX() < dm.widthPixels / 3) {
            if (viewPager.getCurrentItem() > 0) {
                viewPager.setCurrentItem(viewPager.getCurrentItem() - 1, true);
            }else {
                Chapter c = onChapterChangedListener.prevChapter(chapter);
                if (c == null) {
                    Toast.makeText(getContext(), getContext().getString(R.string.no_more), Toast.LENGTH_SHORT).show();
                }else {
                    reloadChapter(c);
                }
            }
        }else if (event.getX() < dm.widthPixels * 2 / 3) {
            extend = !extend;
            hideNavBar(!extend);
        }else {
            if (viewPager.getCurrentItem() < pages.size() - 1) {
                viewPager.setCurrentItem(viewPager.getCurrentItem() + 1, true);
            }else {
                Chapter c = onChapterChangedListener.nextChapter(chapter);
                if (c == null) {
                    Toast.makeText(getContext(), getContext().getString(R.string.no_more), Toast.LENGTH_SHORT).show();
                } else {
                    reloadChapter(c);
                }
            }
        }
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_VOLUME_UP: {
                int idx = viewPager.getCurrentItem();
                if (displayViews.containsKey(idx)) {
                    PictureView pictureView = displayViews.get(idx);
                    if (pictureView.scrollOrCannot(false)) {
                        return true;
                    }
                }
                if (viewPager.getCurrentItem() > 0) {
                    viewPager.setCurrentItem(viewPager.getCurrentItem() - 1, true);
                }else {
                    Chapter c = onChapterChangedListener.prevChapter(chapter);
                    if (c == null) {
                        Toast.makeText(getContext(), getContext().getString(R.string.no_more), Toast.LENGTH_SHORT).show();
                    }else {
                        reloadChapter(c);
                    }
                }
                return true;
            }
            case KeyEvent.KEYCODE_VOLUME_DOWN: {
                int idx = viewPager.getCurrentItem();
                if (displayViews.containsKey(idx)) {
                    PictureView pictureView = displayViews.get(idx);
                    if (pictureView.scrollOrCannot(true)) {
                        return true;
                    }
                }
                if (viewPager.getCurrentItem() < pages.size() - 1) {
                    viewPager.setCurrentItem(viewPager.getCurrentItem() + 1, true);
                }else {
                    Chapter c = onChapterChangedListener.nextChapter(chapter);
                    if (c == null) {
                        Toast.makeText(getContext(), getContext().getString(R.string.no_more), Toast.LENGTH_SHORT).show();
                    } else {
                        reloadChapter(c);
                    }
                }
                return true;
            }
        }
        return false;
    }

    void hiddenNav() {
        if (!canHidden) return;
        extend = false;
        selectButton.setVisibility(View.VISIBLE);
        hideNavBar(!extend);
    }

    void hideNavBar(boolean hidden) {
        try {
            H.navC(this).setNavBarHidden(hidden, true);

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                if (hidden) {
                    Activity.current().getWindow().setStatusBarColor(Color.BLACK);
                }else {
                    Activity.current().getWindow().setStatusBarColor(ActivityCompat.getColor(getContext(), R.color.blue));
                }
            }
        }catch (Exception e) {
            e.printStackTrace();
        }
    }

    void checkTitleSize() {
        try {
            TextPaint paint = H.navC(this).getNavigationBar().getTitleView().getPaint();
            Rect rect = new Rect();
            paint.getTextBounds(getTitle(), 0, getTitle().length(), rect);
            selectButton.getLayoutParams().width = rect.width() + H.dip2px(getContext(), 24);
        }catch (Exception e) {
            e.printStackTrace();
        }
    }

    boolean active = false;

    @Override
    protected void onViewDidAppear() {
        super.onViewDidAppear();

        navigationBar = H.navC(this).getNavigationBar();
        if (selectButton.getParent() != null) {
            ((ViewGroup)selectButton.getParent()).removeView(selectButton);
        }
        navigationBar.addView(selectButton);
        checkTitleSize();

        if (isPortrait()) {
            MainActivity.current().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);
        }else {
            MainActivity.current().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
        }
    }

    @Override
    protected void onViewWillAppear() {
        super.onViewWillAppear();
        active = true;
        ((MainActivity)Activity.current()).getDrawerLayout().setDrawerLockMode(DrawerLayout.LOCK_MODE_LOCKED_CLOSED);
    }

    @Override
    protected void onViewWillDisappear() {
        super.onViewWillDisappear();
        try {
            if (H.navC(this).getNavHidden()) {
                hideNavBar(false);
            }
        }catch (Exception e) {
            e.printStackTrace();
        }
        canHidden = false;
        ((MainActivity)Activity.current()).getDrawerLayout().setDrawerLockMode(DrawerLayout.LOCK_MODE_UNLOCKED);
        navigationBar.removeView(selectButton);
        active = false;
        if (reader != null) {
            reader.apply("stop");
            reader.setOnPageCount(null);
            reader.setOnPageLoaded(null);
            reader = null;
        }
        if (nextRunnable != null) {
            getHandler().removeCallbacks(nextRunnable);
            nextRunnable = null;
        }
        for (Request req : requests) {
            req.cancel();
        }
        requests.clear();
        MainActivity.current().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
    }

    private void setupReader() {
        if (reader == null) {
            prev_status = 0;
            next_status = 0;

            Array<Page> cps = chapter.cachedPages();
            if (cps != null && cps.size() > 0) {
                for (Page page : cps) {
                    pages.add(page);
                    loadedPage(page);
                }
                adapter.notifyDataSetChanged();
                viewPager.setCurrentItem(chapter.lastIndex(), false);
                loadingView.miss();
                updateTitle();
                hiddenNav();
                total_page = cps.size();
                return;
            }
            reader = new Reader(true);

            reader.setOnPageCount(new Callback(true) {
                @Override
                public Object run(Object... args) {
                    boolean success = (boolean)args[0];
                    if (success) {
                        int page_count = (int)args[1];
                        while (pages.size() < page_count) {
                            pages.add(null);
                        }
                        updateTitle();
                        if (loadingView.getStatus() == LoadingView.STATUS_LOADING) {
                            loadingView.miss();
                            hiddenNav();
                        }
                        total_page = page_count;
                        checkPages();
                        adapter.notifyDataSetChanged();
                    }else {
                        loadingView.failed();
                    }
                    return null;
                }
            });
            reader.setOnPageLoaded(new Callback(true) {
                @Override
                public Object run(Object... args) {
                    boolean success = (boolean)args[0];
                    if (success) {
                        int idx = (int)args[1];
                        Page page = (Page)args[2];
                        boolean sizeChanged = false;
                        while (pages.size() <= idx) {
                            pages.add(null);
                            sizeChanged = true;
                        }
                        pages.set(idx, page);
                        loadedPage(page);
                        updateTitle();
                        checkPages();

                        if (pages.size() > 3 && sizeChanged) {
                            if (loadingView.getStatus() == LoadingView.STATUS_LOADING) {
                                loadingView.miss();
                                hiddenNav();
                            }
                            adapter.notifyDataSetChanged();
                        }

                        if (displayViews.containsKey(idx)) {
                            PictureView pictureView = displayViews.get(idx);
                            pictureView.setPage(page);
                        }
                    }
                    return null;
                }
            });
            shop.setupReader(reader, 0);
            loadingView.startLoading();
            reader.apply("process", chapter);
        }
    }

    void setupLocalBook() {
        Array ps = chapter.getPages();
        pages.clear();
        if (ps.size() != 0) {
            for (Object o : ps) {
                pages.add((Page)o);
            }
            adapter.notifyDataSetChanged();
            loadingView.miss();
            hiddenNav();
            viewPager.setCurrentItem(chapter.lastIndex(), false);
        }else {
            loadingView.startLoading();
        }

        onPageStatus = new Callback(true) {
            @Override
            public Object run(Object... args) {
                Page page = (Page)args[0];
                Chapter chapter = (Chapter)args[1];
                int index = (int)args[2];
                int status = (int)args[3];
                if (chapter.equals(ViewController.this.chapter)) {
                    if (status == Chapter.STATUS_COMPLETE ||
                            status == Chapter.STATUS_FAILED) {
                        boolean sizeChanged = false;
                        while (pages.size() <= index) {
                            pages.add(null);
                            sizeChanged = true;
                        }

                        pages.set(index, page);
                        if (sizeChanged) {
                            updateTitle();
                        }
                        if (pages.size() > 3 && sizeChanged) {
                            if (loadingView.getStatus() == LoadingView.STATUS_LOADING) {
                                loadingView.miss();
                                hiddenNav();
                            }
                            adapter.notifyDataSetChanged();
                        }

                        if (displayViews.containsKey(index)) {
                            PictureView pictureView = displayViews.get(index);
                            pictureView.setPage(page);
                        }
                    }
                }
                return null;
            }
        };
        NotificationCenter.getInstance().listen("PAGE_STATUS", onPageStatus);

        onChapterPercent = new Callback(true) {
            @Override
            public Object run(Object... args) {
                Chapter c = (Chapter)args[0];
                float per = (float)args[1];
                if (c == chapter) {
                    Log.i("Chapter", "Percent " + per);
                }
                return null;
            }
        };
        NotificationCenter.getInstance().listen("CHAPTER_PERCENT", onChapterPercent);
        if (Shop.download(book, chapter) == 2) {
            Toast.makeText(getContext(), book.getShopId() + " is not installed.", Toast.LENGTH_SHORT).show();
        }
        if (ps.size() == 0) {
            int size = chapter.pageCount();
            if (size == 0) size = chapter.oldDownloaded();
            if (size > 0) {
                while (pages.size() < size) {
                    pages.add(null);
                }
                adapter.notifyDataSetChanged();
                loadingView.miss();
                hiddenNav();
            }
            onChapterPageCount = new Callback(true) {
                @Override
                public Object run(Object... args) {
                    Chapter chapter = (Chapter)args[0];
                    if (chapter == ViewController.this.chapter) {
                        int page_count = (int)args[1];
                        while (pages.size() < page_count) {
                            pages.add(null);
                        }
                        updateTitle();
                        if (loadingView.getStatus() == LoadingView.STATUS_LOADING) {
                            loadingView.miss();
                            hiddenNav();
                        }
                        adapter.notifyDataSetChanged();
                    }
                    return null;
                }
            };
            NotificationCenter.getInstance().listen("CHAPTER_PAGE_COUNT", onChapterPageCount);
        }
        updateTitle();
    }

    void updateTitle() {
        setTitle(titleString + "(" + (currentIndex + 1) + "/" + pages.size() + ")");
        checkTitleSize();
    }

    @Override
    protected void onViewDidDisappear() {
        super.onViewDidDisappear();
        if (onPageStatus != null) {
            NotificationCenter.getInstance().remove("PAGE_STATUS", onPageStatus);
        }
        if (onChapterPercent != null) {
            NotificationCenter.getInstance().remove("CHAPTER_PERCENT", onChapterPercent);
        }
        if (onChapterPageCount != null) {
            NotificationCenter.getInstance().remove("CHAPTER_PAGE_COUNT", onChapterPageCount);
        }
    }

    private void reloadPage(final int index) {
        final Page page = pages.get(index);

        if (reader == null) {
            if (shop != null) {
                reader = new Reader(true);
                shop.setupReader(reader, 0);
            }
        }

        if (reader != null) {
            if (displayViews.containsKey(index)) {
                PictureView view = displayViews.get(index);
                view.setImageResource(R.drawable.no_image);
            }
            String path = book.picturePath(chapter, index);
            File file = new File(path);
            file.deleteOnExit();

            reloadComplete = new Callback(true) {
                @Override
                public Object run(Object... args) {
                    boolean success = (boolean)args[0];
                    if (success) {
                        Page p = (Page)args[1];

                        while (pages.size() <= index) {
                            pages.add(null);
                        }
                        pages.set(index, page);
                        checkPages();
                        if (displayViews.containsKey(index)) {
                            PictureView view = displayViews.get(index);
                            if (localBook) {
                                requestPicture(p, book, chapter, index);
                            }else {
                                view.setPage(p);
                            }
                        }
                    }
                    return null;
                }
            };
            reader.apply("reloadPage", page, index, reloadComplete);
        }
    }

    @Override
    public boolean onMenuItemClick(MenuItem item) {
        if (loadingView.getStatus() != LoadingView.STATUS_MISSING) {
            return false;
        }
        if (item.getItemId() == R.id.swap) {

            String isPortrait = KeyValue.get(KEY_IS_PORTRAIT);
            int isP = 1;
            try {
                isP = Integer.parseInt(isPortrait);
            }catch (Exception e) {

            }
            isP = (isP + 1) % 2;
            KeyValue.set(KEY_IS_PORTRAIT, "" + isP);

            item.setTitle(isP == 0 ? getContext().getString(R.string.landscape) :
                    getContext().getString(R.string.portrait));

            if (isP == 0) {
                MainActivity.current().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
            }else {
                MainActivity.current().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);
            }

        } else if (item.getItemId() == R.id.collect) {
            shop.collect(book, chapter);
            Toast.makeText(getContext(), getContext().getString(R.string.collect_ok), Toast.LENGTH_SHORT).show();
        } else if (item.getItemId() == R.id.refresh) {
            reloadPage(viewPager.getCurrentItem());
        } else if (item.getItemId() == R.id.share) {
            if (added_share) {
                PostTopicController ctrl = Controller.instantiate(getContext(), PostTopicController.class);
                H.navC(ViewController.this).push(ctrl, true);
            }else {
                ArtBasket.addChapter(book, chapter);
                Toast.makeText(getContext(), R.string.added_share, Toast.LENGTH_LONG).show();
                added_share = true;
            }
        }else if (item.getItemId() == R.id.save) {
            int i = viewPager.getCurrentItem();
            Page page = pages.get(i);
            try {
                Uri url = Uri.parse(page.getPicture());
                Pattern pattern = Pattern.compile("\\.[^\\.]+$");

                Matcher m = pattern.matcher(url.getLastPathSegment());
                StringBuilder sb = new StringBuilder();
                String name = book.getName();
                if (name.length() > 20) {
                    name = name.substring(0, 19);
                }
                name = name.replace('/', '_');
                sb.append(name);
                sb.append('_');
                sb.append(new Date().getTime());
                sb.append("_");
                sb.append(chapter.getName());
                sb.append("_");
                sb.append(i);
                if (m.find()) {
                    sb.append(m.group());
                }else {
                    sb.append(".jpg");
                }

                File df = getExternalStoragePublicDirectory(DIRECTORY_PICTURES);
                if (!df.exists()) {
                    df.mkdirs();
                }
                String path = df.toString() + "/" + sb.toString();

                String oriPath;
                if (localBook) {
                    oriPath = book.picturePath(chapter, i);
                }else {
                    oriPath = Request.get(page.getPicture()).getPath();
                }
                File file = new File(oriPath);
                if (file.exists()) {
                    if (H.copy(oriPath, path)) {
                        Toast.makeText(getContext(), getContext().getString(R.string.save_ok) + ":" + path, Toast.LENGTH_SHORT).show();
                    }else {
                        Toast.makeText(getContext(), R.string.save_failed, Toast.LENGTH_LONG).show();
                    }
                }else {
                    Toast.makeText(getContext(), R.string.save_not_ready, Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }else if (item.getItemId() == R.id.save_zip) {
            if (!localBook) return false;
            final Array<Page> pages = chapter.getPages();
            if (pages != null && pages.size() > 0) {
                StringBuilder sb = new StringBuilder();
                String name = book.getName();
                if (name.length() > 20) {
                    name = name.substring(0, 19);
                }
                name = name.replace('/', '_');
                sb.append(name);
                sb.append('_');
                sb.append(chapter.getName());
                sb.append(".zip");

                File df = getExternalStoragePublicDirectory(DIRECTORY_DOCUMENTS);
                if (!df.exists()) {
                    df.mkdirs();
                }
                final String path = df.toString() + "/" + sb.toString();

                final Thread thread = new Thread(new Runnable() {
                    @Override
                    public void run() {

                        try {

                            ArrayList<File> files = new ArrayList<>();
                            for (int i = 0, t = pages.size(); i < t; ++i) {
                                String p = book.picturePath(chapter, i);
                                File file = new File(p);
                                if (!file.exists()) {
                                    getHandler().post(new Runnable() {
                                        @Override
                                        public void run() {
                                            Toast.makeText(Activity.current(), R.string.save_not_ready, Toast.LENGTH_SHORT).show();
                                        }
                                    });
                                    return;
                                }
                                files.add(file);
                            }
                            FileOutputStream os = new FileOutputStream(new File(path));
                            ZipOutputStream zipos = new ZipOutputStream(os);
                            for (int i = 0, t = files.size(); i < t; ++i) {
                                Page page = pages.get(i);
                                Uri url = Uri.parse(page.getPicture());

                                Pattern pattern = Pattern.compile("\\.[^\\.]+$");

                                Matcher m = pattern.matcher(url.getLastPathSegment());
                                String str = String.format("%04d", i);
                                if (m.find()) {
                                    str += m.group();
                                }else {
                                    str += ".jpg";
                                }
                                ZipEntry entry = new ZipEntry(str);
                                zipos.putNextEntry(entry);
                                FileInputStream is = new FileInputStream(files.get(i));
                                int len;
                                byte[] buffer = new byte[2048];
                                while ((len = is.read(buffer)) > 0) {
                                    zipos.write(buffer, 0, len);
                                }
                                is.close();
                                zipos.flush();
                                zipos.closeEntry();
                            }
                            zipos.close();
                            os.close();
                            getHandler().post(new Runnable() {
                                @Override
                                public void run() {
                                    Toast.makeText(Activity.current(), Activity.current().getString(R.string.save_ok) + ":" + path.toString(), Toast.LENGTH_LONG).show();
                                }
                            });
                        } catch (Exception e) {
                            e.printStackTrace();
                            getHandler().post(new Runnable() {
                                @Override
                                public void run() {
                                    Toast.makeText(Activity.current(), R.string.save_failed, Toast.LENGTH_SHORT).show();
                                }
                            });
                        }
                    }
                });
                getHandler().postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        thread.start();
                    }
                }, 100);

            }else {
                Toast.makeText(Activity.current(), R.string.save_not_ready, Toast.LENGTH_SHORT).show();
            }

        }
        return false;
    }

    public static void copyFile(File sourceFile,File targetFile)
            throws IOException {
        // 新建文件输入流并对它进行缓冲
        FileInputStream input = new FileInputStream(sourceFile);
        BufferedInputStream inBuff=new BufferedInputStream(input);

        // 新建文件输出流并对它进行缓冲
        FileOutputStream output = new FileOutputStream(targetFile);
        BufferedOutputStream outBuff=new BufferedOutputStream(output);

        // 缓冲数组
        byte[] b = new byte[1024 * 5];
        int len;
        while ((len =inBuff.read(b)) != -1) {
            outBuff.write(b, 0, len);
        }
        // 刷新此缓冲的输出流
        outBuff.flush();

        //关闭流
        inBuff.close();
        outBuff.close();
        output.close();
        input.close();
    }

    public void requestPicture(final Page page, Book book, Chapter chapter, final int index) {
        String path = book.picturePath(chapter, index);
        final File file = new File(path);

        Request request = Request.get(page.getPicture());
        request.setReadCache(true);
        request.method = page.getMethod();
        Map headers = page.getHeaders();
        Array keys = headers.keys();
        request.headers = new HashMap<>();
        for (Object key : keys) {
            request.headers.put(key.toString(), headers.get(key).toString());
        }
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                File nf = new File(request.getPath());
                try {
                    copyFile(nf, file);
                    String path = file.getPath();
                    if (displayViews.containsKey(index)) {
                        PictureView pic = displayViews.get(index);

                        pic.setImagePath(path);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onFailed(Exception e) {
            }

            @Override
            public void onCancel(Request request) {
            }
        });
        request.start();

    }

    void reloadChapter(Chapter chapter) {
        reloading = true;
        if (reader != null) {
            reader.apply("stop");
            reader = null;
        }
        total_page = 0;
        viewPager.setCurrentItem(0, false);
        pages.clear();
        Collection<PictureView> pics = displayViews.values();
        for (PictureView p : pics) {
            viewPager.removeView(p);
        }
        displayViews.clear();
        adapter.notifyDataSetChanged();
        setChapter(chapter);
        loadingView.setVisibility(View.VISIBLE);
        loadingView.startLoading();
        extend = true;
        selectButton.setVisibility(View.INVISIBLE);
        hideNavBar(!extend);
        if (localBook) {
            setupLocalBook();
        }else {
            setupReader();
        }
        reloading = false;
    }

    void checkPages() {
        if (total_page != 0) {
            for (Page page : pages) {
                if (page == null) return;
            }
            Array<Page> ps = new Array<Page>(true);
            for (Page page : pages) {
                ps.add(page);
            }
            chapter.cachePages(ps);
        }
    }

    ArrayList<Request> requests = new ArrayList<>();
    int requestIndex = -1;
    boolean requesting = false;
    class NextRunnable implements Runnable {
        Request request;
        public NextRunnable(Request request) {
            this.request = request;
        }
        @Override
        public void run() {
            if (request != null)
                request.start();
            nextRunnable = null;
        }
    }
    NextRunnable nextRunnable;

    void requestComplete(Request request) {
        if (requests.contains(request)) {
            int idx = requests.indexOf(request);
            if (requestIndex == idx) {
                requesting = false;
                checkRequest();
            }
        }
    }


    void checkRequest() {
        if (!requesting) {
            int nIdx = requestIndex + 1;
            if (nIdx < requests.size()) {
                requesting = true;
                requestIndex = nIdx;
                final Request req = requests.get(nIdx);
                nextRunnable = new NextRunnable(req);
                getHandler().postDelayed(nextRunnable, 500);
            }
        }
    }

    void loadedPage(Page page) {
        requests.add(PictureView.requestPage(page));
        checkRequest();
    }

    @Override
    public void run(apps.gen.lib.utils.NotificationCenter.Notification notification) {
        requestComplete((Request) notification.getPostObject());
    }
}

