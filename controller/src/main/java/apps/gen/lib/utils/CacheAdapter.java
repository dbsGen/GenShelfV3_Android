package apps.gen.lib.utils;

import android.content.Context;
import android.support.v4.app.NavUtils;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.RelativeLayout;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.SynchronousQueue;

import apps.gen.lib.views.ListCell;

/**
 * Created by gen on 16/5/2.
 */
public abstract class CacheAdapter extends BaseAdapter {
    Map<String, Queue<ListCell>> viewCache = new HashMap<>();
    Map<Integer, ListCell> cells = new HashMap<>();
    ListCell _template;

    private Context context;

    public CacheAdapter(Context context) {
        this.context = context;
    }

    private class ListContainer extends RelativeLayout {
        private View contentView;

        public ListContainer(Context context) {
            super(context);
        }

        public ListContainer(Context context, AttributeSet attrs) {
            super(context, attrs);
        }

        public ListContainer(Context context, AttributeSet attrs, int defStyleAttr) {
            super(context, attrs, defStyleAttr);
        }

        public void setContentView(View view) {
            if (view == contentView) {
                return;
            }
            if (contentView != null) {
                removeView(contentView);
            }
            if (view.getParent() != null) {
                ((ViewGroup)view.getParent()).removeView(view);
            }
            addView(view);
            contentView = view;
        }

        public View getContentView() {
            return contentView;
        }
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ListContainer container = (ListContainer)convertView;
        if (container == null) {
            container = new ListContainer(context);
        }
        _template = (ListCell) container.getContentView();
        ListCell res = cellView(position);
        cells.put(position, res);
        if (_template != null && !res.equals(_template)) {
            pushCache(_template);
        }
        container.setContentView(res);
        return container;
    }

    public ListCell findCell(int position) {
        if (cells.containsKey(position)) {
            return cells.get(position);
        }else {
            return null;
        }
    }

    void pushCache(ListCell cell) {
        Queue<ListCell> queue = null;
        if (!viewCache.containsKey(cell.getIdentifier())) {
            queue = new LinkedBlockingQueue<>();
            viewCache.put(cell.getIdentifier(), queue);
        }else {
            queue = viewCache.get(cell.getIdentifier());
        }
        queue.add(cell);
    }

    protected ListCell popWithIdentifier(String identifier) {
        if (_template != null) {
            if (_template.getIdentifier().equals(identifier)) {
                ListCell ret = _template;
                _template = null;
                return ret;
            }
        }
        if (viewCache.containsKey(identifier)) {
            Queue<ListCell> queue = viewCache.get(identifier);
            if (queue.size() > 0)
                return queue.poll();
        }
        return null;
    }

    public abstract ListCell cellView(int position);
}
