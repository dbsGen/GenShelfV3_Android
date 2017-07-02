//
// Created by gen on 16/5/30.
//

#ifndef HICORE_OBJECT_H
#define HICORE_OBJECT_H

#include <string>
#include <iostream>
#include <iostream>
#include "Action.h"
#include "Variant.h"
#include "Class.h"
#include "Define.h"
#include "runtime.h"

using namespace std;

/**
 * CLASS_BEGIN_0 定义一个继承自Object的类
 */
#define CLASS_BEGIN_0(NAME)     CLASS_BEGIN(NAME, __CLASS_NS(OBJECT_CLASS))
#define CLASS_BEGIN_0_N(NAME)   CLASS_BEGIN_N(NAME, __CLASS_NS(OBJECT_CLASS))
#define CLASS_BEGIN_0_NV(NAME)  CLASS_BEGIN_NV(NAME, __CLASS_NS(OBJECT_CLASS))
#define CLASS_BEGIN_0_V(NAME)   CLASS_BEGIN_V(NAME, __CLASS_NS(OBJECT_CLASS))

#define OBJECT_CLASS    HObject
#define OBJECT_NAME     "HObject"

namespace hicore {
    class Script;
    class ScriptClass;
    class ScriptInstance;
    class Variant;

    class OBJECT_CLASS {
    private:
        struct Scripts;
        Scripts *scripts_container;
        ActionManager  *on_destroy;
        friend class Variant;
        friend class Script;

    protected:
        _FORCE_INLINE_ static void onClassLoaded(HClass *clz) {}
        _FORCE_INLINE_ virtual void _copy(const HObject *other) {}

        friend class ClassDB;

    public:
        virtual void initialize() {}
        static const HClass *getClass() {
            if (!_class_contrainer<HObject>::_class) {
                const HClass *clazz = ClassDB::getInstance()->find_loaded(ClassDB::connect("hicore", OBJECT_NAME));
                _class_contrainer<HObject>::_class = clazz ? clazz : ClassDB::getInstance()->cl<OBJECT_CLASS>("hicore", OBJECT_NAME, NULL);
            }
            return _class_contrainer<HObject>::_class;
        }

        _FORCE_INLINE_ virtual const HClass *getInstanceClass() const {
            return HObject::getClass();
        }

        _FORCE_INLINE_ bool instanceOf(const HClass *clz) const {
            const HClass *cClz = getInstanceClass();
            while (cClz) {
                if (cClz == clz) return true;
                cClz = cClz->getParent();
            }
            return false;
        }
        void addScript(ScriptInstance *scriptClass);
        void removeScript(ScriptInstance *instance);
        void clearScripts();
#ifdef USING_SCRIPT
        /**
         *
         * @param name      method name
         * @param result    return value
         * @param params    argvs
         * @param count     argv count
         */
        void apply(const StringName &name, Variant *result = NULL, const Variant **params = NULL, int count = 0);
#else
        _FORCE_INLINE_ void apply(const StringName &name, Variant *result = NULL, const Variant **params = NULL, int count = 0) {}
#endif
        /**
         *
         * @param name      method name
         * @param params    vector<Variant*> argvs
         * @return  return value
         */
        Variant apply(const StringName &name, const pointer_vector &params) {
            Variant ret;
            apply(name, &ret, (const Variant **)params.data(), (int)params.size());
            return ret;
        }
        void call(const StringName &name, Variant *result = NULL, const Variant **params = NULL, int count = 0);
        
        Variant call(const StringName &name, const pointer_vector &params) {
            Variant ret;
            call(name, &ret, (const Variant **)params.data(), (int)params.size());
            return ret;
        }
        
        template<class T>
        _FORCE_INLINE_ T *cast_to() {
            return this ? (getInstanceClass()->isTypeOf(T::getClass()) ? static_cast<T*>(this) : NULL) : NULL;
        }
        template<class T>
        _FORCE_INLINE_ const T *cast_to() const {
            return this ? (getInstanceClass()->isTypeOf(T::getClass()) ? static_cast<const T*>(this) : NULL) : NULL;
        }

        _FORCE_INLINE_ virtual string str() const {
            const HClass *cls = getInstanceClass();
            return "[" + string(cls->getFullname().str()) + "]";
        }
        void pushOnDestroy(ActionCallback callback, void *data);
        void removeOnDestroy(ActionCallback callback, void *data);
        Variant var();

        bool copy(const HObject *other);

//        bool test_object;
        _FORCE_INLINE_ HObject():scripts_container(NULL), on_destroy(NULL) {}
        virtual ~HObject();
    };
}


#endif //HICORE_OBJECT_H
