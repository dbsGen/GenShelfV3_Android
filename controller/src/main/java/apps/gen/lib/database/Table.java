package apps.gen.lib.database;

import android.app.Application;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.os.Environment;
import android.os.Handler;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Field;
import java.sql.SQLDataException;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

import apps.gen.lib.Activity;
import apps.gen.lib.utils.H;

/**
 * Created by gen on 16/5/11.
 */
public class Table <T extends Model> implements Model.onEventListener {
    static Handler handler = new Handler();

    private static final String TableListFile = "table.ls";

    static ArrayList<Table> tables = null;
    static HashMap<Class,Table> tableIndexes = new HashMap();
    static synchronized ArrayList<Table> tables() {
        if (tables == null) {
            File file=new File(Activity.current().getFilesDir() + "/" + TableListFile);
            if (file.exists()) {
                try {
                    FileInputStream inputStream = new FileInputStream(file);
                    int len = (int)file.length();
                    byte[] bytes = new byte[len];
                    inputStream.read(bytes, 0, len);
                    String str = new String(bytes);
                    String[] arr = str.split("\n");

                    ArrayList<Table> tis = new ArrayList<Table>();
                    for (String line : arr) {
                        String[] se = line.split(" ");
                        if (se.length != 3) {
                            Table t = new Table();
                            t.modelClass = Class.forName(se[0]);
                            t.tableName = se[1];
                            t.version = Integer.parseInt(se[2]);
                            tis.add(t);
                            tableIndexes.put(t.modelClass, t);
                        }
                    }
                    inputStream.close();
                    tables = tis;
                } catch (IOException | ClassNotFoundException e) {
                    e.printStackTrace();
                }
            }else {
                tables = new ArrayList<>();
            }
        }
        return tables;
    }


    static synchronized void updateTableInfos() {
        if (tables() != null) {
            File file=new File(Activity.current().getFilesDir() + "/" + TableListFile);
            if (file.exists()) {
                file.delete();
            }
            try {
                FileOutputStream output = new FileOutputStream(file);
                for (Table ti : tables()) {
                    String str = String.format("%s %s %d", ti.modelClass.getName(), ti.tableName, ti.version);
                    output.write(str.getBytes());
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    static boolean willSave = false;
    static synchronized void postUpdate() {
        if (willSave) return;
        willSave = true;
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                updateTableInfos();
                willSave = false;
            }
        }, 0);
    }

    private Class<T> modelClass;
    private String tableName;
    private int version;

    public String getTableName() {
        return tableName;
    }

    public int getVersion() {
        return version;
    }

    private static Table makeTable(Class clz) {
        Table table = new Table();
        table.modelClass = clz;
        String name = clz.getName();
        int version = 0;
        Property p = (Property) clz.getAnnotation(Property.class);
        if (p != null) {
            String v = p.value();
            if (v.length() > 0)
                name = v;
            version = p.version();
        }
        table.tableName = name.trim();
        table.version = version;
        return table;
    }

    Table() {
    }

    public static <MT extends Model> Table<MT> from(Class<MT> clz) {
        Table<MT> table;
        if (tableIndexes.containsKey(clz)) {
            table = tableIndexes.get(clz);
        }else {
            table = makeTable(clz);
        }
        if (!table.setupd) table.setup();
        return table;
    }

    public static class FieldInfo {
        String name;
        String type;
        String limit;
        boolean index;
        boolean primary;
        Field field;
        public String getName() {
            return name;
        }
        public String getType() {
            return type;
        }
        public String getLimit() {
            return limit;
        }
        public boolean isIndex() {
            return index;
        }
        public boolean isPrimary() {
            return primary;
        }
    }

    static boolean isTypeOf(Class clz, Class sup) {
        Class sp = clz;
        while (sp != null) {
            if (sup.equals(sp)) {
                return true;
            }
            sp = sp.getSuperclass();
        }
        return false;
    }

    static String sqlTypeFromType(Class type) {
        if (type.equals(Integer.class) ||
                type.equals(Long.class) ||
                type.equals(int.class) ||
                type.equals(long.class)) {
            return "INTEGER";
        }else if (type.equals(Float.class) ||
                type.equals(Double.class) ||
                type.equals(float.class) ||
                type.equals(double.class)) {
            return "REAL";
        }else if (type.equals(String.class)) {
            return "TEXT";
        }else if (isTypeOf(type, Date.class) ||
                type.equals(Boolean.class) ||
                type.equals(boolean.class)) {
            return "NUMERIC";
        }else {
            return "NONE";
        }
    }

    interface SQLHandle {
        void run(SQLiteDatabase db);
    }

    static private final String dataPath = "datas.db";

    static private ArrayList<SQLHandle> sqlQueue = new ArrayList<>();
    static void exec(SQLHandle handle) {
        SQLiteDatabase db = Activity.current().openOrCreateDatabase(dataPath, Context.MODE_PRIVATE, null);
        if (sqlQueue.size() > 0) {
            for (SQLHandle h : sqlQueue) {
                h.run(db);
            }
            sqlQueue.clear();
            willExecQueue = false;
        }
        handle.run(db);
        db.close();
    }
    static private boolean willExecQueue = false;
    static void queueExec(SQLHandle h) {
        sqlQueue.add(h);
        if (!willExecQueue) {
            willExecQueue = true;
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    if (willExecQueue) {
                        SQLiteDatabase db = Activity.current().openOrCreateDatabase(dataPath, Context.MODE_PRIVATE, null);
                        for (SQLHandle handle :
                                sqlQueue) {
                            handle.run(db);
                        }
                        sqlQueue.clear();
                        willExecQueue = false;
                        db.close();
                    }
                }
            }, 0);
        }
    }

    FieldInfo[] fields;
    void progressFields() throws SQLDataException {
        Class cls = modelClass;
        ArrayList<FieldInfo> fieldInfos = new ArrayList<>();
        while (true) {
            Field[] fields = cls.getDeclaredFields();
            boolean hasPrimary = false;
            for (Field field : fields) {
                Property p = field.getAnnotation(Property.class);
                if (p != null) {
                    FieldInfo fi = new FieldInfo();
                    fi.name = field.getName();
                    if (p.value().length() > 0) {
                        fi.name = p.value();
                    }
                    fi.type = p.type();
                    if (fi.type.length() <= 0) {
                        fi.type = sqlTypeFromType(field.getType());
                    }
                    fi.index = p.index();
                    if (field.getAnnotation(PrimaryKey.class) != null) {
                        fi.primary = true;
                        if (hasPrimary)
                        {
                            throw new SQLDataException("There would be only one primary key in one table.");
                        }
                        hasPrimary = true;
                        fi.limit = "AUTOINCREMENT";
                        primaryKey = fi;
                    }else {
                        fi.primary = false;
                        fi.limit = p.limit();
                    }
                    field.setAccessible(true);
                    fi.field = field;
                    fieldInfos.add(fi);
                }
            }

            if (cls.equals(Model.class)) break;
            cls = cls.getSuperclass();
        }
        FieldInfo[] fs = new FieldInfo[fieldInfos.size()];
        this.fields = fieldInfos.toArray(fs);
    }
    FieldInfo primaryKey = null;
    public FieldInfo[] getFields() {
        if (fields == null) {
            try {
                progressFields();
            } catch (SQLDataException e) {
                e.printStackTrace();
            }
        }
        return fields;
    }

    public FieldInfo getPrimaryKey() {
        if (primaryKey == null) {
            try {
                progressFields();
            } catch (SQLDataException e) {
                e.printStackTrace();
            }
        }
        return primaryKey;
    }

    void create() {
        if (!setupd) return;
        FieldInfo[] fs = getFields();
        ArrayList<String> sqlIndexes = new ArrayList<>();

        String sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
        for (int i = 0, t = fs.length; i < t; i++) {
            FieldInfo fi = fs[i];
            sql += fi.getName() + " " + fi.getType();
            if (fi.isPrimary()) {
                sql += " PRIMARY KEY ";
            }
            sql += fi.getLimit();
            if (fi.isIndex()) {
                sqlIndexes.add(String.format("CREATE INDEX IF NOT EXISTS %s_INDEX ON %s(%s)", fi.getName(), tableName, fi.getName()));
            }
            if (i != t - 1) {
                sql += ",";
            }
        }
        sql += ");";
        for (String index :
                sqlIndexes) {
            sql += index + ";";
        }

        final String sqlSen = sql;
        exec(new SQLHandle() {
            @Override
            public void run(SQLiteDatabase db) {
                db.execSQL(sqlSen);
            }
        });
    }
    public void drop() {
        final String sqlSen = "DROP TABLE IF EXISTS " + tableName;
        queueExec(new SQLHandle() {
            @Override
            public void run(SQLiteDatabase db) {
                db.execSQL(sqlSen);
            }
        });
    }

    private boolean setupd = false;

    void setup() {
        if (setupd) return;
        setupd = true;
        if (!tableIndexes.containsKey(modelClass)) {
            create();

            tables().add(this);
            tableIndexes.put(modelClass, this);
        }else {
            Property p = modelClass.getAnnotation(Property.class);
            if (p.version() > version) {
                drop();
                create();
                version = p.version();
            }
        }
        postUpdate();
    }

    public T newModel() {
        try {
            T model =  modelClass.newInstance();
            model.setListener(this);
            return model;
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
        return null;
    }

    public Query<T> query() {
        return new Query<T>(this);
    }

    final int maxCache = 50;
    private ArrayList caches = new ArrayList();
    private HashMap<Integer, T> cachesIndex = new HashMap<>();
    void pushCache(T model) {
        while (caches.size() > maxCache) {
            caches.remove(0);
        }
        caches.add(model);
        if (model.id >= 0)
        cachesIndex.put(model.id, model);
    }
    T cachedWithID(int id) {
        if (cachesIndex.containsKey(id)) {
            T model = cachesIndex.get(id);
            renew(model);
            return model;
        }
        return null;
    }
    private void renew(Model model) {
        if (caches.contains(model)) {
            caches.remove(model);
            caches.add(model);
        }
    }

    @Override
    public void onCreated(Model model) {
        if (caches.contains(model)) {
            cachesIndex.put(model.getId(), (T) model);
            renew(model);
        }
    }

    public T get(int id) {
        T model = cachedWithID(id);
        if (model != null) {
            return model;
        }else {
            return (T) query().equal(primaryKey.getName(), id).first();
        }
    }
}
