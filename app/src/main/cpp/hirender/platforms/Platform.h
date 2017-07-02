//
// Created by gen on 16/7/14.
//

#ifndef VOIPPROJECT_PLATFORM_H
#define VOIPPROJECT_PLATFORM_H

#include <string>
#include <functional>
#include <core/Data.h>
#include <core/Callback.h>
#include <core/Ref.h>
#include "../render_define.h"

using namespace std;
using namespace hicore;

namespace hirender {
    CLASS_BEGIN_0_N(Platform)
    
    static Platform *shared_platform;
    
public:
    METHOD static void reg(Platform *platform);
    METHOD static Platform *sharedPlatform();
    
    _FORCE_INLINE_ Platform() {}
    ~Platform();
    
    //Callback for function<void(int, const string &)>
    METHOD void startInput(const string &text, const string &placeholder, const Ref<Callback> &callback);
    METHOD void endInput();
    
    METHOD string persistencePath();
    
    METHOD Ref<Data> getFontData();
    METHOD void setFontData(const Ref<Data> &data);
    
    //Callback for function<void(int, const string &)>
    EVENT(void, _startInput, const string &text, const string &placeholder, const Ref<Callback> &block);
    EVENT(void, _endInput);
    
    EVENT(const string &, _persistencePath);
    
    protected:
        ON_LOADED_BEGIN(cls, HObject)
            ADD_METHOD(cls, Platform, reg);
            ADD_METHOD(cls, Platform, sharedPlatform);
            ADD_METHOD(cls, Platform, startInput);
            ADD_METHOD(cls, Platform, endInput);
            ADD_METHOD(cls, Platform, persistencePath);
            ADD_METHOD(cls, Platform, getFontData);
            ADD_METHOD(cls, Platform, setFontData);
        ON_LOADED_END
    CLASS_END
}

#endif //VOIPPROJECT_PLATFORM_H
