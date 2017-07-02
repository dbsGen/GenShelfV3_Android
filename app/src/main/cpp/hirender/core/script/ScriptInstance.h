//
// Created by gen on 16/7/4.
//

#ifndef HI_RENDER_PROJECT_ANDROID_SCRIPTINSTANCE_H
#define HI_RENDER_PROJECT_ANDROID_SCRIPTINSTANCE_H

#include "../Object.h"
#include "../StringName.h"
#include "../Variant.h"
#include "../Pointer.h"
#include "../core_define.h"

namespace hicore {
    class Script;
    class ScriptClass;
    
    /**
     * 链接native与script对象的中间件, 传递函数调用，见ScriptClass
     * 某些情况下拥有有c++对象的内存控制权。
     * ScriptInstance对象的内存控制权在script层，请实现对应内存管理。
     */
    CLASS_BEGIN_0_V(ScriptInstance)
    private:
        void *target;
        bool target_ref;
        const Script *script;
        ScriptClass *cls;
        bool single_class;

        _FORCE_INLINE_ void setTarget(void *object, bool tr) {
            target = object;
            target_ref = tr;
        }
        _FORCE_INLINE_ void setScript(const Script *script) {
            this->script = script;
        }

        friend class Script;
        friend class ScriptClass;
        friend class HObject;

    public:
        _FORCE_INLINE_ ScriptInstance() : target(NULL), script(NULL), cls(NULL), single_class(false) {}
        virtual ~ScriptInstance();

        Variant call(const StringName &name, const Variant **params, int count) const;
        Variant get(const StringName &name) const;
        void set(const StringName &name, const Variant &val) const;

        virtual Variant apply(const StringName &name, const Variant **params, int count) = 0;

        _FORCE_INLINE_ Variant getTarget() const {
            return target_ref ? Variant(*(Reference*)target) : Variant(target);
        }
        _FORCE_INLINE_ const Script *getScript() const {
            return script;
        }
        _FORCE_INLINE_ ScriptClass *getMiddleClass() const {
            return cls;
        }
        _FORCE_INLINE_ void setMiddleClass(ScriptClass *cls) {
            this->cls = cls;
        }
        _FORCE_INLINE_ void setSingleClass(bool sc) {
            single_class = sc;
        }
    
    CLASS_END
}


#endif //HI_RENDER_PROJECT_ANDROID_SCRIPTINSTANCE_H
