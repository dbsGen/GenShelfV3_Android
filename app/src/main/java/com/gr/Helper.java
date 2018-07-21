package com.gr;

import android.animation.ObjectAnimator;
import android.util.Log;
import android.util.SizeF;

import com.gr.classes.Array;
import com.gr.classes.Map;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.Dictionary;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Hashtable;

/**
 * Created by gen on 16/9/6.
 */
public class Helper {
    static int toInt(Object obj) {
        if (Boolean.class.isInstance(obj)) {
            return (boolean)obj ? 1 : 0;
        }
        return (int)obj;
    }
    public static long toLong(Object obj) {
        return (long)obj;
    }
    public static float toFloat(Object obj) {
        return (float)obj;
    }
    public static double toDouble(Object obj) {
        return (double)obj;
    }
    public static boolean toBoolean(Object obj) {
        return (boolean)obj;
    }
    public static long toNative(Object obj) {
        return ((GInstance)obj).getNativePtr();
    }

    public static Object fromInt(int i) {
        return i;
    }
    public static Object fromLong(long l) {
        return l;
    }
    public static Object fromFloat(float f) {
        return f;
    }
    public static Object fromDouble(double d) {
        return d;
    }
    public static Object fromBoolean(boolean b) {return b;}
    public static Object fromNative(String cls, long n) {
        GInstance instance = null;
        if (classMap != null && classMap.containsKey(cls)) {
            try {
                instance = (GInstance) classMap.get(cls).newInstance();
            } catch (InstantiationException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }
        if (instance == null) {
            instance = new GInstance();
        }
        instance.setNativePtr(n);
        instance.setGClass(find(cls));
        return instance;
    }
    public static String[] dicKeys(Object dic) {
        Enumeration e = ((Dictionary)dic).keys();
        ArrayList<String> arr = new ArrayList<>();
        while (e.hasMoreElements()) {
            arr.add(e.nextElement().toString());
        }
        String[] ret = new String[arr.size()];
        arr.toArray(ret);
        return ret;
    }
    public static Object getDicValue(Object dic, String key) {
        return ((Dictionary)dic).get(key);
    }

    public static native GClass findc(String fullname);
    public static boolean hasMethod(Class cls, String name) {
        Method[] methods = cls.getMethods();
        for (Method m : methods) {
            if (m.getName().equals(name)) return true;
        }
        return false;
    }
    public static Object newClass(String name, long ptr) {
        return new GClass(name, ptr);
    }

    public static char checkType(Object obj) {
        if (obj instanceof Integer) {
            return 'i';
        }else if (obj instanceof Boolean){
            return 'b';
        } else if (obj instanceof Long) {
            return 'l';
        } else if (obj instanceof Float) {
            return 'f';
        } else if (obj instanceof Double) {
            return 'd';
        } else if (obj instanceof GInstance) {
            return 'n';
        } else if (obj instanceof String){
            return 's';
        } else if (obj instanceof Dictionary) {
            return 'm';
        } else if (obj instanceof Object[]) {
            return 'a';
        } else if (obj == null) {
            return '_';
        } else {
            return 'o';
        }
    }

    static class Base {

        String parseSignature(Object[] objs) {
            StringBuilder sb = new StringBuilder();
            for (Object obj : objs) {
                sb.append(checkType(obj));
            }
            return sb.toString();
        }
    }

    static Method getMethod(Class cls, String name, Object[] params) {
        Class sc = cls;
        while (sc != null) {
            Method[] methods = sc.getMethods();
            for (Method m : methods) {
                if (m.getName().equals(name)) {
                    Class[] p_types = m.getParameterTypes();
                    if (p_types.length == params.length) {
                        boolean win = true;
                        for (int i = 0, t = p_types.length; i < t; ++i) {
                            if (!p_types[i].isAssignableFrom(params[i].getClass())) {
                                win = false;
                            }
                        }
                        if (win) {
                            return m;
                        }
                    }
                }
            }
            sc = sc.getSuperclass();
        }
        return null;
    }

    public static class GInstance extends Base {
        private long nativePtr;
        private GClass cls;
        boolean inited = false;

        void setNativePtr(long nativePtr) {
            this.nativePtr = nativePtr;
        }
        public GClass getGClass() {
            return cls;
        }
        void setGClass(GClass cls) {
            this.cls = cls;
        }

        public GInstance() {
        }

        protected void initialize(Object... args) {
            if (!inited) {
                GClass cls = find(this.getClass());
                if (cls != null) {
                    long ptr = cls.newi(cls.nativePtr, parseSignature(args), args);
                    setNativePtr(ptr);
                    setGClass(cls);
                    initializer(ptr);
                }
                inited = true;
            }
        }

        native void initializer(long ptr);
        static native void delete(long ptr);
        static native Object call(long ptr, String name, String signature, Object[] args);
        static native Object apply(long ptr, String name, String signature, Object[] args);

        public Object call(String name, Object... args) {
            if (nativePtr != 0) {
                return call(nativePtr, name, parseSignature(args), args);
            }
            return null;
        }
        public Object apply(String name, Object... args) {
            if (nativePtr != 0) {
                return apply(nativePtr, name, parseSignature(args), args);
            }
            return null;
        }
        public long getNativePtr() {
            return nativePtr;
        }

        @Override
        protected void finalize() throws Throwable {
            if (nativePtr != 0) delete(nativePtr);
            super.finalize();
        }

        protected Object apply(String name, Object[] params, char[] sigs) {
            Method m = getMethod(getClass(), name, params);
            if (m != null && !Modifier.isStatic(m.getModifiers())) {
                try {
                    return m.invoke(this, params);
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
            }
            return null;
        }

        @Override
        public boolean equals(Object obj) {
            return obj instanceof GInstance && nativePtr == ((GInstance) obj).nativePtr;
        }
    }

    public static class GClass<T extends GInstance> extends Base {
        private Class instanceClass;
        private String name;
        private long nativePtr;

        public void setInstanceClass(Class instanceClass) {
            if (GInstance.class.isAssignableFrom(instanceClass)) {
                this.instanceClass = instanceClass;
            }else {
                Log.e("GRender", instanceClass.getName() + " is not a subclass of HiInstance.");
            }
        }

        public Class getInstanceClass() {
            return instanceClass;
        }

        public GClass(String name, long ptr) {
            this.name = name;
            this.nativePtr = ptr;
        }

        static native long newi(long ptr, String signature, Object[] args);
        static native Object call(long ptr, String name, String signature, Object[] args);
        static native void delete(long ptr);

        T newInstance(Object ...args) {
            if (nativePtr != 0) {
                long ptr = newi(nativePtr, parseSignature(args), args);
                if (ptr != 0) {
                    T instance = null;
                    if (instanceClass != null) {
                        try {
                            instance = (T) instanceClass.newInstance();
                        } catch (InstantiationException e) {
                            e.printStackTrace();
                        } catch (IllegalAccessException e) {
                            e.printStackTrace();
                        }
                    }else {
                        instance = null;
                    }
                    if (instance != null) {
                        instance.setGClass(this);
                        instance.setNativePtr(ptr);
                        instance.initializer(ptr);
                        instance.inited = true;
                        return instance;
                    }
                }
            }
            return null;
        }

        public Object call(String name, Object ...args) {
            if (nativePtr != 0) {
                return call(nativePtr, name, parseSignature(args), args);
            }
            return null;
        }

        @Override
        protected void finalize() throws Throwable {
            if (nativePtr != 0) delete(nativePtr);
            super.finalize();
        }

        private Object apply(String name, Object[] params, char[] sigs) {
            Class cls = instanceClass;
            if (cls == null) cls = GInstance.class;
            Method m = getMethod(cls, name, params);
            if (m != null && Modifier.isStatic(m.getModifiers())) {
                try {
                    return m.invoke(null, params);
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
            }
            return null;
        }
    }

    static HashMap<String, Class> classMap = new HashMap<>();
    public static void registerClass(Class cls) {
        NativeClass c = (NativeClass) cls.getAnnotation(NativeClass.class);
        if (c != null && c.value().length() > 0) {
            classMap.put(c.value(), cls);
        }
    }

    public static GClass find(String fullname) {
        GClass cls = findc(fullname);
        if (cls != null && cls.getInstanceClass() == null && classMap.containsKey(fullname)) {
            cls.setInstanceClass(classMap.get(fullname));
        }
        return cls;
    }

    public static <T extends GInstance> GClass find(Class<T> cls) {
        NativeClass c = (NativeClass) cls.getAnnotation(NativeClass.class);
        if (c != null) {
            String name = c.value();
            if (c != null && name.length() > 0) {
                if (!classMap.containsKey(name)) {
                    classMap.put(name, cls);
                }
                return find(c.value());
            }
        }
        return null;
    }
}
