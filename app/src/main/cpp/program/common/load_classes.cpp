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
#include "Models/KeyValue.h"
#include "Models/DuktapeEngine.h"
#include "Utils/Encoder/Encoder.h"
#include "Models/ArtBasket.h"
#include "Models/History.h"
#include "Models/SearchTip.h"
#include "Models/GBDocument.h"
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
    nl::KeyValue::getClass();
    nl::Art::getClass();
    nl::ArtBasket::getClass();
    nl::History::getClass();
    nl::SearchTip::getClass();
    nl::GBNode::getClass();
    nl::GBDocument::getClass();
}
