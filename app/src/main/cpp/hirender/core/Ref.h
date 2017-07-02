//
// Created by gen on 16/5/30.
//

#ifndef HICORE_REFERENCE_H
#define HICORE_REFERENCE_H

#include <memory>
#include "Object.h"
#include "Reference.h"
#include "Variant.h"
#include "core_define.h"

namespace hicore {

    template<class T>
    class Ref;
    class Reference;

    CLASS_BEGIN_0_NV(RefObject)
    private:
        int count;

    protected:

    public:
        _FORCE_INLINE_ virtual int retain() {return ++count;}
        _FORCE_INLINE_ virtual int release() {return --count;}
        _FORCE_INLINE_ RefObject() : count(0) {}

    CLASS_END

    template <class T>
    CLASS_BEGIN_N(Ref, Reference)
    private:
        _FORCE_INLINE_ bool checkType(const HClass *cls) {
            return cls && (cls == T::getClass() || cls->isSubclassOf(T::getClass()));
        }

    public:

        _FORCE_INLINE_ Ref() : Ref(NULL) {}
        _FORCE_INLINE_ Ref(T *p) : Reference(p) {}
        _FORCE_INLINE_ Ref(const Reference &other) : Reference(other) {}
        _FORCE_INLINE_ ~Ref() {}

        _FORCE_INLINE_ virtual Ref &operator=(const Reference &other) {
            if (checkType(other.getType())) ref(&other);
            return *this;
        }

        _FORCE_INLINE_ Ref &operator=(T *p) {
            Reference::operator=((HObject*)p);
            return *this;
        }

        _FORCE_INLINE_ T *operator*() {return static_cast<T*>(Reference::operator*());}
        _FORCE_INLINE_ T *operator*() const {return (T*)Reference::operator*();}
        _FORCE_INLINE_ T *operator->() {
            return operator*();
        }
        _FORCE_INLINE_ T *operator->() const {
            return operator*();
        }
        _FORCE_INLINE_ Ref(const Variant &other) : Reference(other) {
        }
        static const Ref<T> &null() {
            static Ref<T> _null;
            return _null;
        }

    CLASS_END
}

#endif //HICORE_REFERENCE_H
