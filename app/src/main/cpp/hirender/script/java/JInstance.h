//
// Created by gen on 16/9/6.
//

#ifdef __ANDROID__
#ifndef VOIPPROJECT_JINSTANCE_H
#define VOIPPROJECT_JINSTANCE_H

#include <core/script/ScriptInstance.h>
#include <jni.h>
#include "JScript.h"
#include "../script_define.h"

using namespace hicore;

namespace hiscript {
    class JInstance : public ScriptInstance {
        static jmethodID apply_method;
        static jclass object_class;
        static jcharArray jsigs;
        jobject object;
        Variant tmp;

    public:
        _FORCE_INLINE_ JInstance() : object(NULL) {}
        ~JInstance() {
            if (object) {
                Ref<JNIEnvWrap> env = JScript::getEnv();
                (**env)->DeleteWeakGlobalRef(object);
            }
        }

        virtual Variant apply(const StringName &name, const Variant **params, int count);

        void setJObject(jobject obj, JNIEnv *env) {
            if (object) env->DeleteWeakGlobalRef(object);
            object = obj ? env->NewWeakGlobalRef(obj) : obj;
        }
        _FORCE_INLINE_ jobject getJObject() {
            return object;
        }

    };
}


#endif //VOIPPROJECT_JINSTANCE_H
#endif //__ANDROID__
