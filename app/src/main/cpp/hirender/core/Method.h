//
// Created by gen on 16/8/30.
//

#ifndef VOIPPROJECT_METHODINFO_H
#define VOIPPROJECT_METHODINFO_H

#include <vector>
#include <string>
#include <list>
#include <map>
#include "Variant.h"
#include "Define.h"
#include "core_define.h"

using namespace std;

namespace hicore {
    class HClass;
    class StringName;

    class HMethod {
        BASE_CLASS_DEFINE

#define METHOD_PARAMS_MASK 0xffff
    public:
        enum Type {
            Static,
            Member,
            ConstMb
        };

        const HClass    *return_type;
        const HClass   **params_types;
        variant_map     *labels;
        Variant         *default_values;
        struct _params {
            uint8_t p_count;
            uint8_t d_count;
            uint8_t type;
        } params;
        StringName      name;
    protected:
        HMethod(const char *name);
        ~HMethod();
        _FORCE_INLINE_ void setReturnType(const HClass *rt) {
            return_type = rt;
        }
        // NEED CHECK ?
        void setParamsType(const HClass   **const pts, int count) {
//            int size = count * sizeof(void*);
//            params_types = (const HClass **)malloc(size);
//            memcpy(params_types, pts, size);
            params.p_count = count;
        }
        void setLabels(const variant_map &labels) {
            if (!this->labels) this->labels = new variant_map;
            this->labels->operator=(labels);
        }
        // NEED CHECK ?
        void setDefaultValues(const Variant *dv, int count) {
            default_values = new Variant[count];
            for (int i = 0; i < count; ++i) default_values[i] = dv[i];
            params.d_count = count;
        }
        _FORCE_INLINE_ void setType(Type t) {params.type = t;}

        virtual Variant _call(void *obj, const Variant **params) const = 0;

    public:
        Variant call(void *obj, const Variant **params, int count) const;

        _FORCE_INLINE_ const StringName &getName() const {return name;}
        _FORCE_INLINE_ uint8_t          getParamsCount() const {return params.p_count;}
        _FORCE_INLINE_ uint8_t          getDefaultCount() const {return params.d_count;}
        _FORCE_INLINE_ const Variant *  getDefaultValues() const {return default_values;}
        _FORCE_INLINE_ Type             getType() const {return (Type)params.type;}
        _FORCE_INLINE_ const HClass *   getReturnType() { return return_type; }
        _FORCE_INLINE_ const HClass *   getParamsType(int idx) { return params_types[idx]; }
        _FORCE_INLINE_ const variant_map &getLabels() {return *labels;};

    };
}

#endif //VOIPPROJECT_METHODINFO_H
