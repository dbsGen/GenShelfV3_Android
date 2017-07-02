//
// Created by gen on 16/9/6.
//

#ifndef VOIPPROJECT_NATIVEOBJECT_H
#define VOIPPROJECT_NATIVEOBJECT_H

#include "../Ref.h"
#include "../core_define.h"

/**
 * NativeObject 用于把script中的对象传递到，c++中
 * 所以：
 *   对应不用的script需要重载一个各自的NativeObject,并且实现
 *   对应不用script的保存方法。防止在c++持有的时候对象被释放掉。
 */

namespace hicore {
    CLASS_BEGIN_N(NativeObject, RefObject)

        void *native;
    public:
        _FORCE_INLINE_ virtual void setNative(void *native) {
            this->native = native;
        }
        _FORCE_INLINE_ virtual void *getNative() {
            return native;
        }
        _FORCE_INLINE_ NativeObject() : native(NULL) {}
        INITIALIZE(NativeObject, void *native,
            this->native = native;
        )

    CLASS_END
}

#endif //VOIPPROJECT_NATIVEOBJECT_H
