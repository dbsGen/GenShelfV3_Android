package cn.gen.gsv2.controllers;


import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v7.app.AlertDialog;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.gr.Activity;
import com.gr.classes.Array;

import java.util.ArrayList;
import java.util.Date;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import apps.gen.lib.views.NavigationBar;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Chapter;
import cn.gen.gsv2.models.History;
import cn.gen.gsv2.models.Library;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.views.BookCell;
import cn.gen.gsv2.views.LoadingCell;
import cn.gen.gsv2.views.StatusView;

/**
 * A simple {@link Fragment} subclass.
 */
public class HistoryController extends Controller implements View.OnClickListener {

    ArrayList<Book> books = new ArrayList<>();

    ListView listView;
    StatusView statusView;
    LoadingCell loadingCell;
    BaseAdapter adapter;


    long oldTime = 0;

    public HistoryController() {
        // Required empty public constructor
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
        setTitle(context.getString(R.string.home_history));
        setRightItems(new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.remove), this));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_history, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        listView = (ListView) view.findViewById(R.id.list_view);
        statusView = (StatusView) view.findViewById(R.id.status_view);
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
                if (position >= books.size()) return;
                Book book = books.get(position);
                Array<Shop> shops = Shop.getLocalShops();
                Shop foundShop = null;
                String shopId = book.getShopId();
                for (Shop shop : shops) {
                    if (shop.getIdentifier().equals(shopId)) {
                        foundShop = shop;
                        break;
                    }
                }
                if (foundShop != null) {
                    BookController ctrl = Controller.instantiate(getContext(), BookController.class);
                    ctrl.setBook(book);
                    Library library = new Library(true);
                    foundShop.setupLibrary(library);
                    ctrl.setLibrary(library);
                    ctrl.setShop(foundShop);
                    H.navC(HistoryController.this).push(ctrl, true);
                }else {
                    MainActivity activity = (MainActivity) Activity.current();
                    ShopController ctrl = activity.getShopsController().makeShopController(activity, shopId);
                    if (ctrl != null) {
                        Toast.makeText(getContext(), R.string.no_shop, Toast.LENGTH_LONG).show();
                        H.navC(HistoryController.this).push(ctrl, true);
                    }else {
                        Toast.makeText(getContext(), R.string.unkown_shop, Toast.LENGTH_LONG).show();
                    }
                }
            }
        });
        loadData();
    }

    @Override
    public void onDestroyView() {
        loadingCell = null;
        listView = null;
        statusView = null;
        adapter = null;
        super.onDestroyView();
    }

    void loadData() {
        Array<History> hs = History.histories(new Date().getTime());
        books.clear();
        if (hs.size() > 0) {
            History last = hs.get(hs.size() - 1);
            oldTime = last.getDate();
            for (History his : hs) {
                Book book = his.getBook();
                if (book != null)
                    books.add(book);
            }
            loadingCell.setStatus(LoadingCell.STATUS_NORMAL);
            statusView.setVisibility(View.GONE);
        }else {
            loadingCell.setStatus(LoadingCell.STATUS_NO_MORE);
            statusView.getLabelView().setText(getContext().getString(R.string.no_history));
            statusView.setVisibility(View.VISIBLE);
        }
        adapter.notifyDataSetChanged();
    }
    void loadMore() {
        if (loadingCell.getStatus() == LoadingCell.STATUS_NORMAL) {
            Array<History> hs = History.histories(oldTime);
            if (hs.size() > 0) {
                History last = hs.get(hs.size() - 1);
                oldTime = last.getDate();
                for (History his : hs) {
                    Book book = his.getBook();
                    if (book != null)
                        books.add(book);
                }
                loadingCell.setStatus(LoadingCell.STATUS_NORMAL);
                adapter.notifyDataSetChanged();
            }else {
                loadingCell.setStatus(LoadingCell.STATUS_NO_MORE);
            }
        }
    }

    @Override
    public void onClick(View v) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
        Context context = getContext();
        builder.setMessage(context.getString(R.string.will_remove_history));
        builder.setTitle(context.getString(R.string.confirm));
        builder.setPositiveButton(context.getString(R.string.yes), new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                History.clear();
                loadData();
            }
        });
        builder.setNegativeButton(context.getString(R.string.no), new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        });
        builder.create().show();
    }
}
