package cn.gen.gsv2.controllers;


import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.RecyclerView;
import android.text.InputType;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;

import com.bigkoo.pickerview.OptionsPickerView;
import com.gr.Request;
import com.gr.classes.Array;
import com.gr.classes.Callback;

import java.util.ArrayList;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.CacheAdapter;
import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.KeyValue;
import cn.gen.gsv2.models.Settings;
import cn.gen.gsv2.views.ArrowCell;
import cn.gen.gsv2.views.CheckCell;
import cn.gen.gsv2.views.DividerCell;
import cn.gen.gsv2.views.InputCell;
import cn.gen.gsv2.views.ListViewCell;
import cn.gen.gsv2.views.SwitchCell;

import static android.text.InputType.TYPE_TEXT_VARIATION_NORMAL;
import static android.text.InputType.TYPE_TEXT_VARIATION_PASSWORD;
import static cn.gen.gsv2.models.Settings.SettingItem.TYPE_BUTTON;
import static cn.gen.gsv2.models.Settings.SettingItem.TYPE_OPTION;

/**
 * A simple {@link Fragment} subclass.
 */
public class MainSettingsController extends Controller implements View.OnClickListener,
        InputCell.OnTextChanged,
        CheckCell.OnChecked, SwitchCell.OnSwitchChanged {

    private class SettingItem {
        public int type;
        public String name;
        public Object content;
        public Object params;
    }

    ListView listView;
    CacheAdapter adapter;
    ArrayList<SettingItem> items = new ArrayList<>();
    OptionsPickerView optionsView;
    ArrowCell selectedCell;

    public MainSettingsController() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_main_settings, container, false);
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);

        setTitle(context.getString(R.string.setting));
        items = new ArrayList<>();
        {
            SettingItem item = new SettingItem();
            item.type = Settings.SettingItem.TYPE_DIVIDER;
            item.name = "社交身份";
            items.add(item);
        }
        {
            SettingItem item = new SettingItem();
            item.type = Settings.SettingItem.TYPE_INPUT;
            item.name = "别号";
            item.content = KeyValue.get("author_name");
            item.params = true;
            items.add(item);
        }
        {
            SettingItem item = new SettingItem();
            item.type = Settings.SettingItem.TYPE_DIVIDER;
            item.name = "缓存";
            items.add(item);
        }
        {
            SettingItem item = new SettingItem();
            item.type = Settings.SettingItem.TYPE_INPUT;
            item.name = "占用容量";
            long size = Request.getCacheSize() / 1024 / 1024;
            item.content = "" + size + "M";
            item.params = false;
            items.add(item);
        }
        {
            SettingItem item = new SettingItem();
            item.type = TYPE_BUTTON;
            item.name = "清除缓存";
            item.params = new Callback(true) {
                @Override
                public Object run(Object... args) {
                    Request.clear();
                    InputCell cell = (InputCell)adapter.findCell(3);
                    long size = Request.getCacheSize() / 1024 / 1024;
                    cell.getEditText().setText("" + size + "M");
                    return null;
                }
            };
            items.add(item);
        }
    }

    class ViewHolder extends RecyclerView.ViewHolder {

        ListViewCell viewCell;

        public ListViewCell getViewCell() {
            return viewCell;
        }

        public ViewHolder(Context context) {
            super(new ListViewCell(context));
            viewCell = (ListViewCell)getView();
        }
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        optionsView = new OptionsPickerView.Builder(getContext(), new OptionsPickerView.OnOptionsSelectListener(){

            @Override
            public void onOptionsSelect(int options1, int options2, int options3, View v) {
                Settings.SettingItem item = (Settings.SettingItem)selectedCell.getData();
                item.setValue(options1);
                selectedCell.setSelected(options1);
            }
        }).build();

        listView = (ListView)view.findViewById(R.id.list_view);
        listView.setBackgroundColor(Color.rgb(230, 230, 230));

        adapter = new CacheAdapter(getContext()) {

            @Override
            public int getCount() {
                return items.size();
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
            public ListCell cellView(int position) {
                SettingItem item = items.get(position);
                int type = item.type;
                switch (type) {
                    case 1: {
                        String identifier = "OptionCell";
                        ArrowCell cell = (ArrowCell)popWithIdentifier(identifier);
                        if (cell == null) {
                            cell = new ArrowCell(getContext(), identifier);
                            cell.setOnClickListener(MainSettingsController.this);
                        }
                        cell.getTitleView().setText(item.name);
                        cell.setData(item);
                        try {
                            ArrayList<String> list = new ArrayList<>();
                            Array ops = (Array)item.params;
                            for (Object op : ops) {
                                list.add((String) op);
                            }
                            cell.setOptions(list);
                            Object tar = item.content;
                            if (tar == null)
                                cell.setSelected(0);
                            else
                                cell.setSelected(((Number)tar).intValue());
                        }catch (Exception e) {
                            e.printStackTrace();
                        }
                        return cell;
                    }
                    case 5:
                    case 2: {
                        String identifier = "InputCell";
                        InputCell cell = (InputCell)popWithIdentifier(identifier);
                        if (cell == null) {
                            cell = new InputCell(getContext(), identifier);
                            cell.setOnTextChanged(MainSettingsController.this);
                        }
                        cell.getTitleView().setText(item.name);
                        cell.setData(item);
                        try {
                            cell.getEditText().setText((String)item.content);
                        }catch (Exception e) {
                            e.printStackTrace();
                        }
                        if (type == 5) {
                            cell.getEditText().setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD);
                        }else
                            cell.getEditText().setInputType(InputType.TYPE_CLASS_TEXT);
                        if (item.params!= null && !(boolean)item.params) {
                            cell.getEditText().setFocusable(false);
                        }else {
                            cell.getEditText().setFocusable(true);
                        }
                        return cell;
                    }
                    case 3: {
                        String identifier = "CheckCell";
                        CheckCell cell = (CheckCell)popWithIdentifier(identifier);
                        if (cell == null) {
                            cell = new CheckCell(getContext(), identifier);
                            cell.setOnChecked(MainSettingsController.this);
                        }
                        cell.getTitleView().setText(item.name);
                        cell.setData(item);
                        try {
                            cell.getCheckBox().setChecked((int)item.content != 0);
                        }catch (Exception e) {
                            e.printStackTrace();
                        }
                        return cell;
                    }
                    case 4: {
                        String identifier = "SwitchCell";
                        SwitchCell cell = (SwitchCell)popWithIdentifier(identifier);
                        if (cell == null) {
                            cell = new SwitchCell(getContext(), identifier);
                            cell.setOnSwitchChanged(MainSettingsController.this);
                        }
                        cell.getTitleView().setText(item.name);
                        cell.setData(item);
                        try {
                            cell.getSwitch().setChecked((int)item.content != 0);
                        }catch (Exception e) {
                            e.printStackTrace();
                        }
                        return cell;
                    }
                    case 6: {
                        String identifier = "DividerCell";
                        DividerCell cell = (DividerCell)popWithIdentifier(identifier);
                        if (cell == null) {
                            cell = new DividerCell(getContext(), identifier);
                        }
                        cell.setTitle(item.name);
                        return cell;
                    }
                    case TYPE_BUTTON: {
                        String identifier = "ButtonCell";
                        ArrowCell cell = (ArrowCell)popWithIdentifier(identifier);
                        if (cell == null) {
                            cell = new ArrowCell(getContext(), identifier);
                            cell.setOnClickListener(MainSettingsController.this);
                        }
                        cell.getTitleView().setText(item.name);
                        cell.setData(item);
                        cell.getLabelView().setText("");
                        return cell;
                    }
                }
                return null;
            }
        };
        listView.setAdapter(adapter);
    }


    @Override
    public void onClick(View v) {
        ArrowCell cell = (ArrowCell)v;
        SettingItem item = (SettingItem) cell.getData();
        if (item.type == TYPE_OPTION) {
            selectedCell = cell;
            optionsView.setPicker(cell.getOptions());
            optionsView.setSelectOptions(cell.getSelected());
            optionsView.show();
        }else if (item.type == TYPE_BUTTON) {
            Callback callback = (Callback) item.params;
            callback.invoke();
        }
    }

    @Override
    public void textChanged(InputCell cell, String newText) {
        SettingItem item = (SettingItem)cell.getData();
        if (item.name.equals("别号")) {
            KeyValue.set("author_name", newText);
        }
//        item.setValue(newText);
    }

    @Override
    public void checked(CheckCell cell, boolean checked) {
        SettingItem item = (SettingItem)cell.getData();
//        item.setValue(checked);
    }

    @Override
    public void onSwitch(SwitchCell cell, boolean on) {
        SettingItem item = (SettingItem)cell.getData();
//        item.setValue(on);
    }
}
