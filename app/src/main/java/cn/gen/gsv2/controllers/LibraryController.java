package cn.gen.gsv2.controllers;


import android.content.Context;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.text.TextPaint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.bigkoo.pickerview.OptionsPickerView;
import com.bigkoo.pickerview.listener.OnDismissListener;
import com.gr.Activity;
import com.gr.Request;
import com.gr.classes.Array;
import com.gr.classes.Callback;
import com.miguelcatalan.materialsearchview.MaterialSearchView;

import java.util.ArrayList;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.CacheAdapter;
import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import apps.gen.lib.views.NavigationBar;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Library;
import cn.gen.gsv2.models.Settings;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.views.BookCell;
import cn.gen.gsv2.views.LoadingCell;
import cn.gen.gsv2.views.SelectButton;
import cn.gen.gsv2.views.StatusView;

/**
 * A simple {@link Fragment} subclass.
 */
public class LibraryController extends Controller implements SwipeRefreshLayout.OnRefreshListener {

    SwipeRefreshLayout refreshView;
    ListView listView;
    Library library;
    Callback pageCallback;
    ArrayList<Book> books = new ArrayList<>();
    BaseAdapter adapter;
    LoadingCell loadingCell;
    SelectButton selectButton;
    NavigationBar navigationBar;
    OptionsPickerView optionsView;
    StatusView statusView;
    FloatingActionButton floatingButton;

    Array shops;
    int pageIndex = 0;
    static boolean willReload;

    public LibraryController() {
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        setRightItems(new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.search), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (library != null) {
                    SearchController ctrl = Controller.instantiate(getContext(), SearchController.class);
                    ctrl.setLibrary(library);
                    H.navC(LibraryController.this).push(ctrl, true);
                }
            }
        }));
    }

    @Override
    public void setTitle(String title) {
        super.setTitle(title);

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_library, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        final Shop shop = Shop.getCurrentShop();
        if (shop == null)
            setTitle(getContext().getString(R.string.home_library));
        else {
            setTitle(shop.getName());
        }
        refreshView = (SwipeRefreshLayout)view.findViewById(R.id.refresh);
        listView = (ListView)view.findViewById(R.id.list_view);
        loadingCell = new LoadingCell(getContext());

        adapter = new BaseAdapter() {

            @Override
            public int getCount() {
                return books.size() == 0 ? 0 : books.size() + 1;
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
                if (position < books.size()) {
                    BookCell cell;
                    if (convertView instanceof BookCell) {
                        cell = (BookCell)convertView;
                    }else {
                        cell = new BookCell(getContext());
                    }
                    Book book = books.get(position);
                    cell.getTitleLabel().setText(book.getName());
                    cell.getDescriptionLabel().setText(book.getSubtitle());
                    cell.setImageUrl(book.getThumb(), book.getThumbHeaders());
                    return cell;
                }else {
                    if (loadingCell.getStatus() == 0) {
                        loadMore();
                    }
                    return loadingCell;
                }
            }
        };
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if (position < books.size()) {
                    Shop shop = Shop.getCurrentShop();
                    BookController ctrl = Controller.instantiate(getContext(), BookController.class);
                    ctrl.setBook(books.get(position));
                    ctrl.setShop(shop);
                    ctrl.setLibrary(library);
                    H.navC(LibraryController.this).push(ctrl, true);
                }
            }
        });

        refreshView.setOnRefreshListener(this);
        refreshView.setColorSchemeResources(R.color.blue);

        selectButton = new SelectButton(getContext());
        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(H.dip2px(getContext(), 40), ViewGroup.LayoutParams.MATCH_PARENT);
        layoutParams.setMargins(H.dip2px(getContext(), 44), 0, 0, 0);
        selectButton.setLayoutParams(layoutParams);
        selectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                optionsView.show();
                selectButton.extend(true);
            }
        });

        shops = Shop.getLocalShops();
        optionsView = new OptionsPickerView.Builder(getContext(), new OptionsPickerView.OnOptionsSelectListener(){

            @Override
            public void onOptionsSelect(int options1, int options2, int options3, View v) {
                Shop shop = (Shop)shops.get(options1);
                if (!shop.equals(Shop.getCurrentShop())) {
                    Shop.setCurrentShop(shop);
                    books.clear();
                    library = null;
                    adapter.notifyDataSetChanged();
                    loadLibrary();
                    setTitle(shop.getName());
                    checkTitleSize();
                }
            }
        }).build();
        optionsView.setOnDismissListener(new OnDismissListener() {
            @Override
            public void onDismiss(Object o) {
                selectButton.extend(false);
            }
        });
        ArrayList<String> sps = new ArrayList<>();
        for (Object obj : shops) {
            sps.add(((Shop)obj).getName());
        }
        optionsView.setPicker(sps);

        floatingButton = (FloatingActionButton)view.findViewById(R.id.floating_button);
        floatingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Shop shop = Shop.getCurrentShop();
                if (shop != null) {
                    SettingsController ctrl = Controller.instantiate(getContext(), SettingsController.class);
                    ctrl.setShop(shop);
                    ctrl.setTitle(shop.getName());
                    ctrl.setSettings(shop.getSettings());
                    H.navC(LibraryController.this).push(ctrl, true);
                }
            }
        });

        statusView = (StatusView)view.findViewById(R.id.status_view);
        statusView.getLabelView().setText(getString(R.string.goto_shops));
        statusView.getCheckButton().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ((MainActivity) Activity.current()).setNavItem(R.id.settins);
            }
        });
        if (Shop.getCurrentShop() == null) {
            selectButton.setVisibility(View.GONE);
            adapter.notifyDataSetChanged();
        }else {
            statusView.setVisibility(View.GONE);
            floatingButton.setVisibility(View.VISIBLE);
        }
    }

    @Override
    protected void onViewWillAppear() {
        super.onViewWillAppear();
        loadLibrary();
    }

    void checkTitleSize() {
        TextPaint paint = H.navC(this).getNavigationBar().getTitleView().getPaint();
        Rect rect = new Rect();
        paint.getTextBounds(getTitle(), 0, getTitle().length(), rect);
        selectButton.getLayoutParams().width = rect.width() + H.dip2px(getContext(), 24);
    }

    @Override
    protected void onViewDidAppear() {
        super.onViewDidAppear();

        navigationBar = H.navC(this).getNavigationBar();
        if (selectButton.getParent() != null) {
            ((ViewGroup)selectButton.getParent()).removeView(selectButton);
        }
        navigationBar.addView(selectButton);
        checkTitleSize();
    }

    @Override
    protected void onViewWillDisappear() {
        super.onViewWillDisappear();
        navigationBar.removeView(selectButton);
    }

    public static void setWillReload() {
        willReload = true;
    }

    void loadLibrary() {
        Shop shop = Shop.getCurrentShop();
        if (shop == null) {
            books.clear();
            library = null;
        }else {
            selectButton.setVisibility(View.VISIBLE);
            if (library == null) {
                library = new Library(true);
                shop.setupLibrary(library);
                reloadData();
                willReload = false;
            }
            if (willReload) {
                reloadData();
                willReload = false;
            }
        }
    }

    void reloadData() {
        if (library == null) {
            loadLibrary();
            return;
        }
        pageIndex = 0;
        loadingCell.setStatus(1);
        pageCallback = new Callback(true) {
            @Override
            public Object run(Object... args) {
                boolean suc = (boolean)args[0];
                if (suc) {
                    LibraryController.this.books.clear();
                    Array books = (Array)args[1];
                    boolean noMore = false;
                    if (args.length > 2) {
                        noMore = (boolean)args[2];
                    }
                    String id = Shop.getCurrentShop().getIdentifier();
                    for (Object book : books) {
                        Book b = (Book)book;
                        b.setShopId(id);
                        LibraryController.this.books.add(b);
                    }
                    adapter.notifyDataSetChanged();
                    if (books.size() == 0 || noMore) {
                        loadingCell.setStatus(2);
                        refreshView.setRefreshing(false);
                        return null;
                    }
                }else {
                    Toast.makeText(getContext(), "loading failed.",
                            Toast.LENGTH_SHORT).show();
                }
                loadingCell.setStatus(0);
                refreshView.setRefreshing(false);
                return null;
            }
        };

        refreshView.setRefreshing(true);
        library.applyLoad(0, pageCallback);
    }
    void loadMore() {
        ++pageIndex;
        loadingCell.setStatus(1);
        pageCallback = new Callback(true) {
            @Override
            public Object run(Object... args) {
                boolean res = (boolean)args[0];
                if (res) {
                    Array books = (Array)args[1];
                    boolean noMore = false;
                    if (args.length > 2) {
                        noMore = (boolean)args[2];
                    }
                    String id = Shop.getCurrentShop().getIdentifier();
                    for (Object book : books) {
                        Book b = (Book)book;
                        b.setShopId(id);
                        LibraryController.this.books.add(b);
                    }
                    adapter.notifyDataSetChanged();
                    if (books.size() == 0 || noMore) {
                        loadingCell.setStatus(2);
                        refreshView.setRefreshing(false);
                        return null;
                    }
                }else {
                    Toast.makeText(getContext(), "loading failed.",
                            Toast.LENGTH_SHORT).show();
                }
                loadingCell.setStatus(0);
                refreshView.setRefreshing(false);
                return null;
            }
        };

        refreshView.setRefreshing(true);
        library.applyLoad(pageIndex, pageCallback);
    }

    @Override
    public void onRefresh() {
        reloadData();
    }
}
