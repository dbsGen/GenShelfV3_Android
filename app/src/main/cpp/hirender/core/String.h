//
// Created by gen on 16/7/5.
//

#ifndef HI_RENDER_PROJECT_ANDROID_STRING_H
#define HI_RENDER_PROJECT_ANDROID_STRING_H

#include "Object.h"
#include <string>
#include "Ref.h"
#include "core_define.h"

namespace hicore {
    CLASS_BEGIN_N(String, RefObject)
    private:
        string content;

    public:
        _FORCE_INLINE_ String() {}
        _FORCE_INLINE_ String(const string &content) {
            this->content = content;
        }
        _FORCE_INLINE_ String(const String &other) {
            this->content = other.content;
        }
        _FORCE_INLINE_ operator string() {
            return content;
        }
        _FORCE_INLINE_ operator const string() const {
            return content;
        }
        _FORCE_INLINE_ virtual string str() const {
            return content;
        }
        _FORCE_INLINE_ String &operator=(const string &str) {
            content = str;
            return *this;
        }
        _FORCE_INLINE_ String &operator=(const String &other) {
            content = other.content;
            return *this;
        }
        _FORCE_INLINE_ const char *c_str() {
            return content.c_str();
        }

    CLASS_END

    CLASS_BEGIN_TN(RefString, Ref, 1, String)

    public:
        _FORCE_INLINE_ RefString() {}
        _FORCE_INLINE_ RefString(const string &content) : Ref(new String(content)) {
        }
        _FORCE_INLINE_ operator string() {
            return operator*()->str();
        }
        _FORCE_INLINE_ operator const string() const {
            return operator*()->str();
        }
        _FORCE_INLINE_ virtual string str() const {
            return operator*()->str();
        }
        _FORCE_INLINE_ RefString &operator=(const string &str) {
            operator*()->operator=(str);
            return *this;
        }
        _FORCE_INLINE_ RefString &operator=(const String &other) {
            operator*()->operator=(other);
            return *this;
        }

    CLASS_END
}


#endif //HI_RENDER_PROJECT_ANDROID_STRING_H
