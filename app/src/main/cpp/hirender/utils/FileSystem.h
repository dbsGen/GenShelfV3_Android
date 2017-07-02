//
//  FileSystem.hpp
//  hirender_iOS
//
//  Created by gen on 29/12/2016.
//  Copyright © 2016 gen. All rights reserved.
//

#ifndef FileSystem_hpp
#define FileSystem_hpp

#include "../core/Singleton.h"
#include "../core/Data.h"

using namespace hicore;

namespace hirender {
    CLASS_BEGIN_TNV(FileSystem, Singleton, 1, FileSystem)
    
    string resource_path;
    string storage_path;
    map<StringName, string> configs;
    
    void save() const;
    void updateStoragePath();
    
public:
    
    _FORCE_INLINE_ void setResourcePath(string &&rpath) {
        resource_path = rpath;
    }
    _FORCE_INLINE_ void setResourcePath(const string &rpath) {
        resource_path = rpath;
    }
    _FORCE_INLINE_ const string &getResourcePath() {
        return resource_path;
    }
    
    _FORCE_INLINE_ string resourcePath(const string &path) {
        return resource_path + "/" + path;
    }
    _FORCE_INLINE_ void setStoragePath(const string &path) {
        storage_path = path;
        updateStoragePath();
    }
    _FORCE_INLINE_ void setStoragePath(string &&path) {
        storage_path = path;
        updateStoragePath();
    }
    _FORCE_INLINE_ const string &getStoragePath() {
        return storage_path;
    }
    
    _FORCE_INLINE_ void processDefaultConfig(const Ref<Data> &data);
    bool configGet(const StringName &name, string &str) const;
    void configSet(const StringName &name, const string &value);
    Ref<Data> resource(const string &name);
    
    CLASS_END
}

#endif /* FileSystem_hpp */
