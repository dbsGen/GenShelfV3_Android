//
// Created by gen on 16/5/30.
//

#ifndef HICORE_VARIANT_H
#define HICORE_VARIANT_H

#include <cstdlib>
#include <string>
#include "Define.h"
#include "Reference.h"
#include "StringName.h"

#include "core_define.h"

using namespace std;

namespace hicore {

    template<class T>
    class Ref;
    class Pointer;

    class Variant {
        BASE_CLASS_DEFINE
    private:
        static const HClass * const ref_class;
        static const HClass * const pointer_class;
        void *mem;
        const HClass *type;

        void release();
        void retain(void *buffer, const HClass *cls);
        static bool isRef(const HClass *cls);

        
        template<class T = HObject>
        _FORCE_INLINE_ T *_get() const {
            return isRef() ? (T*)(**(Reference*)mem) : (T*)mem;
        }
        
        static const Variant _null;

    public:

        _FORCE_INLINE_ static const Variant &null() {return _null;}

        _FORCE_INLINE_ Variant(void) : mem(NULL),
                                       type(NULL) { }

        _FORCE_INLINE_ Variant(const Variant &other) : Variant() {
            retain(other.mem, other.type);
        }

        Variant(Variant &&other) : Variant() {
            mem = other.mem;
            type = other.type;
            other.mem = NULL;
            other.type = NULL;
        }
        
        _FORCE_INLINE_ Variant(const Reference &referene) : Variant() {
            const HClass *cls = referene.getInstanceClass();
            retain((void *) &referene, cls);
        }
        
        template <class T>
        _FORCE_INLINE_ static Variant var(const T *object) {
            Variant v;
            if (object) {
                const HClass *cls = object->getInstanceClass();
                v.retain((void*)object, cls);
            }
            return v;
        }
        
        template <class T>
        _FORCE_INLINE_ Variant(const Ref<T> &ref) : Variant(Reference(ref)) {}

        _FORCE_INLINE_ ~Variant() {
            release();
        }
        
        template<class T = HObject>
        _FORCE_INLINE_ T *get() const {
            return (T*)operator void *();
        }

//        void operator=(const HObject *object);
        void operator=(const Variant &other) {
            retain(other.mem, other.type);
        }
        void operator=(Variant &&other) {
            void *tm = mem;
            const HClass *tt = type;
            mem = other.mem;
            type = other.type;
            other.mem = tm;
            other.type = tt;
        }

        bool operator==(const Variant &other) const;

        _FORCE_INLINE_ virtual void copy(const Variant *other) {
            operator=(*other);
        }

        _FORCE_INLINE_ HObject *operator->() {
            return get();
        }

        _FORCE_INLINE_ const HObject *operator->() const {
            return get();
        }

        const HClass *getType() const;

        _FORCE_INLINE_ Reference ref() const {
            return isRef() ? (*(Reference*)mem) : Reference();
        }
        const Pointer *pointer() const;

        _FORCE_INLINE_ bool isRef() const { return isRef(type); }
        _FORCE_INLINE_ bool empty() const { return isRef(type) ? !((Reference*)mem)->getType() : !type; }

        operator bool() const;
        operator char() const;
        operator short() const;
        operator int() const;
        operator long() const;
        operator long long() const;
        operator float() const;
        operator double() const;

        operator string() const;
        
        operator void *() const;
        operator const char *() const;
        operator HObject *() const;
        operator StringName() const;

        virtual string str() const;
        
        Variant(char);
        Variant(short);
        Variant(int);
        Variant(long);
        Variant(long long);
        Variant(float);
        Variant(double);
        Variant(const string &);
        Variant(const char *);
        Variant(const HObject*);
        Variant(void*);
        Variant(const StringName &name);

        template <class T>
        static Variant make(T v) {
            return Variant(&v);
        }

    };

}


#endif //HICORE_VARIANT_H
