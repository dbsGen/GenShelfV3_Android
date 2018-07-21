package cn.gen.gsv2.controllers;


import android.animation.ObjectAnimator;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.text.Editable;
import android.text.SpannableStringBuilder;
import android.text.Spanned;
import android.text.TextWatcher;
import android.text.style.ImageSpan;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.BaseAdapter;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.fichardu.interpolator.EaseOutCubicInterpolator;
import com.gr.Activity;
import com.gr.Request;
import com.gr.classes.Array;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Random;
import java.util.UUID;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.ArtBasket;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Chapter;
import cn.gen.gsv2.models.KeyValue;
import cn.gen.gsv2.models.Library;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.utils.ArtSpan;
import cn.gen.gsv2.views.BooksCover;
import cn.gen.gsv2.views.CommentsCell;
import cn.gen.gsv2.views.ListViewCell;
import cn.gen.gsv2.views.LoadingCell;
import cn.gen.gsv2.views.TopicDisplayView;
import cn.gen.gsv2.views.TouchPanel;

import static android.util.TypedValue.COMPLEX_UNIT_DIP;

/**
 * A simple {@link Fragment} subclass.
 */
public class TopicController extends Controller implements
        Request.OnStatusListener, TopicDisplayView.OnArtListener {

    class DividerView extends RelativeLayout {

        TextView textView;

        public TextView getTextView() {
            return textView;
        }

        public DividerView(Context context) {
            super(context);
            init(context);
        }

        public DividerView(Context context, AttributeSet attrs) {
            super(context, attrs);
            init(context);
        }

        public DividerView(Context context, AttributeSet attrs, int defStyleAttr) {
            super(context, attrs, defStyleAttr);
            init(context);
        }

        void init(Context context) {
            setBackgroundColor(Color.WHITE);

            textView = new TextView(context);
            LayoutParams params = new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.WRAP_CONTENT);
            int m = H.dip2px(context, 10);
            params.setMargins(m, m/2, m, m/2);
            textView.setTextSize(COMPLEX_UNIT_DIP, 16);
            textView.setLayoutParams(params);
            textView.setTextColor(ActivityCompat.getColor(context, R.color.black));
            textView.getPaint().setFakeBoldText(true);
            textView.setText(context.getString(R.string.comments));
            addView(textView);
        }

        public void setCount(int count) {
            getTextView().setText(getContext().getString(R.string.comments) + "(" +count+ ")");
        }
    }

    static class Comment {
        String id;
        Date date;
        String author;
        Array datas;
        String reference;

        public static Comment from(JSONObject jobj) {
            Comment c = new Comment();
            try {
                c.id = jobj.getString("id");
                c.date = new Date(jobj.getLong("date")*1000);
                c.author = jobj.getString("author");
                c.datas = ArtBasket.Art.parse(jobj.getString("content"));
                c.reference = jobj.getString("reference");
            }catch (Exception e) {
                e.printStackTrace();
            }
            return c;
        }
    }

    String topicId;

    ListView listView;
    BaseAdapter baseAdapter;

    TopicDisplayView topicDisplayView;
    DividerView dividerView;
    LoadingCell loadingCell;

    ImageButton booksButton;
    ImageButton submitButton;
    EditText commentEdit;

    String subtitle;
    Array datas;
    BooksCover booksCover;
    SpannableStringBuilder stringBuilder = new SpannableStringBuilder();
    TouchPanel loadingView;
    SwipeRefreshLayout refreshView;
    int commentsCount;
    int page = 0;
    ArrayList<Comment> comments = new ArrayList<>();

    SimpleDateFormat dayFormat = new SimpleDateFormat("yyyy-MM-dd");
    SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm:ss");

    String uuid;

    public TopicController() {
        // Required empty public constructor
    }

    public void setTopicId(String topicId) {
        this.topicId = topicId;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        return inflater.inflate(R.layout.controller_topic, container, false);
    }

    boolean edit = false;
    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        topicDisplayView = new TopicDisplayView(getContext());
        dividerView = new DividerView(getContext());

        loadingCell = new LoadingCell(getContext());

        listView = (ListView)view.findViewById(R.id.list_view);
        baseAdapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return 2 + (comments.size() == 0 ? 0 : comments.size() + 1);
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
                ListViewCell container = (ListViewCell) convertView;
                if (container == null) {
                    container = new ListViewCell(getContext());
                }
                if (position == 0)
                    container.setContentView(topicDisplayView);
                else if (position == 1)
                    container.setContentView(dividerView);
                else if (position == comments.size() + 2){
                    moreComments();
                    container.setContentView(loadingCell);
                }else {
                    CommentsCell cell;
                    Comment comment = comments.get(position - 2);
                    if (!(container.getContentView() instanceof CommentsCell)) {
                        cell = new CommentsCell(getContext());
                        cell.setOnArtListener(new CommentsCell.OnArtListener() {
                            @Override
                            public void onPress(ArtBasket.Art art) {
                                TopicController.this.onPress(art);
                            }
                        });
                    }else {
                        cell = (CommentsCell)container.getContentView();
                    }
                    String nowStr = dayFormat.format(new Date());
                    String dateStr = dayFormat.format(comment.date);
                    if (dateStr.equals(nowStr)) {
                        dateStr = timeFormat.format(comment.date);
                    }
                    cell.setAuthor(comment.author + "@" + dateStr);
                    cell.setDatas(comment.datas);
                    container.setContentView(cell);
                }
                return container;
            }
        };
        listView.setAdapter(baseAdapter);
        listView.setItemsCanFocus(false);
        listView.setDrawSelectorOnTop(false);

        topicDisplayView.setOnArtListener(this);

        topicDisplayView.getSubtitleView().setText(subtitle);
        topicDisplayView.getTitleView().setText(getTitle());
        if (datas != null) {
            topicDisplayView.setDatas(datas);
        }

        booksCover = (BooksCover)view.findViewById(R.id.books_cover);
        booksCover.setOnCheckedListener(new BooksCover.OnCheckedListener() {
            @Override
            public void onChecked(ArtBasket.Art art) {
                insertArt(art);
            }
        });
        booksCover.setArts(ArtBasket.getArts());

        booksButton = (ImageButton)view.findViewById(R.id.books_button);
        booksButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                booksCover.show();
            }
        });

        submitButton = (ImageButton)view.findViewById(R.id.done);
        submitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                commentSubmit();
            }
        });

        commentEdit = (EditText)view.findViewById(R.id.comment_edit);
        commentEdit.addTextChangedListener(new TextWatcher() {
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

        refreshView = (SwipeRefreshLayout)view.findViewById(R.id.refresh);
        refreshView.setColorSchemeResources(R.color.blue);
        refreshView.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                reload();
            }
        });

        loadingView = (TouchPanel)view.findViewById(R.id.loading_view);
        loadingView.setEnableListener(false);
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
    }

    @Override
    protected void onViewWillAppear() {
        super.onViewWillAppear();
        if (datas == null) {
            reload();
        }
    }

    @Override
    protected void onViewWillDisappear() {
        super.onViewWillDisappear();
        closeInput();
    }

    @Override
    public void onProgress(Request request, float percent) {

    }

    void closeInput() {
        InputMethodManager imm = (InputMethodManager)getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.hideSoftInputFromWindow(getView().getWindowToken(),0);
    }

    @Override
    public void onComplete(Request request) {
        String text = H.read(request.getPath());
        boolean hasMore = false;
        try {
            JSONObject json = new JSONObject(text);
            if (json.getInt("code") == 0) {
                page = 0;
                JSONObject ds = json.getJSONObject("datas");
                commentsCount = ds.getInt("cc");
                datas = ArtBasket.Art.parse(ds.getString("content"));
                topicDisplayView.setDatas(datas);
                dividerView.setCount(commentsCount);

                comments.clear();
                JSONArray array = json.getJSONArray("comments");
                for (int i = 0, t = array.length(); i < t; ++i) {
                    JSONObject jobj = array.getJSONObject(i);
                    Comment c = Comment.from(jobj);
                    comments.add(c);
                }
                hasMore = array.length() != 0;
                baseAdapter.notifyDataSetChanged();
            }else {

                if (getContext() != null) {
                    Toast.makeText(getContext(), getContext().getString(R.string.failed) + ":" + json.getString("msg"),
                            Toast.LENGTH_LONG).show();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        loadingCell.setStatus(hasMore ? LoadingCell.STATUS_NORMAL : LoadingCell.STATUS_NO_MORE);
        refreshView.setRefreshing(false);
    }

    @Override
    public void onFailed(Exception e) {
        if (getContext() != null) {
            Toast.makeText(getContext(), R.string.failed, Toast.LENGTH_SHORT).show();
        }
        loadingCell.setStatus(LoadingCell.STATUS_NORMAL);
        refreshView.setRefreshing(false);
    }

    @Override
    public void onCancel(Request request) {

    }

    @Override
    public void onPress(ArtBasket.Art art) {
        String shopId = art.getShopId();
        Shop shop = Shop.find(shopId);
        MainActivity activity = (MainActivity) Activity.current();
        if (shop == null) {
            ShopController ctrl = activity.getShopsController().makeShopController(activity, shopId);
            if (ctrl != null) {
                Toast.makeText(getContext(), R.string.no_shop, Toast.LENGTH_LONG).show();
                H.navC(this).push(ctrl, true);
            }else {
                Toast.makeText(getContext(), R.string.unkown_shop, Toast.LENGTH_LONG).show();
            }
        }else {
            Library library = new Library(true);
            shop.setupLibrary(library);
            BookController ctrl = Controller.instantiate(getContext(), BookController.class);
            Book book = new Book(true);
            book.setShopId(art.getShopId());
            book.setUrl(art.getUrl());
            book.setName(art.getName());
            book.setThumb(art.getThumb());
            ctrl.setBook(book);
            ctrl.setShop(shop);
            ctrl.setLibrary(library);
            if (art.getType() == 0) {
                Chapter chapter = new Chapter(true);
                chapter.setShopId(art.getShopId());
                chapter.setName(art.getChapterName());
                chapter.setUrl(art.getChapterUrl());
                ctrl.setWillPushChapter(chapter);
            }
            H.navC(TopicController.this).push(ctrl, true);
        }
    }

    public void setSubtitle(String subtitle) {
        this.subtitle = subtitle;
        if (topicDisplayView != null)
            topicDisplayView.getSubtitleView().setText(subtitle);
    }

    @Override
    public void setTitle(String title) {
        super.setTitle(title);
        if (topicDisplayView != null)
            topicDisplayView.getTitleView().setText(title);
    }
    void insertArt(ArtBasket.Art art) {
        String imgText = art.html();
        int start = commentEdit.getSelectionStart();
        stringBuilder.replace(start, commentEdit.getSelectionEnd(), imgText);
        ImageSpan artSpan = ArtSpan.from(getContext(), art);
        stringBuilder.setSpan(artSpan, start, start + imgText.length(),
                Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
        edit = true;
        commentEdit.setText(stringBuilder);
        edit = false;
        commentEdit.setSelection(start + imgText.length());
    }

    void commentSubmit() {
        String content = commentEdit.getText().toString().trim();
        if (content.length() == 0) {
            Toast.makeText(getContext(), R.string.require_content, Toast.LENGTH_LONG).show();
            return;
        }
        booksCover.miss();
        showLoading();
        closeInput();
        Request request = Request.get("http://112.74.13.80:3000/comments?tid="+topicId);
        request.setTimeout(5000);
        request.method = "POST";
        String name = KeyValue.get("author_name");
        if (name != null && !name.isEmpty()) {
            request.addParams("author", name);
        }
        if (uuid == null) {
            String str = new Date().toString() + new Random().nextLong();
            uuid = UUID.nameUUIDFromBytes(str.getBytes()).toString();
        }
        request.addParams("content", content);
        request.addParams("udid", uuid);
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                if (getContext() == null) return;
                missLoading();
                try {
                    JSONObject json = new JSONObject(H.read(request.getPath()));
                    if (json.getInt("code") == 0) {
                        commentEdit.setText("");
                        reloadComments();
                    }else {
                        Toast.makeText(getContext(), getContext().getString(R.string.failed) + ":" + json.getString("msg"), Toast.LENGTH_LONG).show();
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                uuid = null;
            }

            @Override
            public void onFailed(Exception e) {
                if (getContext() == null) return;
                missLoading();
                Toast.makeText(getContext(), R.string.failed, Toast.LENGTH_LONG).show();
            }

            @Override
            public void onCancel(Request request) {

            }
        });
        request.start();
    }

    ObjectAnimator loadingAnimator;
    void showLoading() {
        if (loadingAnimator != null) {
            loadingAnimator.cancel();
        }
        loadingView.setEnableListener(true);
        loadingAnimator = ObjectAnimator.ofFloat(loadingView, "alpha", 0, 1);
        loadingAnimator.setInterpolator(new EaseOutCubicInterpolator());
        loadingAnimator.setDuration(300);
        loadingAnimator.start();
    }

    void missLoading() {
        if (loadingAnimator != null) {
            loadingAnimator.cancel();
        }
        loadingView.setEnableListener(false);
        loadingAnimator = ObjectAnimator.ofFloat(loadingView, "alpha", 1, 0);
        loadingAnimator.setInterpolator(new EaseOutCubicInterpolator());
        loadingAnimator.setDuration(300);
        loadingAnimator.start();
    }

    void reload() {
        refreshView.setRefreshing(true);
        loadingCell.setStatus(LoadingCell.STATUS_LOADING);
        Request request = Request.get("http://112.74.13.80:3000/topics?id=" + topicId);
        request.setTimeout(5000);
        request.setReadCache(false);
        request.setReadCacheWhenError(false);
        request.setListener(this);
        request.start();
    }

    void reloadComments() {
        if (loadingCell.getStatus() == LoadingCell.STATUS_LOADING) return;
        refreshView.setRefreshing(true);
        loadingCell.setStatus(LoadingCell.STATUS_LOADING);
        Request request = Request.get("http://112.74.13.80:3000/comments/index?tid=" + topicId);
        request.setTimeout(5000);
        request.setReadCache(false);
        request.setReadCacheWhenError(false);
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                if (getContext() == null) return;
                JSONObject json = null;
                boolean hasMore = false;
                try {
                    json = new JSONObject(H.read(request.getPath()));
                    if (json.getInt("code") == 0) {
                        page = 0;
                        commentsCount = json.getInt("count");
                        dividerView.setCount(commentsCount);
                        comments.clear();
                        JSONArray array = json.getJSONArray("datas");
                        for (int i = 0, t = array.length(); i < t; ++i) {
                            JSONObject jobj = array.getJSONObject(i);
                            Comment c = Comment.from(jobj);
                            comments.add(c);
                        }
                        hasMore = array.length() != 0;
                        baseAdapter.notifyDataSetChanged();
                    }else {
                        Toast.makeText(getContext(), getContext().getString(R.string.failed) + ":" + json.getString("msg"),
                                Toast.LENGTH_LONG).show();
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                refreshView.setRefreshing(false);
                loadingCell.setStatus(hasMore ? LoadingCell.STATUS_NORMAL : LoadingCell.STATUS_NO_MORE);
            }

            @Override
            public void onFailed(Exception e) {
                if (getContext() == null) return;
                Toast.makeText(getContext(), R.string.failed, Toast.LENGTH_SHORT).show();
                refreshView.setRefreshing(false);
                loadingCell.setStatus(LoadingCell.STATUS_NORMAL);
            }

            @Override
            public void onCancel(Request request) {

            }
        });
        request.start();
    }

    void moreComments() {
        if (loadingCell.getStatus() != LoadingCell.STATUS_NORMAL) return;
        refreshView.setRefreshing(true);
        loadingCell.setStatus(LoadingCell.STATUS_LOADING);
        Request request = Request.get("http://112.74.13.80:3000/comments/index?tid=" + topicId + "&p=" + (page + 1));
        request.setTimeout(5000);
        request.setReadCache(false);
        request.setReadCacheWhenError(false);
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                JSONObject json = null;
                boolean hasMore = false;
                try {
                    json = new JSONObject(H.read(request.getPath()));
                    if (json.getInt("code") == 0) {
                        page = page + 1;
                        commentsCount = json.getInt("count");
                        dividerView.setCount(commentsCount);
                        JSONArray array = json.getJSONArray("datas");
                        for (int i = 0, t = array.length(); i < t; ++i) {
                            JSONObject jobj = array.getJSONObject(i);
                            Comment c = Comment.from(jobj);
                            comments.add(c);
                        }
                        hasMore = array.length() != 0;
                        baseAdapter.notifyDataSetChanged();
                    }else {
                        Toast.makeText(getContext(), getContext().getString(R.string.failed) + ":" + json.getString("msg"),
                                Toast.LENGTH_LONG).show();
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                refreshView.setRefreshing(false);
                loadingCell.setStatus(hasMore ? LoadingCell.STATUS_NORMAL : LoadingCell.STATUS_NO_MORE);
            }

            @Override
            public void onFailed(Exception e) {
                if (getContext() != null) {
                    Toast.makeText(getContext(), R.string.failed, Toast.LENGTH_SHORT).show();
                }
                refreshView.setRefreshing(false);
                loadingCell.setStatus(LoadingCell.STATUS_NORMAL);
            }

            @Override
            public void onCancel(Request request) {

            }
        });
        request.start();
    }
}
