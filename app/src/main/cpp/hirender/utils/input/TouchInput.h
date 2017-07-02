//
//  TouchInput.hpp
//  hirender_iOS
//
//  Created by mac on 2016/12/18.
//  Copyright © 2016年 gen. All rights reserved.
//

#ifndef TouchInput_hpp
#define TouchInput_hpp

#include <Plugin.h>
#include <core/Action.h>
#include <object/Camera.h>
#include "../../render_define.h"

namespace hirender {
    CLASS_BEGIN_N(TouchInput, Plugin)

    public:
        enum Phase {
            Begin = 0,
            Move,
            End,
            Cancel
        };

        struct Event {
            float x;
            float y;
            void *identifier;
            Phase phase;

            Event() : x(0), y(0), identifier(NULL), phase(Begin) {}
            Event(const Event &other) : x(other.x), y(other.y), identifier(other.identifier), phase(other.phase) {}
        };

        struct EventsItem {
            TouchInput::Event *events;
            int length;
            TouchInput::Phase phase;

            EventsItem(int length) {
                events = (TouchInput::Event *)malloc(length * sizeof(TouchInput::Event));
                this->length = length;
            }
            ~EventsItem() {
                free(events);
            }
        };

    private:
        void *current_item;
        pointer_vector items;
        list<Ref<Camera> > cameras;
        mutex mtx;

        ActionManager manager;

        void process(EventsItem *ei);

    public:
        TouchInput();
        ~TouchInput();
        Event *begin(int count);
        void commit(Phase phase);

        virtual void fixedStep(Renderer *renderer, Time delta);
        virtual void step(Renderer *renderer, Time delta);

        void addListener(ActionCallback callback, void *data);
        void addCamera(const Ref<Camera> &camera);
        void clear();

    CLASS_END
}

#endif /* TouchInput_hpp */
