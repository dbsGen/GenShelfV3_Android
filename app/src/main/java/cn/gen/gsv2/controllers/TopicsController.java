package cn.gen.gsv2.controllers;


import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.gr.Activity;
import com.gr.Request;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.CacheAdapter;
import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.R;
import cn.gen.gsv2.views.ArrowCell;
import cn.gen.gsv2.views.ArtCell;
import cn.gen.gsv2.views.LoadingCell;
import cn.gen.gsv2.views.TopicCell;

/**
 * A simple {@link Fragment} subclass.
 */
public class TopicsController extends Controller implements AdapterView.OnItemClickListener {

    private int categoryId = 0;

    private static class Topic {
        String title;
        int category;
        String id;
        Date date;
        String author;
        String summary;
        String[] thumbs;
        int comment_count;

        public static Topic fromJson(JSONObject obj) {
            Topic topic = new Topic();
            try {
                topic.title = obj.getString("title");
                topic.category = obj.getInt("category");
                topic.id = obj.getString("id");
                topic.date = new Date(obj.getLong("date") * 1000);
                topic.author = obj.getString("author");
                topic.comment_count = obj.has("cc") ? obj.getInt("cc") : 0;
                topic.summary = obj.has("summary") ? obj.getString("summary") : "";
                if (obj.has("thumbs")) {
                    JSONArray thumbsNodes = obj.getJSONArray("thumbs");
                    int len = thumbsNodes.length();
                    topic.thumbs = new String[len];
                    for (int m = 0; m < len; ++m) {
                        topic.thumbs[m] = thumbsNodes.getString(m);
                    }
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
            return topic;
        }
    }

    SimpleDateFormat dayFormat = new SimpleDateFormat("yyyy-MM-dd");
    SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm:ss");
    ArrayList<Topic> topics = new ArrayList<>();
    ListView listView;
    SwipeRefreshLayout refreshView;
    CacheAdapter adapter;
    int page = 0;
    FloatingActionButton commentButton;
    LoadingCell loadingCell;

    public void setCategoryId(int categoryId) {
        this.categoryId = categoryId;
    }

    public TopicsController() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_topics, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        listView = (ListView)view.findViewById(R.id.list_view);

        loadingCell = new LoadingCell(getContext(), "LoadingCell");
        loadingCell.setStatus(LoadingCell.STATUS_NORMAL);

        adapter = new CacheAdapter(getContext()) {
            @Override
            public int getCount() {
                return topics.size() == 0 ? 0 : topics.size() + 1;
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
            public ListCell cellView(int position) {
                if (position >= topics.size()) {
                    loadMore();
                    return loadingCell;
                }else {
                    String id = "TopicCell";
                    TopicCell cell = (TopicCell)popWithIdentifier(id);
                    if (cell == null) {
                        cell = new TopicCell(getContext(), id);
                        cell.getLabelView().setText(null);
                    }
                    Topic t = topics.get(position);
                    cell.getTitleView().setText(t.title);
                    String nowStr = dayFormat.format(new Date());
                    String dateStr = dayFormat.format(t.date);
                    if (dateStr.equals(nowStr)) {
                        dateStr = timeFormat.format(t.date);
                    }
                    String subtitle = getContext().getString(R.string.topic_subtitle);

                    cell.getSubtitleView().setText(String.format(subtitle, t.author, dateStr, t.comment_count));
                    cell.getDescriptionView().setText(t.summary);
                    cell.setThumbs(t.thumbs);

                    return cell;
                }
            }
        };
        listView.setAdapter(adapter);
        listView.setBackgroundColor(Color.rgb(230, 230, 230));
        listView.setOnItemClickListener(this);

        refreshView = (SwipeRefreshLayout)view.findViewById(R.id.refresh);
        refreshView.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                reload();
            }
        });
        refreshView.setColorSchemeResources(R.color.blue);

        commentButton = (FloatingActionButton)view.findViewById(R.id.floating_button);
        commentButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PostTopicController ctrl = Controller.instantiate(getContext(), PostTopicController.class);
                MainActivity activity = (MainActivity) Activity.current();
                ArrayList<SocialController.Category> categories = activity.getSocialController().getCategories();
                if (categories != null) {
                    int selected = 0;
                    for (int i = 0, t = categories.size(); i < t; ++i) {
                        if (categories.get(i).id == categoryId) {
                            selected = i;
                            break;
                        }
                    }
                    ctrl.setSelected(selected);
                }
                H.navC(TopicsController.this).push(ctrl, true);
            }
        });
    }

    @Override
    protected void onViewWillAppear() {
        super.onViewWillAppear();
        if (topics.size() == 0) {
            reload();
        }
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        try {
            TopicController ctrl = Controller.instantiate(getContext(), TopicController.class);
            Topic topic = topics.get(position);
            ctrl.setTopicId(topic.id);
            ctrl.setTitle(topic.title);
            String nowStr = dayFormat.format(new Date());
            String dateStr = dayFormat.format(topic.date);
            if (dateStr.equals(nowStr)) {
                dateStr = timeFormat.format(topic.date);
            }
            ctrl.setSubtitle(topic.author + "@" + dateStr);
            H.navC(this).push(ctrl, true);
        }catch (Exception e) {
            e.printStackTrace();
        }
    }

    String url() {
        return "http://112.74.13.80:3000/topics/index?category=" + categoryId + "&p=" + page;
    }

    void reload() {
        if (loadingCell.getStatus() == LoadingCell.STATUS_LOADING)
            return;
        loadingCell.setStatus(LoadingCell.STATUS_LOADING);
        refreshView.setRefreshing(true);
        page = 0;
        Request request = Request.get(url());
        request.setTimeout(10000);
        request.setReadCache(false);
        refreshView.setRefreshing(true);
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                if (getContext() == null) return;
                String str = H.read(request.getPath());
                boolean hasMore = false;
                try {
                    JSONObject json = new JSONObject(str);
                    if (json.getInt("code") == 0) {
                        topics.clear();
                        JSONArray arr = json.getJSONArray("datas");
                        for (int i = 0, t = arr.length(); i < t; ++i) {
                            JSONObject obj = arr.getJSONObject(i);
                            Topic topic = Topic.fromJson(obj);
                            topics.add(topic);
                            hasMore = true;
                        }
                        adapter.notifyDataSetChanged();;
                    }else {
                        Toast.makeText(getContext(),
                                getContext().getString(R.string.failed) + json.getString("msg"),
                                Toast.LENGTH_SHORT).show();
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
                Toast.makeText(getContext(),
                        getContext().getString(R.string.failed),
                        Toast.LENGTH_SHORT).show();
                refreshView.setRefreshing(false);
                loadingCell.setStatus(LoadingCell.STATUS_NORMAL);
            }

            @Override
            public void onCancel(Request request) {

            }
        });
        request.start();
    }

    void loadMore() {
        if (loadingCell.getStatus() == LoadingCell.STATUS_LOADING) {
            return;
        }else if (loadingCell.getStatus() == LoadingCell.STATUS_NO_MORE) {
            refreshView.setRefreshing(false);
            return;
        }
        loadingCell.setStatus(LoadingCell.STATUS_LOADING);
        refreshView.setRefreshing(true);
        page++;
        Request request = Request.get(url());
        request.setTimeout(10000);
        request.setReadCache(false);
        refreshView.setRefreshing(true);
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                if (getContext() == null) return;
                String str = H.read(request.getPath());
                boolean hasMore = false;
                try {
                    JSONObject json = new JSONObject(str);
                    if (json.getInt("code") == 0) {
                        JSONArray arr = json.getJSONArray("datas");
                        for (int i = 0, t = arr.length(); i < t; ++i) {
                            JSONObject obj = arr.getJSONObject(i);
                            Topic topic = Topic.fromJson(obj);
                            topics.add(topic);
                            hasMore = true;
                        }
                        adapter.notifyDataSetChanged();;
                    }else {
                        Toast.makeText(getContext(),
                                getContext().getString(R.string.failed) + json.getString("msg"),
                                Toast.LENGTH_SHORT).show();
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
                Toast.makeText(getContext(),
                        getContext().getString(R.string.failed),
                        Toast.LENGTH_SHORT).show();
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
