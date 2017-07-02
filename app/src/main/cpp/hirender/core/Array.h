//
//  Vector.h
//  hirender_iOS
//
//  Created by Gen on 16/9/25.
//  Copyright © 2016年 gen. All rights reserved.
//

#ifndef Vector_h
#define Vector_h


#include "Object.h"
#include <vector>
#include <string>
#include "Ref.h"
#include "Variant.h"
#include "core_define.h"

using namespace std;

namespace hicore {
    class Array;
    
    CLASS_BEGIN_N(Array, RefObject)
    private:
        variant_vector variants;
        friend class RefArray;

    public:
        _FORCE_INLINE_ Array() {}
        _FORCE_INLINE_ Array(const variant_vector &variants) {
            this->variants = variants;
        }
        virtual string str() const;
        _FORCE_INLINE_ Array &operator=(const variant_vector &vs) {
            variants = vs;
            return *this;
        }
        _FORCE_INLINE_ Array &operator=(const Array &other) {
            variants = other.variants;
            return *this;
        }
        _FORCE_INLINE_ operator variant_vector() {
            return variants;
        }
        _FORCE_INLINE_ Variant &operator[](long n) {
            if (n >= variants.size()) variants.resize(n);
            return variants[n];
        }

        _FORCE_INLINE_ const Variant &operator[](long n) const {
            return n < variants.size() ? variants.at(n) : Variant::null();
        }
        METHOD _FORCE_INLINE_ long size() const {
            return variants.size();
        }
        void contact(const variant_vector &other) {
            for (auto it = other.begin(), _e = other.end(); it != _e; ++it) {
                variants.push_back(*it);
            }
        }
        _FORCE_INLINE_ variant_vector::iterator begin() {
            return variants.begin();
        }
        _FORCE_INLINE_ variant_vector::iterator end() {
            return variants.end();
        }
        METHOD _FORCE_INLINE_ void push_back(const Variant &var) {
            variants.push_back(var);
        }
        _FORCE_INLINE_ const Variant &at(long n) const {
            return n < variants.size() ? variants.at(n) : Variant::null();
        }
        METHOD _FORCE_INLINE_ const Variant &get(long n) const {
            return at(n);
        }
        METHOD _FORCE_INLINE_ void erase(long n) {
            if (n < variants.size()) variants.erase(variants.begin()+n);
        }
        METHOD Variant pop_back() {
            Variant ret = variants.back();
            variants.pop_back();
            return ret;
        }
        METHOD void set(long idx, const Variant &var) {
            if (idx < variants.size()) variants[idx] = var;
        }

        METHOD long find(const Variant &var) {
            for (int i = 0, t = variants.size(); i < t; ++i) {
                if (var == variants[i]) {
                    return i;
                }
            }
            return -1;
        }
        METHOD _FORCE_INLINE_ void clear() {
            variants.clear();
        }

    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_METHOD(cls, Array, size);
            ADD_METHOD(cls, Array, push_back);
            ADD_METHOD(cls, Array, get);
            ADD_METHOD(cls, Array, set);
            ADD_METHOD(cls, Array, erase);
            ADD_METHOD(cls, Array, pop_back);
            ADD_METHOD(cls, Array, find);
            ADD_METHOD(cls, Array, clear);
        ON_LOADED_END
    CLASS_END

    CLASS_BEGIN_TN(RefArray, Ref, 1, Array)

    public:
        _FORCE_INLINE_ RefArray() : Ref(new Array(variant_vector())) {}
        _FORCE_INLINE_ RefArray(const variant_vector &variants) : Ref(new Array(variants)) {
        }

        _FORCE_INLINE_ RefArray(const Reference &ref) : Ref(ref) {
        }

        _FORCE_INLINE_ Variant &at(long n) {
            return operator*()->operator[](n);
        }


        _FORCE_INLINE_ const Variant &at(long n) const {
            return operator*()->operator[](n);
        }

        _FORCE_INLINE_ size_t size() const {
            return operator*() ? operator*()->size() : 0;
        }
        variant_vector *vec() const {
            return &this->operator*()->variants;
        }

        _FORCE_INLINE_ operator Variant() const {
            return Variant(*this);
        }
        _FORCE_INLINE_ RefArray(const Variant &var) : RefArray() {
            if (var && var.getType()->isTypeOf(Array::getClass())) {
                operator=(var.ref());
            }
        }
        _FORCE_INLINE_ void contact(const RefArray &other) {
            if (other) {
                operator*()->contact((*other)->variants);
            }
        }

    CLASS_END
}


#endif /* Vector_h */
