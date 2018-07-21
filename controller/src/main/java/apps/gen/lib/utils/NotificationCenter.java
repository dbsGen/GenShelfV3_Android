package apps.gen.lib.utils;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by gen on 16/4/24.
 */
public class NotificationCenter {
    private static NotificationCenter instance;
    public static synchronized NotificationCenter instance() {
        if (instance == null)
            instance = new NotificationCenter();
        return instance;
    }
    public static class Notification {
        private String mName;
        private Object mPostObject;
        private Object mListenObject;
        public String getName() {
            return mName;
        }

        public Object getPostObject() {
            return mPostObject;
        }

        public Object getListenObject() {
            return mListenObject;
        }

        public Notification(String name, Object listenObject, Object postObject) {
            mName = name;
            mListenObject = listenObject;
            mPostObject = postObject;
        }
    }
    class ListenerItem {
        private Runnable mRunnable;
        private Object mObject;

        public Runnable getRunnable() {
            return mRunnable;
        }

        public Object getObject() {
            return mObject;
        }

        public ListenerItem(Runnable runnable, Object object) {
            mRunnable = runnable;
            mObject = object;
        }
    }
    public interface Runnable {
        void run(Notification notification);
    }
    HashMap<String, ArrayList<ListenerItem>> listenersMap = new HashMap<String, ArrayList<ListenerItem>>();


    ArrayList<ListenerItem> getListeners(String name) {
        return listenersMap.containsKey(name) ? listenersMap.get(name) : null;
    }
    ArrayList<ListenerItem> getOrCreateListeners(String name) {
        if (listenersMap.containsKey(name)) {
            return listenersMap.get(name);
        }else {
            ArrayList<ListenerItem> listeners = new ArrayList<>();
            listenersMap.put(name, listeners);
            return listeners;
        }
    }
    public void addListener(String name, Runnable runnable) {addListener(name, runnable, null);}
    public void addListener(String name , Runnable runnable, Object object) {
        ArrayList<ListenerItem> listeners = getOrCreateListeners(name);
        listeners.add(new ListenerItem(runnable, object));
    }
    public void removeListener(String name, Runnable runnable) {removeListener(name, runnable, null);}
    public void removeListener(String name, Runnable runnable, Object object) {
        ArrayList<ListenerItem> listeners = getListeners(name);
        if (listeners != null) {
            ArrayList<ListenerItem> cp_ls = (ArrayList<ListenerItem>)listeners.clone();
            for (ListenerItem item :
                    cp_ls) {
                boolean checkedRunnable = runnable == null || runnable == item.getRunnable();
                boolean checkedObject = object == null || object == item.getObject();
                if (checkedRunnable && checkedObject)
                    listeners.remove(item);
            }
        }
    }
    public void postNotification(String name, Object object) {
        ArrayList<ListenerItem> listeners = getListeners(name);
        if (listeners != null) {
            for (ListenerItem item: listeners) {
                item.getRunnable().run(new Notification(name, item.getObject(), object));
            }
        }
    }
}
