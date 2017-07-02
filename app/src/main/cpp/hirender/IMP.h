//
// Created by gen on 16/6/1.
//

#ifndef HIRENDER_IMP_H
#define HIRENDER_IMP_H

#include "render_define.h"

namespace hirender {
    template <class T>
    CLASS_BEGIN_0_NV(Imp)

    private:
        T *target;

    public:
        _FORCE_INLINE_ virtual void _setTarget(T *tar) {target = tar;}
        _FORCE_INLINE_ T *getTarget() {
            return target;
        }
    _FORCE_INLINE_ const T *getTarget() const {
        return target;
    }

    CLASS_END
}

#endif //HIRENDER_IMP_H
