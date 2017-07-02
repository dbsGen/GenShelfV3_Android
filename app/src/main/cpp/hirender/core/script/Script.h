//
// Created by gen on 16/7/5.
//

#ifndef HI_RENDER_PROJECT_ANDROID_SCRIPT_H
#define HI_RENDER_PROJECT_ANDROID_SCRIPT_H

#include <string>
#include <map>
#include <core/Define.h>
#include <core/Action.h>
#include "../StringName.h"

using namespace std;

namespace hicore {
    class HClass;
    class Script;
    class ScriptClass;
    class ScriptInstance;
    class HObject;
    class Variant;

    /**
     * Script 用于对应不同的script，每个script同时只存在一个Script对象
     * Script对象会管理ScriptClass
     * ScriptClass对象可以使用find和get来管理。
     */
    class Script {
        
        static pointer_map scripts;
        pointer_map classes;
        StringName name;

    protected:
        /**
         * Need override
         *
         * To make a special class
         */
        virtual ScriptClass *makeClass() const = 0;

    public:
        virtual ~Script();

        /**
         * 查找中间类
         */
        ScriptClass *find(const StringName &fullname) const;
        ScriptClass *find(const HClass *cls) const;
        /**
         * 当create是true的时候表明返回值是刚创建出来的
         * 这是需要做一些初始化操作,其中必须建立脚本类与中间
         * 类的联系
         */
        ScriptClass *find(const StringName &fullname, bool &create);
        Script(const StringName &name);
        
        _FORCE_INLINE_ static Script *get(const StringName &name) {
            return (Script *)scripts[name];
        }
        
        ScriptInstance *getScriptInstance(const HObject *target) const;
        /**
         * 查找一个script环境中的类.并创建一个script对象.
         * 这时script instance不拥有target的内存控制权.
         */
        virtual ScriptInstance *newBuff(const string &cls_name, HObject *target, const Variant **params, int count) const = 0;
    };
}


#endif //HI_RENDER_PROJECT_ANDROID_SCRIPT_H
