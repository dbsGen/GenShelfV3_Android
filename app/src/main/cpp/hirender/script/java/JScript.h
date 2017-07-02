//
// Created by gen on 16/7/5.
//

#ifdef __ANDROID__

#ifndef HI_RENDER_PROJECT_ANDROID_JAVASCRIPT_H
#define HI_RENDER_PROJECT_ANDROID_JAVASCRIPT_H

#include <core/Define.h>
#include <core/script/Script.h>
#include <jni.h>
#include <string>
#include <mutex>
#include <core/Variant.h>
#include <android/asset_manager.h>
#include <core/Ref.h>
#include "../script_define.h"

#define JCLASS_CLASS    "java/lang/Class"
#define JSTRING_CLASS   "java/lang/String"
#define JOBJECT_CLASS   "java/lang/Object"

using namespace std;
using namespace hicore;

namespace hiscript {
    class JScript;

    CLASS_BEGIN_N(JNIEnvWrap, RefObject)

    private:
        JNIEnv *env;
        jclass helper_class;
        bool new_thread;

        jmethodID to_int;
        jmethodID to_long;
        jmethodID to_float;
        jmethodID to_double;
        jmethodID to_native;

        jmethodID from_int;
        jmethodID from_long;
        jmethodID from_float;
        jmethodID from_double;
        jmethodID from_native;
        jmethodID dic_keys;
        jmethodID get_dic_value;
        jmethodID check_type;

        friend class JScript;
    public:
        _FORCE_INLINE_ JNIEnvWrap(){}
        JNIEnvWrap(JNIEnv *env, jclass helper_class, bool new_thread);
        ~JNIEnvWrap();

        jmethodID getToInt();
        jmethodID getToLong();
        jmethodID getToFloat();
        jmethodID getToDouble();
        jmethodID getToNative();

        jmethodID getFromInt();
        jmethodID getFromLong();
        jmethodID getFromFloat();
        jmethodID getFromDouble();
        jmethodID getFromNative();
        jmethodID getDicKeys();
        jmethodID getGetDicValue();
        jmethodID getCheckType();

        _FORCE_INLINE_ JNIEnv *operator *() {
            return env;
        }

        _FORCE_INLINE_ JNIEnv *operator->() {
            return env;
        }
        _FORCE_INLINE_ JNIEnv *jniEnv() {
            return env;
        }

        ScriptInstance *toNative(jobject jobj);
        int         toInt(jobject jobj);
        long long   toLong(jobject jobj);
        float       toFloat(jobject jobj);
        double      toDouble(jobject jobj);

        jobject fromNative(jstring class_name, jlong ptr);
        jobject fromInt(int i);
        jobject fromLong(long long l);
        jobject fromFloat(float f);
        jobject fromDouble(double d);
        jobjectArray dicKeys(jobject);
        jobject getDicValue(jobject, jstring);
        jchar checkType(jobject);

    CLASS_END

    class JScript : public Script {
    private:
        static JScript *_instance;

        static jclass helper_class;
        static jmethodID check_method;
        static jmethodID new_class_method;
        static JavaVM *vm;
        static pointer_map envs;
        static void checkHelper(JNIEnv *env);

    protected:
        virtual ScriptClass *makeClass() const;
        virtual ScriptInstance *newBuff(const string &cls_name, HObject *target, const Variant **params, int count) const {return NULL;}

    public:

        _FORCE_INLINE_ static JavaVM *getVM() {return vm;}
        static void loadVM(JavaVM *_vm);

        static Ref<JNIEnvWrap> getEnv(JNIEnv *env = NULL);
        static void registerThread();
        static void unregisterThread();
        static jclass getHelperClass();

        Variant process(const Ref<JNIEnvWrap> &env, char type, jobject jobj);
        vector<Variant> process(const Ref<JNIEnvWrap> &env, jstring jsignature, jobjectArray jarr);
        jobject process(const Ref<JNIEnvWrap> &env, const Variant &variant);

        static jobject newHiClass(JNIEnv *env, jstring name, long ptr);

        _FORCE_INLINE_ JScript() : Script("java") {_instance = this;}
        _FORCE_INLINE_ ~JScript() { if (_instance == this) _instance = NULL;}
        static JScript *instance();
    };

}

#endif //HI_RENDER_PROJECT_ANDROID_JAVASCRIPT_H

#endif
