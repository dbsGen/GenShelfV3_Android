//
// Created by mac on 2017/10/11.
//

#include "SearchTip.h"

using namespace nl;

void SearchTip::insert(const string &key) {
    Ref<Query> q = query();
    Array arr = q->equal("key", key)->results();
    Ref<SearchTip> tip;
    if (arr.size() == 0) {
        tip = new SearchTip;
        tip->setKey(key);
    }else {
        tip = arr.at(0).ref();
    }
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long time = static_cast<long long>(tp.tv_sec * 1000 + tp.tv_usec * 1.0E-3);
    tip->setDate(time);
    tip->save();
}

Array SearchTip::search(const string &key) {
    string search_key = "%";
    if (!key.empty()) {
        search_key += key + '%';
    }
    Array rets;
    Ref<Query> q = query();
    Array arr = q->like("key", search_key)->sortBy("date")->limit(5)->results();
    for (auto it = arr->begin(), _e = arr->end(); it != _e; ++it) {
        Ref<SearchTip> t = *it;
        rets << t->getKey();
    }
    return rets;
}

void SearchTip::removeKey(const string &key) {
    Ref<Query> q = query();
    Array arr = q->equal("key", key)->results();
    if (arr.size() > 0) {
        Ref<SearchTip> tip = arr.at(0).ref();
        tip->remove();
    }
}