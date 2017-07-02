//
//  Math.hpp
//  hirender_iOS
//
//  Created by gen on 16/6/25.
//  Copyright © 2016年 gen. All rights reserved.
//

#ifndef HIRENDER_MATH_H
#define HIRENDER_MATH_H

#include <vector>
#include <math.h>
#include <core/core_define.h>

using namespace std;

namespace hicore {
    inline unsigned int nextPowerOf2(unsigned int in) {
        in -= 1;
        
        in |= in >> 16;
        in |= in >> 8;
        in |= in >> 4;
        in |= in >> 2;
        in |= in >> 1;
        
        return in + 1;
    }

    template <class T>
    inline typename vector<T>::const_iterator list_find(vector<T> list, T target) {
        auto it = list.begin();
        for (auto _e = list.end(); it != _e; ++it) {
            if (*it == target) {
                return it;
            }
        }
        return list.end();
    }



    template <typename T>
    inline T hi_max(T a, T b) {
        return a > b ? a : b;
    }
    template <typename T>
    inline T hi_min(T a, T b) {
        return a < b ? a : b;
    }

    template <typename T>
    inline T lerp(const T &from, const T &to, float p) {
        return (from * (1-p) + to * p);
    }
    template <typename T>
    inline T clamp(const T &value, const T &from, const T &to) {
        return hi_min(hi_max(value, from), to);
    }

#ifndef PI
#define PI 3.1415926535898
#endif

#define LIST_SEARCH(LIST, TARGET) ({ \
    auto it = LIST.begin();\
    for (auto _e = LIST.end(); it != _e; ++it) { \
        if (*it == TARGET) { \
            break;\
        } \
    } \
    it; \
})
    
#define LIST_MIN(LIST) ({ \
    auto i = LIST.front(); \
    for (auto it = LIST.begin(), _e = LIST.end(); it != _e; ++it) { \
        if (*it < i) { \
            i = *it; \
        } \
    } \
    i; \
})
    
#define LIST_MAX(LIST) ({ \
    auto i = LIST.front(); \
    for (auto it = LIST.begin(), _e = LIST.end(); it != _e; ++it) { \
    if (*it > i) { \
        i = *it; \
        } \
    } \
    i; \
})
    
}

#endif /* HIRENDER_MATH_H */
