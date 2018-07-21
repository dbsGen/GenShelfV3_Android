package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;

/**
 * Created by gen on 02/06/2017.
 */

@NativeClass("nl::Settings")
public class Settings extends Helper.GInstance {

    private static Helper.GClass<Settings> _class;
    @NativeClass("nl::SettingItem")
    public static class SettingItem extends Helper.GInstance {
        static Helper.GClass<Settings> _class;

        public static final int TYPE_OPTION = 1,
                TYPE_INPUT = 2,
                TYPE_MARK = 3,
                TYPE_SWITCH = 4,
                TYPE_PASSWORD = 5,
                TYPE_DIVIDER = 6,
                TYPE_BUTTON = 7;

        public SettingItem(){}
        public SettingItem(boolean init) {
            if (init) {
                initialize();
            }
        }

        public String getName() {
            return (String)call("getName");
        }
        public void setName(String name) {
            call("setName", name);
        }

        public int getType() {
            return (int)call("getType");
        }
        public void setType(int type) {
            call("setType", type);
        }

        public Object getParams() {
            return call("getParams");
        }
        public void setParams(Object p) {
            call("setParams", p);
        }

        public Object getDefaultValue() {
            return call("getDefaultValue");
        }
        public void setDefaultValue(Object dv) {
            call("setDefaultValue", dv);
        }

        public Object getValue() {
            return call("getValue");
        }

        public void setValue(Object val) {
            call("setValue", val);
        }
        public boolean isChecked() {
            Object obj = getValue() == null ? getDefaultValue() : getValue();
            if (obj == null) {
                return false;
            }
            return (boolean)obj;
        }
    }
    static {
        _class = Helper.find(Settings.class);
        SettingItem._class = Helper.find(Settings.SettingItem.class);
    }

    public static void rigester() {

    }

    public int getItemsCount() {
        return (int)call("getItemsCount");
    }

    public SettingItem getItem(int idx) {
        return (SettingItem)call("getItem", idx);
    }

    public void save() {
        call("save");
    }
}
