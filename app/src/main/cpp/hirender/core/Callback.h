//
//  Callback.h
//  hirender_iOS
//
//  Created by Gen on 16/9/24.
//  Copyright © 2016年 gen. All rights reserved.
//

#ifndef Callback_h
#define Callback_h

#include "Object.h"
#include "Reference.h"
#include "Variant.h"
#include "Array.h"
#include "MethodImp.h"
#include "core_define.h"

namespace hicore {
    
    CLASS_BEGIN_N(Callback, RefObject)
    
    public:
        Callback() {}
    
        template <typename ...Args>
        _FORCE_INLINE_ Variant operator() (Args && ...args) {
            return invoke(variant_vector{{args...}});
        }
        METHOD virtual Variant invoke(const RefArray &params);
        EVENT(Variant, _invoke, const Array &params);
    
    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_METHOD(cls, Callback, invoke);
        ON_LOADED_END
    CLASS_END
    
    // The Function is too big, do not command to use.
    template <int N>
    _FORCE_INLINE_ static const Variant &_var(const RefArray &params) {
        return N < params.size() ? (*params)->operator[](N) : Variant::null();
    }
    
    template <class M>
    class Function{};
    
    template<class ..._ArgType>
    class Function<void(_ArgType...)> : public Callback {
        
        function<void(_ArgType...)> func;
        
    public:
        _FORCE_INLINE_ Function() {}
        _FORCE_INLINE_ Function(const Function &other) : func(other.func) {
        }
        _FORCE_INLINE_ Function(function<void(_ArgType...)> func) : func(func) {
        }
        template <typename M>
        _FORCE_INLINE_ Function(M func) : func(func) {
        }
        
        _FORCE_INLINE_ Function &operator=(const Function &other) {
            this->func = other.func;
            return *this;
        }
        
        template <int... Is>
        _FORCE_INLINE_ Variant _call(const RefArray &params, seq<Is...>*) const {
            func(type_convert<typename tuple_element<Is, tuple<_ArgType...> >::type >::toType(_var<Is>(params))...);
            return Variant::null();
        }
        
        _FORCE_INLINE_ virtual Variant invoke(const RefArray &params) {
            static const int size = sizeof...(_ArgType);
            gen_seq<size> d;
            return _call(params, &d);
        }
        
    };
    
    template<class _Rp, class ..._ArgType>
    class Function<_Rp(_ArgType...)> : public Callback {
        
        function<_Rp(_ArgType...)> func;
        
    public:
        _FORCE_INLINE_ Function() {}
        _FORCE_INLINE_ Function(const Function &other) : func(other.func) {
        }
        _FORCE_INLINE_ Function(function<_Rp(_ArgType...)> func) : func(func) {
        }
        template <typename M>
        _FORCE_INLINE_ Function(M func) : func(func) {
        }
        
        _FORCE_INLINE_ Function &operator=(const Function &other) {
            this->func = other.func;
            return *this;
        }
        
        template <int... Is>
        _FORCE_INLINE_ Variant _call(const RefArray &params, seq<Is...>*) const {
            return func(type_convert<typename tuple_element<Is, tuple<_ArgType...> >::type >::toType(_var<Is>(params))...);
        }
        
        _FORCE_INLINE_ virtual Variant invoke(const RefArray &params) {
            static const int size = sizeof...(_ArgType);
            gen_seq<size> d;
            return _call(params, &d);
        }
    };
    
    template <class M>
    class SFunction{};
    template<class ..._ArgType>
    class SFunction<void(*)(_ArgType...)> : public Callback {
        void (*func)(_ArgType...);
    public:
        
        _FORCE_INLINE_ SFunction() {}
        _FORCE_INLINE_ SFunction(const SFunction &other) : func(other.func) {
        }
        
        _FORCE_INLINE_ SFunction(void(*func)(_ArgType...)) : func(func) {
        }
        
        _FORCE_INLINE_ SFunction &operator=(const SFunction &other) {
            func = other.func;
            return *this;
        }
        template <int... Is>
        _FORCE_INLINE_ Variant _call(const RefArray &params, seq<Is...>*) const {
            func(type_convert<typename tuple_element<Is, tuple<_ArgType...> >::type >::toType(_var<Is>(params))...);
            return Variant::null();
        }
        _FORCE_INLINE_ virtual Variant invoke(const RefArray &params) {
            static const int size = sizeof...(_ArgType);
            gen_seq<size> d;
            return _call(params, &d);
        }
    };
    
    template<class _Rp, class ..._ArgType>
    class SFunction<_Rp(*)(_ArgType...)> : public Callback {
        _Rp (*func)(_ArgType...);
    public:
        
        _FORCE_INLINE_ SFunction() {}
        _FORCE_INLINE_ SFunction(const SFunction &other) : func(other.func) {
        }
        
        _FORCE_INLINE_ SFunction(_Rp(*func)(_ArgType...)) : func(func) {
        }
        _FORCE_INLINE_ SFunction &operator=(const SFunction &other) {
            func = other.func;
            return *this;
        }
        template <int... Is>
        _FORCE_INLINE_ Variant _call(const RefArray &params, seq<Is...>*) const {
            return func(type_convert<typename tuple_element<Is, tuple<_ArgType...> >::type >::toType(_var<Is>(params))...);
        }
        _FORCE_INLINE_ virtual Variant invoke(const RefArray &params) {
            static const int size = sizeof...(_ArgType);
            gen_seq<size> d;
            return _call(params, &d);
        }
    };
    
    template <typename T>
    struct ft : public ft<decltype(&T::operator())>
    {};
    // For generic types, directly use the result of the signature of its 'operator()'
    
    template <typename ClassType, typename ReturnType, typename... Args>
    struct ft<ReturnType(ClassType::*)(Args...) const>
    // we specialize for pointers to member function
    {
        
//        typedef ...Args args;
        typedef ReturnType(function_type)(Args...);
        
    };
    
    CLASS_BEGIN_TN(RefCallback, Ref, 1, Callback)
    
public:
    template <typename ...Args>
    Variant operator() (Args && ...args) {
        if (this->operator bool())
            return (*this->operator*())(args...);
        else {
            return Variant::null();
        }
    }
    _FORCE_INLINE_ RefCallback() {}
    _FORCE_INLINE_ RefCallback(Callback *ref) : Ref(ref) {
    }
    template <class T>
    _FORCE_INLINE_ RefCallback(Function<T> *ref) : Ref(ref) {
    }
    template <class T>
    _FORCE_INLINE_ RefCallback(SFunction<T> *ref) : Ref(ref) {
    }
    _FORCE_INLINE_ RefCallback(const Reference &ref) : Ref(ref) {
    }
    _FORCE_INLINE_ RefCallback(const Variant &var) : Ref(var) {
    }
    _FORCE_INLINE_ RefCallback(const RefCallback &ref) : Ref(ref) {
    }
    
    CLASS_END
    
    template <typename M>
    RefCallback C(M f) {
        typedef ft<M> func;
        return new Function<typename func::function_type>(f);
    }
    template <typename M>
    RefCallback S(M f) {
        return new SFunction<M>(f);
    }
}


#endif /* Callback_h */
