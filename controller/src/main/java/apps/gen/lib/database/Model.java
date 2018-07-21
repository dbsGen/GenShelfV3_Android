package apps.gen.lib.database;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Objects;

import apps.gen.lib.utils.H;

/**
 * Created by gen on 16/5/11.
 */
public class Model {
    public interface onEventListener {
        void onCreated(Model model);
    }

    private onEventListener listener;

    public onEventListener getListener() {
        return listener;
    }

    public void setListener(onEventListener listener) {
        this.listener = listener;
    }

    private boolean saving = false;
    private boolean deleting = false;

    @PrimaryKey
    @Property("id")
    int id = -1;

    public int getId() {
        return id;
    }

    public Table getTable() {
        return Table.from(getClass());
    }

    public void save() {
        save(true);
    }

    public void save(boolean queue) {
        if (saving) return;
        saving = true;

        Table.SQLHandle handle = new Table.SQLHandle() {
            @Override
            public void run(SQLiteDatabase db) {
                Table table = getTable();
                if (id <= 0) {
                    String sql = "INSERT INTO " + table.getTableName() + " (";
                    String fields = "";
                    String values = "";
                    String primaryID = null;

                    ArrayList<Object> objects = new ArrayList<Object>();
                    for (int i = 0, t = table.fields.length; i < t; i++) {
                        try {
                            Table.FieldInfo fi = table.fields[i];
                            if (fi.isPrimary()) {
                                values += "NULL";
                                primaryID = fi.getName();
                            }else {
                                values += "?";
                                objects.add(fi.field.get(Model.this));
                            }
                            fields += fi.getName();
                            if (i != t - 1)  {
                                values += ",";
                                fields += ",";
                            }
                        } catch (IllegalAccessException e) {
                            e.printStackTrace();
                        }
                    }
                    sql += fields + ") VALUES (" + values + ")";
                    Object[] os = new Object[objects.size()];
                    db.execSQL(sql, objects.toArray(os));
                    H.i(db.getPath());
                    Cursor cursor = db.rawQuery(
                            String.format("SELECT %s FROM %s ORDER BY %s DESC limit 1;", primaryID, table.getTableName(), primaryID),
                            null
                    );
                    cursor.moveToFirst();
                    id = cursor.getInt(0);
                    if (listener!=null) {
                        listener.onCreated(Model.this);
                    }
                }else {
                    String sql = "UPDATE " + table.getTableName() + " SET ";

                    ArrayList<Object> objects = new ArrayList<Object>();
                    ArrayList<String> keys = new ArrayList<>();
                    String keyField = "id";
                    Object keyValue = null;
                    for (int i = 0, t = table.fields.length; i < t; i++) {
                        try {
                            Table.FieldInfo fi = table.fields[i];
                            if (!fi.isPrimary()) {
                                keys.add(fi.getName());
                                objects.add(fi.field.get(Model.this));
                            }else {
                                keyField = fi.getName();
                                keyValue = fi.field.get(Model.this);
                            }
                        } catch (IllegalAccessException e) {
                            e.printStackTrace();
                        }
                    }
                    int count = 0, total = keys.size();
                    Iterator<String> ik = keys.iterator();
                    while (ik.hasNext()) {
                        sql += String.format(" %s=?", ik.next());
                        if (++count < total) {
                            sql += ",";
                        }
                    }
                    objects.add(keyValue);
                    sql += String.format(" WHERE %s = ?", keyField);
                    db.execSQL(sql, objects.toArray());
                }
                saving = false;
            }
        };
        if (queue) {
            Table.queueExec(handle);
        }else {
            Table.exec(handle);
        }
    }

    public void delete() {
        delete(true);
    }

    public void delete(boolean queue) {
        if (deleting) return;
        deleting = true;

        Table.SQLHandle handle = new Table.SQLHandle() {
            @Override
            public void run(SQLiteDatabase db) {
                Table table = getTable();
                try {
                    db.execSQL(
                            String.format("DELETE FROM %s WHERE %s=?", table.getTableName(), table.getPrimaryKey().getName()),
                            new Object[]{table.getPrimaryKey().field.get(Model.this)}
                    );
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                }
                id = -1;
                deleting = false;
            }
        };
        if (queue) {
            Table.queueExec(handle);
        }else {
            Table.exec(handle);
        }
    }
}
