package com.hiar.render.classes;

import android.support.annotation.NonNull;

import com.hiar.render.HiRender;
import com.hiar.render.NativeClass;

import java.util.Collection;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

/**
 * Created by mac on 2017/6/15.
 */


@NativeClass("hicore::Array")
public class Array extends HiRender.HiInstance implements Collection {
    private static HiRender.HiClass<Array> _class;
    static {
        _class = HiRender.find(Array.class);
    }

    public static void register(){}

    private class Iterator implements java.util.Iterator {

        private int index;

        public Iterator(int index) {
            this.index = index;
        }

        @Override
        public boolean hasNext() {
            return index < size();
        }

        @Override
        public Object next() {
            return get(index++);
        }

        @Override
        public void remove() {
            Array.this.remove(index);
        }

        public Object current() {
            return get(index);
        }
    }

    public Array() {

    }
    public Array(boolean init) {
        if (init) initialize();
    }

    public Object get(int idx) {
        return call("get", idx);
    }

    public void set(int idx, Object element) {
        call("set", idx, element);
    }

    public void remove(int idx) {
        call("erase", idx);
    }

    @Override
    public int size() {
        return (int)(long)call("size");
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public boolean contains(Object o) {
        return (long)call("find", o) >= 0;
    }

    @NonNull
    @Override
    public java.util.Iterator iterator() {
        return new Iterator(0);
    }

    @NonNull
    @Override
    public Object[] toArray() {
        int size = size();
        Object[] objs = new Object[size];
        for (int i = 0; i < size; ++i) {
            objs[i] = get(i);
        }
        return objs;
    }

    @Override
    public boolean add(Object o) {
        call("push_back", o);
        return true;
    }

    @Override
    public boolean remove(Object o) {
        int size = size();
        for (int i = 0; i < size; ++i) {
            if (o.equals(get(i))) {
                remove(i);
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean addAll(@NonNull Collection c) {
        for (Object obj : c) {
            add(obj);
        }
        return true;
    }

    @Override
    public void clear() {
        call("clear");
    }

    @Override
    public boolean retainAll(@NonNull Collection c) {
        Iterator it = (Iterator) iterator();
        while (it.hasNext()) {
            Object obj = it.current();
            if (!c.contains(obj)) {
                it.remove();
            }else {
                it.next();
            }
        }
        return true;
    }

    @Override
    public boolean removeAll(@NonNull Collection c) {
        Iterator it = (Iterator) iterator();
        while (it.hasNext()) {
            Object obj = it.current();
            if (c.contains(obj)) {
                it.remove();
            }else {
                it.next();
            }
        }
        return true;
    }

    @Override
    public boolean containsAll(@NonNull Collection c) {
        Iterator it = (Iterator) iterator();
        while (it.hasNext()) {
            Object obj = it.current();
            if (!c.contains(obj)) {
                return false;
            }
        }
        return true;
    }

    @NonNull
    @Override
    public Object[] toArray(@NonNull Object[] a) {
        int size = size();
        for (int i = 0; i < size; ++i) {
            a[i] = get(i);
        }
        return a;
    }
}
