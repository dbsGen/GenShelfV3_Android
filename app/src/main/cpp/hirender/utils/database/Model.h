//
//  Model.hpp
//  hirender_iOS
//
//  Created by gen on 12/05/2017.
//  Copyright © 2017 gen. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <core/Ref.h>
#include <Plugin.h>
#include <core/Callback.h>
#include "DBMaker.h"
#include "../../render_define.h"

using namespace hicore;

namespace hirender {
    struct Table {
        const HClass *cls;
        pointer_map fields;
        float version;
        bool is_init;
        
    };
    template <class T>
    struct TableContainer {
        static Table *table;
    };
    template <class T>
    Table *TableContainer<T>::table = NULL;
    
    struct Field {
        enum Type {
            /**
             * getter: int getter()
             * setter: void setter(int v)
             */
            Integer,
            
            /**
             * getter: float getter()
             * setter: void setter(float v)
             */
            
            Real,
            
            /**
             * getter: const string &getter()
             * setter: void setter(const string & v)
             */
            Text,
            
            /**
             * getter: const Data & getter()
             * setter: void setter(const Data & v)
             */
            Blob,
            None
        };
        
        StringName name;
        string limit;
        bool index;
        bool primary;
        bool nullable;
        Type type;
        
        virtual void get(void *model, void *val) = 0;
        virtual void set(void *model, void *val) = 0;
    };
    
    template<class T, typename I>
    struct FieldImp : public Field {
        typedef void(T::*Setter)(I);
        typedef I(T::*Getter)();
        
        Setter setter;
        Getter getter;
        
        void get(void *model, void *val) {
            *(typename remove_const<typename remove_reference<I>::type>::type*)val = ((*(T*)model).*getter)();
        }
        void set(void *model, void *val) {
            ((*(T*)model).*setter)(*(typename remove_const<typename remove_reference<I>::type>::type*)val);
        }
        
        FieldImp(Setter s, Getter g) : setter(s), getter(g) {
        }
    };
    
    template<class ...Argv>
    struct type_det {};
    template<class T>
    struct type_det<int, T> {
        static const Field::Type type = Field::Integer;
    };
    template<class T>
    struct type_det<float, T> {
        static const Field::Type type = Field::Real;
    };
    template<class T>
    struct type_det<const string &, T> {
        static const Field::Type type = Field::Text;
    };
    
    template<class T, typename I>
    Field *makeField(void(T::*setter)(I),
                     I(T::*getter)(),
                     const StringName &name,
                     bool index,
                     bool primary = false,
                     bool nullable = true) {
        Field *field = new FieldImp<T, I>(setter, getter);
        field->name = name;
        field->type = type_det<I,I>::type;
        field->index = index;
        field->primary = primary;
        field->nullable = nullable;
        return field;
    }
    
    CLASS_BEGIN_NV(Query, RefObject)
    
    bool changed;
    
protected:
    const Table *table;
    int _limit;
    int _offset;
    ref_vector _results;
    _FORCE_INLINE_ void change() {
        changed = true;
    }
    virtual void find() = 0;
    
public:
    Query(const Table *table) : table(table), changed(false), _limit(0), _offset(0) {
    }
    const ref_vector &res();
    METHOD RefArray results();
    METHOD virtual Query *equal(const string &name, const Variant &val) = 0;
    METHOD _FORCE_INLINE_ Query *limit(int l) {
        _limit = l;
        return this;
    }
    METHOD _FORCE_INLINE_ Query *offset(int o) {
        _offset = o;
        return this;
    }
    
    
    protected:
        ON_LOADED_BEGIN(cls, RefObject)
            ADD_METHOD(cls, Query, results);
            ADD_METHOD(cls, Query, equal);
            ADD_METHOD(cls, Query, limit);
            ADD_METHOD(cls, Query, offset);
        ON_LOADED_END
    CLASS_END
    
    CLASS_BEGIN_NV(Database, Plugin)
    
    void checkQueue();
    
protected:
    pointer_vector queue;
    struct QueueItem {
        string statement;
        variant_vector *params;
        Ref<Callback> callback;
        
        QueueItem(const string &statement, variant_vector *params, const Ref<Callback> &callback) : statement(statement), callback(callback), params(params) {}
    };
    mutex mtx;
    
    virtual void begin() = 0;
    virtual void action(const string &statement, variant_vector *params, const Ref<Callback> &callback) = 0;
    virtual void end() = 0;
    
public:
    virtual void fixedStep(Renderer *renderer, Time delta);
    
    virtual Ref<Query> query(Table *table) const = 0;
    virtual void exce(const string &statement, variant_vector *params, const Ref<Callback> &callback);
    virtual void queueExce(const string &statement, variant_vector *params, const Ref<Callback> &callback);
    
    virtual void processTable(Table *table) = 0;
    virtual void update(HObject *model, Table *table) = 0;
    virtual void remove(HObject *model, Table *table) = 0;
    
    ~Database();
    
    CLASS_END
    
    CLASS_BEGIN_N(BaseModel, RefObject)
    
protected:
    bool changed;
public:
    _FORCE_INLINE_ void done() {
        changed = false;
    }
    
    CLASS_END
    
    template <class T>
    CLASS_BEGIN_N(Model, BaseModel)
    
    friend class SQLite;
    
#define DEFINE_FIELD(TYPE, PROPERTY, CAPITALIZE) private: \
    TYPE PROPERTY; \
public: \
    _FORCE_INLINE_ void set##CAPITALIZE(TYPE PROPERTY) { \
        if (this->PROPERTY != PROPERTY) { \
            this->PROPERTY = PROPERTY; \
            changed = true; \
        } \
    }\
    _FORCE_INLINE_ TYPE get##CAPITALIZE() { \
        return PROPERTY; \
    }
    
#define DEFINE_STRING(PROPERTY, CAPITALIZE) private: \
    string PROPERTY; \
public: \
    _FORCE_INLINE_ void set##CAPITALIZE(const string &PROPERTY) { \
        if (this->PROPERTY == PROPERTY) return; \
        this->PROPERTY = PROPERTY; \
        changed = true; \
    }\
    _FORCE_INLINE_ const string &get##CAPITALIZE() { \
        return PROPERTY; \
    }
    
    DEFINE_FIELD(int, identifier, Identifier);
    
protected:
    
    static pointer_map *fields() {
        return &TableContainer<T>::table->fields;
    }
    
    static float version() {
        return 0;
    }
#define ADD_FILED(CLASS, PROPERTY, CAPITALIZE, ...) {StringName name(#PROPERTY);fields()->operator[](name) = makeField(&CLASS::set##CAPITALIZE, &CLASS::get##CAPITALIZE, name, __VA_ARGS__);}
    static void registerFields() {
        if (!TableContainer<T>::table) {
            Table *table = new Table;
            table->cls = T::getClass();
            table->version = T::version();
            table->is_init = false;
            TableContainer<T>::table = table;
        }
        ADD_FILED(Model, identifier, Identifier, true, true);
    }
private:
    static void checkTable() {
        if (!TableContainer<T>::table) {
            T::registerFields();
            db::database()->processTable(TableContainer<T>::table);
        }
    }
    
public:
    Model() : identifier(-1) {
    }
    METHOD _FORCE_INLINE_ static Ref<Query> query() {
        checkTable();
        return db::database()->query(TableContainer<T>::table);
    }
    
    METHOD static Ref<T> find(int identifier) {
        Ref<Query> q = query();
        const ref_vector &results = q->equal("identifier", identifier)->limit(1)->res();
        if (results.size()) {
            return results.front();
        }else {
            return Ref<T>::null();
        }
    }
    
    METHOD void save() {
        if (changed) {
            checkTable();
            db::database()->update(this, TableContainer<T>::table);
        }
    }
    METHOD void remove() {
        checkTable();
        db::database()->remove(this, TableContainer<T>::table);
    }
    
    protected:
        ON_LOADED_BEGIN(cls, BaseModel)
            ADD_METHOD(cls, Model, query);
            ADD_METHOD(cls, Model, find);
            ADD_METHOD(cls, Model, save);
            ADD_METHOD(cls, Model, remove);
        ON_LOADED_END
    CLASS_END
}

#endif /* Model_hpp */
