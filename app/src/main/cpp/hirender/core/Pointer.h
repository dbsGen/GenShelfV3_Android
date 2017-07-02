//
//  Pointer.h
//  hirender_iOS
//
//  Created by Gen on 16/10/1.
//  Copyright © 2016年 gen. All rights reserved.
//

#ifndef Pointer_h
#define Pointer_h

#include "Object.h"
#include "core_define.h"

namespace hicore {
    
    class Pointer {
        BASE_FINAL_CLASS_DEFINE
        
        void *ptr;
        const HClass *type;
        
    public:
        _FORCE_INLINE_ Pointer() : ptr(NULL), type(NULL) {}
        _FORCE_INLINE_ Pointer(void *ptr) : ptr(ptr), type(NULL) {}
        _FORCE_INLINE_ Pointer(const HObject *obj) : ptr((void*)obj), type(obj ? obj->getInstanceClass() : NULL) {}
        _FORCE_INLINE_ Pointer(const Pointer &other) {
            type = other.type;
            ptr = other.ptr;
        }
        _FORCE_INLINE_ bool operator==(const Pointer &other) const {
            return ptr == other.ptr;
        }
        _FORCE_INLINE_ operator void*() const {
            return ptr;
        }
        _FORCE_INLINE_ const HClass *getType() const {
            return type;
        }
        
    };
}

#endif /* Pointer_h */
