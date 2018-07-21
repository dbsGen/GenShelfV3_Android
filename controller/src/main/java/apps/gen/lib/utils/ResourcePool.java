package apps.gen.lib.utils;

import android.util.Log;

import java.util.ArrayList;

/**
 * Created by mac on 2017/8/13.
 */

public class ResourcePool {
    public interface OnReleaseListener {
        void onRelease();
    }

    private static ArrayList<ResourcePool> resourcePools = new ArrayList<>();
    static {
        resourcePools.add(new ResourcePool());
    }

    public static void push(ResourcePool pool) {
        if (pool != null && !resourcePools.contains(pool)) {
            resourcePools.add(pool);
        }
    }

    public static ResourcePool current() {
        return resourcePools.get(resourcePools.size()-1);
    }

    public static void pop(ResourcePool pool) {
        if (pool != null && resourcePools.contains(pool)) {
            pool.release();
            resourcePools.remove(pool);
        }
    }

    private ArrayList<OnReleaseListener> listeners = new ArrayList<>();

    private void release() {
        for (OnReleaseListener listener : listeners) {
            listener.onRelease();
        }
        Log.i("count ", "" + count);
        listeners.clear();
    }

    public void addRelease(OnReleaseListener listener) {
        listeners.add(listener);
    }

    int count = 0;
    public void add() {
        count ++;
    }
    public void minus() {
        count--;
    }
}
