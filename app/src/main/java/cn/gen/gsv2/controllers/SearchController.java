package cn.gen.gsv2.controllers;


import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.widget.SearchView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import com.gr.classes.Array;
import com.gr.classes.Callback;
import com.miguelcatalan.materialsearchview.MaterialSearchView;

import java.util.ArrayList;
import java.util.List;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.CacheAdapter;
import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.HTTPClient;
import cn.gen.gsv2.models.KeyValue;
import cn.gen.gsv2.models.Library;
import cn.gen.gsv2.models.SearchTip;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.views.BookCell;
import cn.gen.gsv2.views.LoadingCell;
import cn.gen.gsv2.views.SearchHistoryCell;

/**
 * A simple {@link Fragment} subclass.
 */
public class SearchController extends Controller implements SwipeRefreshLayout.OnRefreshListener, AdapterView.OnItemClickListener {

    class SearchAdapter extends BaseAdapter {

        Array<String> tips;

        public void setTips(Array<String> tips) {
            this.tips = tips;
            notifyDataSetChanged();
            if (tips.size() > 0)
                searchView.showSuggestions();
        }

        @Override
        public int getCount() {
            return tips == null ? 0 : tips.size();
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
        public View getView(final int position, View convertView, ViewGroup parent) {
            SearchHistoryCell cell;
            if (convertView == null) {
                cell = new SearchHistoryCell(getContext());
            }else {
                cell = (SearchHistoryCell)convertView;
            }
            cell.setOnRemoveListener(new SearchHistoryCell.OnRemoveListener() {
                @Override
                public void onRemove(SearchHistoryCell cell) {
                    SearchTip.removeKey(cell.getLabelView().getText().toString());
                    tips.remove(position);
                    notifyDataSetChanged();
                }
            });
            cell.getLabelView().setText(tips.get(position));
            return cell;
        }
    }

    ListView listView;
    SwipeRefreshLayout refreshView;

    HTTPClient client;
    Library library;
    int index;

    ArrayList<Book> books = new ArrayList<>();
    Callback reloadCallback;
    Callback loadMoreCallback;
    BaseAdapter adapter;
    SearchAdapter searchAdapter;
    LoadingCell loadingCell;
    boolean firstEnter = true;
    MaterialSearchView searchView;

    String searchText;

    public SearchController() {
        // Required empty public constructor
    }

    public void setLibrary(Library library) {
        this.library = library;
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        setTitle(context.getString(R.string.search));

        setRightItems(new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.search), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (searchView != null) {
                    searchAdapter.setTips(SearchTip.search(null));
                    searchView.showSearch(true);
                    searchView.showSuggestions();
                }
            }
        }));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_search, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

//        searchView = (SearchView)view.findViewById(R.id.search);
        listView = (ListView)view.findViewById(R.id.list_view);
//        searchTipsView = (ListView)view.findViewById(R.id.search_tips_view);
        refreshView = (SwipeRefreshLayout)view.findViewById(R.id.refresh);
        refreshView.setColorSchemeResources(R.color.blue);
        refreshView.setOnRefreshListener(this);

        if (loadingCell == null)
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
        listView.setOnItemClickListener(this);

        searchView = new MaterialSearchView(getContext());
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            searchView.setTranslationZ(11);
        }
        searchView.setOnQueryTextListener(new MaterialSearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextSubmit(String query) {
                searchText = query;
                SearchTip.insert(query);
                requestDatas();
                return false;
            }

            @Override
            public boolean onQueryTextChange(String newText) {
                searchAdapter.setTips(SearchTip.search(newText));
                return false;
            }
        });

        searchAdapter = new SearchAdapter();
        searchView.setAdapter(searchAdapter);

        searchView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                searchText = searchAdapter.tips.get(position);
                SearchTip.insert(searchText);
                requestDatas();
                searchView.closeSearch();
            }
        });
    }

    Runnable showSearch = new Runnable() {
        @Override
        public void run() {
            searchView.showSearch(true);
        }
    };

    @Override
    protected void onViewWillDisappear() {
        super.onViewWillDisappear();
        InputMethodManager imm = (InputMethodManager)getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.hideSoftInputFromWindow(searchView.getWindowToken(),0);
        if (client != null) {
            client.cancel();
        }
        if (loadingCell.getStatus() == LoadingCell.STATUS_LOADING)
            loadingCell.setStatus(LoadingCell.STATUS_NORMAL);
        H.navC(this).getView().removeView(searchView);
        getHandler().removeCallbacks(showSearch);
    }

    @Override
    protected void onViewDidAppear() {
        super.onViewDidAppear();
        H.navC(this).getView().addView(searchView);
        if (firstEnter) {
            getHandler().postDelayed(showSearch, 10);
            firstEnter = false;
        }
    }

    private void requestDatas() {
        refreshView.setRefreshing(true);

        index = 0;
        reloadCallback = new Callback(true) {
            @Override
            public Object run(Object... args) {
                boolean success = (boolean)args[0];
                if (success) {
                    Array<Book> bs = (Array<Book>)args[1];
                    boolean no_more = false;
                    if (args.length > 2 && args[2] != null) {
                        no_more = (boolean)args[2];
                    }
                    books.clear();
                    String id = Shop.getCurrentShop().getIdentifier();
                    for (Book b : bs) {
                        b.setShopId(id);
                        books.add(b);
                    }
                    adapter.notifyDataSetChanged();
                    loadingCell.setStatus((no_more || bs.size() == 0) ? LoadingCell.STATUS_NO_MORE : LoadingCell.STATUS_NORMAL);
                }else {
                    Toast.makeText(getContext(), "loading failed.",
                            Toast.LENGTH_SHORT).show();
                }
                refreshView.setRefreshing(false);
                return null;
            }
        };

        Object ret = library.apply("search", searchText, index, reloadCallback);
        if (ret instanceof HTTPClient) {
            client = (HTTPClient)ret;
        }
    }

    private void loadMore() {
        if (loadingCell.getStatus() == LoadingCell.STATUS_NORMAL) {
            ++index;
            refreshView.setRefreshing(true);
            loadingCell.setStatus(LoadingCell.STATUS_LOADING);
            loadMoreCallback = new Callback(true) {
                @Override
                public Object run(Object... args) {
                    boolean success = (boolean)args[0];
                    if (success) {
                        Array<Book> bs = (Array) args[1];
                        boolean no_more = false;
                        if (args.length > 2 && args[2] != null) {
                            no_more = (boolean)args[2];
                        }
                        if (bs.size() > 0) {
                            String id = Shop.getCurrentShop().getIdentifier();
                            for (Book b : bs) {
                                b.setShopId(id);
                                books.add(b);
                            }
                            adapter.notifyDataSetChanged();
                            loadingCell.setStatus(no_more ? LoadingCell.STATUS_NO_MORE : LoadingCell.STATUS_NORMAL);
                        }else {
                            loadingCell.setStatus(LoadingCell.STATUS_NO_MORE);
                        }
                    }else {
                        Toast.makeText(getContext(), "loading failed.",
                                Toast.LENGTH_SHORT).show();
                        loadingCell.setStatus(LoadingCell.STATUS_NORMAL);
                    }
                    refreshView.setRefreshing(false);
                    return null;
                }
            };
            Object ret = library.apply("search", searchText, index, loadMoreCallback);
            if (ret instanceof HTTPClient) {
                client = (HTTPClient)ret;
            }
        }
    }

    @Override
    public void onRefresh() {
        requestDatas();
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        if (position < books.size()) {
            Shop shop = Shop.getCurrentShop();
            BookController ctrl = Controller.instantiate(getContext(), BookController.class);
            ctrl.setBook(books.get(position));
            ctrl.setShop(shop);
            ctrl.setLibrary(library);
            H.navC(this).push(ctrl, true);
        }
    }

    @Override
    public boolean onBackPressed() {
        if (searchView.isSearchOpen()) {
            searchView.closeSearch();
            return true;
        }
        return super.onBackPressed();
    }
}
