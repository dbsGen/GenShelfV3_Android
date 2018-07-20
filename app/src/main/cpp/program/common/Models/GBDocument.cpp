//
// Created by mac on 2018/7/18.
//

#include "GBDocument.h"

using namespace nl;

Array GBNode::css(const char *str) {
    Array arr;

    CSelection selection = node.find(str);
    for (int i = 0, t = selection.nodeNum(); i < t; ++i) {
        arr << new GBNode(selection.nodeAt(i));
    }

    return arr;
}

string GBNode::getAttribute(const char *name) {
    return node.attribute(name);
}

string GBNode::getContent() {
    return node.text();
}

long GBNode::getChildrenCount() {
    return node.childNum();
}

Ref<GBNode> GBNode::getChild(int i) {
    return new GBNode(node.childAt(i));
}

void GBDocument::initialize(const Ref<Data> &data) {
    doc.parse(data->text());
}

Array GBDocument::css(const char *str) {
    Array arr;

    CSelection selection = doc.find(str);
    for (int i = 0, t = selection.nodeNum(); i < t; ++i) {
        arr << new GBNode(selection.nodeAt(i));
    }

    return arr;
}