package cn.gen.gsv2.controllers;


import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v7.app.AlertDialog;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;

import com.gr.Activity;
import com.gr.classes.Array;

import java.util.ArrayList;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import apps.gen.lib.views.NavigationBar;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.views.BookCell;
import cn.gen.gsv2.views.StatusView;

/**
 * A simple {@link Fragment} subclass.
 */
public class ShelfController extends Controller implements AdapterView.OnItemClickListener, AdapterView.OnItemLongClickListener {

    ListView listView;
    BaseAdapter adapter;
    StatusView statusView;
    ArrayList<Book> books = new ArrayList<>();
    LikesController likesController;
    FloatingActionButton floatingButton;

    public ShelfController() {
        // Required empty public constructor
    }

    public LikesController getLikesController(Context context) {
        if (likesController == null) {
            likesController = Controller.instantiate(context, LikesController.class);
            likesController.setShelfController(ShelfController.this);
        }
        return likesController;
    }

    public LikesController getLikesController() {
        return likesController;
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
        setTitle(context.getString(R.string.home_shelf));
        setRightItems(new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.like), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (likesController == null) {
                    likesController = Controller.instantiate(getContext(), LikesController.class);
                    likesController.setShelfController(ShelfController.this);
                }
                LikesController.likeStatus = 1;
                H.navC(ShelfController.this).setControllers(new Controller[]{likesController}, true);
            }
        }));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_shelf, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        books.clear();
        Array bs = Book.localBooks();
        for (Object b : bs) {
            books.add((Book)b);
        }

        listView = (ListView)view.findViewById(R.id.list_view);
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
        floatingButton = (FloatingActionButton)view.findViewById(R.id.floating_button);
        if (books.size() != 0) {
            statusView.setVisibility(View.GONE);
            floatingButton.setVisibility(View.VISIBLE);
        }else {
            floatingButton.setVisibility(View.GONE);
        }

        floatingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ProcessController ctrl = Controller.instantiate(getContext(), ProcessController.class);
                H.navC(ShelfController.this).push(ctrl, true);
            }
        });
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Book book = books.get(position);
        LocalBookController ctrl = Controller.instantiate(getContext(), LocalBookController.class);
        ctrl.setBook(book);
        H.navC(this).push(ctrl, true);
    }

    @Override
    public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
        final Book book = books.get(position);
        Context context = getContext();
        builder.setMessage(context.getString(R.string.will_delete).replace("{0}", book.getName()));
        builder.setTitle(context.getString(R.string.confirm));
        builder.setPositiveButton(context.getString(R.string.yes), new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                book.removeBook();
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
