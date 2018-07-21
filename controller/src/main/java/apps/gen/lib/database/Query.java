package apps.gen.lib.database;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import java.lang.reflect.Field;
import java.util.ArrayList;

import apps.gen.lib.utils.H;

/**
 * Created by gen on 16/5/15.
 */
public class Query<T extends Model> {

    ArrayList<String> sqlElements = new ArrayList<>();
    ArrayList<String> sqlObjects = new ArrayList<>();
    String sqlSentence = "";

    Query(Table<T> table) {
        this.table = table;
    }

    Table<T> table;
    public Table<?> getTable() {
        return table;
    }

    private void pushElement(String sql) {
        sqlElements.add(sql);
    }

    void insertAction(String field, Object val, String operator) {
        sqlSentence += String.format(" %s %s ? ", field, operator);
        sqlObjects.add(val.toString());
    }
    public Query equal(String field, Object val) {
        insertAction(field, val, "=");
        return this;
    }
    public Query nEqual(String field, Object val) {
        insertAction(field, val, "!=");
        return this;
    }
    public Query or() {
        sqlSentence += " or ";
        return this;
    }
    public Query and() {
        sqlSentence += " and ";
        return this;
    }
    public Query clear() {
        sqlSentence = "";
        sqlObjects.clear();
        return this;
    }
    public Query greater(String field, Object val) {
        insertAction(field, val, ">");
        return this;
    }
    public Query nGreater(String field, Object val) {
        insertAction(field, val, "<=");
        return this;
    }
    public Query less(String field, Object val) {
        insertAction(field, val, "<");
        return this;
    }
    public Query nLess(String field, Object val) {
        insertAction(field, val, ">=");
        return this;
    }
    public Query link(String field, String val) {
        sqlSentence += String.format(" %s LIKE '%s' ", field, val);
        return this;
    }
    public Query in(String field, Object[] vals) {
        sqlSentence += String.format(" %s IN (", field);
        for (int i = 0, t = vals.length; i < t; i++) {
            sqlSentence += "?";
            if (i != vals.length - 1) {
                sqlSentence += ",";
            }
            sqlObjects.add(vals[i].toString());
        }
        sqlSentence += ") ";
        return this;
    }
    public Query nIn(String field, Object[] vals) {
        sqlSentence += String.format(" %s NOT IN (", field);
        for (int i = 0, t = vals.length; i < t; i++) {
            sqlSentence += "?";
            if (i != vals.length - 1) {
                sqlSentence += ",";
            }
            sqlObjects.add(vals[i].toString());
        }
        sqlSentence += ") ";
        return this;
    }
    public Query between(String field, Object le, Object gr) {
        sqlSentence += String.format(" %s BETWEEN ? AND ?", field);
        sqlObjects.add(le.toString());
        sqlObjects.add(gr.toString());
        return this;
    }

    private int idIndex = 0;
    public T[] commit() {
        final ArrayList<T> models = new ArrayList<>();
        Table.exec(new Table.SQLHandle() {
            @Override
            public void run(SQLiteDatabase db) {
                String sql = "SELECT ";
                for (int i = 0, t = table.getFields().length; i < t; i++) {
                    Table.FieldInfo fieldInfo = table.getFields()[i];
                    sql += fieldInfo.getName();
                    if (i != t - 1) {
                        sql += ",";
                    }
                    if (fieldInfo.isPrimary()) {
                        idIndex = i;
                    }
                }
                sql += " FROM " + table.getTableName() + " WHERE ";
                sql += sqlSentence;
                String[] strs = new String[sqlObjects.size()];
                Cursor cursor = db.rawQuery(sql, sqlObjects.toArray(strs));

                while (cursor.moveToNext()) {
                    int id = cursor.getInt(idIndex);
                    T model = table.cachedWithID(id);
                    if (model == null) {
                        model = table.newModel();
                        table.pushCache(model);
                    }
                    for (int i = 0, t = table.getFields().length; i < t; i++) {
                        Table.FieldInfo fieldInfo = table.getFields()[i];
                        Field field = fieldInfo.field;
                        try {
                            switch (cursor.getType(i)) {
                                case Cursor.FIELD_TYPE_FLOAT:
                                    field.set(model, cursor.getFloat(i));
                                    break;
                                case Cursor.FIELD_TYPE_INTEGER:
                                    field.set(model, cursor.getInt(i));
                                    break;
                                case Cursor.FIELD_TYPE_BLOB:
                                    field.set(model, cursor.getBlob(i));
                                    break;
                                case Cursor.FIELD_TYPE_STRING:
                                    field.set(model, cursor.getString(i));
                                    break;
                                default:
                                    break;
                            }
                        } catch (IllegalAccessException e) {
                            e.printStackTrace();
                            H.i("Can not set %s", fieldInfo.getName());
                        }
                    }
                    models.add(model);
                }
            }
        });
        T[] res = (T[]) new Model[models.size()];
        return models.toArray(res);
    }

    public T first() {
        T[] res = commit();
        if (res.length > 0) {
            return res[0];
        }else {
            return null;
        }
    }
}
