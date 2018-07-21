package cn.gen.gsv2.models;

import com.gr.Helper;
import com.gr.NativeClass;
import com.gr.classes.Array;
import com.gr.classes.Renderer;

import java.util.Objects;

/**
 * Created by mac on 2017/5/27.
 */


@NativeClass("nl::Shop")
public class Shop extends Helper.GInstance {
    private static Helper.GClass<Shop> _class;

    static {
        _class = Helper.find(Shop.class);
    }

    public Shop(){
    }

    public Shop(boolean init) {
        if (init) {
            initialize();
        }
    }

    public static Helper.GClass<Shop> getNativeClass() {
        return _class;
    }

    public static Array getLocalShops() {
        return (Array) getNativeClass().call("getLocalShops");
    }

    public static Array parseShops(String path) {
        return (Array) getNativeClass().call("parseShops", path);
    }

    public String getIdentifier() {
        return (String)call("getIdentifier");
    }
    public void setIdentifier(String identifier) {
        call("setIdentifier", identifier);
    }

    public String getName() {
        return (String)call("getName");
    }

    public String getHost() {
        return (String)call("getHost");
    }

    public String getIcon() {
        return (String)call("getIcon");
    }

    public int getVersion() {
        return (int)call("getVersion");
    }
    public void setVersion(int version) {
        call("setVersion", version);
    }

    public String getDescription() {
        return (String)call("getDescription");
    }
    public boolean isLocalize() {
        return (boolean)call("isLocalize");
    }
    public void install() {
        call("install");
    }
    public void remove() {
        call("remove");
    }

    public Settings getSettings() {
        Settings.rigester();
        return (Settings)call("getSettings");
    }

    static public Shop getCurrentShop() {
        return (Shop)_class.call("getCurrentShop");
    }
    static public void setCurrentShop(Shop shop) {
        _class.call("setCurrentShop", shop);
    }

    public void setupLibrary(Library library) {
        call("setupLibrary", library);
    }
    public void setupReader(Reader reader, int reader_script) {
        call("setupReader", reader, reader_script);
    }

    public int collect(Book book, Chapter chapter) {
        return (int)call("collect", book, chapter);
    }
    public int like(Book book) {
        return (int)call("like", book);
    }
    public static Shop find(String id) {
        return (Shop) _class.call("find", id);
    }

    public static int download(Book book, Chapter chapter) {
        return (int)_class.call("download", book, chapter);
    }

    public int getPackageVersion() {
        return (int)call("getPackageVersion");
    }
}
