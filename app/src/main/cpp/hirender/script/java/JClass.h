//
// Created by gen on 16/9/6.
//

#ifdef __ANDROID__
#ifndef VOIPPROJECT_JCLASS_H
#define VOIPPROJECT_JCLASS_H

#include <core/script/ScriptClass.h>
#include <jni.h>
#include "../script_define.h"

using namespace hicore;

namespace hiscript {
    class JScript;

    class JClass : public ScriptClass {
        jobject clz;
    protected:
        virtual ScriptInstance *makeInstance() const;

    public:
        _FORCE_INLINE_ JClass() : clz(NULL) {}
        ~JClass();
        virtual Variant apply(const StringName &name, const Variant **params, int count) const;
        jobject getJavaClass() {return clz;}
        void setJavaClass(jobject new_cls, JNIEnv *env);

    };
}


#endif //VOIPPROJECT_JCLASS_H
#endif //__ANDROID__
