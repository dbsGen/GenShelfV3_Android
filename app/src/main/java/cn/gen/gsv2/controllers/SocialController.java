package cn.gen.gsv2.controllers;


import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
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

import com.gr.Request;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;
import cn.gen.gsv2.views.ArrowCell;
import cn.gen.gsv2.views.CategoryCell;

/**
 * A simple {@link Fragment} subclass.
 */
public class SocialController extends Controller {

    class Category {
        String name;
        String description;
        int id;
    }

    ListView listView;
    SwipeRefreshLayout refreshView;
    BaseAdapter adapter;
    ArrayList<Category> categories = new ArrayList<>();
    FloatingActionButton commentButton;
    boolean loading = false;

    public SocialController() {
        // Required empty public constructor
    }

    public ArrayList<Category> getCategories() {
        return categories;
    }

    @Override
    protected void initialize(final Context context) {
        super.initialize(context);
        setTitle(context.getString(R.string.home_social));


        Drawable d = ActivityCompat.getDrawable(context, R.drawable.setting);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            d.setTint(Color.WHITE);
        }
        setRightItems(new NavigationItem(d, new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MainSettingsController ctrl = Controller.instantiate(context, MainSettingsController.class);
                H.navC(SocialController.this).push(ctrl, true);
            }
        }));
//        setRightItems(new NavigationItem(context.getDrawable(R.drawable.setting), new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                MainSettingsController ctrl = Controller.instantiate(context, MainSettingsController.class);
//                H.navC(SocialController.this).push(ctrl, true);
//            }
//        }));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_social, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        listView = (ListView) view.findViewById(R.id.list_view);

        adapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return categories.size();
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
                Category c = categories.get(position);
                CategoryCell cell = (CategoryCell)convertView;
                if (cell == null) {
                    cell = new CategoryCell(getContext());
                }
                cell.getTitleView().setText(c.name);
                cell.getDescriptionView().setText(c.description);
                return cell;
            }
        };

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if (position < categories.size()) {
                    Category c = categories.get(position);
                    TopicsController ctrl = Controller.instantiate(getContext(), TopicsController.class);
                    ctrl.setCategoryId(c.id);
                    ctrl.setTitle(c.name);
                    H.navC(SocialController.this).push(ctrl, true);
                }
            }
        });
        listView.setAdapter(adapter);
        listView.setBackgroundColor(Color.rgb(230, 230, 230));

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
                H.navC(SocialController.this).push(ctrl, true);
            }
        });
    }

    @Override
    protected void onViewWillAppear() {
        super.onViewWillAppear();
        if (categories.size() == 0) {
            reload();
        }
    }

    public void reload() {
        if (loading) return;
        if (refreshView != null) {
            refreshView.setRefreshing(true);
        }
        loading = true;
        Request request = Request.get("http://112.74.13.80:3000/categories");
        request.setReadCache(false);
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                String log = H.read(request.getPath());
                try {
                    JSONArray arr = new JSONArray(log);
                    categories.clear();
                    for (int i = 0, t = arr.length(); i < t; ++i) {
                        JSONObject obj = (JSONObject) arr.get(i);
                        Category c = new Category();
                        c.name = obj.getString("name");
                        c.id = obj.getInt("id");
                        c.description = obj.getString("des");
                        categories.add(c);
                    }
                    if (adapter != null)
                        adapter.notifyDataSetChanged();
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                if (refreshView != null)
                    refreshView.setRefreshing(false);
                loading = false;
            }

            @Override
            public void onFailed(Exception e) {
                Toast.makeText(getContext(),
                        getContext().getString(R.string.failed),
                        Toast.LENGTH_SHORT).show();
                refreshView.setRefreshing(false);
                loading = false;
            }

            @Override
            public void onCancel(Request request) {

            }
        });
        request.start();
    }
}
