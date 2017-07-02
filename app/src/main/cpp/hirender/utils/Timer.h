//
// Created by gen on 16/9/20.
//

#ifndef VOIPPROJECT_TIMER_H
#define VOIPPROJECT_TIMER_H

#include <core/Action.h>
#include "../Plugin.h"

#include "../render_define.h"

namespace hirender {
    class TimerManager;

    CLASS_BEGIN_NV(Timer, RefObject)

        Time max_life;
        Time life;
        ActionItem callback;
        friend class TimerManager;
        Timer(Time, ActionCallback, void*);

    public:
        void cancel();
        bool step(Time delta);

    CLASS_END

    CLASS_BEGIN_N(TimerManager, Plugin)

        ref_list timers;
        static TimerManager *instance;
        static mutex mtx;

    protected:
        void fixedStep(Renderer *renderer, Time delta);

    public:
        static TimerManager *sharedInstance();
        Timer* fire(Time time, ActionCallback action, void *data);
        void cancel(Timer *timer);

        TimerManager();
        ~TimerManager();

    CLASS_END
}


#endif //VOIPPROJECT_TIMER_H
