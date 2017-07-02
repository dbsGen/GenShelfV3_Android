//
// Created by gen on 16/9/9.
//

#ifdef __ANDROID__
#ifndef VOIPPROJECT_ASSETDATA_H
#define VOIPPROJECT_ASSETDATA_H

#include <core/Data.h>
#include <android/asset_manager.h>
#include "../../render_define.h"

namespace hirender {
    CLASS_BEGIN_N(AssetData, hicore::Data)

        static AAssetManager *asset_manager;
        AAsset *asset;
        string resource_path;

    public:
        _FORCE_INLINE_ static void setAssetManager(AAssetManager *manager) {
            asset_manager = manager;
        }

        virtual long getSize() const;
        virtual const void *getBuffer();
        virtual bool empty() const;
        virtual bool gets(void *chs, long start, long len);
        virtual void close();

        AssetData();
        AssetData(const char *name);
        ~AssetData();

    CLASS_END
}


#endif //VOIPPROJECT_ASSETDATA_H
#endif //__ANDROID__
