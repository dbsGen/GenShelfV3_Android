//
// Created by gen on 16/9/6.
//

#ifndef VOIPPROJECT_SCRIPTCLASS_H
#define VOIPPROJECT_SCRIPTCLASS_H

#include "../Object.h"
#include "../StringName.h"
#include "../Variant.h"

#include "../core_define.h"

namespace hicore {
    class HObject;
    class Script;

    
    /**
     * ScriptClass 是c++和script层中class的中间件,负责转发函数调用
     * 以及创建c++对象和native对象。
     * 为了命名统一定义以下命名规则：
     * c++层 -> native
     * 中间件 -> middle
     * script-> script
     */
    CLASS_BEGIN_0_V(ScriptClass)
    private:
        const HClass *cls;
        const Script *script;
        friend class Script;

    protected:
        /*
         * 重载这个方法 
         * 只需要new一个对应script的instance并返回即可。
         */
        virtual ScriptInstance *makeInstance() const = 0;

    public:
        _FORCE_INLINE_ ScriptClass() : cls(NULL), script(NULL) {}
        _FORCE_INLINE_ virtual ~ScriptClass() {}

        _FORCE_INLINE_ const HClass *getNativeClass() const {
            return cls;
        }
        _FORCE_INLINE_ const Script *getScript() const {
            return script;
        }
        _FORCE_INLINE_ void setNativeClass(const HClass *cls) {
            this->cls = cls;
        }
        _FORCE_INLINE_ void setScript(const Script *script) {
            this->script = script;
        }
    
        /**
         * 在把native转换为script类型的时候应该首先把get一次middle instance
         * 如果存在那么直接通过middle instance获得script instance
         * 如果不存在，得create一个middle instance记得给script instance
         * 一个middle的引用然后给middle一个script的引用。
         * 
         * 在初始化一个注册在native中的script instance的时候
         * 使用newInstance 创建middle instance附加操作和create一致。
         */
        /**
         * 获得一个中间件，没有找到返回空(NULL)
         */
        ScriptInstance *get(HObject *target) const;
    
        /**
         * 创建一个中间件, 通过这个方法得到ScriptInstance
         * 将不会拥有target内存管理的控制权。
         * 在回调给script层的参数中有未被管理(不在HiRender体系中)的native对象时使用。
         * 或者newBuff中使用.
         */
        ScriptInstance *create(void *target) const;

        /**
         * 创建一个中间件, 通过这个方法得到ScriptInstance
         * 如果target是RefObject那么将会拥有一个内存引用。
         * 否则将会作为指针保存
         * 在回调给script层的参数中有native对象时使用。
         */
        ScriptInstance *createVariant(HObject *target) const;
    
        /**
         * 初始化一个新的ScriptInstance并且会创建对应的c++对象，
         * 通过这个方法获得的ScriptInstance持有c++对象的内存控制权。
         * 在script中创建对象时使用。
         */
        ScriptInstance *newInstance(const Variant **params, int count) const;
    
        ScriptInstance *newInstance() const;
        /**
         * native -> script
         */
        virtual Variant apply(const StringName &name, const Variant **params, int count) const = 0;
        /**
         * script -> native
         */
        Variant call(const StringName &name, const Variant **params, int count) const;
    

    CLASS_END

}


#endif //VOIPPROJECT_SCRIPTCLASS_H
