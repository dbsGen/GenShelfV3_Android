//
// Created by gen on 16/9/1.
//

#ifndef VOIPPROJECT_PROPERTY_H
#define VOIPPROJECT_PROPERTY_H

#include <map>
#include "Method.h"
#include "core_define.h"

namespace hicore {
    class Property {
        BASE_CLASS_DEFINE

        const HClass    *clazz;
        const HMethod   *getter;
        const HMethod   *setter;
        StringName      *name;

        variant_map     *labels;

    public:
        _FORCE_INLINE_ Property() {}
        Property(const HClass *clazz,
                 const char *name,
                 const HMethod *getter,
                 const HMethod *setter);
        Property(const HClass *clazz,
                 const char *name,
                 const HMethod *getter,
                 const HMethod *setter,
                 const variant_map &labels);
        ~Property();

        _FORCE_INLINE_ const HClass *getOwnerClass() const {
            return clazz;
        }

        _FORCE_INLINE_ const HMethod *getGetter() const {
            return getter;
        }
        _FORCE_INLINE_ const HMethod *getSetter() const {
            return setter;
        }
        _FORCE_INLINE_ const StringName &getName() const {
            return *name;
        }

        _FORCE_INLINE_ Variant get(HObject *obj) const {
            return getter->call(obj, NULL, 0);
        }
        _FORCE_INLINE_ void set(HObject *obj, const Variant &v) const {
            const Variant *vp[] = {&v};
            setter->call(obj, vp, 1);
        }
        _FORCE_INLINE_ const Variant &getLabel(const StringName &name) const {
            return getLabel(name);
        }
        _FORCE_INLINE_ bool hasLabel(const StringName &name) const {
            return hasLabel(name);
        }
    };
}

#endif //VOIPPROJECT_PROPERTY_H
