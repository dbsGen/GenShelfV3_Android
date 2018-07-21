package cn.gen.gsv2.controllers;


import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
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

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Library;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.views.BookCell;
import cn.gen.gsv2.views.StatusView;

/**
 * A simple {@link Fragment} subclass.
 */
public class LikesController extends Controller implements AdapterView.OnItemClickListener,
        AdapterView.OnItemLongClickListener {

    private ShelfController shelfController;

    public static int likeStatus = -1;

    private ListView listView;
    private StatusView statusView;
    ArrayList<Book> books = new ArrayList<>();
    BaseAdapter adapter;

    public LikesController() {
        // Required empty public constructor
    }

    public void setShelfController(ShelfController shelfController) {
        this.shelfController = shelfController;
        setLeftItems(shelfController.getLeftItems());
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        setTitle(context.getString(R.string.home_like));
        setRightItems(new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.squares), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                H.navC(LikesController.this).setControllers(new Controller[]{shelfController}, true);
                LikesController.likeStatus = 0;
            }
        }));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_likes, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        listView = (ListView)view.findViewById(R.id.list_view);

        books.clear();
        Array bs = Book.likedBooks();
        for (Object b : bs) {
            books.add((Book)b);
        }
        adapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return books.size();
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
                }
                Book book = books.get(position);
                cell.setImageUrl(book.getThumb());
                cell.getTitleLabel().setText(book.getName());
                cell.getDescriptionLabel().setText(book.getSubtitle());
                return cell;
            }
        };
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(this);
        listView.setOnItemLongClickListener(this);

        statusView = (StatusView)view.findViewById(R.id.status_view);
        statusView.getLabelView().setText(getString(R.string.goto_library));
        statusView.getCheckButton().setText(getString(R.string.go));
        statusView.getCheckButton().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ((MainActivity) Activity.current()).setNavItem(R.id.library);
            }
        });

        if (books.size() != 0) {
            statusView.setVisibility(View.GONE);
        }
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
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
            H.navC(this).push(ctrl, true);
        }else {
            MainActivity activity = (MainActivity) Activity.current();
            ShopController ctrl = activity.getShopsController().makeShopController(activity, shopId);
            if (ctrl != null) {
                Toast.makeText(getContext(), R.string.no_shop, Toast.LENGTH_LONG).show();
                H.navC(this).push(ctrl, true);
            }else {
                Toast.makeText(getContext(), R.string.unkown_shop, Toast.LENGTH_LONG).show();
            }
        }
    }

    @Override
    public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
        final Book book = books.get(position);
        Context context = getContext();
        builder.setMessage(context.getString(R.string.will_unlike).replace("{0}", book.getName()));
        builder.setTitle(context.getString(R.string.confirm));
        builder.setPositiveButton(context.getString(R.string.yes), new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                book.unlikeBook();
                books.remove(book);
                adapter.notifyDataSetChanged();
                dialog.dismiss();
            }
        });
        builder.setNegativeButton(context.getString(R.string.no), new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        });
        builder.create().show();
        return true;
    }
}
