//
// Created by gen on 16/5/30.
//

#ifndef HICORE_SINGLETON_H
#define HICORE_SINGLETON_H

#include "Define.h"
#include <mutex>
#include "core_define.h"
#include "Ref.h"
#include "Object.h"

using namespace std;
namespace hicore {
    template <class T>
    CLASS_BEGIN_NV(Singleton, HObject)
    private:
        static T *instance;
        static mutex mtx;
    protected:
        Singleton(){}
    public:

        METHOD _FORCE_INLINE_ static T *getInstance() {
            mtx.lock();
            if (!instance) {
                instance = new T();
            }
            mtx.unlock();
            return instance;
        }
    protected:
        ON_LOADED_BEGIN(cls, HObject)
            ADD_METHOD(cls, Singleton, getInstance);
        ON_LOADED_END
    CLASS_END

    template <class T>
    T *Singleton<T>::instance = NULL;
    template <class T>
    mutex Singleton<T>::mtx;
}


#endif //HICORE_SINGLETON_H
