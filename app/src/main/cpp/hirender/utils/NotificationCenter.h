//
// Created by gen on 16/7/7.
//

#ifndef VOIPPROJECT_NOTIFICATIONCENTER_H
#define VOIPPROJECT_NOTIFICATIONCENTER_H

#include <core/Singleton.h>
#include <core/Action.h>
#include <core/Callback.h>
#include <vector>
#include <core/Callback.h>
#include "../render_define.h"


#define IMPLEMENT_NOTIFICATION(CLASS, KEY) const StringName CLASS::KEY(#CLASS #KEY)

using namespace hicore;

namespace hirender {
    CLASS_BEGIN_TN(NotificationCenter, Singleton, 1, NotificationCenter)

    private:
        struct NotificationItem {
            StringName key;
            ActionCallback listener;
            RefCallback callback;
            void *data;

            NotificationItem(const StringName &key,
                             ActionCallback listener, void* data) {
                this->key = key;
                this->listener = listener;
                this->data = data;
            }
            NotificationItem(const RefCallback &callback) {
                listener = NULL;
                data = NULL;
                this->callback = callback;
            }
            NotificationItem(const NotificationItem &other) {
                key = other.key;
                listener = other.listener;
                data = other.data;
                callback = other.callback;
            }
            NotificationItem &operator=(const NotificationItem &other) {
                key = other.key;
                listener = other.listener;
                data = other.data;
                callback = other.callback;
                return *this;
            }
        };

        pointer_map listeners;
        mutex mtx;

    public:
        NotificationCenter(){}
        ~NotificationCenter();

        /**
         * @params function((StringName*)key, (vector<Variant>*)params, customor_data)
         */
        void listen(const StringName &name,
                    ActionCallback function,
                    const StringName &key, void *data = NULL);
        METHOD void listen(const StringName &name, const RefCallback &callback);
        void trigger(const StringName &name, vector<Variant> *params = NULL);
        void remove(const StringName &name, const StringName &key);
        METHOD void remove(const StringName &name, const RefCallback &callback);
        static StringName keyFromObject(HObject *object);

    protected:
        ON_LOADED_BEGIN(cls, Singleton<NotificationCenter>)
            ADD_METHOD_E(cls, NotificationCenter, void(NotificationCenter::*)(const StringName &name, const RefCallback &callback), listen);
            ADD_METHOD_E(cls, NotificationCenter, void(NotificationCenter::*)(const StringName &name, const RefCallback &callback), remove);
        ON_LOADED_END
    CLASS_END
}


#endif //VOIPPROJECT_NOTIFICATIONCENTER_H
