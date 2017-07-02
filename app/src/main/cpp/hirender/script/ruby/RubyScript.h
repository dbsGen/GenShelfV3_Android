//
//  RubyScript.hpp
//  hirender_iOS
//
//  Created by Gen on 16/9/28.
//  Copyright © 2016年 gen. All rights reserved.
//

#ifdef HAS_RUBY
#ifndef RubyScript_hpp
#define RubyScript_hpp

#include <thirdparties/mruby/mruby.h>
#include <core/script/NativeObject.h>
#include <core/script/Script.h>
#include <core/script/ScriptClass.h>
#include <core/script/ScriptInstance.h>

#include "../script_define.h"

using namespace hicore;

struct mrb_state;
struct RClass;
struct RObject;
struct mrb_value;

namespace hiscript {
    class RubyClass;
    class RubyInstance;
    
    class RubyScript : public Script {
        string context_root;
        mrb_state *mrb;
        
        void _setup(const char *root) const;
        
    protected:
        virtual ScriptClass *makeClass() const;
    public:
        RubyScript();
        ~RubyScript();
        
        ScriptInstance  *newBuff(const string &cls_name, HObject *target, const Variant **params, int count) const;
        RubyInstance    *newBuff(struct RClass *cls, HObject *target, const Variant **params, int count) const;
        RubyClass       *reg_class(struct RClass *cls, const StringName &name);
        
        void reset();
        void setup(const char *root);
        void addEnvPath(const char *path);
        mrb_value run(const char *filepath) const;
        mrb_value runScript(const char *script) const;
        _FORCE_INLINE_ mrb_state *getMRB() {
            return mrb;
        }
    };
    
    CLASS_BEGIN_N(RubyClass, ScriptClass)
        struct RClass *script_class;
        friend class RubyScript;
        
    protected:
        virtual ScriptInstance *makeInstance() const;
    public:
        _FORCE_INLINE_ struct RClass *getScriptClass() const {
            return script_class;
        }
    
    public:
        
        virtual Variant apply(const StringName &name, const Variant **params, int count) const;
    CLASS_END
    
    CLASS_BEGIN_N(RubyInstance, ScriptInstance)
        struct RObject *script_instance;
        struct RClass *script_class;
    
        friend class RubyScript;
        
    public:
        _FORCE_INLINE_ struct RObject *getScriptInstance() {
            return script_instance;
        }
        _FORCE_INLINE_ void setScriptInstance(struct RObject *si) {
            script_instance = si;
        }
        
        virtual Variant apply(const StringName &name, const Variant **params, int count);
    CLASS_END
    
    CLASS_BEGIN_N(RubyNativeObject, NativeObject)
public:
    _FORCE_INLINE_ RubyNativeObject() {}
    RubyNativeObject(void *native);
    virtual void setNative(void *native);
    ~RubyNativeObject();
    CLASS_END
}

#endif /* RubyScript_hpp */

#endif
