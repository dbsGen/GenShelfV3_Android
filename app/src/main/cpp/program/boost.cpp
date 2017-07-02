//
// Created by mac on 2017/5/26.
//



#include <jni.h>
#include <utils/FileSystem.h>
#include "common/load_classes.h"

extern "C" {

JNIEXPORT void JNICALL Java_cn_gen_gsv2_MainActivity_init(JNIEnv * env, jobject jobj, jstring resource_path, jstring storage_path) {
    const char *rpath = env->GetStringUTFChars(resource_path, NULL);
    hirender::FileSystem::getInstance()->setResourcePath(rpath);
    env->ReleaseStringUTFChars(resource_path, rpath);
    const char *spath = env->GetStringUTFChars(storage_path, NULL);
    hirender::FileSystem::getInstance()->setStoragePath(spath);
    env->ReleaseStringUTFChars(resource_path, spath);
    GS_load_classes();
}

}