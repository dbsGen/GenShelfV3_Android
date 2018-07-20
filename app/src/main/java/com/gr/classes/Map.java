package com.gr.classes;

import android.support.annotation.NonNull;

import com.gr.Helper;
import com.gr.NativeClass;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Dictionary;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by mac on 2017/6/15.
 */

@NativeClass("gcore::_Map")
public class Map extends Helper.GInstance implements java.util.Map<String, Object> {
    private static Helper.GClass<Map> _class;
    static {
        _class = Helper.find(Map.class);
    }

    public Map(){

    }
    public Map(boolean init) {
        if (init) initialize();
    }

    public static void register() {
    }

    @Override
    public int size() {
        return (int)(long)call("size");
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    public Array<String> keys() {
        return (Array<String>)call("keys");
    }

    @Override
    public boolean containsKey(Object key) {
        return keys().contains(key);
    }

    @Override
    public boolean containsValue(Object value) {
        for (String k : keys()) {
            if (get(k).equals(value)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public Object get(Object key) {
        return call("get", key);
    }

    @Override
    public Object put(String key, Object value) {
        return call("set", key, value);
    }

    @Override
    public Object remove(Object key) {
        Object ret = get(key);
        if (ret != null) {
            call("erase", key);
        }
        return ret;
    }

    @Override
    public void putAll(@NonNull java.util.Map m) {
        Set<Entry> set = m.entrySet();
        for (Entry e : set) {
            put((String) e.getKey(), e.getValue());
        }
    }

    @Override
    public void clear() {
        call("clear");
    }

    @NonNull
    @Override
    public Set keySet() {
        HashSet rets = new HashSet();
        for (Object k : keys()) {
            rets.add(k);
        }
        return rets;
    }

    @NonNull
    @Override
    public Collection values() {
        ArrayList rets = new ArrayList();
        for (Object k : keys()) {
            rets.add(get(k));
        }
        return rets;
    }

    class MapEntry implements Entry {

        Object key;

        public MapEntry(Object k) {
            key = k;
        }

        @Override
        public Object getKey() {
            return key;
        }

        @Override
        public Object getValue() {
            return get(key);
        }

        @Override
        public Object setValue(Object value) {
            Object old = get(key);
            put((String) key, value);
            return old;
        }
    }

    @NonNull
    @Override
    public Set<Entry<String, Object> > entrySet() {
        HashSet<Entry<String, Object> > rets = new HashSet<>();
        for (Object k : keys()) {
            rets.add(new MapEntry(k));
        }
        return rets;
    }
}
