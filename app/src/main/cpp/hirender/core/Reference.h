//
// Created by gen on 16/8/31.
//

#ifndef VOIPPROJECT_REFERENCE_H
#define VOIPPROJECT_REFERENCE_H

#include "Define.h"

namespace hicore {
    class HObject;
    class HClass;
    class Variant;
    class StringName;

    class Reference {
    BASE_CLASS_DEFINE
    private:
        static Reference nullRef;

        struct __ref_count {
            uint32_t count;
            _FORCE_INLINE_ __ref_count(uint32_t c) {
                count = c;
            }

            _FORCE_INLINE_ uint32_t retain() {
                return ++count;
            }
            _FORCE_INLINE_ uint32_t release() {
                return --count;
            }
        };

        HObject *ptr;
        __ref_count *ref_count;

        bool isRefObject();

    protected:
        void release();
        void retain();

        friend class ClassDB;

    public:
        Reference(const Reference &other) : ptr(other.ptr), ref_count(other.ref_count) {
            retain();
        }
        _FORCE_INLINE_ Reference() : ptr(NULL), ref_count(NULL) {}
        template <typename T>
        _FORCE_INLINE_ Reference(T *p) : ptr(p), ref_count(NULL) {retain();}

        _FORCE_INLINE_ virtual ~Reference() {
            release();
        }

        void ref(const Reference *other);
        _FORCE_INLINE_ void clear() {
            release();
            ptr = NULL;
            ref_count = NULL;
        }
        _FORCE_INLINE_ static const Reference &null() {
            return nullRef;
        }

        _FORCE_INLINE_ virtual Reference &operator=(const Reference &other) {
            ref(&other);
            return *this;
        }
        virtual Reference &operator=(HObject *p);
        _FORCE_INLINE_ virtual HObject *operator->() {return ptr;}
        _FORCE_INLINE_ virtual HObject *operator->() const {return ptr;}

        _FORCE_INLINE_ virtual HObject *operator*() {return ptr;}
        _FORCE_INLINE_ virtual HObject *operator*() const {return ptr;}

        _FORCE_INLINE_ bool operator==(const Reference &other) const {
            return ptr == other.ptr;
        }
        _FORCE_INLINE_ bool operator!=(const Reference &other) const {
            return ptr != other.ptr;
        }
        _FORCE_INLINE_ operator HObject*() const {
            return ptr;
        }
        const HClass *getType() const;
        _FORCE_INLINE_ virtual operator bool() const {
            return ptr != NULL;
        }
        _FORCE_INLINE_ virtual void copy(const Reference *other) {
            operator=(*other);
        }
        void call(const StringName &name, Variant *result, const Variant **params, int count);
        
        Reference(const Variant &other);

        virtual std::string str() const;
    };
}

#endif //VOIPPROJECT_REFERENCE_H
