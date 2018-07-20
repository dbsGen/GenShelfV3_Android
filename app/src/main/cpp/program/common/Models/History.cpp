//
// Created by mac on 2017/8/27.
//

#include "History.h"

using namespace nl;

const int History_count_per_page = 20;


void History::visit(const Ref<Book> &book) {
    if (book && !book->getUrl().empty()) {
        const string &url = book->getUrl();

        Array arr = query()->equal("url", url)->results();
        Ref<History> his;
        if (arr.size() > 0) {
            his = arr.at(0).ref();
        }else {
            his = new History;
            JSONNODE *node = book->unparse();
            char *str = json_write(node);
            his->setContent(str);
            his->setUrl(url);
            json_free(str);
            json_delete(node);
        }
        struct timeval tp;
        gettimeofday(&tp, NULL);
        long long time = static_cast<long long>(tp.tv_sec * 1000 + tp.tv_usec * 1.0E-3);
        his->setDate(time);
        his->save();
    }
}

Array History::histories(long long from) {
    Ref<Query> q = query()->less("date", from)->sortBy("date")->limit(History_count_per_page);
    q->setSortAsc(false);
    return q->results();
}

Ref<Book> History::getBook() const {
    JSONNODE *node = json_parse(getContent().c_str());
    Book *book = Book::parse(node);
    json_delete(node);
    return book;
}

void History::clear() {
    query()->remove();
}