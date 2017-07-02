//
//  load_classes.cpp
//  GenS
//
//  Created by gen on 17/05/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#include "load_classes.h"
#include "Models/Book.h"
#include "Models/Chapter.h"
#include "Models/Page.h"
#include "Models/Shop.h"
#include "Models/Settings.h"
#include "Models/DuktapeEngine.h"
#include "Utils/Encoder/Encoder.h"
#include <core/math/Type.h>

void GS_load_classes() {
    nl::Book::getClass();
    nl::Chapter::getClass();
    nl::Page::getClass();
    nl::SettingItem::getClass();
    nl::Shop::getClass();
    nl::Library::getClass();
    nl::Reader::getClass();
    nl::DuktapeEngine::getClass();
    nl::Encoder::getClass();
}
