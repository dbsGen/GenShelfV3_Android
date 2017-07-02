//
//  SQLite.hpp
//  hirender_iOS
//
//  Created by gen on 12/05/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#ifndef SQLite_hpp
#define SQLite_hpp

#include <Plugin.h>
#include "Model.h"
#include "../../render_define.h"

struct sqlite3;
typedef struct sqlite3 sqlite3;
namespace hirender {
    
    CLASS_BEGIN_NV(SQLQuery, Query)
    
    string sql_sentence;
    
    void insertAction(const string &name, const Variant &val, const char *action);
    
protected:
    void find();
    
public:
    Query *equal(const string &name, const Variant &val);
    _FORCE_INLINE_ SQLQuery(Table *table) : Query(table) {
    }
    
    CLASS_END
    
    CLASS_BEGIN_N(SQLite, Database)
    
    sqlite3 *db;
    string path;
    
protected:
    void begin();
    void action(const string &statement, variant_vector *params, const Ref<Callback> &callback);
    void end();
public:
    SQLite() {}
    _FORCE_INLINE_ virtual Ref<Query> query(Table *table) const {
        return new SQLQuery(table);
    }
    void initialize(const string &path);
    
    void processTable(Table *table);
    void update(HObject *model, Table *table);
    void remove(HObject *model, Table *table);
    
    CLASS_END
    
}

#endif /* SQLite_hpp */
