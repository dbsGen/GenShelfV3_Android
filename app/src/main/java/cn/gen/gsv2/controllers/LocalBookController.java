package cn.gen.gsv2.controllers;


import android.app.ActivityManager;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AlertDialog;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.gr.classes.Map;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Dictionary;
import java.util.Enumeration;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.ArtBasket;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Chapter;
import cn.gen.gsv2.models.History;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.views.BookHeaderCell;
import cn.gen.gsv2.views.ChapterCell;
import cn.gen.gsv2.views.DescriptionCell;

/**
 * A simple {@link Fragment} subclass.
 */
public class LocalBookController extends Controller implements ChapterCell.OnClickListener, ViewController.OnChapterChangedListener {

    ListView listView;
    BookHeaderCell headerCell;
    DescriptionCell descriptionCell;
    BaseAdapter adapter;
    Chapter lastChapter;
    Book book;
    ArrayList<Chapter> chapters = new ArrayList<>();

    FloatingActionButton floatingButton;

    boolean checkedShare = false;

    public LocalBookController() {
        // Required empty public constructor
    }

    public void setBook(Book book) {
        this.book = book;
        chapters.clear();
        Map cs = book.getChapters();
        Collection en = cs.values();
        for (Object obj : en) {
            chapters.add((Chapter) obj);
        }

        Collections.sort(chapters, new Comparator<Chapter>() {
            @Override
            public int compare(Chapter o1, Chapter o2) {
                return o1.getName().compareTo(o2.getName());
            }
        });

        setTitle(book.getName());
    }


    private void updateData() {

        headerCell.setImageUrl(book.getThumb(), book.getThumbHeaders());
        headerCell.getTitleLabel().setText(book.getName());
        headerCell.getDescriptionLabel().setText(book.getSubtitle());

        descriptionCell.getLabelView().setText(book.getDes());
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_local_book, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        listView = (ListView)view.findViewById(R.id.list_view);

        headerCell = new BookHeaderCell(getContext());
        descriptionCell = new DescriptionCell(getContext());
        lastChapter = book.lastChapter();

        adapter = new BaseAdapter() {
            @Override
            public int getCount() {
                int size = chapters.size();
                int count = size/3;
                if (size % 3 > 0) {
                    count += 1;
                }
                return 2 + count;
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
                if (position == 0)
                    return headerCell;
                else if (position == 1)
                    return descriptionCell;
                else {
                    ChapterCell cell;
                    if (convertView instanceof ChapterCell) {
                        cell = (ChapterCell) convertView;
                    }else {
                        cell = new ChapterCell(getContext());
                        cell.setButtonClicked(LocalBookController.this);
                    }
                    if (lastChapter != null)
                        cell.setCheckUrl(lastChapter.getUrl());
                    cell.setChapters(chapters, (position-2) * 3);
                    return cell;
                }
            }
        };
        listView.setAdapter(adapter);

        headerCell.getHostButton().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(book.getUrl()));
                startActivity(browserIntent);
            }
        });

        updateData();

        floatingButton = (FloatingActionButton)view.findViewById(R.id.floating_button);
        floatingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!checkedShare) {
                    ArtBasket.addBook(book);
                    Toast.makeText(getContext(), getContext().getString(R.string.added_share), Toast.LENGTH_SHORT).show();
                    checkedShare = true;
                }else {
                    PostTopicController ctrl = Controller.instantiate(getContext(), PostTopicController.class);
                    H.navC(LocalBookController.this).push(ctrl, true);
                }
            }
        });
        History.visit(book);
    }

    @Override
    public void click(int index) {
        ViewController ctrl = Controller.instantiate(getContext(), ViewController.class);
        ctrl.setBook(book);
        ctrl.setLocalBook(true);
        Chapter cha = chapters.get(index);
        ctrl.setChapter(cha);
        book.setLastChapter(cha);
        ctrl.setShop(Shop.find(book.getShopId()));
        ctrl.setOnChapterChangedListener(this);
        H.navC(this).push(ctrl, true);
    }

    @Override
    public boolean longClick(int index) {

        AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
        final Chapter chapter = chapters.get(index);
        Context context = getContext();
        builder.setMessage(context.getString(R.string.will_delete).replace("{0}", chapter.getName()));
        builder.setTitle(context.getString(R.string.confirm));
        builder.setPositiveButton(context.getString(R.string.yes), new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                book.removeChapter(chapter);
                chapters.remove(chapter);
                dialog.dismiss();
                if (chapters.size() == 0) {
                    book.removeBook();
                    H.navC(LocalBookController.this).pop(true);
                }else
                    adapter.notifyDataSetChanged();
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

    @Override
    public Chapter prevChapter(Chapter chapter) {
        int idx = chapters.indexOf(chapter);
        if (idx >= 0 && idx < chapters.size() - 1) {
            Chapter cha = chapters.get(idx + 1);
            book.setLastChapter(cha);
            return cha;
        }
        return null;
    }

    @Override
    public Chapter nextChapter(Chapter chapter) {
        int idx = chapters.indexOf(chapter);
        if (idx >= 0 && idx > 0) {
            Chapter cha = chapters.get(idx - 1);
            book.setLastChapter(cha);
            return cha;
        }
        return null;
    }

    @Override
    public void onViewStateRestored(@Nullable Bundle savedInstanceState) {
        super.onViewStateRestored(savedInstanceState);
    }

    @Override
    public void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }
}
