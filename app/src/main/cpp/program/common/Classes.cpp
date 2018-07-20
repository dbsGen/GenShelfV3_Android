//
// Created by gen on 09/08/2017.
//


#include <utils/xml/XMLDocument.h>
#include <utils/network/HTTPClient.h>
#include <core/Data.h>
#include <core/Callback.h>
#include <core/Map.h>
#include <core/Array.h>
#include <utils/NotificationCenter.h>
#include <script/java/JScript.h>
#include <script/java/JClass.h>
#include <script/java/JInstance.h>

using namespace gcore;

void ClassDB::loadClasses() {
#ifdef USING_SCRIPT
    class_loaders[h("gr::HTTPClient")] = (void*)&gr::HTTPClient::getClass;
    class_loaders[h("gcore::Callback")] = (void*)&gcore::Callback::getClass;
    class_loaders[h("gr::XMLDocument")] = (void*)&gr::XMLDocument::getClass;
    class_loaders[h("gr::XMLNode")] = (void*)&gr::XMLNode::getClass;
    class_loaders[h("gcore::FileData")] = (void*)&gcore::FileData::getClass;
    class_loaders[h("gr::NotificationCenter")] = (void*)&gr::NotificationCenter::getClass;
    class_loaders[h("gcore::Map")] = (void*)&gcore::Map::getClass;
    class_loaders[h("gcore::Array")] = (void*)&gcore::Array::getClass;

//    class_loaders[h("hirender::Animator")] = (void*)&hirender::Animator::getClass;
//    class_loaders[h("hirender::AnimatorMethod")] = (void*)&hirender::AnimatorMethod::getClass;
//    class_loaders[h("hirender::AnimatorAction")] = (void*)&hirender::AnimatorAction::getClass;
//    class_loaders[h("hirender::Ease")] = (void*)&hirender::Ease::getClass;
#ifdef __ANDROID__
    void *load_jscript = (void*)&gscript::JScript::instance;
    class_loaders[h("gscript::JClass")] = (void*)&gscript::JClass::getClass;
    class_loaders[h("gscript::JInstance")] = (void*)&gscript::JInstance::getClass;
#endif

#endif
}
