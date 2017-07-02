//
//  Action.h
//  hirender_iOS
//
//  Created by gen on 16/9/27.
//  Copyright © 2016年 gen. All rights reserved.
//

#ifndef Action_h
#define Action_h

#include <stdlib.h>
#include <list>
#include "Define.h"

namespace hicore {
    typedef void (*ActionCallback)(void *sender, void *send_data, void *data);
    
    struct ActionItem {
        ActionCallback callback;
        void *data;
        
        _FORCE_INLINE_ ActionItem() : callback(NULL), data(NULL) {}
        _FORCE_INLINE_ ActionItem(ActionCallback callback, void *data) {
            this->callback = callback;
            this->data = data;
        }
        
        _FORCE_INLINE_ void operator()(void *sender, void *send_data = NULL) const {
            if (callback) {
                callback(sender, send_data, data);
            }
        }
    };
    
    class ActionManager {
        
    public:
        std::list<ActionItem> items;
        
        _FORCE_INLINE_ ActionManager() {}
        _FORCE_INLINE_ ~ActionManager() {
        }
        _FORCE_INLINE_ void push(ActionCallback callback, void *data) {
            items.push_back(ActionItem(callback, data));
        }
        void remove(ActionCallback callback, void *data) {
            auto it = items.begin(), _e = items.end();
            while (it != _e) {
                const ActionItem &item = *it;
                if (item.callback == callback && item.data == data) {
                    it = items.erase(it);
                }else {
                    ++it;
                }
            }
        }
        _FORCE_INLINE_ void clear() {
            items.clear();
        }
        _FORCE_INLINE_ size_t size() {
            return items.size();
        }
        _FORCE_INLINE_ void operator() (void *sender, void *send_data = NULL) {
            auto items = this->items;
            for (auto it = items.begin(), _e = items.end(); it != _e; ++it)
                (*it)(sender, send_data);
        }
    };
}

#endif /* Action_h */
