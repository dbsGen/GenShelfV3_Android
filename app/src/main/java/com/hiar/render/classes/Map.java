package com.hiar.render.classes;

import android.support.annotation.NonNull;

import com.hiar.render.HiRender;
import com.hiar.render.NativeClass;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Dictionary;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by mac on 2017/6/15.
 */

@NativeClass("hicore::Map")
public class Map extends HiRender.HiInstance implements java.util.Map {
    private static HiRender.HiClass<Map> _class;
    static {
        _class = HiRender.find(Map.class);
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

    public Array keys() {
        return (Array)call("keys");
    }

    @Override
    public boolean containsKey(Object key) {
        return keys().contains(key);
    }

    @Override
    public boolean containsValue(Object value) {
        for (Object k : keys()) {
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
    public Object put(Object key, Object value) {
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
            put(e.getKey(), e.getValue());
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
            put(key, value);
            return old;
        }
    }

    @NonNull
    @Override
    public Set<Entry> entrySet() {
        HashSet<Entry> rets = new HashSet<>();
        for (Object k : keys()) {
            rets.add(new MapEntry(k));
        }
        return rets;
    }
}
