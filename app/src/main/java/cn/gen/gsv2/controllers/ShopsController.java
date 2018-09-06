package cn.gen.gsv2.controllers;


import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v4.content.ContextCompat;
import android.support.v4.widget.SwipeRefreshLayout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.Toast;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.views.BookCell;

import com.gr.Activity;
import com.gr.Request;
import com.gr.classes.Array;
import com.gr.classes.Callback;
import com.gr.classes.NotificationCenter;
import com.nhaarman.listviewanimations.itemmanipulation.DynamicListView;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;
import cn.nekocode.badge.BadgeDrawable;

/**
 * A simple {@link Fragment} subclass.
 */
public class ShopsController extends Controller implements SwipeRefreshLayout.OnRefreshListener {

    public static final String NOTIFICATION_UPDATE_BADGE = "UPDATE_BADGE";
    final int SUPPORT_PACKAGE_VERSION = 13;

    ListView listView;
    SwipeRefreshLayout refreshView;

    ArrayList<Shop> displayShops = new ArrayList<>();
    HashMap<String, Shop> localIndex = new HashMap<>();
    HashMap<String, Shop> onlineIndex = new HashMap<>();
    Drawable updateDrawable;
    BaseAdapter adapter;
    boolean loaded = false;
    boolean loading = false;
    static Callback installedListener = null;
    static Callback removedListener = null;

    public ShopsController() {
    }

    public static void checkNumber() {
        MainActivity mainActivity = (MainActivity) Activity.current();
        if (mainActivity != null) {
            ShopsController sc = mainActivity.getShopsController();
            int count = 0;
            for (Shop shop : sc.displayShops) {
                Shop os = null, ls = null;
                String id = shop.getIdentifier();
                if (sc.onlineIndex.containsKey(id)) {
                    os = sc.onlineIndex.get(id);
                }
                if (sc.localIndex.containsKey(id)) {
                    ls = sc.localIndex.get(id);
                }
                if (os != null && ls != null && (!os.isLocalize() && ls.isLocalize()) && os.getVersion() > ls.getVersion()) {
                    ++count;
                }
            }
            H.NC().postNotification(NOTIFICATION_UPDATE_BADGE, count);

        }
    }

    @Override
    protected void initialize(final Context context) {
        super.initialize(context);
        setTitle(context.getString(R.string.home_shops));
        Array shops = Shop.getLocalShops();
        for (int i = 0, t = shops.size(); i < t; ++i) {
            Shop shop = (Shop)shops.get(i);
            displayShops.add(shop);
            localIndex.put(shop.getIdentifier() , shop);
        }
        if (installedListener == null) {
            installedListener = new Callback(true) {
                @Override
                public Object run(Object... args) {
                    Activity activity = Activity.current();
                    if (activity == null) return null;
                    Shop shop = (Shop) args[0];
                    if (shop.isLocalize()) {
                        Toast.makeText(activity, activity.getString(R.string.install_complete),
                                Toast.LENGTH_SHORT).show();
                    }else {
                        Toast.makeText(activity, activity.getString(R.string.install_failed),
                                Toast.LENGTH_SHORT).show();
                    }
                    checkNumber();
                    return null;
                }
            };
            NotificationCenter.getInstance().listen("SHOP_INSTALLED", installedListener);
        }
        if (removedListener == null) {
            removedListener = new Callback(true) {
                @Override
                public Object run(Object... args) {
                    Activity activity = Activity.current();
                    if (activity == null) return null;
                    Shop shop = (Shop) args[0];
                    Toast.makeText(activity, "<" + shop.getName() + ">" + activity.getString(R.string.removed),
                            Toast.LENGTH_SHORT).show();
                    checkNumber();
                    return null;
                }
            };
            NotificationCenter.getInstance().listen("SHOP_REMOVED", removedListener);
        }

        Drawable d = ActivityCompat.getDrawable(context, R.drawable.setting);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            d.setTint(Color.WHITE);
        }
        setRightItems(new NavigationItem(d, new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MainSettingsController ctrl = Controller.instantiate(getContext(), MainSettingsController.class);
                H.navC(ShopsController.this).push(ctrl, true);
            }
        }));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_shops, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        updateDrawable = new BadgeDrawable.Builder().type(BadgeDrawable.TYPE_ONLY_ONE_TEXT)
                .badgeColor(ActivityCompat.getColor(getContext(), R.color.red))
                .text1("NEW").build();
        listView = (ListView)view.findViewById(R.id.list_view);
        adapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return displayShops.size();
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
                BookCell cell = (BookCell) convertView;
                if (cell == null) {
                    cell = new BookCell(getContext());
                    cell.getNewView().setImageDrawable(updateDrawable);
                }
                Shop shop = displayShops.get(position);
                cell.getTitleLabel().setText(shop.getName());
                cell.getDescriptionLabel().setText(shop.getDescription());
                cell.setImageUrl(shop.getIcon());
                Shop os = null, ls = null;
                String id = shop.getIdentifier();
                if (onlineIndex.containsKey(id)) {
                    os = onlineIndex.get(id);
                }
                if (localIndex.containsKey(id)) {
                    ls = localIndex.get(id);
                }
                if (os != null && ls != null && (!os.isLocalize() && ls.isLocalize()) && os.getVersion() > ls.getVersion()) {
                    cell.getNewView().setVisibility(View.VISIBLE);
                }else {
                    cell.getNewView().setVisibility(View.GONE);
                }

                return cell;
            }
        };
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                clickedAt(position);
            }
        });

        refreshView = (SwipeRefreshLayout)view.findViewById(R.id.refresh);
        refreshView.setOnRefreshListener(this);
        refreshView.setColorSchemeResources(R.color.blue);
        if (loading) refreshView.setRefreshing(true);
    }

    public void startRequest() {
        if (!loaded) {
            requestDatas();
            loaded = true;
        }
    }

    void requestDatas() {
        loading = true;
        String url = "https://coding.net/u/dbsGen/p/GenShelf_Packages/git/raw/master/index.json";
        Request request = Request.get(url, url);
        request.setReadCache(false);
        request.setListener(new Request.OnStatusListener() {
            @Override
            public void onProgress(Request request, float percent) {

            }

            @Override
            public void onComplete(Request request) {
                loading = false;
                Array shops = Shop.parseShops(request.getPath());
                int updateCount = 0;
                for (int i = 0, t = shops.size(); i < t; ++i) {
                    Shop shop = (Shop)shops.get(i);
                    if (shop.getPackageVersion() <= SUPPORT_PACKAGE_VERSION) {
                        Shop localShop = null;
                        for (int _i = 0, _t = displayShops.size(); _i < _t; ++_i) {
                            Shop s = displayShops.get(_i);
                            if (s.getIdentifier().equals(shop.getIdentifier())) {
                                localShop = s;
                                displayShops.set(_i, shop);
                                break;
                            }
                        }
                        if (localShop == null) {
                            displayShops.add(shop);
                        }else {
                            if (shop.getVersion() > localShop.getVersion()) {
                                updateCount++;
                            }
                        }
                        onlineIndex.put(shop.getIdentifier(), shop);
                    }
                }
                H.NC().postNotification(NOTIFICATION_UPDATE_BADGE, updateCount);
                if (adapter != null)
                    adapter.notifyDataSetChanged();
                if (refreshView != null)
                    refreshView.setRefreshing(false);
            }

            @Override
            public void onFailed(Exception e) {
                loading = false;
                Log.i("request", "failed!");
                if (refreshView != null)
                    refreshView.setRefreshing(false);
            }

            @Override
            public void onCancel(Request request) {

            }
        });
        request.start();
    }

    @Override
    public void onRefresh() {
        requestDatas();
    }

    void clickedAt(int position) {

        Shop shop = displayShops.get(position);
        ShopController shopCtrl = Controller.instantiate(getContext(), ShopController.class);
        String id = shop.getIdentifier();
        if (localIndex.containsKey(id))
            shopCtrl.setLocalShop(localIndex.get(id));
        if (onlineIndex.containsKey(id))
            shopCtrl.setOnlineShop(onlineIndex.get(id));

        H.navC(this).push(shopCtrl, true);
    }

    public ShopController makeShopController(Context context, String shopId) {
        Shop localShop = localIndex.containsKey(shopId) ? localIndex.get(shopId) : null;
        Shop onlineShop = onlineIndex.containsKey(shopId) ? onlineIndex.get(shopId) : null;
        if (localShop != null || onlineShop != null) {
            ShopController shopCtrl = Controller.instantiate(context, ShopController.class);
            shopCtrl.setLocalShop(localShop);
            shopCtrl.setOnlineShop(onlineShop);
            return shopCtrl;
        }
        return null;
    }
}
