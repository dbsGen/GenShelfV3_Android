package cn.gen.gsv2.controllers;


import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.text.Editable;
import android.text.InputType;
import android.text.TextWatcher;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;

import com.bigkoo.pickerview.OptionsPickerView;
import com.gr.Activity;
import com.gr.classes.Array;
import com.gr.classes.Callback;
import com.gr.classes.NotificationCenter;
import com.nhaarman.listviewanimations.itemmanipulation.DynamicListView;

import java.util.ArrayList;

import apps.gen.lib.controllers.Controller;
import apps.gen.lib.utils.CacheAdapter;
import apps.gen.lib.utils.H;
import apps.gen.lib.views.ListCell;
import cn.gen.gsv2.MainActivity;
import cn.gen.gsv2.R;
import cn.gen.gsv2.models.Settings;
import cn.gen.gsv2.models.Shop;
import cn.gen.gsv2.views.ArrowCell;
import cn.gen.gsv2.views.CheckCell;
import cn.gen.gsv2.views.DividerCell;
import cn.gen.gsv2.views.InputCell;
import cn.gen.gsv2.views.SwitchCell;

import static android.text.InputType.TYPE_TEXT_VARIATION_NORMAL;
import static android.text.InputType.TYPE_TEXT_VARIATION_PASSWORD;
import static android.text.InputType.TYPE_TEXT_VARIATION_VISIBLE_PASSWORD;

/**
 * A simple {@link Fragment} subclass.
 */
public class SettingsController extends Controller implements View.OnClickListener,
        InputCell.OnTextChanged, CheckCell.OnChecked, SwitchCell.OnSwitchChanged {

    Settings settings;
    ListView listView;
    BaseAdapter adapter;
    OptionsPickerView optionsView;
    ArrowCell selectedCell;
    Shop shop;

    public void setSettings(Settings settings) {
        this.settings = settings;
    }

    public void setShop(Shop shop) {
        this.shop = shop;
    }

    public SettingsController() {
        // Required empty public constructor
    }

    @Override
    protected void initialize(Context context) {
        super.initialize(context);
    }

    public void showRightItems(Context context) {
        setRightItems(new NavigationItem(ActivityCompat.getDrawable(context, R.drawable.home), new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ((MainActivity) Activity.current()).setNavItem(R.id.library);
            }
        }));
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.controller_settings, container, false);
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
        listView.setPadding(0, H.dip2px(getContext(), 14), 0, H.dip2px(getContext(), 14));
        adapter = new CacheAdapter(getContext()) {
            @Override
            public int getCount() {
                return settings.getItemsCount();
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
                Settings.SettingItem item = settings.getItem(position);
                int type = item.getType();
                switch (type) {
                    case 1: {
                        String identifier = "OptionCell";
                        ArrowCell cell = (ArrowCell)popWithIdentifier(identifier);
                        if (cell == null) {
                            cell = new ArrowCell(getContext(), identifier);
                            cell.setOnClickListener(SettingsController.this);
                        }
                        cell.getTitleView().setText(item.getName());
                        cell.setData(item);
                        try {
                            ArrayList<String> list = new ArrayList<>();
                            Array ops = (Array)item.getParams();
                            for (Object op : ops) {
                                list.add((String) op);
                            }
                            cell.setOptions(list);
                            Object tar = (item.getValue() == null ? item.getDefaultValue() : item.getValue());
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
                            cell.setOnTextChanged(SettingsController.this);
                        }
                        cell.getTitleView().setText(item.getName());
                        cell.setData(item);
                        try {
                            cell.getEditText().setText((String)(item.getValue() == null ? item.getDefaultValue() : item.getValue()));
                        }catch (Exception e) {
                            e.printStackTrace();
                        }
                        if (type == 5) {
                            cell.getEditText().setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD);
                        }else
                            cell.getEditText().setInputType(InputType.TYPE_CLASS_TEXT);
                        return cell;
                    }
                    case 3: {
                        String identifier = "CheckCell";
                        CheckCell cell = (CheckCell)popWithIdentifier(identifier);
                        if (cell == null) {
                            cell = new CheckCell(getContext(), identifier);
                            cell.setOnChecked(SettingsController.this);
                        }
                        cell.getTitleView().setText(item.getName());
                        cell.setData(item);
                        try {
                            cell.getCheckBox().setChecked(item.isChecked());
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
                            cell.setOnSwitchChanged(SettingsController.this);
                        }
                        cell.getTitleView().setText(item.getName());
                        cell.setData(item);
                        try {
                            cell.getSwitch().setChecked(item.isChecked());
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
                        cell.setTitle(item.getName());
                        return cell;
                    }
                    case 7: {
                        String identifier = "ButtonCell";
                        ArrowCell cell = (ArrowCell)popWithIdentifier(identifier);
                        if (cell == null) {
                            cell = new ArrowCell(getContext(), identifier);
                            cell.setOnClickListener(SettingsController.this);
                        }
                        cell.setData(item);
                        cell.getTitleView().setText(item.getName());
                        cell.getLabelView().setText("");
                        return cell;
                    }
                }
                return null;
            }
        };
        listView.setAdapter(adapter);
    }

    Callback webViewCallback;
    Callback openWebViewListener = new Callback(true) {
        @Override
        public Object run(Object... args) {
            String url = (String)args[0];
            String name = (String)args[1];
            webViewCallback = (Callback) args[2];
            WebViewController ctrl = Controller.instantiate(getContext(), WebViewController.class);
            if (name != null) {
                ctrl.setTitle(name);
            }else {
                ctrl.setTitle("WebView");
            }
            ctrl.setUrl(url);
            ctrl.setOnComplete(new WebViewController.OnCompleteListener() {
                @Override
                public void onComplete(WebViewController webViewController, String cookies) {
                    webViewCallback.invoke(cookies);
                    webViewCallback = null;
                }
            });
            H.navC(SettingsController.this).push(ctrl, true);
            return null;
        }
    };

    @Override
    protected void onViewDidAppear() {
        super.onViewDidAppear();

        NotificationCenter.getInstance().listen("OPEN_WEB_VIEW", openWebViewListener);
    }

    @Override
    protected void onViewWillDisappear() {
        super.onViewWillDisappear();
        NotificationCenter.getInstance().remove("OPEN_WEB_VIEW", openWebViewListener);

        settings.save();
        if (shop.getIdentifier().equals(Shop.getCurrentShop().getIdentifier())) {
            LibraryController.setWillReload();
        }
    }

    @Override
    public void onClick(View v) {
        ArrowCell cell = (ArrowCell)v;
        Settings.SettingItem item = (Settings.SettingItem)cell.getData();
        switch (item.getType()) {
            case Settings.SettingItem.TYPE_OPTION: {
                selectedCell = cell;
                optionsView.setPicker(cell.getOptions());
                optionsView.setSelectOptions(cell.getSelected());
                optionsView.show();
                break;
            }
            case Settings.SettingItem.TYPE_BUTTON: {
                Callback callback = (Callback)item.getParams();
                callback.invoke();
                break;
            }
        }
    }

    @Override
    public void textChanged(InputCell cell, String newText) {
        Settings.SettingItem item = (Settings.SettingItem)cell.getData();
        item.setValue(newText);
    }


    @Override
    public void checked(CheckCell cell, boolean checked) {
        Settings.SettingItem item = (Settings.SettingItem)cell.getData();
        item.setValue(checked);
    }

    @Override
    public void onSwitch(SwitchCell cell, boolean on) {
        Settings.SettingItem item = (Settings.SettingItem)cell.getData();
        item.setValue(on);
    }
}
