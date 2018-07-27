package cn.gen.gsv2.controllers;


import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AlertDialog;
import android.text.SpannableStringBuilder;
import android.text.Spanned;
import android.text.method.LinkMovementMethod;
import android.text.style.ClickableSpan;
import android.text.style.ForegroundColorSpan;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.gr.classes.Array;
import com.gr.classes.Callback;

import java.util.ArrayList;
import java.util.Date;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.H;
import apps.gen.lib.views.NavigationBar;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.ArtBasket;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Chapter;
import cn.gen.gsv2.models.History;
import cn.gen.gsv2.models.Library;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.views.BookHeaderCell;
import cn.gen.gsv2.views.ChapterCell;
import cn.gen.gsv2.views.DescriptionCell;

/**
 * A simple {@link Fragment} subclass.
 */
public class BookController extends Controller implements SwipeRefreshLayout.OnRefreshListener, ChapterCell.OnClickListener, ViewController.OnChapterChangedListener {

    SwipeRefreshLayout refresh;
    ListView listView;
    BookHeaderCell headerCell;
    DescriptionCell descriptionCell;
    BaseAdapter adapter;
    Book book;
    Shop shop;
    Library library;
    boolean hasMore;
    ArrayList<Chapter> chapters = new ArrayList<>();
    Chapter lastChapter;

    Chapter willPushChapter;

    FloatingActionButton floatingButton;

    NavigationItem likeItem, likedItem;

    boolean checkedShare = false;

    public BookController() {
        // Required empty public constructor
    }

    @Override
    protected void initialize(final Context context) {
        super.initialize(context);

        likeItem = new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.like), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                H.navC(BookController.this).setRightNavItem(likedItem, NavigationBar.AnimationType.FADE);
                shop.like(book);
                Toast.makeText(context, context.getString(R.string.like_book).replace("{0}", book.getName()), Toast.LENGTH_SHORT).show();
            }
        });
        likedItem = new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.liked), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                H.navC(BookController.this).setRightNavItem(likeItem, NavigationBar.AnimationType.FADE);
                book.unlikeBook();
                Toast.makeText(context, context.getString(R.string.unlike_book), Toast.LENGTH_SHORT).show();
            }
        });
        setRightItems(likeItem);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_book, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        refresh = (SwipeRefreshLayout)view.findViewById(R.id.refresh);
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
                        cell.setButtonClicked(BookController.this);
                    }
                    if (lastChapter != null)
                        cell.setCheckUrl(lastChapter.getUrl());
                    cell.setChapters(chapters, (position-2) * 3);
                    return cell;
                }
            }
        };
        listView.setAdapter(adapter);

        refresh.setOnRefreshListener(this);
        refresh.setColorSchemeResources(R.color.blue);

        headerCell.getHostButton().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(book.getUrl()));
                startActivity(browserIntent);
            }
        });

        updateData();

        setRightItems(book.isLiked() ? likedItem : likeItem);

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
                    H.navC(BookController.this).push(ctrl, true);
                }
            }
        });
        History.visit(book);
    }

    @Override
    public void onDestroyView() {
        refresh = null;
        listView = null;
        headerCell = null;
        descriptionCell = null;
        adapter = null;
        super.onDestroyView();
    }

    private void updateData() {
        SpannableStringBuilder builder = new SpannableStringBuilder();
        builder.append(book.getName());
        headerCell.setImageUrl(book.getThumb(), book.getThumbHeaders());
        headerCell.getDescriptionLabel().setText(book.getSubtitle());
        if (lastChapter != null && !lastChapter.getName().isEmpty()) {
            builder.append(" ");
            builder.append(getContext().getString(R.string.last));
            builder.append('[');
            int start = builder.length();
            String con = lastChapter.getName();
            int end = start + con.length();
            builder.append(con);
            builder.append(']');
            builder.setSpan(new ForegroundColorSpan(ActivityCompat.getColor(getContext(), R.color.blue)),
                    start, end, Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
            builder.setSpan(new ClickableSpan() {
                @Override
                public void onClick(View widget) {
                    ViewController ctrl = Controller.instantiate(getContext(), ViewController.class);
                    ctrl.setChapter(lastChapter);
                    ctrl.setShop(shop);
                    ctrl.setBook(book);
                    ctrl.setLocalBook(false);
                    ctrl.setOnChapterChangedListener(BookController.this);
                    H.navC(BookController.this).push(ctrl, true);
                }
            }, start, end, Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
        }
        headerCell.getTitleLabel().setMovementMethod(LinkMovementMethod.getInstance());
        headerCell.getTitleLabel().setText(builder);

        descriptionCell.getLabelView().setText(book.getDes());
    }

    public void setBook(Book book) {
        this.book = book;
        setTitle(book.getName());
    }

    public void setShop(Shop shop) {
        this.shop = shop;
    }

    public void setLibrary(Library library) {
        this.library = library;
    }
    Callback callback;

    boolean active = false;

    @Override
    protected void onViewWillAppear() {
        super.onViewWillAppear();

        active = true;
        if (chapters.size() == 0) {
            refresh.setRefreshing(true);
            onRefresh();
        }
    }

    @Override
    protected void onViewWillDisappear() {
        super.onViewWillDisappear();

        active = false;
    }

    @Override
    public void onRefresh() {

        callback = new Callback(true) {
            @Override
            public Object run(Object... args) {
                if (!active) return null;
                boolean success = (boolean)args[0];
                if (success) {
                    Book book = (Book)args[1];
                    Array chapters = (Array)args[2];
                    boolean hasMore = (boolean)args[3];
                    book.setShopId(Shop.getCurrentShop().getIdentifier());
                    BookController.this.book = book;
                    updateData();
                    BookController.this.chapters.clear();
                    for (Object c : chapters) {
                        Chapter chapter = (Chapter)c;
                        chapter.setShopId(book.getShopId());
                        BookController.this.chapters.add(chapter);
                    }
                    BookController.this.hasMore = hasMore;
                    adapter.notifyDataSetChanged();
                }else {

                }
                if (willPushChapter != null) {
                    ViewController ctrl = Controller.instantiate(getContext(), ViewController.class);
                    ctrl.setChapter(willPushChapter);
                    ctrl.setShop(shop);
                    ctrl.setBook(book);
                    ctrl.setLocalBook(false);
                    ctrl.setOnChapterChangedListener(BookController.this);
                    H.navC(BookController.this).push(ctrl, true);
                    willPushChapter = null;
                }
                refresh.setRefreshing(false);
                return null;
            }
        };
        library.apply("loadBook", book, 0, callback);
    }

    @Override
    public void click(int index) {
        if (!active) return;
        ViewController ctrl = Controller.instantiate(getContext(), ViewController.class);
        Chapter chapter = chapters.get(index);
        book.setLastChapter(chapter);
        ctrl.setChapter(chapter);
        ctrl.setShop(shop);
        ctrl.setBook(book);
        ctrl.setLocalBook(false);
        ctrl.setOnChapterChangedListener(this);
        try {
            H.navC(this).push(ctrl, true);
        }catch (Exception e) {
        }
    }

    @Override
    public boolean longClick(int index) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
        final Chapter chapter = chapters.get(index);
        Context context = getContext();
        builder.setMessage(context.getString(R.string.will_collect).replace("{0}", chapter.getName()));
        builder.setTitle(context.getString(R.string.confirm));
        builder.setPositiveButton(context.getString(R.string.yes), new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                shop.collect(book, chapter);
                Toast.makeText(getContext(), getContext().getString(R.string.collect_ok), Toast.LENGTH_SHORT).show();
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
    public void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }

    public void setWillPushChapter(Chapter willPushChapter) {
        this.willPushChapter = willPushChapter;
    }
}
