//
// Created by gen on 13/04/2017.
//

#ifndef NEXTLAUNCHER_GIT_MODELLOADER_H
#define NEXTLAUNCHER_GIT_MODELLOADER_H

#include <core/Object.h>
#include <core/Data.h>
#include <core/Array.h>
#include <mesh/Mesh.h>
#include "../render_define.h"

using namespace hicore;

namespace hirender {
    CLASS_BEGIN_0_N(ModelLoader)

        pointer_map meshes;
        RefArray names;
        float version;
        size_t cursor;

        bool read(Data *data, void *buffer, size_t len);
        uint64_t readLength(Data *data);

    public:
        ~ModelLoader();

        void clear();
        void load(Data *data);

        /**
         *
         * @return array of StringName
         */
        const RefArray &getNames() {
            return names;
        }
        const Ref<Mesh> &getMesh(const StringName &name);
        _FORCE_INLINE_ float getVersion() {
            return version;
        }

    CLASS_END
}


#endif //NEXTLAUNCHER_GIT_MODELLOADER_H
