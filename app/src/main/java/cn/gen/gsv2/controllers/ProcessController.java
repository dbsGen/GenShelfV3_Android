package cn.gen.gsv2.controllers;


import android.content.Context;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.text.Html;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ListView;

import com.gr.classes.Array;

import apps.gen.lib.controllers.Controller;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Book;
import cn.gen.gsv2.models.Chapter;
import cn.gen.gsv2.views.ProcessCell;

/**
 * A simple {@link Fragment} subclass.
 */
public class ProcessController extends Controller {

    Array<Book> books = new Array<>(true);
    Array<Chapter> chapters = new Array<>(true);

    ListView listView;
    BaseAdapter adapter;

    public ProcessController() {
        // Required empty public constructor
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
        setTitle(context.getString(R.string.gen_downloading));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_process, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        books.clear();
        chapters.clear();
        Chapter.downloadingChapters(books, chapters);

        listView = (ListView)view.findViewById(R.id.list_view);
        adapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return chapters.size();
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
                ProcessCell cell;
                if (convertView == null) {
                    cell = new ProcessCell(getContext());
                }else {
                    cell = (ProcessCell)convertView;
                }
                cell.setData(books.get(position), chapters.get(position));
                return cell;
            }
        };

        listView.setAdapter(adapter);
    }
}
