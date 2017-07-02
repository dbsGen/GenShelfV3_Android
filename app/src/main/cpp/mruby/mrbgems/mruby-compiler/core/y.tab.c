/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 7 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:339  */

#undef PARSER_DEBUG
#ifdef PARSER_DEBUG
# define YYDEBUG 1
#endif
#define YYERROR_VERBOSE 1
/*
 * Force yacc to use our memory management.  This is a little evil because
 * the macros assume that "parser_state *p" is in scope
 */
#define YYMALLOC(n)    mrb_malloc(p->mrb, (n))
#define YYFREE(o)      mrb_free(p->mrb, (o))
#define YYSTACK_USE_ALLOCA 0

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>
#include <mruby/error.h>
#include <mruby/throw.h>
#include "node.h"

#define YYLEX_PARAM p

typedef mrb_ast_node node;
typedef struct mrb_parser_state parser_state;
typedef struct mrb_parser_heredoc_info parser_heredoc_info;

static int yyparse(parser_state *p);
static int yylex(void *lval, parser_state *p);
static void yyerror(parser_state *p, const char *s);
static void yywarn(parser_state *p, const char *s);
static void yywarning(parser_state *p, const char *s);
static void backref_error(parser_state *p, node *n);
static void tokadd(parser_state *p, int32_t c);

#define identchar(c) (ISALNUM(c) || (c) == '_' || !ISASCII(c))

typedef unsigned int stack_type;

#define BITSTACK_PUSH(stack, n) ((stack) = ((stack)<<1)|((n)&1))
#define BITSTACK_POP(stack)     ((stack) = (stack) >> 1)
#define BITSTACK_LEXPOP(stack)  ((stack) = ((stack) >> 1) | ((stack) & 1))
#define BITSTACK_SET_P(stack)   ((stack)&1)

#define COND_PUSH(n)    BITSTACK_PUSH(p->cond_stack, (n))
#define COND_POP()      BITSTACK_POP(p->cond_stack)
#define COND_LEXPOP()   BITSTACK_LEXPOP(p->cond_stack)
#define COND_P()        BITSTACK_SET_P(p->cond_stack)

#define CMDARG_PUSH(n)  BITSTACK_PUSH(p->cmdarg_stack, (n))
#define CMDARG_POP()    BITSTACK_POP(p->cmdarg_stack)
#define CMDARG_LEXPOP() BITSTACK_LEXPOP(p->cmdarg_stack)
#define CMDARG_P()      BITSTACK_SET_P(p->cmdarg_stack)

#define SET_LINENO(c,n) ((c)->lineno = (n))
#define NODE_LINENO(c,n) do {\
  if (n) {\
     (c)->filename_index = (n)->filename_index;\
     (c)->lineno = (n)->lineno;\
  }\
} while (0)

#define sym(x) ((mrb_sym)(intptr_t)(x))
#define nsym(x) ((node*)(intptr_t)(x))
#define nint(x) ((node*)(intptr_t)(x))
#define intn(x) ((int)(intptr_t)(x))

static inline mrb_sym
intern_cstr_gen(parser_state *p, const char *s)
{
  return mrb_intern_cstr(p->mrb, s);
}
#define intern_cstr(s) intern_cstr_gen(p,(s))

static inline mrb_sym
intern_gen(parser_state *p, const char *s, size_t len)
{
  return mrb_intern(p->mrb, s, len);
}
#define intern(s,len) intern_gen(p,(s),(len))

static inline mrb_sym
intern_gen_c(parser_state *p, const char c)
{
  return mrb_intern(p->mrb, &c, 1);
}
#define intern_c(c) intern_gen_c(p,(c))

static void
cons_free_gen(parser_state *p, node *cons)
{
  cons->cdr = p->cells;
  p->cells = cons;
}
#define cons_free(c) cons_free_gen(p, (c))

static void*
parser_palloc(parser_state *p, size_t size)
{
  void *m = mrb_pool_alloc(p->pool, size);

  if (!m) {
    MRB_THROW(p->jmp);
  }
  return m;
}

static node*
cons_gen(parser_state *p, node *car, node *cdr)
{
  node *c;

  if (p->cells) {
    c = p->cells;
    p->cells = p->cells->cdr;
  }
  else {
    c = (node *)parser_palloc(p, sizeof(mrb_ast_node));
  }

  c->car = car;
  c->cdr = cdr;
  c->lineno = p->lineno;
  c->filename_index = p->current_filename_index;
  return c;
}
#define cons(a,b) cons_gen(p,(a),(b))

static node*
list1_gen(parser_state *p, node *a)
{
  return cons(a, 0);
}
#define list1(a) list1_gen(p, (a))

static node*
list2_gen(parser_state *p, node *a, node *b)
{
  return cons(a, cons(b,0));
}
#define list2(a,b) list2_gen(p, (a),(b))

static node*
list3_gen(parser_state *p, node *a, node *b, node *c)
{
  return cons(a, cons(b, cons(c,0)));
}
#define list3(a,b,c) list3_gen(p, (a),(b),(c))

static node*
list4_gen(parser_state *p, node *a, node *b, node *c, node *d)
{
  return cons(a, cons(b, cons(c, cons(d, 0))));
}
#define list4(a,b,c,d) list4_gen(p, (a),(b),(c),(d))

static node*
list5_gen(parser_state *p, node *a, node *b, node *c, node *d, node *e)
{
  return cons(a, cons(b, cons(c, cons(d, cons(e, 0)))));
}
#define list5(a,b,c,d,e) list5_gen(p, (a),(b),(c),(d),(e))

static node*
list6_gen(parser_state *p, node *a, node *b, node *c, node *d, node *e, node *f)
{
  return cons(a, cons(b, cons(c, cons(d, cons(e, cons(f, 0))))));
}
#define list6(a,b,c,d,e,f) list6_gen(p, (a),(b),(c),(d),(e),(f))

static node*
append_gen(parser_state *p, node *a, node *b)
{
  node *c = a;

  if (!a) return b;
  while (c->cdr) {
    c = c->cdr;
  }
  if (b) {
    c->cdr = b;
  }
  return a;
}
#define append(a,b) append_gen(p,(a),(b))
#define push(a,b) append_gen(p,(a),list1(b))

static char*
parser_strndup(parser_state *p, const char *s, size_t len)
{
  char *b = (char *)parser_palloc(p, len+1);

  memcpy(b, s, len);
  b[len] = '\0';
  return b;
}
#undef strndup
#define strndup(s,len) parser_strndup(p, s, len)

static char*
parser_strdup(parser_state *p, const char *s)
{
  return parser_strndup(p, s, strlen(s));
}
#undef strdup
#define strdup(s) parser_strdup(p, s)

/* xxx ----------------------------- */

static node*
local_switch(parser_state *p)
{
  node *prev = p->locals;

  p->locals = cons(0, 0);
  return prev;
}

static void
local_resume(parser_state *p, node *prev)
{
  p->locals = prev;
}

static void
local_nest(parser_state *p)
{
  p->locals = cons(0, p->locals);
}

static void
local_unnest(parser_state *p)
{
  if (p->locals) {
    p->locals = p->locals->cdr;
  }
}

static mrb_bool
local_var_p(parser_state *p, mrb_sym sym)
{
  node *l = p->locals;

  while (l) {
    node *n = l->car;
    while (n) {
      if (sym(n->car) == sym) return TRUE;
      n = n->cdr;
    }
    l = l->cdr;
  }
  return FALSE;
}

static void
local_add_f(parser_state *p, mrb_sym sym)
{
  if (p->locals) {
    p->locals->car = push(p->locals->car, nsym(sym));
  }
}

static void
local_add(parser_state *p, mrb_sym sym)
{
  if (!local_var_p(p, sym)) {
    local_add_f(p, sym);
  }
}

static node*
locals_node(parser_state *p)
{
  return p->locals ? p->locals->car : NULL;
}

/* (:scope (vars..) (prog...)) */
static node*
new_scope(parser_state *p, node *body)
{
  return cons((node*)NODE_SCOPE, cons(locals_node(p), body));
}

/* (:begin prog...) */
static node*
new_begin(parser_state *p, node *body)
{
  if (body) {
    return list2((node*)NODE_BEGIN, body);
  }
  return cons((node*)NODE_BEGIN, 0);
}

#define newline_node(n) (n)

/* (:rescue body rescue else) */
static node*
new_rescue(parser_state *p, node *body, node *resq, node *els)
{
  return list4((node*)NODE_RESCUE, body, resq, els);
}

/* (:ensure body ensure) */
static node*
new_ensure(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_ENSURE, cons(a, cons(0, b)));
}

/* (:nil) */
static node*
new_nil(parser_state *p)
{
  return list1((node*)NODE_NIL);
}

/* (:true) */
static node*
new_true(parser_state *p)
{
  return list1((node*)NODE_TRUE);
}

/* (:false) */
static node*
new_false(parser_state *p)
{
  return list1((node*)NODE_FALSE);
}

/* (:alias new old) */
static node*
new_alias(parser_state *p, mrb_sym a, mrb_sym b)
{
  return cons((node*)NODE_ALIAS, cons(nsym(a), nsym(b)));
}

/* (:if cond then else) */
static node*
new_if(parser_state *p, node *a, node *b, node *c)
{
  return list4((node*)NODE_IF, a, b, c);
}

/* (:unless cond then else) */
static node*
new_unless(parser_state *p, node *a, node *b, node *c)
{
  return list4((node*)NODE_IF, a, c, b);
}

/* (:while cond body) */
static node*
new_while(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_WHILE, cons(a, b));
}

/* (:until cond body) */
static node*
new_until(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_UNTIL, cons(a, b));
}

/* (:for var obj body) */
static node*
new_for(parser_state *p, node *v, node *o, node *b)
{
  return list4((node*)NODE_FOR, v, o, b);
}

/* (:case a ((when ...) body) ((when...) body)) */
static node*
new_case(parser_state *p, node *a, node *b)
{
  node *n = list2((node*)NODE_CASE, a);
  node *n2 = n;

  while (n2->cdr) {
    n2 = n2->cdr;
  }
  n2->cdr = b;
  return n;
}

/* (:postexe a) */
static node*
new_postexe(parser_state *p, node *a)
{
  return cons((node*)NODE_POSTEXE, a);
}

/* (:self) */
static node*
new_self(parser_state *p)
{
  return list1((node*)NODE_SELF);
}

/* (:call a b c) */
static node*
new_call(parser_state *p, node *a, mrb_sym b, node *c, int pass)
{
  node *n = list4(nint(pass?NODE_CALL:NODE_SCALL), a, nsym(b), c);
  NODE_LINENO(n, a);
  return n;
}

/* (:fcall self mid args) */
static node*
new_fcall(parser_state *p, mrb_sym b, node *c)
{
  node *n = new_self(p);
  NODE_LINENO(n, c);
  n = list4((node*)NODE_FCALL, n, nsym(b), c);
  NODE_LINENO(n, c);
  return n;
}

/* (:super . c) */
static node*
new_super(parser_state *p, node *c)
{
  return cons((node*)NODE_SUPER, c);
}

/* (:zsuper) */
static node*
new_zsuper(parser_state *p)
{
  return list1((node*)NODE_ZSUPER);
}

/* (:yield . c) */
static node*
new_yield(parser_state *p, node *c)
{
  if (c) {
    if (c->cdr) {
      yyerror(p, "both block arg and actual block given");
    }
    return cons((node*)NODE_YIELD, c->car);
  }
  return cons((node*)NODE_YIELD, 0);
}

/* (:return . c) */
static node*
new_return(parser_state *p, node *c)
{
  return cons((node*)NODE_RETURN, c);
}

/* (:break . c) */
static node*
new_break(parser_state *p, node *c)
{
  return cons((node*)NODE_BREAK, c);
}

/* (:next . c) */
static node*
new_next(parser_state *p, node *c)
{
  return cons((node*)NODE_NEXT, c);
}

/* (:redo) */
static node*
new_redo(parser_state *p)
{
  return list1((node*)NODE_REDO);
}

/* (:retry) */
static node*
new_retry(parser_state *p)
{
  return list1((node*)NODE_RETRY);
}

/* (:dot2 a b) */
static node*
new_dot2(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_DOT2, cons(a, b));
}

/* (:dot3 a b) */
static node*
new_dot3(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_DOT3, cons(a, b));
}

/* (:colon2 b c) */
static node*
new_colon2(parser_state *p, node *b, mrb_sym c)
{
  return cons((node*)NODE_COLON2, cons(b, nsym(c)));
}

/* (:colon3 . c) */
static node*
new_colon3(parser_state *p, mrb_sym c)
{
  return cons((node*)NODE_COLON3, nsym(c));
}

/* (:and a b) */
static node*
new_and(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_AND, cons(a, b));
}

/* (:or a b) */
static node*
new_or(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_OR, cons(a, b));
}

/* (:array a...) */
static node*
new_array(parser_state *p, node *a)
{
  return cons((node*)NODE_ARRAY, a);
}

/* (:splat . a) */
static node*
new_splat(parser_state *p, node *a)
{
  return cons((node*)NODE_SPLAT, a);
}

/* (:hash (k . v) (k . v)...) */
static node*
new_hash(parser_state *p, node *a)
{
  return cons((node*)NODE_HASH, a);
}

/* (:sym . a) */
static node*
new_sym(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_SYM, nsym(sym));
}

static mrb_sym
new_strsym(parser_state *p, node* str)
{
  const char *s = (const char*)str->cdr->car;
  size_t len = (size_t)str->cdr->cdr;

  return mrb_intern(p->mrb, s, len);
}

/* (:lvar . a) */
static node*
new_lvar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_LVAR, nsym(sym));
}

/* (:gvar . a) */
static node*
new_gvar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_GVAR, nsym(sym));
}

/* (:ivar . a) */
static node*
new_ivar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_IVAR, nsym(sym));
}

/* (:cvar . a) */
static node*
new_cvar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_CVAR, nsym(sym));
}

/* (:const . a) */
static node*
new_const(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_CONST, nsym(sym));
}

/* (:undef a...) */
static node*
new_undef(parser_state *p, mrb_sym sym)
{
  return list2((node*)NODE_UNDEF, nsym(sym));
}

/* (:class class super body) */
static node*
new_class(parser_state *p, node *c, node *s, node *b)
{
  return list4((node*)NODE_CLASS, c, s, cons(locals_node(p), b));
}

/* (:sclass obj body) */
static node*
new_sclass(parser_state *p, node *o, node *b)
{
  return list3((node*)NODE_SCLASS, o, cons(locals_node(p), b));
}

/* (:module module body) */
static node*
new_module(parser_state *p, node *m, node *b)
{
  return list3((node*)NODE_MODULE, m, cons(locals_node(p), b));
}

/* (:def m lv (arg . body)) */
static node*
new_def(parser_state *p, mrb_sym m, node *a, node *b)
{
  return list5((node*)NODE_DEF, nsym(m), locals_node(p), a, b);
}

/* (:sdef obj m lv (arg . body)) */
static node*
new_sdef(parser_state *p, node *o, mrb_sym m, node *a, node *b)
{
  return list6((node*)NODE_SDEF, o, nsym(m), locals_node(p), a, b);
}

/* (:arg . sym) */
static node*
new_arg(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_ARG, nsym(sym));
}

/* (m o r m2 b) */
/* m: (a b c) */
/* o: ((a . e1) (b . e2)) */
/* r: a */
/* m2: (a b c) */
/* b: a */
static node*
new_args(parser_state *p, node *m, node *opt, mrb_sym rest, node *m2, mrb_sym blk)
{
  node *n;

  n = cons(m2, nsym(blk));
  n = cons(nsym(rest), n);
  n = cons(opt, n);
  return cons(m, n);
}

/* (:block_arg . a) */
static node*
new_block_arg(parser_state *p, node *a)
{
  return cons((node*)NODE_BLOCK_ARG, a);
}

/* (:block arg body) */
static node*
new_block(parser_state *p, node *a, node *b)
{
  return list4((node*)NODE_BLOCK, locals_node(p), a, b);
}

/* (:lambda arg body) */
static node*
new_lambda(parser_state *p, node *a, node *b)
{
  return list4((node*)NODE_LAMBDA, locals_node(p), a, b);
}

/* (:asgn lhs rhs) */
static node*
new_asgn(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_ASGN, cons(a, b));
}

/* (:masgn mlhs=(pre rest post)  mrhs) */
static node*
new_masgn(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_MASGN, cons(a, b));
}

/* (:asgn lhs rhs) */
static node*
new_op_asgn(parser_state *p, node *a, mrb_sym op, node *b)
{
  return list4((node*)NODE_OP_ASGN, a, nsym(op), b);
}

/* (:int . i) */
static node*
new_int(parser_state *p, const char *s, int base)
{
  return list3((node*)NODE_INT, (node*)strdup(s), nint(base));
}

/* (:float . i) */
static node*
new_float(parser_state *p, const char *s)
{
  return cons((node*)NODE_FLOAT, (node*)strdup(s));
}

/* (:str . (s . len)) */
static node*
new_str(parser_state *p, const char *s, int len)
{
  return cons((node*)NODE_STR, cons((node*)strndup(s, len), nint(len)));
}

/* (:dstr . a) */
static node*
new_dstr(parser_state *p, node *a)
{
  return cons((node*)NODE_DSTR, a);
}

/* (:str . (s . len)) */
static node*
new_xstr(parser_state *p, const char *s, int len)
{
  return cons((node*)NODE_XSTR, cons((node*)strndup(s, len), nint(len)));
}

/* (:xstr . a) */
static node*
new_dxstr(parser_state *p, node *a)
{
  return cons((node*)NODE_DXSTR, a);
}

/* (:dsym . a) */
static node*
new_dsym(parser_state *p, node *a)
{
  return cons((node*)NODE_DSYM, new_dstr(p, a));
}

/* (:str . (a . a)) */
static node*
new_regx(parser_state *p, const char *p1, const char* p2, const char* p3)
{
  return cons((node*)NODE_REGX, cons((node*)p1, cons((node*)p2, (node*)p3)));
}

/* (:dregx . a) */
static node*
new_dregx(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_DREGX, cons(a, b));
}

/* (:backref . n) */
static node*
new_back_ref(parser_state *p, int n)
{
  return cons((node*)NODE_BACK_REF, nint(n));
}

/* (:nthref . n) */
static node*
new_nth_ref(parser_state *p, int n)
{
  return cons((node*)NODE_NTH_REF, nint(n));
}

/* (:heredoc . a) */
static node*
new_heredoc(parser_state *p)
{
  parser_heredoc_info *inf = (parser_heredoc_info *)parser_palloc(p, sizeof(parser_heredoc_info));
  return cons((node*)NODE_HEREDOC, (node*)inf);
}

static void
new_bv(parser_state *p, mrb_sym id)
{
}

static node*
new_literal_delim(parser_state *p)
{
  return cons((node*)NODE_LITERAL_DELIM, 0);
}

/* (:words . a) */
static node*
new_words(parser_state *p, node *a)
{
  return cons((node*)NODE_WORDS, a);
}

/* (:symbols . a) */
static node*
new_symbols(parser_state *p, node *a)
{
  return cons((node*)NODE_SYMBOLS, a);
}

/* xxx ----------------------------- */

/* (:call a op) */
static node*
call_uni_op(parser_state *p, node *recv, const char *m)
{
  return new_call(p, recv, intern_cstr(m), 0, 1);
}

/* (:call a op b) */
static node*
call_bin_op(parser_state *p, node *recv, const char *m, node *arg1)
{
  return new_call(p, recv, intern_cstr(m), list1(list1(arg1)), 1);
}

static void
args_with_block(parser_state *p, node *a, node *b)
{
  if (b) {
    if (a->cdr) {
      yyerror(p, "both block arg and actual block given");
    }
    a->cdr = b;
  }
}

static void
call_with_block(parser_state *p, node *a, node *b)
{
  node *n;

  switch ((enum node_type)intn(a->car)) {
  case NODE_SUPER:
  case NODE_ZSUPER:
    if (!a->cdr) a->cdr = cons(0, b);
    else {
      args_with_block(p, a->cdr, b);
    }
    break;
  case NODE_CALL:
  case NODE_FCALL:
    n = a->cdr->cdr->cdr;
    if (!n->car) n->car = cons(0, b);
    else {
      args_with_block(p, n->car, b);
    }
    break;
  default:
    break;
  }
}

static node*
negate_lit(parser_state *p, node *n)
{
  return cons((node*)NODE_NEGATE, n);
}

static node*
cond(node *n)
{
  return n;
}

static node*
ret_args(parser_state *p, node *n)
{
  if (n->cdr) {
    yyerror(p, "block argument should not be given");
    return NULL;
  }
  if (!n->car->cdr) return n->car->car;
  return new_array(p, n->car);
}

static void
assignable(parser_state *p, node *lhs)
{
  if (intn(lhs->car) == NODE_LVAR) {
    local_add(p, sym(lhs->cdr));
  }
}

static node*
var_reference(parser_state *p, node *lhs)
{
  node *n;

  if (intn(lhs->car) == NODE_LVAR) {
    if (!local_var_p(p, sym(lhs->cdr))) {
      n = new_fcall(p, sym(lhs->cdr), 0);
      cons_free(lhs);
      return n;
    }
  }

  return lhs;
}

typedef enum mrb_string_type  string_type;

static node*
new_strterm(parser_state *p, string_type type, int term, int paren)
{
  return cons(nint(type), cons((node*)0, cons(nint(paren), nint(term))));
}

static void
end_strterm(parser_state *p)
{
  cons_free(p->lex_strterm->cdr->cdr);
  cons_free(p->lex_strterm->cdr);
  cons_free(p->lex_strterm);
  p->lex_strterm = NULL;
}

static parser_heredoc_info *
parsing_heredoc_inf(parser_state *p)
{
  node *nd = p->parsing_heredoc;
  if (nd == NULL)
    return NULL;
  /* mrb_assert(nd->car->car == NODE_HEREDOC); */
  return (parser_heredoc_info*)nd->car->cdr;
}

static void
heredoc_treat_nextline(parser_state *p)
{
  if (p->heredocs_from_nextline == NULL)
    return;
  if (p->parsing_heredoc == NULL) {
    node *n;
    p->parsing_heredoc = p->heredocs_from_nextline;
    p->lex_strterm_before_heredoc = p->lex_strterm;
    p->lex_strterm = new_strterm(p, parsing_heredoc_inf(p)->type, 0, 0);
    n = p->all_heredocs;
    if (n) {
      while (n->cdr)
        n = n->cdr;
      n->cdr = p->parsing_heredoc;
    }
    else {
      p->all_heredocs = p->parsing_heredoc;
    }
  }
  else {
    node *n, *m;
    m = p->heredocs_from_nextline;
    while (m->cdr)
      m = m->cdr;
    n = p->all_heredocs;
    mrb_assert(n != NULL);
    if (n == p->parsing_heredoc) {
      m->cdr = n;
      p->all_heredocs = p->heredocs_from_nextline;
      p->parsing_heredoc = p->heredocs_from_nextline;
    }
    else {
      while (n->cdr != p->parsing_heredoc) {
        n = n->cdr;
        mrb_assert(n != NULL);
      }
      m->cdr = n->cdr;
      n->cdr = p->heredocs_from_nextline;
      p->parsing_heredoc = p->heredocs_from_nextline;
    }
  }
  p->heredocs_from_nextline = NULL;
}

static void
heredoc_end(parser_state *p)
{
  p->parsing_heredoc = p->parsing_heredoc->cdr;
  if (p->parsing_heredoc == NULL) {
    p->lstate = EXPR_BEG;
    p->cmd_start = TRUE;
    end_strterm(p);
    p->lex_strterm = p->lex_strterm_before_heredoc;
    p->lex_strterm_before_heredoc = NULL;
    p->heredoc_end_now = TRUE;
  }
  else {
    /* next heredoc */
    p->lex_strterm->car = nint(parsing_heredoc_inf(p)->type);
  }
}
#define is_strterm_type(p,str_func) (intn((p)->lex_strterm->car) & (str_func))

/* xxx ----------------------------- */


#line 1079 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    keyword_class = 258,
    keyword_module = 259,
    keyword_def = 260,
    keyword_begin = 261,
    keyword_if = 262,
    keyword_unless = 263,
    keyword_while = 264,
    keyword_until = 265,
    keyword_for = 266,
    keyword_undef = 267,
    keyword_rescue = 268,
    keyword_ensure = 269,
    keyword_end = 270,
    keyword_then = 271,
    keyword_elsif = 272,
    keyword_else = 273,
    keyword_case = 274,
    keyword_when = 275,
    keyword_break = 276,
    keyword_next = 277,
    keyword_redo = 278,
    keyword_retry = 279,
    keyword_in = 280,
    keyword_do = 281,
    keyword_do_cond = 282,
    keyword_do_block = 283,
    keyword_do_LAMBDA = 284,
    keyword_return = 285,
    keyword_yield = 286,
    keyword_super = 287,
    keyword_self = 288,
    keyword_nil = 289,
    keyword_true = 290,
    keyword_false = 291,
    keyword_and = 292,
    keyword_or = 293,
    keyword_not = 294,
    modifier_if = 295,
    modifier_unless = 296,
    modifier_while = 297,
    modifier_until = 298,
    modifier_rescue = 299,
    keyword_alias = 300,
    keyword_BEGIN = 301,
    keyword_END = 302,
    keyword__LINE__ = 303,
    keyword__FILE__ = 304,
    keyword__ENCODING__ = 305,
    tIDENTIFIER = 306,
    tFID = 307,
    tGVAR = 308,
    tIVAR = 309,
    tCONSTANT = 310,
    tCVAR = 311,
    tLABEL = 312,
    tINTEGER = 313,
    tFLOAT = 314,
    tCHAR = 315,
    tXSTRING = 316,
    tREGEXP = 317,
    tSTRING = 318,
    tSTRING_PART = 319,
    tSTRING_MID = 320,
    tNTH_REF = 321,
    tBACK_REF = 322,
    tREGEXP_END = 323,
    tUPLUS = 324,
    tUMINUS = 325,
    tPOW = 326,
    tCMP = 327,
    tEQ = 328,
    tEQQ = 329,
    tNEQ = 330,
    tGEQ = 331,
    tLEQ = 332,
    tANDOP = 333,
    tOROP = 334,
    tMATCH = 335,
    tNMATCH = 336,
    tDOT2 = 337,
    tDOT3 = 338,
    tAREF = 339,
    tASET = 340,
    tLSHFT = 341,
    tRSHFT = 342,
    tCOLON2 = 343,
    tCOLON3 = 344,
    tOP_ASGN = 345,
    tASSOC = 346,
    tLPAREN = 347,
    tLPAREN_ARG = 348,
    tRPAREN = 349,
    tLBRACK = 350,
    tLBRACE = 351,
    tLBRACE_ARG = 352,
    tSTAR = 353,
    tAMPER = 354,
    tLAMBDA = 355,
    tANDDOT = 356,
    tSYMBEG = 357,
    tREGEXP_BEG = 358,
    tWORDS_BEG = 359,
    tSYMBOLS_BEG = 360,
    tSTRING_BEG = 361,
    tXSTRING_BEG = 362,
    tSTRING_DVAR = 363,
    tLAMBEG = 364,
    tHEREDOC_BEG = 365,
    tHEREDOC_END = 366,
    tLITERAL_DELIM = 367,
    tHD_LITERAL_DELIM = 368,
    tHD_STRING_PART = 369,
    tHD_STRING_MID = 370,
    tLOWEST = 371,
    tUMINUS_NUM = 372,
    tLAST_TOKEN = 373
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 1024 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:355  */

    node *nd;
    mrb_sym id;
    int num;
    stack_type stack;
    const struct vtable *vars;

#line 1243 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (parser_state *p);



/* Copy the second part of user declarations.  */

#line 1259 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   10987

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  145
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  163
/* YYNRULES -- Number of rules.  */
#define YYNRULES  559
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  972

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   373

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     144,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   131,     2,     2,     2,   129,   124,     2,
     139,   140,   127,   125,   137,   126,   143,   128,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   119,   142,
     121,   117,   120,   118,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   136,     2,   141,   123,     2,   138,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   134,   122,   135,   132,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   130,   133
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  1176,  1176,  1176,  1187,  1193,  1197,  1202,  1206,  1212,
    1214,  1213,  1225,  1252,  1258,  1262,  1267,  1271,  1277,  1277,
    1281,  1285,  1289,  1293,  1297,  1301,  1305,  1310,  1311,  1315,
    1319,  1323,  1327,  1331,  1336,  1340,  1345,  1349,  1353,  1357,
    1360,  1364,  1371,  1372,  1376,  1380,  1384,  1388,  1391,  1398,
    1399,  1402,  1403,  1407,  1406,  1419,  1423,  1428,  1432,  1437,
    1441,  1446,  1450,  1454,  1458,  1462,  1468,  1472,  1478,  1479,
    1485,  1489,  1493,  1497,  1501,  1505,  1509,  1513,  1517,  1521,
    1527,  1528,  1534,  1538,  1544,  1548,  1554,  1558,  1562,  1566,
    1570,  1574,  1580,  1586,  1593,  1597,  1601,  1605,  1609,  1613,
    1619,  1625,  1632,  1636,  1639,  1643,  1647,  1653,  1654,  1655,
    1656,  1661,  1668,  1669,  1672,  1676,  1676,  1682,  1683,  1684,
    1685,  1686,  1687,  1688,  1689,  1690,  1691,  1692,  1693,  1694,
    1695,  1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,  1704,
    1705,  1706,  1707,  1708,  1709,  1710,  1713,  1713,  1713,  1714,
    1714,  1715,  1715,  1715,  1716,  1716,  1716,  1716,  1717,  1717,
    1717,  1718,  1718,  1718,  1719,  1719,  1719,  1719,  1720,  1720,
    1720,  1720,  1721,  1721,  1721,  1721,  1722,  1722,  1722,  1722,
    1723,  1723,  1723,  1723,  1724,  1724,  1727,  1731,  1735,  1739,
    1743,  1747,  1751,  1755,  1759,  1764,  1769,  1774,  1778,  1782,
    1786,  1790,  1794,  1798,  1802,  1806,  1810,  1814,  1818,  1822,
    1826,  1830,  1834,  1838,  1842,  1846,  1850,  1854,  1858,  1862,
    1866,  1870,  1874,  1878,  1882,  1886,  1890,  1894,  1898,  1902,
    1908,  1915,  1916,  1921,  1925,  1932,  1938,  1939,  1942,  1943,
    1944,  1949,  1954,  1961,  1966,  1971,  1976,  1981,  1988,  1988,
    1999,  2005,  2009,  2015,  2020,  2025,  2029,  2033,  2037,  2043,
    2047,  2051,  2057,  2058,  2059,  2060,  2061,  2062,  2063,  2064,
    2069,  2068,  2080,  2084,  2079,  2089,  2089,  2093,  2097,  2101,
    2105,  2110,  2115,  2119,  2123,  2127,  2131,  2135,  2139,  2143,
    2144,  2150,  2156,  2149,  2168,  2176,  2184,  2184,  2184,  2191,
    2191,  2191,  2198,  2204,  2209,  2211,  2208,  2220,  2218,  2234,
    2239,  2232,  2254,  2252,  2267,  2271,  2266,  2286,  2292,  2285,
    2307,  2311,  2315,  2319,  2325,  2332,  2333,  2334,  2337,  2338,
    2341,  2342,  2350,  2351,  2357,  2361,  2364,  2368,  2374,  2378,
    2384,  2388,  2392,  2396,  2400,  2404,  2408,  2412,  2416,  2422,
    2426,  2430,  2434,  2438,  2442,  2446,  2450,  2454,  2458,  2462,
    2466,  2470,  2474,  2478,  2484,  2485,  2492,  2496,  2500,  2507,
    2511,  2517,  2518,  2521,  2526,  2529,  2533,  2539,  2543,  2550,
    2549,  2562,  2572,  2576,  2581,  2588,  2592,  2596,  2600,  2604,
    2608,  2612,  2616,  2620,  2627,  2626,  2639,  2638,  2652,  2660,
    2669,  2672,  2679,  2682,  2686,  2687,  2690,  2694,  2697,  2701,
    2704,  2705,  2706,  2707,  2710,  2711,  2712,  2716,  2722,  2723,
    2729,  2734,  2733,  2744,  2748,  2754,  2758,  2764,  2768,  2774,
    2777,  2778,  2781,  2782,  2785,  2791,  2797,  2798,  2801,  2808,
    2807,  2821,  2825,  2832,  2836,  2843,  2850,  2851,  2852,  2853,
    2854,  2858,  2864,  2868,  2874,  2875,  2876,  2880,  2886,  2890,
    2894,  2898,  2902,  2908,  2914,  2918,  2922,  2926,  2930,  2934,
    2941,  2950,  2951,  2955,  2959,  2958,  2974,  2980,  2986,  2990,
    2994,  2998,  3002,  3006,  3010,  3014,  3018,  3022,  3026,  3030,
    3034,  3038,  3043,  3049,  3054,  3059,  3064,  3071,  3075,  3082,
    3086,  3092,  3096,  3102,  3109,  3115,  3121,  3125,  3131,  3135,
    3141,  3142,  3145,  3150,  3157,  3158,  3161,  3168,  3172,  3179,
    3184,  3184,  3209,  3210,  3216,  3221,  3227,  3231,  3237,  3238,
    3239,  3242,  3243,  3244,  3245,  3248,  3249,  3250,  3253,  3254,
    3257,  3261,  3267,  3268,  3274,  3275,  3278,  3279,  3282,  3285,
    3288,  3289,  3290,  3293,  3294,  3298,  3297,  3304,  3305,  3309
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "keyword_class", "keyword_module",
  "keyword_def", "keyword_begin", "keyword_if", "keyword_unless",
  "keyword_while", "keyword_until", "keyword_for", "keyword_undef",
  "keyword_rescue", "keyword_ensure", "keyword_end", "keyword_then",
  "keyword_elsif", "keyword_else", "keyword_case", "keyword_when",
  "keyword_break", "keyword_next", "keyword_redo", "keyword_retry",
  "keyword_in", "keyword_do", "keyword_do_cond", "keyword_do_block",
  "keyword_do_LAMBDA", "keyword_return", "keyword_yield", "keyword_super",
  "keyword_self", "keyword_nil", "keyword_true", "keyword_false",
  "keyword_and", "keyword_or", "keyword_not", "modifier_if",
  "modifier_unless", "modifier_while", "modifier_until", "modifier_rescue",
  "keyword_alias", "keyword_BEGIN", "keyword_END", "keyword__LINE__",
  "keyword__FILE__", "keyword__ENCODING__", "tIDENTIFIER", "tFID", "tGVAR",
  "tIVAR", "tCONSTANT", "tCVAR", "tLABEL", "tINTEGER", "tFLOAT", "tCHAR",
  "tXSTRING", "tREGEXP", "tSTRING", "tSTRING_PART", "tSTRING_MID",
  "tNTH_REF", "tBACK_REF", "tREGEXP_END", "tUPLUS", "tUMINUS", "tPOW",
  "tCMP", "tEQ", "tEQQ", "tNEQ", "tGEQ", "tLEQ", "tANDOP", "tOROP",
  "tMATCH", "tNMATCH", "tDOT2", "tDOT3", "tAREF", "tASET", "tLSHFT",
  "tRSHFT", "tCOLON2", "tCOLON3", "tOP_ASGN", "tASSOC", "tLPAREN",
  "tLPAREN_ARG", "tRPAREN", "tLBRACK", "tLBRACE", "tLBRACE_ARG", "tSTAR",
  "tAMPER", "tLAMBDA", "tANDDOT", "tSYMBEG", "tREGEXP_BEG", "tWORDS_BEG",
  "tSYMBOLS_BEG", "tSTRING_BEG", "tXSTRING_BEG", "tSTRING_DVAR", "tLAMBEG",
  "tHEREDOC_BEG", "tHEREDOC_END", "tLITERAL_DELIM", "tHD_LITERAL_DELIM",
  "tHD_STRING_PART", "tHD_STRING_MID", "tLOWEST", "'='", "'?'", "':'",
  "'>'", "'<'", "'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "tUMINUS_NUM", "'!'", "'~'", "tLAST_TOKEN", "'{'", "'}'", "'['", "','",
  "'`'", "'('", "')'", "']'", "';'", "'.'", "'\\n'", "$accept", "program",
  "$@1", "top_compstmt", "top_stmts", "top_stmt", "@2", "bodystmt",
  "compstmt", "stmts", "stmt", "$@3", "command_asgn", "expr", "expr_value",
  "command_call", "block_command", "cmd_brace_block", "$@4", "command",
  "mlhs", "mlhs_inner", "mlhs_basic", "mlhs_item", "mlhs_list",
  "mlhs_post", "mlhs_node", "lhs", "cname", "cpath", "fname", "fsym",
  "undef_list", "$@5", "op", "reswords", "arg", "arg_value", "aref_args",
  "paren_args", "opt_paren_args", "opt_call_args", "call_args",
  "command_args", "@6", "block_arg", "opt_block_arg", "args", "mrhs",
  "primary", "@7", "@8", "$@9", "$@10", "@11", "@12", "$@13", "$@14",
  "$@15", "$@16", "$@17", "$@18", "@19", "@20", "@21", "@22", "@23", "@24",
  "@25", "@26", "primary_value", "then", "do", "if_tail", "opt_else",
  "for_var", "f_marg", "f_marg_list", "f_margs", "block_param",
  "opt_block_param", "block_param_def", "opt_bv_decl", "bv_decls", "bvar",
  "f_larglist", "lambda_body", "do_block", "$@27", "block_call",
  "method_call", "brace_block", "@28", "@29", "case_body", "cases",
  "opt_rescue", "exc_list", "exc_var", "opt_ensure", "literal", "string",
  "string_rep", "string_interp", "@30", "xstring", "regexp", "heredoc",
  "opt_heredoc_bodies", "heredoc_bodies", "heredoc_body",
  "heredoc_string_rep", "heredoc_string_interp", "@31", "words", "symbol",
  "basic_symbol", "sym", "symbols", "numeric", "variable", "var_lhs",
  "var_ref", "backref", "superclass", "$@32", "f_arglist", "f_args",
  "f_bad_arg", "f_norm_arg", "f_arg_item", "f_arg", "f_opt_asgn", "f_opt",
  "f_block_opt", "f_block_optarg", "f_optarg", "restarg_mark",
  "f_rest_arg", "blkarg_mark", "f_block_arg", "opt_f_block_arg",
  "singleton", "$@33", "assoc_list", "assocs", "assoc", "operation",
  "operation2", "operation3", "dot_or_colon", "call_op", "call_op2",
  "opt_terms", "opt_nl", "rparen", "rbracket", "trailer", "term", "nl",
  "$@34", "terms", "none", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,    61,    63,    58,
      62,    60,   124,    94,    38,    43,    45,    42,    47,    37,
     372,    33,   126,   373,   123,   125,    91,    44,    96,    40,
      41,    93,    59,    46,    10
};
# endif

#define YYPACT_NINF -751

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-751)))

#define YYTABLE_NINF -560

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-560)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -751,   158,  3017,  -751,  7449,  9273,  9603,  5681,  -751,  8931,
    8931,  -751,  -751,  9383,  6843,  5197,  8133,  8133,  -751,  -751,
    8133,  3389,  2850,  -751,  -751,  -751,  -751,    29,  6843,  -751,
      44,  -751,  -751,  5818,  3125,  -751,  -751,  5932,  -751,  -751,
    -751,  -751,  -751,  -751,  -751,  9045,  9045,   131,  4595,   157,
    8247,  8475,  7115,  -751,  6571,   706,   908,  1008,  1032,   690,
    -751,   277,  9159,  9045,  -751,   245,  -751,   806,  -751,   309,
    -751,  -751,   182,   138,  -751,   107,  9493,  -751,   199,  3239,
     222,   363,   260,   120,  -751,  -751,  -751,  -751,  -751,  -751,
    -751,  -751,  -751,  -751,    60,   176,  -751,   293,    82,  -751,
    -751,  -751,  -751,  -751,   240,   265,   285,   422,   557,  8931,
     366,  4710,   340,  -751,   325,  -751,   388,  -751,  -751,    82,
    -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,
    -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,
    -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,    38,    53,
     100,   219,  -751,  -751,  -751,  -751,  -751,  -751,   251,   266,
    -751,   272,  -751,   276,  -751,  -751,  -751,  -751,  -751,  -751,
    -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,
    -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,
    -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,   280,  3797,
     428,   309,    78,   360,   399,    54,   373,    58,    78,  8931,
    8931,   440,  -751,  -751,   633,   472,    67,   122,  -751,  -751,
    -751,  -751,  -751,  -751,  -751,  -751,  6707,  -751,  -751,   370,
    -751,  -751,  -751,   245,   483,  -751,  -751,   375,  9045,  9045,
    9045,  9045,  -751,  3239,   417,  -751,  -751,   378,   381,  -751,
    -751,  -751,  5082,  -751,  8133,  8133,  -751,  -751,  5312,  8931,
    -751,  -751,   385,  4825,  -751,   694,   450,   377,  7677,  4595,
     386,   245,   806,   392,   412,  -751,  8931,   392,   396,    23,
      25,  -751,   417,   427,    25,  -751,   492,  9713,   423,   721,
     750,   783,   761,  -751,  -751,  -751,  -751,  1108,  -751,  -751,
    -751,  -751,  -751,  -751,   338,  1054,  -751,  -751,  1152,  -751,
    1171,  -751,  1183,  -751,   779,   493,   497,  -751,  -751,  -751,
    -751,  5427,  8931,  8931,  8931,  8931,  7677,  8931,  8931,  -751,
    -751,  8589,  -751,  4595,  7225,   432,  8589,  9045,  9045,  9045,
    9045,  9045,  9045,  9045,  9045,  9045,  9045,  9045,  9045,  9045,
    9045,  9045,  9045,  9045,  9045,  9045,  9045,  9045,  9045,  9045,
    9045,  9045,  9045,  1678,  -751,  8133,  -751,  2419,  -751,  -751,
   10815,  -751,  -751,  -751,  9159,  9159,  -751,   473,  -751,   309,
    -751,   819,  -751,  -751,  -751,  -751,  -751,  2613,  8133,  9995,
    3797,  8931,  -751,  -751,  -751,  -751,   563,   559,    62,  -751,
    3939,   574,  9045, 10077,  8133, 10159,  9045,  9045,  4223,   127,
     127,   136, 10241,  8133, 10323,  -751,   530,  -751,   338,   483,
    8703,   587,  -751,  -751,  -751,  -751,  9045,  7335,  -751,  -751,
    8361,  -751,   392,   465,  -751,  -751,   392,  -751,   481,   482,
    -751,   128,  -751,  -751,  6843,  4338,   475, 10077, 10159,  9045,
     806,   392,  -751,  -751,  5541,   485,   309,  -751,  -751,  7563,
    -751,  -751,  8475,  -751,  -751,  -751,   819,   107,  9713,  -751,
    9713, 10405,  8133, 10487,   512,  -751,  -751,  -751,  -751,  1219,
    -751,  -751,  -751,  -751,   937,  -751,  -751,  -751,  -751,  -751,
     503,  9045,  -751,   504,   579,   505,   598,  -751,  -751,  1203,
    4825,  -751,  -751,  -751,   338,  -751,   346,  -751,  -751,  -751,
    -751,  -751,  -751,  -751,  9045,  9045,  -751,  -751,  -751,  -751,
    -751,  -751,  -751,  -751,    76,  9045,  -751,   523,   525,  -751,
     392,  9713,   527,  -751,  -751,  -751,   549,  2243,  -751,  -751,
     450,  2042,  2042,  2042,  2042,  1072,  1072,  2439,  1437,  2042,
    2042,  3503,  3503,   577,   577, 10843,  1072,  1072,   425,   425,
     918,    66,    66,   450,   450,   450,  3521,  6320,  3653,  6434,
    -751,   265,  -751,   392,   408,  -751,   438,  -751,  -751,  3257,
    -751,  -751,  1088,    76,    76,  -751,  2713,  -751,  3239,  -751,
    -751,   245,  8931,  3797,   573,   214,  -751,   265,   392,   265,
     653,   128,   924,  6979,  -751,  8817,   657,  -751,   424,  -751,
    3371,  6046,  6183,   392,    63,    92,   657,  -751,  -751,  -751,
    -751,   204,   235,   392,   139,   149,  8931,  6843,  -751,   338,
     662,   119,  -751,  -751,  9045,   417,  -751,  7791,   381,  -751,
    -751,  -751,  -751,  7335,  8361,  -751,  -751,   543,  -751,  3239,
      39,   806,   392,    25,   432,  -751,   205,   214,   392,   268,
     341,  -751,  -751,  1219,   599,  -751,   544,   392,  -751,   392,
      83,   937,  -751,  -751,  -751,   937,  -751,  -751,   737,  -751,
    -751,  -751,   547,  4825,  -751,  -751,  -751,   450,   450,  -751,
     616,  4967,  -751,  -751,   551,  7905,  -751,  -751,  9713,  9159,
    9045,   575,  9159,  9159,  -751,   473,   554,   442,  9159,  9159,
    -751,  -751,   473,  -751,   120,   182,  4967,  4825,  9045,    76,
    -751,   245,   677,  -751,  -751,  -751,   937,  3797,   245,  -751,
     523,  -751,   608,  -751,  4480,   696,  -751,  8931,   698,  -751,
    9045,  9045,   303,  9045,  9045,   703,  4967,  4967,   159,   127,
    -751,  -751,  8019,  4081,  -751,  9045,  -751,  -751,   582,  -751,
    -751,  -751,   365,   392,   673,   601,  1270,  -751,   571,   593,
    4967,  4825,  -751,  -751,   604,   605,  -751,   607,  -751,   610,
     607,  -751,   613,   392,   627,   615,  9823,  -751,   620,   629,
    -751,   735,  9045,   637,  -751,  3239,  9045,  -751,  3239,  -751,
    3239,  -751,  -751,  9159,  -751,  3239,  -751,  3239,  -751,  -751,
    -751,   764,   645,  3239,  4825,  3797,  -751,  -751,   392,   766,
    -751,   924,  9933,    78,  -751,  -751,  4967,  -751,  -751,    78,
    -751,  9045,  -751,   770,   781,  -751,  -751,   466,  -751,  8361,
    -751,   664,   673,   708,  -751,  -751,   895,   784,   669,   937,
    -751,   737,  -751,   737,  -751,   737,  -751,  -751,  -751,   683,
    -751,   937,  -751,   751,   882,   937,  -751,   737,  -751,  -751,
     674,  3239,  -751,  3239,  -751,  -751,   678,   809,  -751,  -751,
    3797,   771,  -751,   894,    94,   126,  3797,  -751,  3939,  -751,
    -751,  4967,  -751,  -751,  -751,   673,   664,   673,   691,  -751,
      26,  -751,  -751,  -751,  -751,   607,   695,   607,   607,  -751,
     702,   704,  -751, 10569,   607,  -751,   715,   607,  -751,  -751,
     816,   135, 10651,  8133, 10733,   559,   424,   839,   664,   673,
     895,  -751,  -751,   737,  -751,  -751,  -751,   937,  -751,   737,
    -751,   716,   723,  -751,   737,  -751,  -751,  -751,   123,   167,
     392,   143,   184,  -751,  -751,  -751,   664,  -751,   607,   607,
     731,   607,   607,   185,  -751,  -751,   737,  -751,  -751,  -751,
     607,  -751
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     0,   270,     0,
       0,   296,   299,     0,     0,   544,   320,   321,   322,   323,
     282,   248,   248,   466,   465,   467,   468,   546,     0,    10,
       0,   470,   469,   458,   530,   460,   459,   462,   461,   454,
     455,   414,   415,   471,   472,     0,     0,     0,     0,   272,
     559,   559,    78,   291,     0,     0,     0,     0,     0,     0,
     429,     0,     0,     0,     3,   544,     6,     9,    27,    39,
      42,    50,    49,     0,    66,     0,    70,    80,     0,    47,
     229,     0,    51,   289,   262,   263,   264,   265,   266,   412,
     411,   443,   413,   410,   464,     0,   267,   268,   248,     5,
       8,   320,   321,   282,   285,   392,     0,   102,   103,     0,
       0,     0,     0,   105,   473,   324,     0,   464,   268,     0,
     312,   156,   166,   157,   153,   182,   183,   184,   185,   164,
     179,   172,   162,   161,   177,   160,   159,   155,   180,   154,
     167,   171,   173,   165,   158,   174,   181,   176,   175,   168,
     178,   163,   152,   170,   169,   151,   149,   150,   146,   147,
     148,   107,   109,   108,   141,   142,   138,   120,   121,   122,
     129,   126,   128,   123,   124,   143,   144,   130,   131,   135,
     125,   127,   117,   118,   119,   132,   133,   134,   136,   137,
     139,   140,   145,   520,   314,   110,   111,   519,     0,     0,
       0,    48,     0,     0,     0,   464,     0,   268,     0,     0,
       0,     0,   335,   334,     0,     0,   464,   268,   175,   168,
     178,   163,   146,   147,   107,   108,     0,   112,   114,    20,
     113,   553,   555,   544,     0,   557,   554,   545,     0,     0,
       0,     0,   243,   230,   253,    64,   247,   559,   559,   524,
      65,    63,   546,    62,     0,   559,   391,    61,   546,     0,
     547,    18,     0,     0,   207,     0,   208,   279,     0,     0,
       0,   544,    15,   546,    68,    14,     0,   546,     0,   550,
     550,   231,     0,     0,   550,   522,     0,     0,    76,     0,
      86,    93,   492,   448,   447,   449,   450,     0,   446,   445,
     427,   421,   420,   423,     0,     0,   418,   441,     0,   452,
       0,   416,     0,   425,     0,   456,   457,    46,   222,   223,
       4,   545,     0,     0,     0,     0,     0,     0,     0,   379,
     381,     0,    82,     0,    74,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   541,   559,   540,     0,   543,   542,
       0,   396,   394,   290,     0,     0,   385,    55,   288,   309,
     102,   103,   104,   456,   457,   474,   307,     0,   559,     0,
       0,     0,   315,   539,   538,   317,     0,   559,   279,   326,
       0,   325,     0,     0,   559,     0,     0,     0,     0,     0,
       0,   279,     0,   559,     0,   304,     0,   115,   430,     0,
       0,     0,   558,   527,   254,   250,     0,     0,   244,   252,
       0,   245,   546,     0,   284,   249,   546,   239,   559,   559,
     238,   546,   287,    45,     0,     0,     0,     0,     0,     0,
      17,   546,   277,    13,   545,    67,   273,   276,   280,   552,
     232,   551,   552,   234,   281,   523,    92,    84,     0,    79,
       0,     0,   559,     0,   498,   495,   494,   493,   496,     0,
     511,   515,   514,   510,   492,   292,   376,   497,   499,   501,
     559,     0,   508,   559,   513,   559,     0,   491,   451,     0,
       0,   434,   439,   438,   424,   432,     0,   436,   428,   419,
     442,   453,   417,   426,     0,     0,     7,    21,    22,    23,
      24,    25,    43,    44,   559,     0,    28,    37,     0,    38,
     546,     0,    72,    83,    41,    40,     0,   186,   253,    36,
     204,   212,   217,   218,   219,   214,   216,   226,   227,   220,
     221,   197,   198,   224,   225,   546,   213,   215,   209,   210,
     211,   199,   200,   201,   202,   203,   531,   536,   532,   537,
     390,   248,   388,   546,   531,   533,   532,   534,   389,   248,
     531,   532,   248,   559,   559,    29,   188,    35,   196,    53,
      56,     0,     0,     0,   102,   103,   106,     0,   546,   559,
       0,   546,   492,     0,   271,   559,   559,   402,   559,   327,
     186,   535,   278,   546,   531,   532,   559,   329,   297,   328,
     300,   535,   278,   546,   531,   532,     0,     0,   556,   431,
       0,     0,   303,   526,     0,   255,   251,     0,   559,   525,
     283,   548,   235,   240,   242,   286,    19,     0,    26,   195,
      69,    16,   546,   550,    85,    77,   535,    91,   546,   531,
     532,   503,   498,     0,   347,   338,   340,   546,   336,   546,
       0,     0,   484,   518,   504,     0,   487,   512,     0,   489,
     516,   444,     0,     0,   433,   435,   437,   205,   206,   367,
     546,     0,   365,   364,   261,     0,    81,    75,     0,     0,
       0,     0,     0,     0,   387,    59,     0,   393,     0,     0,
     237,   386,    57,   236,   382,    52,     0,     0,     0,   559,
     310,     0,     0,   393,   313,   521,   492,     0,     0,   318,
     403,   404,   559,   405,     0,   559,   332,     0,     0,   330,
       0,     0,   393,     0,     0,     0,     0,     0,   393,     0,
     116,   302,     0,     0,   256,     0,   257,   246,   559,    11,
     274,   233,   393,   546,     0,   345,     0,   500,     0,   369,
       0,     0,   293,   502,   559,   559,   517,   559,   509,   559,
     559,   422,     0,   546,     0,   559,     0,   506,   559,   559,
     363,     0,     0,   259,    73,   187,     0,    34,   193,    33,
     194,    60,   549,     0,    31,   191,    32,   192,    58,   383,
     384,     0,     0,   189,     0,     0,   475,   308,   546,     0,
     477,   492,     0,     0,   407,   333,     0,    12,   409,     0,
     294,     0,   295,     0,     0,   305,   255,   559,   258,   241,
     337,   348,     0,   343,   339,   375,     0,     0,     0,     0,
     480,     0,   482,     0,   488,     0,   485,   490,   440,     0,
     366,   354,   356,     0,   505,     0,   359,     0,   361,   380,
     260,   228,    30,   190,   397,   395,     0,     0,   476,   316,
       0,     0,   406,     0,   464,   268,     0,   408,     0,   298,
     301,     0,   399,   400,   398,     0,   346,     0,   341,   373,
     546,   371,   374,   378,   377,   559,   559,   559,   559,   368,
     559,   559,   279,     0,   559,   507,   559,   559,    54,   311,
       0,   279,     0,   559,     0,   559,   559,     0,   344,     0,
       0,   370,   481,     0,   478,   483,   486,     0,   351,     0,
     353,   535,   278,   360,     0,   357,   362,   319,   535,   278,
     546,   531,   532,   401,   331,   306,   342,   372,   559,   559,
     559,   559,   559,   393,   479,   352,     0,   349,   355,   358,
     559,   350
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -751,  -751,  -751,   433,  -751,    30,  -751,  -360,   323,  -751,
     112,  -751,  -311,   216,     8,   -19,  -751,  -336,  -751,   -13,
     859,  -148,   -12,   -52,  -267,  -406,     0,   854,   -73,   867,
      22,   -15,  -751,  -751,  -328,  -751,  1633,    42,  -751,    -8,
     300,  -300,    51,     5,  -751,  -349,  -231,    46,  -286,     3,
    -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,
    -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,  -751,
     611,  -186,  -379,   -43,  -499,  -751,  -681,  -706,   226,  -751,
    -461,  -751,  -572,  -751,   -40,  -751,  -751,   180,  -751,  -751,
    -751,   -82,  -751,  -751,  -398,  -751,   -28,  -751,  -751,  -751,
    -751,  -751,    43,  -181,  -751,  -751,  -751,  -751,  -751,  -213,
    -430,  -751,   393,  -751,  -751,  -751,    12,  -751,  -751,  -751,
    1892,   892,   904,  2128,  -751,  -751,    80,  -282,  -740,    34,
    -562,   319,  -633,  -622,  -750,    52,   246,  -751,  -541,  -751,
    -210,  1291,  -751,  -751,  -751,    -5,  -392,  1131,  -316,  -751,
    -751,   -76,  -751,     7,   -25,  -217,  -518,  -252,    18,     4,
    -751,   -21,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    64,    65,    66,   262,   396,   397,   271,
     272,   444,    68,    69,   202,    70,    71,   590,   719,    72,
      73,   273,    74,    75,    76,   469,    77,   203,   113,   114,
     227,   228,   229,   627,   195,   196,    79,   244,   278,   570,
     711,   436,   437,   253,   254,   246,   428,   438,   529,    80,
     199,   276,   652,   277,   292,   670,   209,   746,   210,   747,
     626,   891,   593,   591,   815,   390,   392,   602,   603,   821,
     265,   400,   618,   738,   739,   215,   665,   666,   667,   783,
     691,   692,   768,   900,   901,   485,   772,   330,   524,    82,
      83,   378,   584,   583,   421,   894,   606,   732,   823,   827,
      84,    85,   305,   306,   500,    86,    87,    88,   628,   637,
     505,   506,   507,   683,    89,    90,    91,   299,    92,    93,
     205,   206,    96,   207,   386,   592,   727,   728,   487,   488,
     489,   490,   491,   492,   787,   788,   493,   494,   495,   496,
     776,   672,   198,   391,   283,   439,   249,   119,   597,   572,
     395,   389,   370,   234,   433,   434,   707,   460,   401,   260,
     418,   237,   275
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      99,   373,   259,   242,   242,   367,   369,   242,   115,   115,
     486,   248,   248,   261,   256,   248,   115,   431,   208,   236,
     468,   630,   408,   233,   335,   534,   230,   257,   463,   194,
     600,   620,   465,   235,   100,   569,   274,   382,   639,   577,
     230,   442,   577,   317,   321,   280,   284,   571,   281,   285,
     539,   579,   288,   778,   582,   115,   455,   786,   841,   569,
     457,   577,   247,   247,   655,   573,   247,   245,   250,   236,
     639,   251,   320,   599,   684,   569,   298,   577,   636,   115,
     723,   636,   497,   235,   569,   844,   577,   571,   598,   579,
     376,   504,   -94,   282,   399,   742,   279,   256,   599,   308,
     310,   312,   314,   377,   613,   748,   902,   735,   371,   773,
     -94,   376,   770,   623,    67,   915,    67,   745,   784,   569,
     577,   451,   716,   717,   509,   697,  -466,   509,   405,   509,
     775,   509,   599,   509,   779,   399,   896,   337,   414,   -97,
     762,  -465,  -101,   569,  -463,   577,   371,  -101,   407,   789,
    -463,  -100,   449,   743,   617,   689,   -67,   599,     3,   -96,
     459,  -100,   462,   930,   -96,   327,   328,   232,   258,   232,
     232,   -94,   658,   232,   -98,  -101,   -81,   -94,   263,  -100,
     -96,  -466,   744,   -99,   -95,   530,   267,   915,  -467,   448,
     902,   928,   771,   360,   361,   362,  -465,   -86,   690,   684,
     -98,   -95,   669,   468,   -86,   629,   236,   684,   431,   -98,
     329,   859,   236,   473,   844,   640,   372,   409,   410,   642,
     231,   255,   232,   956,   645,   201,   201,   778,   786,   -97,
     -89,   201,   786,   722,   650,   467,   -94,   236,   -94,   242,
     419,   242,   242,  -467,   332,   429,   429,   248,   298,   248,
     454,   235,   639,   440,   372,   331,   752,   274,   814,   -93,
     -99,   231,  -531,   232,   468,   -97,   374,   -97,  -101,   231,
    -101,   232,   232,   -92,   497,   236,   -88,  -100,   453,  -100,
     423,   424,   425,   461,   461,   -96,   -90,   -96,   461,   235,
     115,   773,   794,   -88,   636,   636,   -87,  -275,   247,   773,
     247,  -275,  -278,   432,   786,   435,  -532,  -468,   906,   -99,
    -324,   -99,   526,   696,   596,  -278,   336,   535,   509,   731,
     911,   274,   -89,  -324,   916,   379,   -98,   -95,   -98,   -95,
     517,   518,   519,   520,   532,   315,   316,   115,   892,  -470,
     499,   -89,   -89,  -531,  -531,   -89,   327,   328,   368,   -89,
    -278,   516,   242,  -532,  -469,   585,   587,  -278,  -324,   578,
    -458,   364,  -468,   440,  -462,  -324,   -90,   819,   393,   801,
     835,   270,   -91,   527,  -532,   242,   808,   528,   538,   252,
     450,   578,   528,   375,   725,   -88,   440,   231,   534,   232,
     -87,   242,   497,   831,  -470,   607,   960,   578,   383,   384,
     242,   761,   440,   366,   255,   -88,   578,   757,   -88,  -469,
    -101,   440,   -88,   236,   236,  -458,   654,   380,   467,  -462,
     -95,   381,   638,   394,   258,   201,   201,   619,   619,   646,
     -93,   468,   963,    67,   270,   760,   429,   429,   521,   893,
     578,   737,   734,    99,   818,   753,   385,   639,  -528,   501,
     767,   363,   502,   503,   653,   877,   230,   685,   -90,   242,
     502,   503,   538,   406,   364,   578,   631,   449,   633,   635,
     440,   115,   282,   115,   441,   443,   387,   402,   -90,   467,
     790,   -90,   -87,   398,   734,   -90,   420,   403,   673,   364,
     636,   673,   456,   673,  -100,   411,   337,   415,   708,   365,
     364,   635,   -87,   420,   282,   -87,   366,   417,   426,   -87,
    -458,   350,   351,   668,   -92,   427,   497,   422,   430,   445,
     920,   337,   693,  -458,   388,   -96,   452,   757,   709,   -66,
     701,   366,   803,   674,   115,   404,   232,   458,   201,   201,
     201,   201,   366,   522,   523,   -88,   840,   466,   706,   357,
     358,   359,   360,   361,   362,   -98,  -528,    67,  -458,   -95,
     470,  -528,   464,   704,   514,  -458,   651,   694,   515,   533,
     589,   710,   605,   706,   710,   -90,   705,   713,   604,   -87,
     713,   693,   693,  -529,   712,   569,   446,   715,   706,   704,
     609,   710,   270,   498,   569,   236,   577,   713,   706,  -535,
     721,   878,   632,   733,   736,   641,   736,   601,   599,   720,
     648,   497,   750,    81,   736,    81,   116,   116,   643,   644,
     204,   204,   -81,   950,   214,   729,   204,   204,   204,   661,
     677,   204,   809,   706,   749,   236,   429,   886,   758,   230,
     671,   675,   678,   888,   769,  -462,   467,   730,   337,   680,
     662,   528,   475,   476,   477,   478,   270,   461,  -462,    81,
    -253,  -535,   695,   289,   698,   769,   699,   474,   724,   475,
     476,   477,   478,   204,  -535,   734,   754,   751,   759,   756,
     535,   766,   781,   797,   799,   635,   282,   289,  -254,   804,
     806,  -529,   817,  -462,   796,   802,  -529,   668,   765,   822,
    -462,   115,   358,   359,   360,   361,   362,  -535,   479,  -535,
     826,   845,  -531,   830,   480,   481,  -535,   693,   832,   839,
     204,   412,    81,   608,   662,   236,   475,   476,   477,   478,
     824,   616,   236,   828,   364,   846,   764,   793,   842,   816,
     482,   849,   851,   483,   853,   829,   820,   855,   858,   860,
     869,   313,   861,   236,   301,   302,   429,   865,   769,   662,
     232,   475,   476,   477,   478,   663,   867,   619,   300,   413,
     301,   302,   673,   673,  -255,   673,   366,   673,   673,   874,
     875,   879,   447,   673,   872,   889,   673,   673,   662,   115,
     475,   476,   477,   478,   836,   364,   890,   838,   668,   903,
     668,   895,   303,   304,   904,   909,   912,   924,   201,   471,
      81,  -256,   474,   918,   475,   476,   477,   478,   303,   304,
     204,   204,   364,   682,   919,   115,   921,   236,   929,   479,
     404,   947,   933,   236,   870,   736,   481,   366,  -464,   937,
     513,   939,   201,   301,   302,   897,   322,   323,   324,   325,
     326,  -464,   944,   479,   955,  -531,    78,   472,    78,   480,
     481,   482,  -532,   204,   366,   204,   204,   213,   966,   204,
     204,  -268,   212,   120,    81,   931,   668,   898,   647,    81,
      81,   282,   714,   954,  -268,   482,  -464,   204,   483,   763,
     957,   303,   304,  -464,    95,   810,    95,   953,   289,   686,
     484,   880,    78,   673,   673,   673,   673,  -279,   673,   673,
     242,   197,   673,   910,   673,   673,   578,   774,     0,  -268,
    -279,   440,     0,   607,   736,   706,  -268,     0,     0,   668,
       0,   668,    81,   204,   204,   204,   204,    81,   204,   204,
      95,     0,   204,     0,    81,   289,   899,   204,   475,   476,
     477,   478,     0,   201,     0,  -279,   673,   673,   673,   673,
     673,     0,  -279,   668,     0,    78,     0,     0,   673,     0,
     913,   307,   301,   302,     0,   474,   204,   475,   476,   477,
     478,     0,   922,   364,     0,   204,   204,     0,   474,   337,
     475,   476,   477,   478,   777,   364,     0,   780,     0,   204,
       0,    81,   204,    95,   350,   351,   782,     0,     0,   785,
       0,    81,     0,     0,   791,   204,   479,     0,   388,    81,
     303,   304,   480,   481,   204,   366,     0,     0,     0,   479,
     923,     0,     0,     0,     0,   480,   481,   366,     0,   811,
     812,     0,     0,   358,   359,   360,   361,   362,   482,     0,
       0,   483,     0,    78,     0,     0,    81,   825,     0,     0,
       0,   482,     0,   726,   483,    81,     0,     0,     0,   833,
     834,   309,   301,   302,     0,     0,   837,     0,     0,   289,
       0,   289,     0,   204,     0,     0,     0,     0,  -559,     0,
       0,    95,     0,   847,   848,   311,   301,   302,     0,     0,
       0,  -559,  -559,  -559,  -559,  -559,  -559,     0,  -559,     0,
       0,    81,     0,     0,  -559,  -559,   508,    78,   301,   302,
     303,   304,    78,    78,     0,  -559,  -559,     0,  -559,  -559,
    -559,  -559,  -559,    98,     0,    98,     0,   876,     0,     0,
      98,    98,   289,   337,   303,   304,    98,    98,    98,   887,
       0,    98,     0,     0,     0,    95,     0,     0,   350,   351,
      95,    95,     0,     0,     0,     0,   303,   304,   905,     0,
     907,   498,   301,   302,   908,    78,  -559,     0,     0,    98,
      78,     0,     0,     0,   914,     0,   917,    78,     0,  -559,
     536,     0,     0,    98,   355,   356,   357,   358,   359,   360,
     361,   362,     0,   204,    81,     0,     0,     0,     0,   925,
       0,   926,     0,    95,   927,   510,   301,   302,    95,     0,
     303,   304,  -559,  -559,     0,    95,     0,   255,  -559,     0,
    -559,  -559,  -559,     0,   511,   301,   302,   204,     0,     0,
      98,     0,    98,     0,    78,     0,   512,   301,   302,     0,
       0,     0,   958,     0,    78,     0,   959,     0,   961,     0,
       0,     0,    78,   962,   303,   304,   681,   301,   302,     0,
     662,     0,   475,   476,   477,   478,     0,     0,     0,     0,
       0,     0,    95,   303,   304,   970,     0,     0,     0,     0,
       0,     0,    95,     0,    81,   303,   304,     0,     0,    78,
      95,     0,    81,     0,     0,     0,     0,     0,    78,   289,
     204,   663,     0,   204,   204,   303,   304,   664,     0,   204,
     204,   662,     0,   475,   476,   477,   478,    81,    81,     0,
      98,     0,     0,     0,     0,     0,     0,    95,    81,     0,
      98,    98,     0,     0,     0,    81,    95,     0,   204,     0,
       0,     0,     0,     0,    78,     0,     0,    81,    81,     0,
       0,     0,   663,     0,    81,     0,     0,     0,   843,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    81,    81,    98,     0,    98,    98,     0,     0,    98,
      98,     0,    95,     0,    98,     0,     0,   864,     0,    98,
      98,     0,     0,     0,     0,     0,     0,    98,     0,     0,
       0,     0,     0,     0,   204,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    81,    81,     0,     0,     0,
       0,     0,     0,   883,     0,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,    98,    98,    98,    98,    98,    98,    98,    98,
       0,     0,    98,     0,    98,     0,     0,    98,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    95,     0,     0,     0,     0,
       0,    81,     0,     0,     0,     0,    98,    81,     0,    81,
       0,     0,    81,     0,     0,    98,    98,     0,   337,   338,
     339,   340,   341,   342,   343,   344,     0,   346,   347,    98,
       0,    98,    98,   350,   351,     0,     0,     0,     0,     0,
       0,    98,     0,     0,   204,    98,     0,    78,     0,    98,
       0,     0,     0,     0,    98,    78,     0,     0,     0,     0,
       0,     0,     0,   536,     0,     0,     0,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,     0,     0,     0,
      78,    78,     0,     0,     0,    95,    98,     0,     0,     0,
       0,    78,     0,    95,     0,    98,     0,     0,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      78,    78,     0,    98,     0,     0,     0,    78,    95,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
       0,     0,     0,     0,    78,    78,    95,     0,     0,     0,
       0,    98,     0,     0,     0,     0,     0,     0,    95,    95,
       0,     0,     0,     0,     0,    95,     0,     0,     0,   243,
     243,     0,     0,   243,     0,     0,     0,     0,     0,     0,
       0,     0,    95,    95,     0,     0,     0,     0,    78,    78,
       0,     0,     0,     0,     0,     0,   882,     0,   264,   266,
      78,     0,     0,   243,   243,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   318,   319,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    95,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    95,     0,
       0,     0,     0,    98,    98,     0,     0,     0,     0,   566,
     567,     0,     0,   568,    78,     0,     0,     0,     0,     0,
      78,     0,    78,     0,     0,    78,     0,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     0,    98,   173,   174,
       0,     0,   175,   176,   177,   178,     0,     0,     0,     0,
       0,     0,    95,     0,     0,     0,   179,     0,    95,     0,
      95,     0,     0,    95,   676,     0,   679,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,     0,   190,
     191,     0,     0,     0,    98,     0,   192,   255,     0,     0,
       0,     0,    98,     0,     0,     0,     0,     0,     0,     0,
      98,     0,     0,    98,    98,     0,     0,     0,     0,    98,
      98,     0,     0,     0,     0,     0,     0,    98,    98,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98,     0,
       0,     0,     0,     0,     0,    98,     0,     0,    98,     0,
       0,   243,   243,   243,   318,     0,     0,    98,    98,     0,
       0,     0,     0,     0,    98,   243,     0,   243,   243,     0,
       0,     0,     0,     0,    94,     0,    94,   117,   117,   117,
       0,    98,    98,     0,     0,   216,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    98,     0,     0,     0,     0,     0,
      94,     0,     0,     0,   290,    98,    98,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    98,     0,     0,
       0,     0,     0,     0,   243,     0,     0,     0,   290,   537,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,     0,     0,   243,     0,
       0,     0,     0,    94,     0,     0,     0,   586,   588,     0,
       0,    98,     0,     0,     0,     0,     0,    98,     0,    98,
       0,   243,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   610,     0,   243,     0,   586,
     588,     0,     0,     0,     0,     0,   243,     0,     0,     0,
       0,     0,     0,   243,    98,     0,     0,     0,     0,   243,
     243,     0,     0,   243,     0,   850,   852,     0,   854,     0,
     856,   857,     0,     0,     0,     0,   862,     0,     0,   866,
     868,     0,   649,     0,     0,     0,     0,     0,     0,     0,
       0,    94,   243,     0,     0,   243,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   243,     0,     0,     0,     0,
       0,     0,     0,   337,  -560,  -560,  -560,  -560,   342,   343,
       0,     0,  -560,  -560,   243,     0,     0,     0,   350,   351,
      97,     0,    97,   118,   118,     0,     0,     0,     0,     0,
       0,   217,     0,     0,     0,     0,     0,   687,   688,     0,
       0,     0,     0,     0,     0,    94,     0,     0,   243,     0,
      94,    94,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,     0,     0,     0,     0,    97,     0,     0,   290,
     291,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   932,   934,   935,   936,
       0,   938,   940,     0,   291,   943,     0,   945,   946,     0,
       0,     0,     0,    94,     0,     0,     0,     0,    94,     0,
       0,     0,     0,     0,     0,    94,   290,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   243,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   964,
     965,   967,   968,   969,     0,     0,     0,     0,     0,     0,
       0,   971,     0,     0,     0,     0,     0,   243,     0,     0,
     243,     0,     0,     0,     0,     0,   243,   243,     0,     0,
       0,     0,    94,     0,     0,     0,     0,   700,     0,     0,
       0,     0,    94,     0,     0,     0,     0,     0,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,    97,   243,   350,
     351,     0,   610,   795,     0,   798,   800,    94,     0,     0,
       0,   805,   807,     0,     0,     0,    94,     0,     0,     0,
       0,   813,     0,     0,     0,     0,     0,     0,     0,     0,
     290,   352,   290,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   798,   800,     0,   805,   807,     0,     0,
    -230,     0,     0,     0,     0,   243,     0,     0,   243,     0,
       0,    97,    94,     0,     0,     0,    97,    97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   291,     0,     0,     0,     0,
       0,     0,     0,   290,     0,   243,     0,     0,     0,   871,
       0,     0,     0,     0,     0,     0,   873,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    97,
       0,     0,     0,     0,    97,     0,     0,     0,     0,     0,
       0,    97,   291,     0,   873,     0,     0,     0,     0,     0,
     574,   575,   243,     0,   576,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,   173,
     174,     0,     0,   175,   176,   177,   178,     0,     0,     0,
     337,   338,   339,   340,   341,   342,   343,   179,    97,   346,
     347,     0,     0,     0,     0,   350,   351,     0,    97,     0,
       0,     0,     0,     0,     0,     0,    97,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
     190,   191,     0,     0,     0,     0,   243,   192,   255,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,     0,
       0,     0,     0,    97,     0,    94,     0,     0,     0,     0,
       0,     0,    97,    94,     0,     0,     0,     0,     0,     0,
     290,     0,     0,     0,     0,     0,   291,     0,   291,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
       0,     0,     0,     0,     0,     0,    94,     0,    97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,    94,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   291,
       0,     0,    94,    94,   594,   567,     0,     0,   595,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,     0,
       0,     0,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,   173,   174,     0,     0,   175,   176,   177,
     178,     0,     0,     0,     0,     0,    94,    94,     0,     0,
       0,   179,     0,     0,   884,     0,     0,     0,    94,     0,
       0,    97,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,   190,   191,     0,     0,     0,     0,
       0,   192,   255,     0,     0,     0,     0,   718,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,     0,     0,     0,     0,     0,    94,     0,
      94,     0,     0,    94,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,     0,     0,   350,
     351,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    97,     0,     0,     0,     0,     0,     0,     0,    97,
       0,     0,     0,     0,     0,     0,   291,     0,     0,     0,
       0,   352,     0,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,     0,    97,    97,     0,     0,     0,     0,
    -392,     0,     0,     0,     0,    97,     0,     0,     0,     0,
       0,     0,    97,  -392,  -392,  -392,  -392,  -392,  -392,     0,
    -392,     0,     0,     0,    97,    97,  -392,  -392,  -392,     0,
       0,    97,     0,     0,     0,     0,     0,  -392,  -392,     0,
    -392,  -392,  -392,  -392,  -392,     0,     0,     0,    97,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,     0,     0,     0,     0,     0,
       0,  -392,  -392,  -392,  -392,  -392,  -392,  -392,  -392,  -392,
    -392,  -392,  -392,  -392,     0,     0,  -392,  -392,  -392,     0,
       0,  -392,    97,    97,     0,     0,     0,  -392,     0,     0,
     885,  -392,     0,     0,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -392,     0,
    -392,  -392,  -392,  -392,  -392,  -392,  -392,  -392,  -392,  -392,
       0,     0,     0,     0,  -392,  -392,  -392,  -392,     0,   255,
    -392,  -392,  -392,  -392,  -392,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,     0,
       0,     0,     0,     0,    97,     0,    97,  -559,     4,    97,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,     0,     0,     0,    15,     0,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,    29,    30,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,     0,     0,    48,
      49,     0,    50,    51,     0,    52,     0,    53,     0,    54,
      55,    56,    57,    58,    59,  -269,     0,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -269,  -269,
    -269,  -269,  -269,  -269,     0,  -269,     0,    61,    62,    63,
       0,     0,  -269,  -269,  -269,     0,     0,     0,     0,  -559,
       0,  -559,  -269,  -269,     0,  -269,  -269,  -269,  -269,  -269,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,     0,
       0,  -269,  -269,  -269,     0,     0,  -269,     0,     0,     0,
       0,     0,  -269,     0,     0,     0,  -269,     0,     0,     0,
       0,     0,     0,     0,  -269,     0,     0,     0,     0,     0,
       0,     0,     0,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,     0,     0,  -559,     0,     0,
    -269,  -269,  -269,     0,     0,  -269,  -269,  -269,  -269,  -269,
    -559,  -559,  -559,  -559,  -559,  -559,     0,  -559,     0,     0,
       0,     0,     0,  -559,  -559,  -559,     0,     0,     0,     0,
       0,     0,     0,     0,  -559,  -559,     0,  -559,  -559,  -559,
    -559,  -559,     0,     0,     0,     0,     0,     0,     0,     0,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,     0,     0,   350,   351,     0,  -559,  -559,
    -559,  -559,  -559,  -559,  -559,  -559,  -559,  -559,  -559,  -559,
    -559,     0,     0,  -559,  -559,  -559,     0,     0,  -559,     0,
       0,     0,     0,     0,  -559,     0,     0,   352,  -559,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,     0,
       0,     0,     0,     0,     0,  -559,     0,  -559,  -559,  -559,
    -559,  -559,  -559,  -559,  -559,  -559,  -559,     0,     0,  -285,
       0,  -559,  -559,  -559,  -559,     0,   255,  -559,  -559,  -559,
    -559,  -559,  -285,  -285,  -285,  -285,  -285,  -285,     0,  -285,
       0,     0,     0,     0,     0,   700,  -285,  -285,     0,     0,
       0,     0,     0,     0,     0,     0,  -285,  -285,     0,  -285,
    -285,  -285,  -285,  -285,     0,     0,     0,     0,     0,     0,
       0,     0,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,     0,     0,   350,   351,     0,
    -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,
    -285,  -285,  -285,     0,     0,  -285,  -285,  -285,     0,     0,
    -285,     0,     0,     0,     0,     0,  -285,     0,     0,   352,
    -285,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,     0,     0,     0,     0,     0,     0,  -285,     0,  -285,
    -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,     0,
       0,  -535,     0,     0,  -285,  -285,  -285,     0,   252,  -285,
    -285,  -285,  -285,  -285,  -535,  -535,  -535,     0,  -535,  -535,
       0,  -535,     0,     0,     0,     0,     0,  -535,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -535,  -535,
       0,  -535,  -535,  -535,  -535,  -535,     0,     0,     0,     0,
       0,     0,     0,     0,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,  -560,  -560,     0,     0,   350,
     351,     0,  -535,  -535,  -535,  -535,  -535,  -535,  -535,  -535,
    -535,  -535,  -535,  -535,  -535,     0,     0,  -535,  -535,  -535,
       0,   702,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -535,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,     0,     0,     0,     0,     0,   -97,  -535,
       0,  -535,  -535,  -535,  -535,  -535,  -535,  -535,  -535,  -535,
    -535,     0,     0,  -278,     0,  -535,  -535,  -535,   -89,     0,
       0,  -535,     0,  -535,  -535,  -535,  -278,  -278,  -278,     0,
    -278,  -278,     0,  -278,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -278,  -278,     0,  -278,  -278,  -278,  -278,  -278,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,     0,     0,  -278,
    -278,  -278,     0,   703,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -278,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -99,  -278,     0,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,     0,     0,     0,     0,     0,  -278,  -278,
     -91,     0,     0,  -278,     0,  -278,  -278,  -278,   268,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
    -559,  -559,  -559,     0,     0,  -559,    15,     0,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,     0,    30,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,     0,     0,    48,
      49,     0,    50,    51,     0,    52,     0,    53,     0,    54,
      55,    56,    57,    58,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,    62,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -559,
     268,  -559,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,  -559,     0,  -559,  -559,    15,     0,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,     0,    28,     0,    30,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,     0,
       0,    48,    49,     0,    50,    51,     0,    52,     0,    53,
       0,    54,    55,    56,    57,    58,    59,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -559,   268,  -559,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,  -559,     0,     0,  -559,
      15,  -559,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,     0,    30,    31,
      32,     0,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,     0,     0,    48,    49,     0,    50,    51,     0,    52,
       0,    53,     0,    54,    55,    56,    57,    58,    59,     0,
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -559,   268,  -559,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,  -559,     0,
       0,  -559,    15,     0,    16,    17,    18,    19,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,     0,    28,     0,
      30,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,    45,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    47,     0,     0,    48,    49,     0,    50,    51,
       0,    52,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     0,     0,     0,     4,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,     0,     0,    61,    62,    63,     0,    15,     0,    16,
      17,    18,    19,     0,     0,  -559,     0,  -559,    20,    21,
      22,    23,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,     0,    28,    29,    30,    31,    32,     0,    33,
      34,    35,    36,    37,    38,     0,    39,    40,    41,     0,
       0,    42,     0,     0,    43,    44,     0,    45,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,     0,     0,
      48,    49,     0,    50,    51,     0,    52,     0,    53,     0,
      54,    55,    56,    57,    58,    59,     0,     0,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,     0,     0,  -559,     0,     0,     0,     0,     0,     0,
    -559,   268,  -559,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,     0,  -559,  -559,     0,     0,     0,    15,
       0,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,     0,    30,    31,    32,
       0,    33,    34,    35,    36,    37,    38,     0,    39,    40,
      41,     0,     0,    42,     0,     0,    43,    44,     0,    45,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    47,
       0,     0,    48,    49,     0,    50,    51,     0,    52,     0,
      53,     0,    54,    55,    56,    57,    58,    59,     0,     0,
      60,     0,     0,     0,     0,     0,   268,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
      61,    62,    63,     0,    15,     0,    16,    17,    18,    19,
       0,     0,  -559,     0,  -559,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,     0,    30,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47,     0,     0,   269,    49,     0,
      50,    51,     0,    52,     0,    53,     0,    54,    55,    56,
      57,    58,    59,     0,     0,    60,     0,     0,     0,     0,
       0,   268,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,    61,    62,    63,     0,    15,
       0,    16,    17,    18,    19,  -559,     0,  -559,     0,  -559,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,     0,    30,    31,    32,
       0,    33,    34,    35,    36,    37,    38,     0,    39,    40,
      41,     0,     0,    42,     0,     0,    43,    44,     0,    45,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    47,
       0,     0,    48,    49,     0,    50,    51,     0,    52,     0,
      53,     0,    54,    55,    56,    57,    58,    59,     0,     0,
      60,     0,     0,     0,     0,     0,   268,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
      61,    62,    63,     0,    15,     0,    16,    17,    18,    19,
    -559,     0,  -559,     0,  -559,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,     0,    30,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47,     0,     0,    48,    49,     0,
      50,    51,     0,    52,     0,    53,     0,    54,    55,    56,
      57,    58,    59,     0,     0,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,     0,     0,
    -559,     0,     0,     0,     0,     0,     0,  -559,   268,  -559,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,  -559,     0,     0,     0,    15,     0,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,     0,    30,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,     0,     0,    48,
      49,     0,    50,    51,     0,    52,     0,    53,     0,    54,
      55,    56,    57,    58,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,    61,    62,    63,
       0,    15,     0,    16,    17,    18,    19,     0,     0,  -559,
       0,  -559,    20,    21,    22,    23,    24,    25,    26,     0,
       0,   106,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,    33,    34,    35,    36,    37,    38,   238,
      39,    40,    41,     0,     0,    42,     0,     0,    43,    44,
       0,    45,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   200,     0,     0,   111,    49,     0,    50,    51,     0,
     239,   240,    53,     0,    54,    55,    56,    57,    58,    59,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,    61,   241,    63,     0,    15,     0,    16,    17,
      18,    19,     0,     0,     0,     0,   232,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,     0,     0,   111,
      49,     0,    50,    51,     0,     0,     0,    53,     0,    54,
      55,    56,    57,    58,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,    61,    62,    63,
       0,    15,     0,    16,    17,    18,    19,     0,     0,   231,
       0,   232,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    32,     0,    33,    34,    35,    36,    37,    38,     0,
      39,    40,    41,     0,     0,    42,     0,     0,    43,    44,
       0,    45,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   200,     0,     0,   111,    49,     0,    50,    51,     0,
       0,     0,    53,     0,    54,    55,    56,    57,    58,    59,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,    61,    62,    63,     0,    15,     0,    16,    17,
      18,    19,     0,     0,     0,     0,   232,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,    29,    30,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,     0,     0,    48,
      49,     0,    50,    51,     0,    52,     0,    53,     0,    54,
      55,    56,    57,    58,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,    61,    62,    63,
      15,     0,    16,    17,    18,    19,     0,     0,     0,   422,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,     0,    30,    31,
      32,     0,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,     0,     0,    48,    49,     0,    50,    51,     0,    52,
       0,    53,     0,    54,    55,    56,    57,    58,    59,     0,
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   422,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,     0,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,     0,     0,     0,     0,     0,   155,   156,   157,   158,
     159,   160,   161,   162,    35,    36,   163,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,   173,   174,     0,     0,   175,   176,   177,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,     0,   190,   191,     0,     0,     0,     0,     0,   192,
     193,  -528,  -528,  -528,  -528,  -528,  -528,  -528,  -528,  -528,
       0,     0,     0,     0,     0,     0,     0,  -528,     0,  -528,
    -528,  -528,  -528,     0,  -528,     0,     0,     0,  -528,  -528,
    -528,  -528,  -528,  -528,  -528,     0,     0,  -528,     0,     0,
       0,     0,     0,     0,     0,     0,  -528,  -528,     0,  -528,
    -528,  -528,  -528,  -528,  -528,  -528,  -528,  -528,  -528,     0,
       0,  -528,     0,     0,  -528,  -528,     0,  -528,  -528,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -528,     0,     0,
    -528,  -528,     0,  -528,  -528,     0,  -528,  -528,  -528,     0,
    -528,  -528,  -528,  -528,  -528,  -528,     0,     0,  -528,     0,
       0,     0,     0,     0,     0,  -529,  -529,  -529,  -529,  -529,
    -529,  -529,  -529,  -529,     0,     0,     0,     0,  -528,  -528,
    -528,  -529,  -528,  -529,  -529,  -529,  -529,  -528,  -529,     0,
       0,     0,  -529,  -529,  -529,  -529,  -529,  -529,  -529,     0,
       0,  -529,     0,     0,     0,     0,     0,     0,     0,     0,
    -529,  -529,     0,  -529,  -529,  -529,  -529,  -529,  -529,  -529,
    -529,  -529,  -529,     0,     0,  -529,     0,     0,  -529,  -529,
       0,  -529,  -529,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -529,     0,     0,  -529,  -529,     0,  -529,  -529,     0,
    -529,  -529,  -529,     0,  -529,  -529,  -529,  -529,  -529,  -529,
       0,     0,  -529,     0,     0,     0,     0,     0,     0,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,  -531,     0,     0,
       0,     0,  -529,  -529,  -529,  -531,  -529,  -531,  -531,  -531,
    -531,  -529,     0,     0,     0,     0,  -531,  -531,  -531,  -531,
    -531,  -531,  -531,     0,     0,  -531,     0,     0,     0,     0,
       0,     0,     0,     0,  -531,  -531,     0,  -531,  -531,  -531,
    -531,  -531,  -531,  -531,  -531,  -531,  -531,     0,     0,  -531,
       0,     0,  -531,  -531,     0,  -531,  -531,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -531,   740,     0,  -531,  -531,
       0,  -531,  -531,     0,  -531,  -531,  -531,     0,  -531,  -531,
    -531,  -531,  -531,  -531,     0,     0,  -531,     0,     0,     0,
       0,     0,     0,   -97,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -531,  -531,  -531,     0,
       0,     0,     0,     0,     0,  -531,  -532,  -532,  -532,  -532,
    -532,  -532,  -532,  -532,  -532,     0,     0,     0,     0,     0,
       0,     0,  -532,     0,  -532,  -532,  -532,  -532,     0,     0,
       0,     0,     0,  -532,  -532,  -532,  -532,  -532,  -532,  -532,
       0,     0,  -532,     0,     0,     0,     0,     0,     0,     0,
       0,  -532,  -532,     0,  -532,  -532,  -532,  -532,  -532,  -532,
    -532,  -532,  -532,  -532,     0,     0,  -532,     0,     0,  -532,
    -532,     0,  -532,  -532,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -532,   741,     0,  -532,  -532,     0,  -532,  -532,
       0,  -532,  -532,  -532,     0,  -532,  -532,  -532,  -532,  -532,
    -532,     0,     0,  -532,     0,     0,     0,     0,     0,     0,
     -99,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -532,  -532,  -532,     0,     0,     0,     0,
       0,     0,  -532,  -533,  -533,  -533,  -533,  -533,  -533,  -533,
    -533,  -533,     0,     0,     0,     0,     0,     0,     0,  -533,
       0,  -533,  -533,  -533,  -533,     0,     0,     0,     0,     0,
    -533,  -533,  -533,  -533,  -533,  -533,  -533,     0,     0,  -533,
       0,     0,     0,     0,     0,     0,     0,     0,  -533,  -533,
       0,  -533,  -533,  -533,  -533,  -533,  -533,  -533,  -533,  -533,
    -533,     0,     0,  -533,     0,     0,  -533,  -533,     0,  -533,
    -533,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -533,
       0,     0,  -533,  -533,     0,  -533,  -533,     0,  -533,  -533,
    -533,     0,  -533,  -533,  -533,  -533,  -533,  -533,     0,     0,
    -533,     0,     0,     0,     0,     0,     0,  -534,  -534,  -534,
    -534,  -534,  -534,  -534,  -534,  -534,     0,     0,     0,     0,
    -533,  -533,  -533,  -534,     0,  -534,  -534,  -534,  -534,  -533,
       0,     0,     0,     0,  -534,  -534,  -534,  -534,  -534,  -534,
    -534,     0,     0,  -534,     0,     0,     0,     0,     0,     0,
       0,     0,  -534,  -534,     0,  -534,  -534,  -534,  -534,  -534,
    -534,  -534,  -534,  -534,  -534,     0,     0,  -534,     0,     0,
    -534,  -534,     0,  -534,  -534,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -534,     0,     0,  -534,  -534,     0,  -534,
    -534,     0,  -534,  -534,  -534,     0,  -534,  -534,  -534,  -534,
    -534,  -534,     0,     0,  -534,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -534,  -534,  -534,     0,     0,     0,
       0,     0,     0,  -534,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,     0,     0,
       0,   145,   146,   147,   218,   219,   220,   221,   152,   153,
     154,     0,     0,     0,     0,     0,   155,   156,   157,   222,
     223,   160,   224,   162,   293,   294,   225,   295,     0,     0,
       0,     0,     0,     0,   296,     0,     0,     0,     0,     0,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,   173,   174,     0,     0,   175,   176,   177,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,     0,     0,     0,     0,     0,   297,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,     0,   190,   191,     0,     0,     0,     0,     0,   192,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,   145,   146,   147,
     218,   219,   220,   221,   152,   153,   154,     0,     0,     0,
       0,     0,   155,   156,   157,   222,   223,   160,   224,   162,
     293,   294,   225,   295,     0,     0,     0,     0,     0,     0,
     296,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,   173,   174,     0,
       0,   175,   176,   177,   178,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,     0,     0,     0,
       0,     0,     0,   416,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,   190,   191,
       0,     0,     0,     0,     0,   192,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
       0,     0,     0,   145,   146,   147,   218,   219,   220,   221,
     152,   153,   154,     0,     0,     0,     0,     0,   155,   156,
     157,   222,   223,   160,   224,   162,     0,     0,   225,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,   173,   174,     0,     0,   175,   176,   177,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,     0,     0,   226,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,   190,   191,     0,     0,     0,     0,
       0,   192,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,     0,     0,     0,   145,
     146,   147,   218,   219,   220,   221,   152,   153,   154,     0,
       0,     0,     0,     0,   155,   156,   157,   222,   223,   160,
     224,   162,     0,     0,   225,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,   173,
     174,     0,     0,   175,   176,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
     190,   191,     0,     0,     0,     0,     0,   192,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,     0,     0,     0,    15,     0,   101,   102,    18,    19,
       0,     0,     0,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   286,     0,     0,   111,    49,     0,
      50,    51,     0,     0,     0,    53,     0,    54,    55,    56,
      57,    58,    59,     0,     0,    60,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,     0,     0,     0,    15,   112,   101,   102,    18,    19,
       0,     0,   287,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   286,     0,     0,   111,    49,     0,
      50,    51,     0,     0,     0,    53,     0,    54,    55,    56,
      57,    58,    59,     0,     0,    60,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,     0,     0,     0,    15,   112,   101,   102,    18,    19,
       0,     0,   531,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,   238,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,     0,     0,   111,    49,     0,
      50,    51,     0,   634,   240,    53,     0,    54,    55,    56,
      57,    58,    59,     0,     0,    60,   501,     0,     0,   502,
     503,     0,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,     0,    61,   241,    63,    15,     0,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,     0,    28,    29,    30,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,     0,
       0,    48,    49,     0,    50,    51,     0,    52,     0,    53,
       0,    54,    55,    56,    57,    58,    59,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,    61,
      62,    63,    15,     0,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
     238,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,    45,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   200,     0,     0,   111,    49,     0,    50,    51,
       0,   634,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,   501,     0,     0,   502,   503,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,     0,    61,   241,    63,    15,     0,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,     0,    30,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,     0,     0,    48,
      49,     0,    50,    51,     0,    52,     0,    53,     0,    54,
      55,    56,    57,    58,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,    61,    62,    63,
      15,     0,   101,   102,    18,    19,     0,     0,     0,     0,
       0,   103,   104,   105,    23,    24,    25,    26,     0,     0,
     106,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     200,     0,     0,   111,    49,     0,    50,    51,     0,   755,
       0,    53,     0,    54,    55,    56,    57,    58,    59,     0,
       0,    60,   501,     0,     0,   502,   503,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,    61,   241,    63,    15,     0,   101,   102,    18,    19,
       0,     0,     0,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,     0,     0,   111,    49,     0,
      50,    51,     0,   792,     0,    53,     0,    54,    55,    56,
      57,    58,    59,     0,     0,    60,   501,     0,     0,   502,
     503,     0,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,     0,    61,   241,    63,    15,     0,
     101,   102,    18,    19,     0,     0,     0,     0,     0,   103,
     104,   105,    23,    24,    25,    26,     0,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   200,     0,
       0,   111,    49,     0,    50,    51,     0,   634,     0,    53,
       0,    54,    55,    56,    57,    58,    59,     0,     0,    60,
     501,     0,     0,   502,   503,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,    61,
     241,    63,    15,     0,    16,    17,    18,    19,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
     238,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,    45,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   200,     0,     0,   111,    49,     0,    50,    51,
       0,   239,   240,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,    61,   241,    63,    15,     0,   101,   102,
      18,    19,     0,     0,     0,     0,     0,   103,   104,   105,
      23,    24,    25,    26,     0,     0,   106,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,    33,    34,
      35,    36,    37,    38,   238,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,     0,     0,   111,
      49,     0,    50,    51,     0,   239,     0,    53,     0,    54,
      55,    56,    57,    58,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,    61,   241,    63,
      15,     0,   101,   102,    18,    19,     0,     0,     0,     0,
       0,   103,   104,   105,    23,    24,    25,    26,     0,     0,
     106,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,    33,    34,    35,    36,    37,    38,   238,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     200,     0,     0,   111,    49,     0,    50,    51,     0,     0,
     240,    53,     0,    54,    55,    56,    57,    58,    59,     0,
       0,    60,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,    61,   241,    63,    15,     0,   101,   102,    18,    19,
       0,     0,     0,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,   238,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,     0,     0,   111,    49,     0,
      50,    51,     0,     0,     0,    53,     0,    54,    55,    56,
      57,    58,    59,     0,     0,    60,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,     0,    61,   241,    63,    15,     0,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   200,     0,
       0,   111,    49,     0,    50,    51,     0,   525,     0,    53,
       0,    54,    55,    56,    57,    58,    59,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,    61,
     241,    63,    15,     0,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,    45,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   200,     0,     0,   111,    49,     0,    50,    51,
       0,   239,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,    61,   241,    63,    15,     0,   101,   102,
      18,    19,     0,     0,     0,     0,     0,   103,   104,   105,
      23,    24,    25,    26,     0,     0,   106,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,     0,    33,    34,
      35,    36,    37,    38,     0,    39,    40,    41,     0,     0,
      42,     0,     0,    43,    44,     0,    45,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,     0,     0,   111,
      49,     0,    50,    51,     0,   525,     0,    53,     0,    54,
      55,    56,    57,    58,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,    61,   241,    63,
      15,     0,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      32,     0,    33,    34,    35,    36,    37,    38,     0,    39,
      40,    41,     0,     0,    42,     0,     0,    43,    44,     0,
      45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     200,     0,     0,   111,    49,     0,    50,    51,     0,     0,
       0,    53,     0,    54,    55,    56,    57,    58,    59,     0,
       0,    60,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,    61,    62,    63,    15,     0,   101,   102,    18,    19,
       0,     0,     0,     0,     0,   103,   104,   105,    23,    24,
      25,    26,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,    31,    32,     0,    33,    34,    35,    36,
      37,    38,     0,    39,    40,    41,     0,     0,    42,     0,
       0,    43,    44,     0,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,     0,     0,   111,    49,     0,
      50,    51,     0,     0,     0,    53,     0,    54,    55,    56,
      57,    58,    59,     0,     0,    60,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,     0,     0,     0,    61,   241,    63,    15,     0,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,     0,
      33,    34,    35,    36,    37,    38,     0,    39,    40,    41,
       0,     0,    42,     0,     0,    43,    44,     0,    45,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   200,     0,
       0,   111,    49,     0,    50,    51,     0,     0,     0,    53,
       0,    54,    55,    56,    57,    58,    59,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,    61,
     241,    63,    15,     0,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,   107,    34,    35,    36,   108,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   109,
       0,     0,   110,     0,     0,   111,    49,     0,    50,    51,
       0,     0,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,    15,   112,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   211,     0,     0,    48,    49,     0,    50,    51,
       0,    52,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,    15,   112,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   286,     0,     0,   333,    49,     0,    50,    51,
       0,   334,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,    15,   112,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,   107,    34,    35,    36,   108,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,     0,     0,   111,    49,     0,    50,    51,
       0,     0,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,    15,   112,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   286,     0,     0,   333,    49,     0,    50,    51,
       0,     0,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,    15,   112,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   863,     0,     0,   111,    49,     0,    50,    51,
       0,     0,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,    15,   112,   101,   102,    18,    19,     0,     0,
       0,     0,     0,   103,   104,   105,    23,    24,    25,    26,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    32,     0,    33,    34,    35,    36,    37,    38,
       0,    39,    40,    41,     0,     0,    42,     0,     0,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   881,     0,     0,   111,    49,     0,    50,    51,
       0,     0,     0,    53,     0,    54,    55,    56,    57,    58,
      59,     0,     0,    60,     0,     0,   580,   575,     0,     0,
     581,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,   173,   174,     0,     0,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,     0,   190,   191,   611,   567,
       0,     0,   612,   192,   255,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,   173,   174,     0,
       0,   175,   176,   177,   178,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,   190,   191,
     614,   575,     0,     0,   615,   192,   255,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,   173,
     174,     0,     0,   175,   176,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
     190,   191,   621,   567,     0,     0,   622,   192,   255,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,   173,   174,     0,     0,   175,   176,   177,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,     0,   190,   191,   624,   575,     0,     0,   625,   192,
     255,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,   173,   174,     0,     0,   175,   176,   177,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,   190,   191,   656,   567,     0,     0,
     657,   192,   255,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,   173,   174,     0,     0,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,     0,   190,   191,   659,   575,
       0,     0,   660,   192,   255,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,   173,   174,     0,
       0,   175,   176,   177,   178,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,     0,   190,   191,
     941,   567,     0,     0,   942,   192,   255,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,   173,
     174,     0,     0,   175,   176,   177,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
     190,   191,   948,   567,     0,     0,   949,   192,   255,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,   173,   174,     0,     0,   175,   176,   177,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,     0,   190,   191,   951,   575,     0,     0,   952,   192,
     255,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,   173,   174,     0,     0,   175,   176,   177,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,   190,   191,   580,   575,     0,     0,
     581,   192,   255,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,   173,   174,     0,     0,   175,
     176,   177,   178,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,     0,     0,   350,
     351,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,     0,   190,   191,     0,     0,
       0,     0,     0,   192,     0,     0,     0,     0,     0,     0,
       0,   352,     0,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   232
};

static const yytype_int16 yycheck[] =
{
       2,    83,    27,    16,    17,    81,    82,    20,     5,     6,
     292,    16,    17,    28,    22,    20,    13,   248,    10,    15,
     287,   419,   208,    15,    76,   336,    14,    22,   280,     7,
     390,   410,   284,    15,     4,   363,    48,   110,   430,   367,
      28,   258,   370,    62,    65,    50,    51,   363,    50,    51,
     336,   367,    52,   675,   370,    52,   273,   690,   764,   387,
     277,   389,    16,    17,   470,   365,    20,    16,    17,    65,
     462,    20,    65,   389,   504,   403,    54,   405,   427,    76,
     598,   430,   292,    65,   412,   766,   414,   403,   388,   405,
      98,   304,    25,    51,    16,   613,    50,   105,   414,    56,
      57,    58,    59,    98,   404,   623,   846,   606,    26,   671,
      16,   119,    29,   413,     2,   865,     4,   616,   690,   447,
     448,   269,   583,   584,   305,   531,    88,   308,   204,   310,
     671,   312,   448,   314,   675,    16,   842,    71,   214,    16,
     658,    88,    16,   471,    90,   473,    26,    25,    90,   690,
      90,    16,    90,    90,    27,    79,   117,   473,     0,    16,
     137,    25,   137,   137,    25,    37,    38,   144,   139,   144,
     144,   117,   472,   144,    25,   117,   137,   117,   134,   117,
     117,   143,    90,    16,    25,   333,    55,   937,    88,   265,
     930,   897,   109,   127,   128,   129,   143,   137,   122,   629,
      16,    16,   484,   470,   137,   418,   202,   637,   439,   117,
      28,   783,   208,   289,   895,   432,   134,   209,   210,   436,
     142,   139,   144,   929,   441,     9,    10,   849,   861,    25,
      25,    15,   865,   593,   451,   287,   142,   233,   144,   252,
     233,   254,   255,   143,   137,   247,   248,   252,   226,   254,
     271,   233,   644,   255,   134,   117,   137,   269,   719,   137,
      25,   142,   139,   144,   531,   142,    90,   144,   142,   142,
     144,   144,   144,   137,   484,   271,   137,   142,   271,   144,
     238,   239,   240,   279,   280,   142,   137,   144,   284,   271,
     287,   853,   698,    25,   643,   644,   137,   140,   252,   861,
     254,   144,    88,   252,   937,   254,   139,    88,   849,   142,
      88,   144,   331,   530,   387,   101,   117,   336,   499,   605,
     861,   333,   117,   101,   865,   109,   142,   142,   144,   144,
     322,   323,   324,   325,   334,    58,    59,   334,   837,    88,
     297,   137,   137,   139,   139,   140,    37,    38,    88,   144,
     136,   321,   365,   139,    88,   374,   375,   143,   136,   367,
      88,   101,   143,   365,    88,   143,    25,   727,    88,   705,
     749,    48,   137,   331,   139,   388,   712,   331,   336,   139,
     268,   389,   336,    90,   601,   117,   388,   142,   699,   144,
      25,   404,   602,    90,   143,   397,   937,   405,    58,    59,
     413,   653,   404,   143,   139,   137,   414,   638,   140,   143,
     117,   413,   144,   409,   410,   143,   468,    51,   470,   143,
     117,    55,   427,   143,   139,   209,   210,   409,   410,   444,
     137,   698,   950,   321,   111,   652,   438,   439,   326,   837,
     448,    17,    18,   445,   726,   631,   121,   839,    26,   111,
     667,    88,   114,   115,   459,   815,   444,   111,   117,   472,
     114,   115,   420,    90,   101,   473,   420,    90,   426,   427,
     472,   468,   430,   470,   258,   259,    88,   117,   137,   531,
     690,   140,   117,    55,    18,   144,    20,    88,   490,   101,
     839,   493,   276,   495,   117,    55,    71,    25,    90,   136,
     101,   459,   137,    20,   462,   140,   143,   137,    91,   144,
      88,    86,    87,   479,   137,   137,   726,   142,   137,   134,
     880,    71,   524,   101,   136,   117,   140,   758,    90,   117,
     555,   143,    90,   491,   531,   136,   144,   141,   322,   323,
     324,   325,   143,   327,   328,   137,   763,    55,   573,   124,
     125,   126,   127,   128,   129,   117,   134,   445,   136,   117,
     137,   139,   135,   571,    71,   143,   454,   525,    71,   137,
      97,   579,    13,   598,   582,   137,   571,   579,    15,   137,
     582,   583,   584,    26,   579,   913,   263,   582,   613,   597,
      16,   599,   269,    63,   922,   591,   924,   599,   623,    26,
     592,   818,    15,   605,   606,   140,   608,   391,   924,   591,
     135,   821,   627,     2,   616,     4,     5,     6,   137,   137,
       9,    10,   137,   923,    13,   603,    15,    16,    17,   117,
      51,    20,   714,   658,   626,   631,   638,   823,   643,   627,
     137,   137,   137,   829,   669,    88,   698,   605,    71,    51,
      51,   605,    53,    54,    55,    56,   333,   653,   101,    48,
     137,    88,   137,    52,   137,   690,   117,    51,    15,    53,
      54,    55,    56,    62,   101,    18,   634,    15,   135,   637,
     699,   137,   135,   702,   703,   643,   644,    76,   137,   708,
     709,   134,    15,   136,   119,   141,   139,   663,   664,    91,
     143,   698,   125,   126,   127,   128,   129,   134,    92,   136,
      14,   140,   139,    15,    98,    99,   143,   719,    15,   137,
     109,    88,   111,   400,    51,   721,    53,    54,    55,    56,
     732,   408,   728,   735,   101,   142,   137,   695,   137,   721,
     124,   137,   137,   127,   137,   737,   728,   137,   135,   122,
      15,    61,   137,   749,    64,    65,   758,   137,   783,    51,
     144,    53,    54,    55,    56,    92,   137,   749,    62,   136,
      64,    65,   774,   775,   137,   777,   143,   779,   780,    15,
     135,    15,    88,   785,   803,    15,   788,   789,    51,   786,
      53,    54,    55,    56,   752,   101,    15,   755,   764,    15,
     766,   137,   112,   113,   135,   122,    55,   883,   592,    88,
     199,   137,    51,   135,    53,    54,    55,    56,   112,   113,
     209,   210,   101,   500,    15,   822,    55,   823,   137,    92,
     136,    15,   137,   829,   792,   837,    99,   143,    88,   137,
      61,   137,   626,    64,    65,   137,    40,    41,    42,    43,
      44,   101,   137,    92,    15,   139,     2,   136,     4,    98,
      99,   124,   139,   252,   143,   254,   255,    13,   137,   258,
     259,    88,    13,     6,   263,   900,   842,   843,   445,   268,
     269,   839,   582,   926,   101,   124,   136,   276,   127,   663,
     930,   112,   113,   143,     2,   715,     4,   925,   287,   506,
     139,   821,    48,   905,   906,   907,   908,    88,   910,   911,
     923,     7,   914,   861,   916,   917,   924,   671,    -1,   136,
     101,   923,    -1,   925,   926,   950,   143,    -1,    -1,   895,
      -1,   897,   321,   322,   323,   324,   325,   326,   327,   328,
      48,    -1,   331,    -1,   333,   334,    51,   336,    53,    54,
      55,    56,    -1,   737,    -1,   136,   958,   959,   960,   961,
     962,    -1,   143,   929,    -1,   111,    -1,    -1,   970,    -1,
      88,    63,    64,    65,    -1,    51,   365,    53,    54,    55,
      56,    -1,    88,   101,    -1,   374,   375,    -1,    51,    71,
      53,    54,    55,    56,   675,   101,    -1,   678,    -1,   388,
      -1,   390,   391,   111,    86,    87,   683,    -1,    -1,   690,
      -1,   400,    -1,    -1,   691,   404,    92,    -1,   136,   408,
     112,   113,    98,    99,   413,   143,    -1,    -1,    -1,    92,
     136,    -1,    -1,    -1,    -1,    98,    99,   143,    -1,   716,
     717,    -1,    -1,   125,   126,   127,   128,   129,   124,    -1,
      -1,   127,    -1,   199,    -1,    -1,   445,   734,    -1,    -1,
      -1,   124,    -1,   139,   127,   454,    -1,    -1,    -1,   746,
     747,    63,    64,    65,    -1,    -1,   753,    -1,    -1,   468,
      -1,   470,    -1,   472,    -1,    -1,    -1,    -1,     0,    -1,
      -1,   199,    -1,   770,   771,    63,    64,    65,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,   500,    -1,    -1,    26,    27,    62,   263,    64,    65,
     112,   113,   268,   269,    -1,    37,    38,    -1,    40,    41,
      42,    43,    44,     2,    -1,     4,    -1,   814,    -1,    -1,
       9,    10,   531,    71,   112,   113,    15,    16,    17,   826,
      -1,    20,    -1,    -1,    -1,   263,    -1,    -1,    86,    87,
     268,   269,    -1,    -1,    -1,    -1,   112,   113,   849,    -1,
     851,    63,    64,    65,   855,   321,    88,    -1,    -1,    48,
     326,    -1,    -1,    -1,   865,    -1,   867,   333,    -1,   101,
     336,    -1,    -1,    62,   122,   123,   124,   125,   126,   127,
     128,   129,    -1,   592,   593,    -1,    -1,    -1,    -1,   886,
      -1,   888,    -1,   321,   891,    63,    64,    65,   326,    -1,
     112,   113,   134,   135,    -1,   333,    -1,   139,   140,    -1,
     142,   143,   144,    -1,    63,    64,    65,   626,    -1,    -1,
     109,    -1,   111,    -1,   390,    -1,    63,    64,    65,    -1,
      -1,    -1,   933,    -1,   400,    -1,   937,    -1,   939,    -1,
      -1,    -1,   408,   944,   112,   113,    63,    64,    65,    -1,
      51,    -1,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,   390,   112,   113,   966,    -1,    -1,    -1,    -1,
      -1,    -1,   400,    -1,   683,   112,   113,    -1,    -1,   445,
     408,    -1,   691,    -1,    -1,    -1,    -1,    -1,   454,   698,
     699,    92,    -1,   702,   703,   112,   113,    98,    -1,   708,
     709,    51,    -1,    53,    54,    55,    56,   716,   717,    -1,
     199,    -1,    -1,    -1,    -1,    -1,    -1,   445,   727,    -1,
     209,   210,    -1,    -1,    -1,   734,   454,    -1,   737,    -1,
      -1,    -1,    -1,    -1,   500,    -1,    -1,   746,   747,    -1,
      -1,    -1,    92,    -1,   753,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   770,   771,   252,    -1,   254,   255,    -1,    -1,   258,
     259,    -1,   500,    -1,   263,    -1,    -1,   786,    -1,   268,
     269,    -1,    -1,    -1,    -1,    -1,    -1,   276,    -1,    -1,
      -1,    -1,    -1,    -1,   803,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   814,   815,    -1,    -1,    -1,
      -1,    -1,    -1,   822,    -1,    -1,    -1,   826,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   593,    -1,    -1,
      -1,    -1,   321,   322,   323,   324,   325,   326,   327,   328,
      -1,    -1,   331,    -1,   333,    -1,    -1,   336,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   593,    -1,    -1,    -1,    -1,
      -1,   880,    -1,    -1,    -1,    -1,   365,   886,    -1,   888,
      -1,    -1,   891,    -1,    -1,   374,   375,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    -1,    80,    81,   388,
      -1,   390,   391,    86,    87,    -1,    -1,    -1,    -1,    -1,
      -1,   400,    -1,    -1,   923,   404,    -1,   683,    -1,   408,
      -1,    -1,    -1,    -1,   413,   691,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   699,    -1,    -1,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,    -1,    -1,
     716,   717,    -1,    -1,    -1,   683,   445,    -1,    -1,    -1,
      -1,   727,    -1,   691,    -1,   454,    -1,    -1,   734,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     746,   747,    -1,   472,    -1,    -1,    -1,   753,   716,   717,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   727,
      -1,    -1,    -1,    -1,   770,   771,   734,    -1,    -1,    -1,
      -1,   500,    -1,    -1,    -1,    -1,    -1,    -1,   746,   747,
      -1,    -1,    -1,    -1,    -1,   753,    -1,    -1,    -1,    16,
      17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   770,   771,    -1,    -1,    -1,    -1,   814,   815,
      -1,    -1,    -1,    -1,    -1,    -1,   822,    -1,    45,    46,
     826,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   814,   815,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   826,    -1,
      -1,    -1,    -1,   592,   593,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    55,   880,    -1,    -1,    -1,    -1,    -1,
     886,    -1,   888,    -1,    -1,   891,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,   626,    80,    81,
      -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,   880,    -1,    -1,    -1,    98,    -1,   886,    -1,
     888,    -1,    -1,   891,   493,    -1,   495,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,    -1,   131,
     132,    -1,    -1,    -1,   683,    -1,   138,   139,    -1,    -1,
      -1,    -1,   691,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     699,    -1,    -1,   702,   703,    -1,    -1,    -1,    -1,   708,
     709,    -1,    -1,    -1,    -1,    -1,    -1,   716,   717,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   727,    -1,
      -1,    -1,    -1,    -1,    -1,   734,    -1,    -1,   737,    -1,
      -1,   238,   239,   240,   241,    -1,    -1,   746,   747,    -1,
      -1,    -1,    -1,    -1,   753,   252,    -1,   254,   255,    -1,
      -1,    -1,    -1,    -1,     2,    -1,     4,     5,     6,     7,
      -1,   770,   771,    -1,    -1,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   803,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    52,   814,   815,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   826,    -1,    -1,
      -1,    -1,    -1,    -1,   331,    -1,    -1,    -1,    76,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,    -1,    -1,   365,    -1,
      -1,    -1,    -1,   111,    -1,    -1,    -1,   374,   375,    -1,
      -1,   880,    -1,    -1,    -1,    -1,    -1,   886,    -1,   888,
      -1,   388,   891,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   402,    -1,   404,    -1,   406,
     407,    -1,    -1,    -1,    -1,    -1,   413,    -1,    -1,    -1,
      -1,    -1,    -1,   420,   923,    -1,    -1,    -1,    -1,   426,
     427,    -1,    -1,   430,    -1,   774,   775,    -1,   777,    -1,
     779,   780,    -1,    -1,    -1,    -1,   785,    -1,    -1,   788,
     789,    -1,   449,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   199,   459,    -1,    -1,   462,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   472,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    80,    81,   491,    -1,    -1,    -1,    86,    87,
       2,    -1,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    13,    -1,    -1,    -1,    -1,    -1,   514,   515,    -1,
      -1,    -1,    -1,    -1,    -1,   263,    -1,    -1,   525,    -1,
     268,   269,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,    -1,    -1,    -1,    -1,    48,    -1,    -1,   287,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   905,   906,   907,   908,
      -1,   910,   911,    -1,    76,   914,    -1,   916,   917,    -1,
      -1,    -1,    -1,   321,    -1,    -1,    -1,    -1,   326,    -1,
      -1,    -1,    -1,    -1,    -1,   333,   334,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   605,   111,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   958,
     959,   960,   961,   962,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   970,    -1,    -1,    -1,    -1,    -1,   634,    -1,    -1,
     637,    -1,    -1,    -1,    -1,    -1,   643,   644,    -1,    -1,
      -1,    -1,   390,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,   400,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     408,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,   199,   695,    86,
      87,    -1,   699,   700,    -1,   702,   703,   445,    -1,    -1,
      -1,   708,   709,    -1,    -1,    -1,   454,    -1,    -1,    -1,
      -1,   718,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     468,   118,   470,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   740,   741,    -1,   743,   744,    -1,    -1,
     137,    -1,    -1,    -1,    -1,   752,    -1,    -1,   755,    -1,
      -1,   263,   500,    -1,    -1,    -1,   268,   269,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   287,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   531,    -1,   792,    -1,    -1,    -1,   796,
      -1,    -1,    -1,    -1,    -1,    -1,   803,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   321,
      -1,    -1,    -1,    -1,   326,    -1,    -1,    -1,    -1,    -1,
      -1,   333,   334,    -1,   831,    -1,    -1,    -1,    -1,    -1,
      51,    52,   839,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   593,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    80,
      81,    -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    98,   390,    80,
      81,    -1,    -1,    -1,    -1,    86,    87,    -1,   400,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   408,    -1,    -1,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
     131,   132,    -1,    -1,    -1,    -1,   923,   138,   139,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
      -1,    -1,    -1,   445,    -1,   683,    -1,    -1,    -1,    -1,
      -1,    -1,   454,   691,    -1,    -1,    -1,    -1,    -1,    -1,
     698,    -1,    -1,    -1,    -1,    -1,   468,    -1,   470,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   716,   717,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   727,
      -1,    -1,    -1,    -1,    -1,    -1,   734,    -1,   500,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   746,   747,
      -1,    -1,    -1,    -1,    -1,   753,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   531,
      -1,    -1,   770,   771,    51,    52,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   786,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    80,    81,    -1,    -1,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    -1,   814,   815,    -1,    -1,
      -1,    98,    -1,    -1,   822,    -1,    -1,    -1,   826,    -1,
      -1,   593,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,   131,   132,    -1,    -1,    -1,    -1,
      -1,   138,   139,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   880,    -1,    -1,    -1,    -1,    -1,   886,    -1,
     888,    -1,    -1,   891,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    86,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   683,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   691,
      -1,    -1,    -1,    -1,    -1,    -1,   698,    -1,    -1,    -1,
      -1,   118,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,   716,   717,    -1,    -1,    -1,    -1,
       0,    -1,    -1,    -1,    -1,   727,    -1,    -1,    -1,    -1,
      -1,    -1,   734,    13,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    -1,   746,   747,    26,    27,    28,    -1,
      -1,   753,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    -1,   770,   771,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   786,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    86,    87,    88,    -1,
      -1,    91,   814,   815,    -1,    -1,    -1,    97,    -1,    -1,
     822,   101,    -1,    -1,   826,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,    -1,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
      -1,    -1,    -1,    -1,   134,   135,   136,   137,    -1,   139,
     140,   141,   142,   143,   144,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   880,    -1,
      -1,    -1,    -1,    -1,   886,    -1,   888,     0,     1,   891,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,   100,    -1,   102,
     103,   104,   105,   106,   107,     0,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    18,    -1,    20,    -1,   130,   131,   132,
      -1,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,   142,
      -1,   144,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    86,    87,    88,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,    -1,     0,    -1,    -1,
     135,   136,   137,    -1,    -1,   140,   141,   142,   143,   144,
      13,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    86,    87,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    86,    87,    88,    -1,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    97,    -1,    -1,   118,   101,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
      -1,    -1,    -1,    -1,    -1,   118,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,    -1,     0,
      -1,   134,   135,   136,   137,    -1,   139,   140,   141,   142,
     143,   144,    13,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    44,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    86,    87,    -1,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    86,    87,    88,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,   118,
     101,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,    -1,    -1,    -1,    -1,    -1,   118,    -1,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
      -1,     0,    -1,    -1,   135,   136,   137,    -1,   139,   140,
     141,   142,   143,   144,    13,    14,    15,    -1,    17,    18,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    86,
      87,    -1,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    86,    87,    88,
      -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,    -1,    -1,    -1,    -1,   117,   118,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,    -1,     0,    -1,   134,   135,   136,   137,    -1,
      -1,   140,    -1,   142,   143,   144,    13,    14,    15,    -1,
      17,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    86,
      87,    88,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,    -1,    -1,    -1,    -1,   135,   136,
     137,    -1,    -1,   140,    -1,   142,   143,   144,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    18,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,   100,    -1,   102,
     103,   104,   105,   106,   107,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,   131,   132,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
       1,   144,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    15,    -1,    17,    18,    19,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    47,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,   100,
      -1,   102,   103,   104,   105,   106,   107,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,
     131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,     1,   144,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    15,    -1,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      -1,   100,    -1,   102,   103,   104,   105,   106,   107,    -1,
      -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   130,   131,   132,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,     1,   144,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    -1,    15,    -1,
      -1,    18,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      47,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,   130,   131,   132,    -1,    19,    -1,    21,
      22,    23,    24,    -1,    -1,   142,    -1,   144,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    -1,    51,
      52,    53,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    98,    -1,   100,    -1,
     102,   103,   104,   105,   106,   107,    -1,    -1,   110,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,   131,
     132,    -1,    -1,   135,    -1,    -1,    -1,    -1,    -1,    -1,
     142,     1,   144,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,    49,
      -1,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,    -1,    -1,
     110,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    -1,
     130,   131,   132,    -1,    19,    -1,    21,    22,    23,    24,
      -1,    -1,   142,    -1,   144,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,   130,   131,   132,    -1,    19,
      -1,    21,    22,    23,    24,   140,    -1,   142,    -1,   144,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,    49,
      -1,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,    -1,    -1,
     110,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    -1,
     130,   131,   132,    -1,    19,    -1,    21,    22,    23,    24,
     140,    -1,   142,    -1,   144,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   130,   131,   132,    -1,    -1,
     135,    -1,    -1,    -1,    -1,    -1,    -1,   142,     1,   144,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    15,    -1,    -1,    -1,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,   100,    -1,   102,
     103,   104,   105,   106,   107,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,   130,   131,   132,
      -1,    19,    -1,    21,    22,    23,    24,    -1,    -1,   142,
      -1,   144,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,
      98,    99,   100,    -1,   102,   103,   104,   105,   106,   107,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,   130,   131,   132,    -1,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,   144,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    -1,    -1,   100,    -1,   102,
     103,   104,   105,   106,   107,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,   130,   131,   132,
      -1,    19,    -1,    21,    22,    23,    24,    -1,    -1,   142,
      -1,   144,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    -1,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,
      -1,    -1,   100,    -1,   102,   103,   104,   105,   106,   107,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,   130,   131,   132,    -1,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,   144,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,   100,    -1,   102,
     103,   104,   105,   106,   107,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    -1,   130,   131,   132,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,   142,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      -1,   100,    -1,   102,   103,   104,   105,   106,   107,    -1,
      -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   130,   131,   132,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    80,    81,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,   131,   132,    -1,    -1,    -1,    -1,    -1,   138,
     139,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    21,
      22,    23,    24,    -1,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    98,    99,   100,    -1,
     102,   103,   104,   105,   106,   107,    -1,    -1,   110,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,   130,   131,
     132,    19,   134,    21,    22,    23,    24,   139,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,
      98,    99,   100,    -1,   102,   103,   104,   105,   106,   107,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,   130,   131,   132,    19,   134,    21,    22,    23,
      24,   139,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    92,    93,
      -1,    95,    96,    -1,    98,    99,   100,    -1,   102,   103,
     104,   105,   106,   107,    -1,    -1,   110,    -1,    -1,    -1,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   130,   131,   132,    -1,
      -1,    -1,    -1,    -1,    -1,   139,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    99,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,
     117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   130,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,   139,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    99,
     100,    -1,   102,   103,   104,   105,   106,   107,    -1,    -1,
     110,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
     130,   131,   132,    19,    -1,    21,    22,    23,    24,   139,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    98,    99,   100,    -1,   102,   103,   104,   105,
     106,   107,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   130,   131,   132,    -1,    -1,    -1,
      -1,    -1,    -1,   139,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    80,    81,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,   131,   132,    -1,    -1,    -1,    -1,    -1,   138,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    80,    81,    -1,
      -1,    84,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,   131,   132,
      -1,    -1,    -1,    -1,    -1,   138,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    80,    81,    -1,    -1,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,   131,   132,    -1,    -1,    -1,    -1,
      -1,   138,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    80,
      81,    -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
     131,   132,    -1,    -1,    -1,    -1,    -1,   138,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,    -1,    -1,   110,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    19,   130,    21,    22,    23,    24,
      -1,    -1,   137,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,    -1,    -1,   110,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    19,   130,    21,    22,    23,    24,
      -1,    -1,   137,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    99,   100,    -1,   102,   103,   104,
     105,   106,   107,    -1,    -1,   110,   111,    -1,    -1,   114,
     115,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    -1,   130,   131,   132,    19,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,   100,
      -1,   102,   103,   104,   105,   106,   107,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,   130,
     131,   132,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,   111,    -1,    -1,   114,   115,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    -1,   130,   131,   132,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,   100,    -1,   102,
     103,   104,   105,   106,   107,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,   130,   131,   132,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      -1,   100,    -1,   102,   103,   104,   105,   106,   107,    -1,
      -1,   110,   111,    -1,    -1,   114,   115,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,   130,   131,   132,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,    -1,    -1,   110,   111,    -1,    -1,   114,
     115,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,   130,   131,   132,    19,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,   100,
      -1,   102,   103,   104,   105,   106,   107,    -1,    -1,   110,
     111,    -1,    -1,   114,   115,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,   130,
     131,   132,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    99,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,   130,   131,   132,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,   100,    -1,   102,
     103,   104,   105,   106,   107,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,   130,   131,   132,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    -1,
      99,   100,    -1,   102,   103,   104,   105,   106,   107,    -1,
      -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,   130,   131,   132,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,   130,   131,   132,    19,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,   100,
      -1,   102,   103,   104,   105,   106,   107,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,   130,
     131,   132,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,   130,   131,   132,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,   100,    -1,   102,
     103,   104,   105,   106,   107,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,   130,   131,   132,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    -1,
      -1,   100,    -1,   102,   103,   104,   105,   106,   107,    -1,
      -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,   130,   131,   132,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,   130,   131,   132,    19,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    -1,    -1,   100,
      -1,   102,   103,   104,   105,   106,   107,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,   130,
     131,   132,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    -1,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,   130,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,   130,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,   130,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    -1,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,   130,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    -1,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,   130,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    -1,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,   130,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    -1,    -1,   100,    -1,   102,   103,   104,   105,   106,
     107,    -1,    -1,   110,    -1,    -1,    51,    52,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   130,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,    84,
      85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,   131,   132,    51,    52,
      -1,    -1,    55,   138,   139,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    80,    81,    -1,
      -1,    84,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,   131,   132,
      51,    52,    -1,    -1,    55,   138,   139,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    80,
      81,    -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
     131,   132,    51,    52,    -1,    -1,    55,   138,   139,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    80,    81,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,   131,   132,    51,    52,    -1,    -1,    55,   138,
     139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    80,    81,    -1,    -1,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,   131,   132,    51,    52,    -1,    -1,
      55,   138,   139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,    84,
      85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,   131,   132,    51,    52,
      -1,    -1,    55,   138,   139,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    80,    81,    -1,
      -1,    84,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,   131,   132,
      51,    52,    -1,    -1,    55,   138,   139,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    80,
      81,    -1,    -1,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
     131,   132,    51,    52,    -1,    -1,    55,   138,   139,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    80,    81,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,   131,   132,    51,    52,    -1,    -1,    55,   138,
     139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    80,    81,    -1,    -1,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,   131,   132,    51,    52,    -1,    -1,
      55,   138,   139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,    84,
      85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    86,
      87,    -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,   131,   132,    -1,    -1,
      -1,    -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   144
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   146,   147,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    19,    21,    22,    23,    24,
      30,    31,    32,    33,    34,    35,    36,    39,    45,    46,
      47,    48,    49,    51,    52,    53,    54,    55,    56,    58,
      59,    60,    63,    66,    67,    69,    70,    89,    92,    93,
      95,    96,    98,   100,   102,   103,   104,   105,   106,   107,
     110,   130,   131,   132,   148,   149,   150,   155,   157,   158,
     160,   161,   164,   165,   167,   168,   169,   171,   172,   181,
     194,   215,   234,   235,   245,   246,   250,   251,   252,   259,
     260,   261,   263,   264,   265,   266,   267,   268,   292,   307,
     150,    21,    22,    30,    31,    32,    39,    51,    55,    86,
      89,    92,   130,   173,   174,   194,   215,   265,   268,   292,
     174,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    45,    46,    47,    48,    49,
      50,    51,    52,    55,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    80,    81,    84,    85,    86,    87,    98,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     131,   132,   138,   139,   175,   179,   180,   267,   287,   195,
      89,   158,   159,   172,   215,   265,   266,   268,   159,   201,
     203,    89,   165,   172,   215,   220,   265,   268,    33,    34,
      35,    36,    48,    49,    51,    55,   102,   175,   176,   177,
     261,   142,   144,   159,   298,   303,   304,   306,    57,    98,
      99,   131,   164,   181,   182,   187,   190,   192,   290,   291,
     187,   187,   139,   188,   189,   139,   184,   188,   139,   299,
     304,   176,   151,   134,   181,   215,   181,    55,     1,    92,
     153,   154,   155,   166,   167,   307,   196,   198,   183,   192,
     290,   307,   182,   289,   290,   307,    89,   137,   171,   215,
     265,   268,   199,    53,    54,    56,    63,   106,   175,   262,
      62,    64,    65,   112,   113,   247,   248,    63,   247,    63,
     247,    63,   247,    61,   247,    58,    59,   160,   181,   181,
     298,   306,    40,    41,    42,    43,    44,    37,    38,    28,
     232,   117,   137,    92,    98,   168,   117,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      86,    87,   118,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    88,   101,   136,   143,   296,    88,   296,
     297,    26,   134,   236,    90,    90,   184,   188,   236,   158,
      51,    55,   173,    58,    59,   121,   269,    88,   136,   296,
     210,   288,   211,    88,   143,   295,   152,   153,    55,    16,
     216,   303,   117,    88,   136,   296,    90,    90,   216,   159,
     159,    55,    88,   136,   296,    25,   106,   137,   305,   298,
      20,   239,   142,   182,   182,   182,    91,   137,   191,   307,
     137,   191,   187,   299,   300,   187,   186,   187,   192,   290,
     307,   158,   300,   158,   156,   134,   153,    88,   296,    90,
     155,   166,   140,   298,   306,   300,   158,   300,   141,   137,
     302,   304,   137,   302,   135,   302,    55,   168,   169,   170,
     137,    88,   136,   296,    51,    53,    54,    55,    56,    92,
      98,    99,   124,   127,   139,   230,   272,   273,   274,   275,
     276,   277,   278,   281,   282,   283,   284,   285,    63,   247,
     249,   111,   114,   115,   254,   255,   256,   257,    62,   248,
      63,    63,    63,    61,    71,    71,   150,   159,   159,   159,
     159,   155,   158,   158,   233,    98,   160,   182,   192,   193,
     166,   137,   171,   137,   157,   160,   172,   181,   182,   193,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,    51,    52,    55,   179,
     184,   293,   294,   186,    51,    52,    55,   179,   184,   293,
      51,    55,   293,   238,   237,   160,   181,   160,   181,    97,
     162,   208,   270,   207,    51,    55,   173,   293,   186,   293,
     152,   158,   212,   213,    15,    13,   241,   307,   153,    16,
     181,    51,    55,   186,    51,    55,   153,    27,   217,   303,
     217,    51,    55,   186,    51,    55,   205,   178,   253,   254,
     239,   192,    15,   182,    98,   182,   190,   254,   290,   291,
     300,   140,   300,   137,   137,   300,   176,   148,   135,   181,
     300,   155,   197,   290,   168,   170,    51,    55,   186,    51,
      55,   117,    51,    92,    98,   221,   222,   223,   274,   272,
     200,   137,   286,   307,   182,   137,   286,    51,   137,   286,
      51,    63,   153,   258,   255,   111,   257,   181,   181,    79,
     122,   225,   226,   307,   182,   137,   300,   170,   137,   117,
      44,   299,    90,    90,   184,   188,   299,   301,    90,    90,
     184,   185,   188,   307,   185,   188,   225,   225,    44,   163,
     303,   159,   152,   301,    15,   300,   139,   271,   272,   175,
     182,   193,   242,   307,    18,   219,   307,    17,   218,   219,
      90,    90,   301,    90,    90,   219,   202,   204,   301,   159,
     176,    15,   137,   216,   182,    98,   182,   191,   290,   135,
     300,   302,   301,   223,   137,   274,   137,   300,   227,   299,
      29,   109,   231,   275,   281,   283,   285,   276,   278,   283,
     276,   135,   153,   224,   227,   276,   277,   279,   280,   283,
     285,   153,    98,   182,   170,   181,   119,   160,   181,   160,
     181,   162,   141,    90,   160,   181,   160,   181,   162,   236,
     232,   153,   153,   181,   225,   209,   303,    15,   272,   152,
     303,   214,    91,   243,   307,   153,    14,   244,   307,   159,
      15,    90,    15,   153,   153,   217,   182,   153,   182,   137,
     300,   222,   137,    98,   221,   140,   142,   153,   153,   137,
     286,   137,   286,   137,   286,   137,   286,   286,   135,   227,
     122,   137,   286,    89,   215,   137,   286,   137,   286,    15,
     182,   181,   160,   181,    15,   135,   153,   152,   300,    15,
     271,    89,   172,   215,   265,   268,   216,   153,   216,    15,
      15,   206,   219,   239,   240,   137,   222,   137,   274,    51,
     228,   229,   273,    15,   135,   276,   283,   276,   276,   122,
     280,   283,    55,    88,   276,   279,   283,   276,   135,    15,
     152,    55,    88,   136,   296,   153,   153,   153,   222,   137,
     137,   299,   286,   137,   286,   286,   286,   137,   286,   137,
     286,    51,    55,   286,   137,   286,   286,    15,    51,    55,
     186,    51,    55,   241,   218,    15,   222,   229,   276,   276,
     283,   276,   276,   301,   286,   286,   137,   286,   286,   286,
     276,   286
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   145,   147,   146,   148,   149,   149,   149,   149,   150,
     151,   150,   152,   153,   154,   154,   154,   154,   156,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     157,   157,   158,   158,   158,   158,   158,   158,   159,   160,
     160,   161,   161,   163,   162,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   165,   165,   166,   166,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     168,   168,   169,   169,   170,   170,   171,   171,   171,   171,
     171,   171,   171,   171,   172,   172,   172,   172,   172,   172,
     172,   172,   173,   173,   174,   174,   174,   175,   175,   175,
     175,   175,   176,   176,   177,   178,   177,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     182,   183,   183,   183,   183,   184,   185,   185,   186,   186,
     186,   186,   186,   187,   187,   187,   187,   187,   189,   188,
     190,   191,   191,   192,   192,   192,   192,   192,   192,   193,
     193,   193,   194,   194,   194,   194,   194,   194,   194,   194,
     195,   194,   196,   197,   194,   198,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   199,   200,   194,   194,   194,   201,   202,   194,   203,
     204,   194,   194,   194,   205,   206,   194,   207,   194,   208,
     209,   194,   210,   194,   211,   212,   194,   213,   214,   194,
     194,   194,   194,   194,   215,   216,   216,   216,   217,   217,
     218,   218,   219,   219,   220,   220,   221,   221,   222,   222,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   225,   225,   226,   226,   226,   227,
     227,   228,   228,   229,   229,   230,   230,   231,   231,   233,
     232,   234,   234,   234,   234,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   237,   236,   238,   236,   239,   240,
     240,   241,   241,   242,   242,   242,   243,   243,   244,   244,
     245,   245,   245,   245,   246,   246,   246,   246,   247,   247,
     248,   249,   248,   248,   248,   250,   250,   251,   251,   252,
     253,   253,   254,   254,   255,   255,   256,   256,   257,   258,
     257,   259,   259,   260,   260,   261,   262,   262,   262,   262,
     262,   262,   263,   263,   264,   264,   264,   264,   265,   265,
     265,   265,   265,   266,   267,   267,   267,   267,   267,   267,
     267,   268,   268,   269,   270,   269,   271,   271,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   273,   273,   273,   273,   274,   274,   275,
     275,   276,   276,   277,   278,   279,   280,   280,   281,   281,
     282,   282,   283,   283,   284,   284,   285,   286,   286,   287,
     288,   287,   289,   289,   290,   290,   291,   291,   292,   292,
     292,   293,   293,   293,   293,   294,   294,   294,   295,   295,
     296,   296,   297,   297,   298,   298,   299,   299,   300,   301,
     302,   302,   302,   303,   303,   305,   304,   306,   306,   307
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     3,     2,     1,
       0,     5,     4,     2,     1,     1,     3,     2,     0,     4,
       2,     3,     3,     3,     3,     3,     4,     1,     3,     3,
       6,     5,     5,     5,     5,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     4,     0,     5,     2,     3,     4,     5,     4,
       5,     2,     2,     2,     2,     2,     1,     3,     1,     3,
       1,     2,     3,     5,     2,     4,     2,     4,     1,     3,
       1,     3,     2,     3,     1,     2,     1,     4,     3,     3,
       3,     3,     2,     1,     1,     4,     3,     3,     3,     3,
       2,     1,     1,     1,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     3,     5,
       6,     5,     5,     5,     5,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     4,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     3,     6,     1,
       1,     1,     2,     4,     2,     3,     1,     1,     1,     1,
       2,     4,     2,     1,     2,     2,     4,     1,     0,     2,
       2,     2,     1,     1,     2,     3,     4,     4,     5,     3,
       4,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     0,     5,     0,     3,     3,     3,     2,
       3,     3,     1,     4,     3,     1,     4,     3,     2,     1,
       2,     0,     0,     5,     6,     6,     0,     0,     7,     0,
       0,     7,     5,     4,     0,     0,     9,     0,     6,     0,
       0,     8,     0,     5,     0,     0,     7,     0,     0,     9,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     5,     1,     2,     1,     1,     1,     3,     1,     3,
       1,     4,     6,     3,     5,     2,     4,     1,     3,     6,
       8,     4,     6,     4,     2,     6,     2,     4,     6,     2,
       4,     2,     4,     1,     1,     1,     3,     1,     4,     1,
       4,     1,     3,     1,     1,     4,     1,     3,     3,     0,
       5,     2,     4,     5,     5,     2,     4,     4,     3,     3,
       3,     2,     1,     4,     0,     5,     0,     5,     5,     1,
       1,     6,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     1,     2,
       1,     0,     4,     1,     2,     2,     3,     2,     3,     1,
       0,     1,     1,     2,     1,     2,     1,     2,     1,     0,
       4,     2,     3,     1,     4,     2,     1,     1,     1,     1,
       1,     2,     2,     3,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     0,     4,     3,     2,     6,     8,
       4,     6,     4,     6,     2,     4,     6,     2,     4,     2,
       4,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     2,     2,     2,     1,     3,     1,     3,
       1,     1,     2,     1,     1,     1,     2,     2,     1,     1,
       0,     4,     1,     2,     1,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     0,     1,     2,     2,
       0,     1,     1,     1,     1,     0,     3,     1,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (p, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, p); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, parser_state *p)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (p);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, parser_state *p)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, p);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, parser_state *p)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , p);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, p); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, parser_state *p)
{
  YYUSE (yyvaluep);
  YYUSE (p);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (parser_state *p)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, p);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 1176 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lstate = EXPR_BEG;
                      if (!p->locals) p->locals = cons(0,0);
                    }
#line 5096 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 1181 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->tree = new_scope(p, (yyvsp[0].nd));
                      NODE_LINENO(p->tree, (yyvsp[0].nd));
                    }
#line 5105 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 1188 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 5113 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 1194 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 5121 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 1198 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_begin(p, (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 5130 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 1203 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), newline_node((yyvsp[0].nd)));
                    }
#line 5138 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 1207 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 5146 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 1214 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = local_switch(p);
                    }
#line 5154 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 1218 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "BEGIN not supported");
                      local_resume(p, (yyvsp[-3].nd));
                      (yyval.nd) = 0;
                    }
#line 5164 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 1229 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if ((yyvsp[-2].nd)) {
                        (yyval.nd) = new_rescue(p, (yyvsp[-3].nd), (yyvsp[-2].nd), (yyvsp[-1].nd));
                        NODE_LINENO((yyval.nd), (yyvsp[-3].nd));
                      }
                      else if ((yyvsp[-1].nd)) {
                        yywarn(p, "else without rescue is useless");
                        (yyval.nd) = push((yyvsp[-3].nd), (yyvsp[-1].nd));
                      }
                      else {
                        (yyval.nd) = (yyvsp[-3].nd);
                      }
                      if ((yyvsp[0].nd)) {
                        if ((yyval.nd)) {
                          (yyval.nd) = new_ensure(p, (yyval.nd), (yyvsp[0].nd));
                        }
                        else {
                          (yyval.nd) = push((yyvsp[0].nd), new_nil(p));
                        }
                      }
                    }
#line 5190 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 1253 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 5198 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 1259 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 5206 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 1263 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_begin(p, (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 5215 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 1268 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), newline_node((yyvsp[0].nd)));
                    }
#line 5223 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 1272 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_begin(p, (yyvsp[0].nd));
                    }
#line 5231 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 1277 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {p->lstate = EXPR_FNAME;}
#line 5237 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 1278 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_alias(p, (yyvsp[-2].id), (yyvsp[0].id));
                    }
#line 5245 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 1282 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 5253 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 1286 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_if(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd), 0);
                    }
#line 5261 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 1290 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_unless(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd), 0);
                    }
#line 5269 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 1294 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_while(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd));
                    }
#line 5277 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 1298 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_until(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd));
                    }
#line 5285 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 1302 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_rescue(p, (yyvsp[-2].nd), list1(list3(0, 0, (yyvsp[0].nd))), 0);
                    }
#line 5293 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 1306 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "END not supported");
                      (yyval.nd) = new_postexe(p, (yyvsp[-1].nd));
                    }
#line 5302 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 1312 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 5310 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 1316 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, (yyvsp[-2].nd), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 5318 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 1320 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-5].nd), intern("[]",2), (yyvsp[-3].nd), '.'), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 5326 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 1324 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 5334 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 1328 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 5342 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 1332 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "constant re-assignment");
                      (yyval.nd) = 0;
                    }
#line 5351 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 1337 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, tCOLON2), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 5359 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 1341 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      backref_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 5368 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 1346 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), new_array(p, (yyvsp[0].nd)));
                    }
#line 5376 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 1350 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 5384 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1354 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-2].nd), new_array(p, (yyvsp[0].nd)));
                    }
#line 5392 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1361 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 5400 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1365 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 5408 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1373 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_and(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 5416 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1377 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_or(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 5424 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1381 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "!");
                    }
#line 5432 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1385 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "!");
                    }
#line 5440 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1392 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if (!(yyvsp[0].nd)) (yyval.nd) = new_nil(p);
                      else (yyval.nd) = (yyvsp[0].nd);
                    }
#line 5449 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1407 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_nest(p);
                    }
#line 5457 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1413 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_block(p, (yyvsp[-2].nd), (yyvsp[-1].nd));
                      local_unnest(p);
                    }
#line 5466 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1420 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_fcall(p, (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 5474 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1424 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      args_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = new_fcall(p, (yyvsp[-2].id), (yyvsp[-1].nd));
                    }
#line 5483 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1429 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 5491 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1433 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      args_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), (yyvsp[-3].num));
                   }
#line 5500 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1438 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), tCOLON2);
                    }
#line 5508 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1442 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      args_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), tCOLON2);
                    }
#line 5517 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1447 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_super(p, (yyvsp[0].nd));
                    }
#line 5525 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1451 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_yield(p, (yyvsp[0].nd));
                    }
#line 5533 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1455 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_return(p, ret_args(p, (yyvsp[0].nd)));
                    }
#line 5541 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1459 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_break(p, ret_args(p, (yyvsp[0].nd)));
                    }
#line 5549 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1463 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_next(p, ret_args(p, (yyvsp[0].nd)));
                    }
#line 5557 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1469 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 5565 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1473 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 5573 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1480 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 5581 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1486 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 5589 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1490 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1(push((yyvsp[-1].nd),(yyvsp[0].nd)));
                    }
#line 5597 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1494 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list2((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 5605 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1498 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3((yyvsp[-4].nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 5613 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1502 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list2((yyvsp[-1].nd), new_nil(p));
                    }
#line 5621 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1506 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3((yyvsp[-3].nd), new_nil(p), (yyvsp[0].nd));
                    }
#line 5629 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1510 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list2(0, (yyvsp[0].nd));
                    }
#line 5637 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1514 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3(0, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 5645 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1518 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list2(0, new_nil(p));
                    }
#line 5653 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1522 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3(0, new_nil(p), (yyvsp[0].nd));
                    }
#line 5661 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1529 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-1].nd), NULL);
                    }
#line 5669 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1535 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1((yyvsp[-1].nd));
                    }
#line 5677 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1539 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[-1].nd));
                    }
#line 5685 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1545 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 5693 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1549 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 5701 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1555 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      assignable(p, (yyvsp[0].nd));
                    }
#line 5709 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1559 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), intern("[]",2), (yyvsp[-1].nd), '.');
                    }
#line 5717 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1563 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 5725 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1567 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, tCOLON2);
                    }
#line 5733 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1571 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 5741 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1575 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "dynamic constant assignment");
                      (yyval.nd) = new_colon2(p, (yyvsp[-2].nd), (yyvsp[0].id));
                    }
#line 5751 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1581 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "dynamic constant assignment");
                      (yyval.nd) = new_colon3(p, (yyvsp[0].id));
                    }
#line 5761 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1587 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      backref_error(p, (yyvsp[0].nd));
                      (yyval.nd) = 0;
                    }
#line 5770 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1594 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      assignable(p, (yyvsp[0].nd));
                    }
#line 5778 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1598 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), intern("[]",2), (yyvsp[-1].nd), '.');
                    }
#line 5786 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1602 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 5794 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1606 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, tCOLON2);
                    }
#line 5802 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1610 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 5810 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1614 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "dynamic constant assignment");
                      (yyval.nd) = new_colon2(p, (yyvsp[-2].nd), (yyvsp[0].id));
                    }
#line 5820 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1620 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "dynamic constant assignment");
                      (yyval.nd) = new_colon3(p, (yyvsp[0].id));
                    }
#line 5830 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1626 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      backref_error(p, (yyvsp[0].nd));
                      (yyval.nd) = 0;
                    }
#line 5839 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1633 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "class/module name must be CONSTANT");
                    }
#line 5847 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1640 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons((node*)1, nsym((yyvsp[0].id)));
                    }
#line 5855 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1644 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons((node*)0, nsym((yyvsp[0].id)));
                    }
#line 5863 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1648 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons((yyvsp[-2].nd), nsym((yyvsp[0].id)));
                    }
#line 5871 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1657 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lstate = EXPR_ENDFN;
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 5880 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1662 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lstate = EXPR_ENDFN;
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 5889 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1673 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_undef(p, (yyvsp[0].id));
                    }
#line 5897 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1676 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {p->lstate = EXPR_FNAME;}
#line 5903 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1677 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-3].nd), nsym((yyvsp[0].id)));
                    }
#line 5911 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1682 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('|');   }
#line 5917 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1683 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('^');   }
#line 5923 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1684 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('&');   }
#line 5929 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1685 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("<=>",3); }
#line 5935 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1686 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("==",2);  }
#line 5941 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1687 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("===",3); }
#line 5947 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1688 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("=~",2);  }
#line 5953 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1689 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("!~",2);  }
#line 5959 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1690 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('>');   }
#line 5965 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1691 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern(">=",2);  }
#line 5971 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1692 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('<');   }
#line 5977 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1693 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("<=",2);  }
#line 5983 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1694 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("!=",2);  }
#line 5989 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1695 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("<<",2);  }
#line 5995 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1696 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern(">>",2);  }
#line 6001 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1697 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('+');   }
#line 6007 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1698 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('-');   }
#line 6013 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1699 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('*');   }
#line 6019 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1700 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('*');   }
#line 6025 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1701 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('/');   }
#line 6031 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1702 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('%');   }
#line 6037 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1703 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("**",2);  }
#line 6043 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1704 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('!');   }
#line 6049 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1705 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('~');   }
#line 6055 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1706 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("+@",2);  }
#line 6061 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1707 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("-@",2);  }
#line 6067 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1708 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("[]",2);  }
#line 6073 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1709 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern("[]=",3); }
#line 6079 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1710 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    { (yyval.id) = intern_c('`');   }
#line 6085 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1728 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6093 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1732 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-4].nd), new_rescue(p, (yyvsp[-2].nd), list1(list3(0, 0, (yyvsp[0].nd))), 0));
                    }
#line 6101 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1736 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, (yyvsp[-2].nd), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6109 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1740 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, (yyvsp[-4].nd), (yyvsp[-3].id), new_rescue(p, (yyvsp[-2].nd), list1(list3(0, 0, (yyvsp[0].nd))), 0));
                    }
#line 6117 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1744 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-5].nd), intern("[]",2), (yyvsp[-3].nd), '.'), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6125 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1748 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6133 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1752 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6141 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1756 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, tCOLON2), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6149 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1760 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "constant re-assignment");
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 6158 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1765 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "constant re-assignment");
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 6167 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1770 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      backref_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 6176 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1775 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_dot2(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6184 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1779 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_dot3(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6192 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1783 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "+", (yyvsp[0].nd));
                    }
#line 6200 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1787 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "-", (yyvsp[0].nd));
                    }
#line 6208 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1791 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "*", (yyvsp[0].nd));
                    }
#line 6216 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1795 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "/", (yyvsp[0].nd));
                    }
#line 6224 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1799 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "%", (yyvsp[0].nd));
                    }
#line 6232 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1803 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "**", (yyvsp[0].nd));
                    }
#line 6240 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1807 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, call_bin_op(p, (yyvsp[-2].nd), "**", (yyvsp[0].nd)), "-@");
                    }
#line 6248 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1811 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, call_bin_op(p, (yyvsp[-2].nd), "**", (yyvsp[0].nd)), "-@");
                    }
#line 6256 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1815 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, (yyvsp[0].nd), "+@");
                    }
#line 6264 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1819 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, (yyvsp[0].nd), "-@");
                    }
#line 6272 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1823 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "|", (yyvsp[0].nd));
                    }
#line 6280 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1827 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "^", (yyvsp[0].nd));
                    }
#line 6288 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1831 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "&", (yyvsp[0].nd));
                    }
#line 6296 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1835 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<=>", (yyvsp[0].nd));
                    }
#line 6304 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1839 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), ">", (yyvsp[0].nd));
                    }
#line 6312 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1843 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), ">=", (yyvsp[0].nd));
                    }
#line 6320 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1847 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<", (yyvsp[0].nd));
                    }
#line 6328 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1851 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<=", (yyvsp[0].nd));
                    }
#line 6336 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1855 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "==", (yyvsp[0].nd));
                    }
#line 6344 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1859 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "===", (yyvsp[0].nd));
                    }
#line 6352 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1863 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "!=", (yyvsp[0].nd));
                    }
#line 6360 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1867 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "=~", (yyvsp[0].nd));
                    }
#line 6368 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1871 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "!~", (yyvsp[0].nd));
                    }
#line 6376 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1875 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "!");
                    }
#line 6384 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1879 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "~");
                    }
#line 6392 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1883 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<<", (yyvsp[0].nd));
                    }
#line 6400 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1887 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), ">>", (yyvsp[0].nd));
                    }
#line 6408 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1891 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_and(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6416 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1895 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_or(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6424 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1899 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-5].nd)), (yyvsp[-3].nd), (yyvsp[0].nd));
                    }
#line 6432 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1903 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 6440 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1909 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
                    }
#line 6449 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1917 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 6458 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1922 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-3].nd), new_hash(p, (yyvsp[-1].nd)));
                    }
#line 6466 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1926 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(new_hash(p, (yyvsp[-1].nd)), 0);
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 6475 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1933 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 6483 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1945 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons((yyvsp[-1].nd),0);
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 6492 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1950 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(push((yyvsp[-3].nd), new_hash(p, (yyvsp[-1].nd))), 0);
                      NODE_LINENO((yyval.nd), (yyvsp[-3].nd));
                    }
#line 6501 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1955 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(list1(new_hash(p, (yyvsp[-1].nd))), 0);
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 6510 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1962 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(list1((yyvsp[0].nd)), 0);
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 6519 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1967 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons((yyvsp[-1].nd), (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 6528 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1972 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(list1(new_hash(p, (yyvsp[-1].nd))), (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 6537 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1977 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(push((yyvsp[-3].nd), new_hash(p, (yyvsp[-1].nd))), (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-3].nd));
                    }
#line 6546 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1982 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(0, (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 6555 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1988 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.stack) = p->cmdarg_stack;
                      CMDARG_PUSH(1);
                    }
#line 6564 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1993 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->cmdarg_stack = (yyvsp[-1].stack);
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 6573 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 2000 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_block_arg(p, (yyvsp[0].nd));
                    }
#line 6581 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 2006 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 6589 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 2010 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = 0;
                    }
#line 6597 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 2016 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons((yyvsp[0].nd), 0);
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 6606 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 2021 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(new_splat(p, (yyvsp[0].nd)), 0);
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 6615 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 2026 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6623 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 2030 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-3].nd), new_splat(p, (yyvsp[0].nd)));
                    }
#line 6631 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 2034 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-3].nd), (yyvsp[0].nd));
                    }
#line 6639 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 2038 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-4].nd), new_splat(p, (yyvsp[0].nd)));
                    }
#line 6647 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 2044 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6655 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 2048 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-3].nd), new_splat(p, (yyvsp[0].nd)));
                    }
#line 6663 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 2052 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1(new_splat(p, (yyvsp[0].nd)));
                    }
#line 6671 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 2065 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_fcall(p, (yyvsp[0].id), 0);
                    }
#line 6679 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 2069 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 6688 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 2075 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->cmdarg_stack = (yyvsp[-2].stack);
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 6697 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 2080 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 6706 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 2084 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {p->lstate = EXPR_ENDARG;}
#line 6712 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 2085 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->cmdarg_stack = (yyvsp[-3].stack);
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 6721 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 2089 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {p->lstate = EXPR_ENDARG;}
#line 6727 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 2090 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = 0;
                    }
#line 6735 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 2094 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 6743 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 2098 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_colon2(p, (yyvsp[-2].nd), (yyvsp[0].id));
                    }
#line 6751 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 2102 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_colon3(p, (yyvsp[0].id));
                    }
#line 6759 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 2106 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_array(p, (yyvsp[-1].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 6768 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 2111 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_hash(p, (yyvsp[-1].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 6777 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 2116 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_return(p, 0);
                    }
#line 6785 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 2120 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_yield(p, (yyvsp[-1].nd));
                    }
#line 6793 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 2124 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_yield(p, 0);
                    }
#line 6801 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 2128 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_yield(p, 0);
                    }
#line 6809 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 2132 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[-1].nd)), "!");
                    }
#line 6817 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 2136 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = call_uni_op(p, new_nil(p), "!");
                    }
#line 6825 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 2140 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_fcall(p, (yyvsp[-1].id), cons(0, (yyvsp[0].nd)));
                    }
#line 6833 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 2145 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      call_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 6842 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 2150 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_nest(p);
                      (yyval.num) = p->lpar_beg;
                      p->lpar_beg = ++p->paren_nest;
                    }
#line 6852 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 2156 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 6861 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 2161 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lpar_beg = (yyvsp[-3].num);
                      (yyval.nd) = new_lambda(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                      local_unnest(p);
                      p->cmdarg_stack = (yyvsp[-1].stack);
                      CMDARG_LEXPOP();
                    }
#line 6873 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 2172 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-4].nd)), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-5].num));
                    }
#line 6882 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 2180 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_unless(p, cond((yyvsp[-4].nd)), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-5].num));
                    }
#line 6891 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 2184 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {COND_PUSH(1);}
#line 6897 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 2184 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {COND_POP();}
#line 6903 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 2187 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_while(p, cond((yyvsp[-4].nd)), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-6].num));
                    }
#line 6912 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 2191 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {COND_PUSH(1);}
#line 6918 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 2191 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {COND_POP();}
#line 6924 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 2194 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_until(p, cond((yyvsp[-4].nd)), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-6].num));
                    }
#line 6933 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2201 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_case(p, (yyvsp[-3].nd), (yyvsp[-1].nd));
                    }
#line 6941 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2205 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_case(p, 0, (yyvsp[-1].nd));
                    }
#line 6949 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2209 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {COND_PUSH(1);}
#line 6955 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2211 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {COND_POP();}
#line 6961 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2214 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_for(p, (yyvsp[-7].nd), (yyvsp[-4].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-8].num));
                    }
#line 6970 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2220 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "class definition in method body");
                      (yyval.nd) = local_switch(p);
                    }
#line 6980 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 2227 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_class(p, (yyvsp[-4].nd), (yyvsp[-3].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-5].num));
                      local_resume(p, (yyvsp[-2].nd));
                    }
#line 6990 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2234 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.num) = p->in_def;
                      p->in_def = 0;
                    }
#line 6999 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2239 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(local_switch(p), nint(p->in_single));
                      p->in_single = 0;
                    }
#line 7008 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 2245 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_sclass(p, (yyvsp[-5].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-7].num));
                      local_resume(p, (yyvsp[-2].nd)->car);
                      p->in_def = (yyvsp[-4].num);
                      p->in_single = intn((yyvsp[-2].nd)->cdr);
                    }
#line 7020 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 2254 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "module definition in method body");
                      (yyval.nd) = local_switch(p);
                    }
#line 7030 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 2261 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_module(p, (yyvsp[-3].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-4].num));
                      local_resume(p, (yyvsp[-2].nd));
                    }
#line 7040 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 2267 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 7049 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 2271 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->in_def++;
                      (yyval.nd) = local_switch(p);
                    }
#line 7058 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2278 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_def(p, (yyvsp[-5].id), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-6].num));
                      local_resume(p, (yyvsp[-3].nd));
                      p->in_def--;
                      p->cmdarg_stack = (yyvsp[-4].stack);
                    }
#line 7070 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2286 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lstate = EXPR_FNAME;
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 7080 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 2292 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->in_single++;
                      p->lstate = EXPR_ENDFN; /* force for args */
                      (yyval.nd) = local_switch(p);
                    }
#line 7090 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 2300 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_sdef(p, (yyvsp[-7].nd), (yyvsp[-4].id), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-8].num));
                      local_resume(p, (yyvsp[-3].nd));
                      p->in_single--;
                      p->cmdarg_stack = (yyvsp[-5].stack);
                    }
#line 7102 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2308 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_break(p, 0);
                    }
#line 7110 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2312 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_next(p, 0);
                    }
#line 7118 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2316 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_redo(p);
                    }
#line 7126 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2320 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_retry(p);
                    }
#line 7134 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2326 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
                    }
#line 7143 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2345 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-3].nd)), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 7151 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2352 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7159 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2358 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1(list1((yyvsp[0].nd)));
                    }
#line 7167 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2365 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_arg(p, (yyvsp[0].id));
                    }
#line 7175 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2369 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-1].nd), 0);
                    }
#line 7183 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2375 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 7191 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2379 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7199 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2385 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3((yyvsp[0].nd),0,0);
                    }
#line 7207 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2389 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3((yyvsp[-3].nd), new_arg(p, (yyvsp[0].id)), 0);
                    }
#line 7215 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2393 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3((yyvsp[-5].nd), new_arg(p, (yyvsp[-2].id)), (yyvsp[0].nd));
                    }
#line 7223 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2397 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3((yyvsp[-2].nd), (node*)-1, 0);
                    }
#line 7231 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2401 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3((yyvsp[-4].nd), (node*)-1, (yyvsp[0].nd));
                    }
#line 7239 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2405 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3(0, new_arg(p, (yyvsp[0].id)), 0);
                    }
#line 7247 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2409 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3(0, new_arg(p, (yyvsp[-2].id)), (yyvsp[0].nd));
                    }
#line 7255 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2413 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3(0, (node*)-1, 0);
                    }
#line 7263 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 2417 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list3(0, (node*)-1, (yyvsp[0].nd));
                    }
#line 7271 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2423 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].id));
                    }
#line 7279 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 2427 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-7].nd), (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 7287 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2431 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), (yyvsp[-1].nd), 0, 0, (yyvsp[0].id));
                    }
#line 7295 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 2435 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 7303 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2439 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), 0, (yyvsp[-1].id), 0, (yyvsp[0].id));
                    }
#line 7311 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 2443 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-1].nd), 0, 1, 0, 0);
                    }
#line 7319 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2447 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 7327 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 2451 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-1].nd), 0, 0, 0, (yyvsp[0].id));
                    }
#line 7335 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2455 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].id));
                    }
#line 7343 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 2459 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 7351 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2463 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-1].nd), 0, 0, (yyvsp[0].id));
                    }
#line 7359 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 2467 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 7367 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 2471 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-1].id), 0, (yyvsp[0].id));
                    }
#line 7375 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2475 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 7383 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2479 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, 0, 0, 0, (yyvsp[0].id));
                    }
#line 7391 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2486 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->cmd_start = TRUE;
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7400 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2493 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = 0;
                    }
#line 7408 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2497 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = 0;
                    }
#line 7416 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2501 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 7424 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2508 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = 0;
                    }
#line 7432 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 2512 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = 0;
                    }
#line 7440 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2522 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_add_f(p, (yyvsp[0].id));
                      new_bv(p, (yyvsp[0].id));
                    }
#line 7449 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2530 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 7457 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2534 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7465 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2540 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 7473 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2544 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 7481 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2550 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_nest(p);
                    }
#line 7489 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2556 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_block(p,(yyvsp[-2].nd),(yyvsp[-1].nd));
                      local_unnest(p);
                    }
#line 7498 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2563 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if ((yyvsp[-1].nd)->car == (node*)NODE_YIELD) {
                        yyerror(p, "block given to yield");
                      }
                      else {
                        call_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      }
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 7512 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2573 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 7520 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2577 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), (yyvsp[-3].num));
                      call_with_block(p, (yyval.nd), (yyvsp[0].nd));
                    }
#line 7529 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2582 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), (yyvsp[-3].num));
                      call_with_block(p, (yyval.nd), (yyvsp[0].nd));
                    }
#line 7538 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2589 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_fcall(p, (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7546 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 2593 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 7554 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2597 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), tCOLON2);
                    }
#line 7562 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2601 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, tCOLON2);
                    }
#line 7570 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2605 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), intern("call",4), (yyvsp[0].nd), (yyvsp[-1].num));
                    }
#line 7578 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2609 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), intern("call",4), (yyvsp[0].nd), tCOLON2);
                    }
#line 7586 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2613 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_super(p, (yyvsp[0].nd));
                    }
#line 7594 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2617 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_zsuper(p);
                    }
#line 7602 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2621 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), intern("[]",2), (yyvsp[-1].nd), '.');
                    }
#line 7610 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2627 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_nest(p);
                      (yyval.num) = p->lineno;
                    }
#line 7619 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2633 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_block(p,(yyvsp[-2].nd),(yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-3].num));
                      local_unnest(p);
                    }
#line 7629 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2639 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_nest(p);
                      (yyval.num) = p->lineno;
                    }
#line 7638 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2645 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_block(p,(yyvsp[-2].nd),(yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-3].num));
                      local_unnest(p);
                    }
#line 7648 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2655 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(cons((yyvsp[-3].nd), (yyvsp[-1].nd)), (yyvsp[0].nd));
                    }
#line 7656 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2661 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if ((yyvsp[0].nd)) {
                        (yyval.nd) = cons(cons(0, (yyvsp[0].nd)), 0);
                      }
                      else {
                        (yyval.nd) = 0;
                      }
                    }
#line 7669 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2675 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1(list3((yyvsp[-4].nd), (yyvsp[-3].nd), (yyvsp[-1].nd)));
                      if ((yyvsp[0].nd)) (yyval.nd) = append((yyval.nd), (yyvsp[0].nd));
                    }
#line 7678 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2683 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                        (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 7686 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 406:
#line 2691 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7694 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2698 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7702 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2713 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7710 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2717 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_dstr(p, push((yyvsp[-1].nd), (yyvsp[0].nd)));
                    }
#line 7718 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2724 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = append((yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 7726 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2730 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 7734 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2734 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = p->lex_strterm;
                      p->lex_strterm = NULL;
                    }
#line 7743 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2740 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lex_strterm = (yyvsp[-2].nd);
                      (yyval.nd) = list2((yyvsp[-3].nd), (yyvsp[-1].nd));
                    }
#line 7752 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2745 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1(new_literal_delim(p));
                    }
#line 7760 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2749 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1(new_literal_delim(p));
                    }
#line 7768 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2755 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                        (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7776 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2759 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_dxstr(p, push((yyvsp[-1].nd), (yyvsp[0].nd)));
                    }
#line 7784 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2765 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                        (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7792 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2769 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_dregx(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 7800 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2786 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      parser_heredoc_info * inf = parsing_heredoc_inf(p);
                      inf->doc = push(inf->doc, new_str(p, "", 0));
                      heredoc_end(p);
                    }
#line 7810 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2792 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      heredoc_end(p);
                    }
#line 7818 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2802 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      parser_heredoc_info * inf = parsing_heredoc_inf(p);
                      inf->doc = push(inf->doc, (yyvsp[0].nd));
                      heredoc_treat_nextline(p);
                    }
#line 7828 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2808 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = p->lex_strterm;
                      p->lex_strterm = NULL;
                    }
#line 7837 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2814 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      parser_heredoc_info * inf = parsing_heredoc_inf(p);
                      p->lex_strterm = (yyvsp[-2].nd);
                      inf->doc = push(push(inf->doc, (yyvsp[-3].nd)), (yyvsp[-1].nd));
                    }
#line 7847 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2822 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_words(p, list1((yyvsp[0].nd)));
                    }
#line 7855 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2826 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_words(p, push((yyvsp[-1].nd), (yyvsp[0].nd)));
                    }
#line 7863 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2833 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_sym(p, (yyvsp[0].id));
                    }
#line 7871 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2837 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lstate = EXPR_END;
                      (yyval.nd) = new_dsym(p, push((yyvsp[-1].nd), (yyvsp[0].nd)));
                    }
#line 7880 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2844 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lstate = EXPR_END;
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 7889 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2855 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.id) = new_strsym(p, (yyvsp[0].nd));
                    }
#line 7897 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2859 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.id) = new_strsym(p, (yyvsp[0].nd));
                    }
#line 7905 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2865 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_symbols(p, list1((yyvsp[0].nd)));
                    }
#line 7913 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2869 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_symbols(p, push((yyvsp[-1].nd), (yyvsp[0].nd)));
                    }
#line 7921 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2877 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = negate_lit(p, (yyvsp[0].nd));
                    }
#line 7929 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2881 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = negate_lit(p, (yyvsp[0].nd));
                    }
#line 7937 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2887 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_lvar(p, (yyvsp[0].id));
                    }
#line 7945 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2891 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_ivar(p, (yyvsp[0].id));
                    }
#line 7953 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 460:
#line 2895 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_gvar(p, (yyvsp[0].id));
                    }
#line 7961 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2899 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_cvar(p, (yyvsp[0].id));
                    }
#line 7969 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2903 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_const(p, (yyvsp[0].id));
                    }
#line 7977 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 463:
#line 2909 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      assignable(p, (yyvsp[0].nd));
                    }
#line 7985 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2915 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = var_reference(p, (yyvsp[0].nd));
                    }
#line 7993 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2919 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_nil(p);
                    }
#line 8001 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2923 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_self(p);
                    }
#line 8009 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2927 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_true(p);
                    }
#line 8017 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2931 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_false(p);
                    }
#line 8025 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2935 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if (!p->filename) {
                        p->filename = "(null)";
                      }
                      (yyval.nd) = new_str(p, p->filename, strlen(p->filename));
                    }
#line 8036 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2942 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      char buf[16];

                      snprintf(buf, sizeof(buf), "%d", p->lineno);
                      (yyval.nd) = new_int(p, buf, 10);
                    }
#line 8047 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2955 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = 0;
                    }
#line 8055 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2959 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lstate = EXPR_BEG;
                      p->cmd_start = TRUE;
                    }
#line 8064 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2964 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8072 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2975 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                      p->lstate = EXPR_BEG;
                      p->cmd_start = TRUE;
                    }
#line 8082 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2981 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8090 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2987 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].id));
                    }
#line 8098 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2991 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-7].nd), (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 8106 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2995 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), (yyvsp[-1].nd), 0, 0, (yyvsp[0].id));
                    }
#line 8114 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2999 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 8122 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 482:
#line 3003 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), 0, (yyvsp[-1].id), 0, (yyvsp[0].id));
                    }
#line 8130 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 483:
#line 3007 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 8138 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 484:
#line 3011 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, (yyvsp[-1].nd), 0, 0, 0, (yyvsp[0].id));
                    }
#line 8146 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 485:
#line 3015 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].id));
                    }
#line 8154 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 486:
#line 3019 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 8162 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 487:
#line 3023 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-1].nd), 0, 0, (yyvsp[0].id));
                    }
#line 8170 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 488:
#line 3027 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 8178 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 489:
#line 3031 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-1].id), 0, (yyvsp[0].id));
                    }
#line 8186 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 490:
#line 3035 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 8194 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 491:
#line 3039 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_args(p, 0, 0, 0, 0, (yyvsp[0].id));
                    }
#line 8202 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 492:
#line 3043 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_add_f(p, 0);
                      (yyval.nd) = new_args(p, 0, 0, 0, 0, 0);
                    }
#line 8211 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 493:
#line 3050 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "formal argument cannot be a constant");
                      (yyval.nd) = 0;
                    }
#line 8220 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 494:
#line 3055 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "formal argument cannot be an instance variable");
                      (yyval.nd) = 0;
                    }
#line 8229 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 495:
#line 3060 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "formal argument cannot be a global variable");
                      (yyval.nd) = 0;
                    }
#line 8238 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 496:
#line 3065 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      yyerror(p, "formal argument cannot be a class variable");
                      (yyval.nd) = 0;
                    }
#line 8247 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 497:
#line 3072 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.id) = 0;
                    }
#line 8255 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 498:
#line 3076 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_add_f(p, (yyvsp[0].id));
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 8264 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 499:
#line 3083 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_arg(p, (yyvsp[0].id));
                    }
#line 8272 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 500:
#line 3087 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-1].nd), 0);
                    }
#line 8280 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 501:
#line 3093 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 8288 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 502:
#line 3097 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8296 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 503:
#line 3103 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_add_f(p, (yyvsp[-1].id));
                      (yyval.id) = (yyvsp[-1].id);
                    }
#line 8305 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 504:
#line 3110 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(nsym((yyvsp[-1].id)), (yyvsp[0].nd));
                    }
#line 8313 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 505:
#line 3116 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(nsym((yyvsp[-1].id)), (yyvsp[0].nd));
                    }
#line 8321 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 506:
#line 3122 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 8329 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 507:
#line 3126 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8337 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 508:
#line 3132 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 8345 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 509:
#line 3136 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8353 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 512:
#line 3146 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_add_f(p, (yyvsp[0].id));
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 8362 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 513:
#line 3151 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_add_f(p, 0);
                      (yyval.id) = -1;
                    }
#line 8371 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 516:
#line 3162 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_add_f(p, (yyvsp[0].id));
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 8380 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 517:
#line 3169 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 8388 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 518:
#line 3173 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      local_add_f(p, 0);
                      (yyval.id) = 0;
                    }
#line 8397 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 519:
#line 3180 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[0].nd);
                      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
                    }
#line 8406 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 520:
#line 3184 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {p->lstate = EXPR_BEG;}
#line 8412 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 521:
#line 3185 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      if ((yyvsp[-1].nd) == 0) {
                        yyerror(p, "can't define singleton method for ().");
                      }
                      else {
                        switch ((enum node_type)intn((yyvsp[-1].nd)->car)) {
                        case NODE_STR:
                        case NODE_DSTR:
                        case NODE_XSTR:
                        case NODE_DXSTR:
                        case NODE_DREGX:
                        case NODE_MATCH:
                        case NODE_FLOAT:
                        case NODE_ARRAY:
                        case NODE_HEREDOC:
                          yyerror(p, "can't define singleton method for literals");
                        default:
                          break;
                        }
                      }
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8439 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 523:
#line 3211 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8447 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 524:
#line 3217 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 8456 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 525:
#line 3222 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8464 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 526:
#line 3228 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8472 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 527:
#line 3232 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = cons(new_sym(p, (yyvsp[-1].id)), (yyvsp[0].nd));
                    }
#line 8480 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 540:
#line 3258 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.num) = '.';
                    }
#line 8488 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 541:
#line 3262 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.num) = 0;
                    }
#line 8496 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 543:
#line 3269 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.num) = tCOLON2;
                    }
#line 8504 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 553:
#line 3293 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {yyerrok;}
#line 8510 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 555:
#line 3298 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      p->lineno++;
                      p->column = 0;
                    }
#line 8519 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3305 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {yyerrok;}
#line 8525 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3309 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1646  */
    {
                      (yyval.nd) = 0;
                    }
#line 8533 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
    break;


#line 8537 "/Users/gen/Programs/mruby/build/host/mrbgems/mruby-compiler/core/y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (p, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (p, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, p);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, p);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (p, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, p);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, p);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 3313 "/Users/gen/Programs/mruby/mrbgems/mruby-compiler/core/parse.y" /* yacc.c:1906  */

#define yylval  (*((YYSTYPE*)(p->ylval)))

static void
yyerror(parser_state *p, const char *s)
{
  char* c;
  int n;

  if (! p->capture_errors) {
#ifndef MRB_DISABLE_STDIO
    if (p->filename) {
      fprintf(stderr, "%s:%d:%d: %s\n", p->filename, p->lineno, p->column, s);
    }
    else {
      fprintf(stderr, "line %d:%d: %s\n", p->lineno, p->column, s);
    }
#endif
  }
  else if (p->nerr < sizeof(p->error_buffer) / sizeof(p->error_buffer[0])) {
    n = strlen(s);
    c = (char *)parser_palloc(p, n + 1);
    memcpy(c, s, n + 1);
    p->error_buffer[p->nerr].message = c;
    p->error_buffer[p->nerr].lineno = p->lineno;
    p->error_buffer[p->nerr].column = p->column;
  }
  p->nerr++;
}

static void
yyerror_i(parser_state *p, const char *fmt, int i)
{
  char buf[256];

  snprintf(buf, sizeof(buf), fmt, i);
  yyerror(p, buf);
}

static void
yywarn(parser_state *p, const char *s)
{
  char* c;
  int n;

  if (! p->capture_errors) {
#ifndef MRB_DISABLE_STDIO
    if (p->filename) {
      fprintf(stderr, "%s:%d:%d: %s\n", p->filename, p->lineno, p->column, s);
    }
    else {
      fprintf(stderr, "line %d:%d: %s\n", p->lineno, p->column, s);
    }
#endif
  }
  else if (p->nwarn < sizeof(p->warn_buffer) / sizeof(p->warn_buffer[0])) {
    n = strlen(s);
    c = (char *)parser_palloc(p, n + 1);
    memcpy(c, s, n + 1);
    p->warn_buffer[p->nwarn].message = c;
    p->warn_buffer[p->nwarn].lineno = p->lineno;
    p->warn_buffer[p->nwarn].column = p->column;
  }
  p->nwarn++;
}

static void
yywarning(parser_state *p, const char *s)
{
  yywarn(p, s);
}

static void
yywarning_s(parser_state *p, const char *fmt, const char *s)
{
  char buf[256];

  snprintf(buf, sizeof(buf), fmt, s);
  yywarning(p, buf);
}

static void
backref_error(parser_state *p, node *n)
{
  int c;

  c = (int)(intptr_t)n->car;

  if (c == NODE_NTH_REF) {
    yyerror_i(p, "can't set variable $%d", (int)(intptr_t)n->cdr);
  }
  else if (c == NODE_BACK_REF) {
    yyerror_i(p, "can't set variable $%c", (int)(intptr_t)n->cdr);
  }
  else {
    mrb_bug(p->mrb, "Internal error in backref_error() : n=>car == %S", mrb_fixnum_value(c));
  }
}

static void pushback(parser_state *p, int c);
static mrb_bool peeks(parser_state *p, const char *s);
static mrb_bool skips(parser_state *p, const char *s);

static inline int
nextc(parser_state *p)
{
  int c;

  if (p->pb) {
    node *tmp;

    c = (int)(intptr_t)p->pb->car;
    tmp = p->pb;
    p->pb = p->pb->cdr;
    cons_free(tmp);
  }
  else {
#ifndef MRB_DISABLE_STDIO
    if (p->f) {
      if (feof(p->f)) goto eof;
      c = fgetc(p->f);
      if (c == EOF) goto eof;
    }
    else
#endif
      if (!p->s || p->s >= p->send) {
        goto eof;
      }
      else {
        c = (unsigned char)*p->s++;
      }
  }
  if (c >= 0) {
    p->column++;
  }
  if (c == '\r') {
    c = nextc(p);
    if (c != '\n') {
      pushback(p, c);
      return '\r';
    }
    return c;
  }
  return c;

  eof:
  if (!p->cxt) return -1;
  else {
    if (p->cxt->partial_hook(p) < 0)
      return -1;                /* end of program(s) */
    return -2;                  /* end of a file in the program files */
  }
}

static void
pushback(parser_state *p, int c)
{
  if (c >= 0) {
    p->column--;
  }
  p->pb = cons((node*)(intptr_t)c, p->pb);
}

static void
skip(parser_state *p, char term)
{
  int c;

  for (;;) {
    c = nextc(p);
    if (c < 0) break;
    if (c == term) break;
  }
}

static int
peekc_n(parser_state *p, int n)
{
  node *list = 0;
  int c0;

  do {
    c0 = nextc(p);
    if (c0 == -1) return c0;    /* do not skip partial EOF */
    if (c0 >= 0) --p->column;
    list = push(list, (node*)(intptr_t)c0);
  } while(n--);
  if (p->pb) {
    p->pb = append((node*)list, p->pb);
  }
  else {
    p->pb = list;
  }
  return c0;
}

static mrb_bool
peek_n(parser_state *p, int c, int n)
{
  return peekc_n(p, n) == c && c >= 0;
}
#define peek(p,c) peek_n((p), (c), 0)

static mrb_bool
peeks(parser_state *p, const char *s)
{
  int len = strlen(s);

#ifndef MRB_DISABLE_STDIO
  if (p->f) {
    int n = 0;
    while (*s) {
      if (!peek_n(p, *s++, n++)) return FALSE;
    }
    return TRUE;
  }
  else
#endif
    if (p->s && p->s + len <= p->send) {
      if (memcmp(p->s, s, len) == 0) return TRUE;
    }
  return FALSE;
}

static mrb_bool
skips(parser_state *p, const char *s)
{
  int c;

  for (;;) {
    /* skip until first char */
    for (;;) {
      c = nextc(p);
      if (c < 0) return c;
      if (c == '\n') {
        p->lineno++;
        p->column = 0;
      }
      if (c == *s) break;
    }
    s++;
    if (peeks(p, s)) {
      int len = strlen(s);

      while (len--) {
        if (nextc(p) == '\n') {
          p->lineno++;
          p->column = 0;
        }
      }
      return TRUE;
    }
    else{
      s--;
    }
  }
  return FALSE;
}


static int
newtok(parser_state *p)
{
  p->bidx = 0;
  return p->column - 1;
}

static void
tokadd(parser_state *p, int32_t c)
{
  char utf8[4];
  unsigned len;

  /* mrb_assert(-0x10FFFF <= c && c <= 0xFF); */
  if (c >= 0) {
    /* Single byte from source or non-Unicode escape */
    utf8[0] = (char)c;
    len = 1;
  }
  else {
    /* Unicode character */
    c = -c;
    if (c < 0x80) {
      utf8[0] = (char)c;
      len = 1;
    }
    else if (c < 0x800) {
      utf8[0] = (char)(0xC0 | (c >> 6));
      utf8[1] = (char)(0x80 | (c & 0x3F));
      len = 2;
    }
    else if (c < 0x10000) {
      utf8[0] = (char)(0xE0 |  (c >> 12)        );
      utf8[1] = (char)(0x80 | ((c >>  6) & 0x3F));
      utf8[2] = (char)(0x80 | ( c        & 0x3F));
      len = 3;
    }
    else {
      utf8[0] = (char)(0xF0 |  (c >> 18)        );
      utf8[1] = (char)(0x80 | ((c >> 12) & 0x3F));
      utf8[2] = (char)(0x80 | ((c >>  6) & 0x3F));
      utf8[3] = (char)(0x80 | ( c        & 0x3F));
      len = 4;
    }
  }
  if (p->bidx+len <= MRB_PARSER_BUF_SIZE) {
    unsigned i;
    for (i = 0; i < len; i++) {
      p->buf[p->bidx++] = utf8[i];
    }
  }
}

static int
toklast(parser_state *p)
{
  return p->buf[p->bidx-1];
}

static void
tokfix(parser_state *p)
{
  int i = p->bidx, imax = MRB_PARSER_BUF_SIZE - 1;

  if (i > imax) {
    i = imax;
    yyerror(p, "string too long (truncated)");
  }
  p->buf[i] = '\0';
}

static const char*
tok(parser_state *p)
{
  return p->buf;
}

static int
toklen(parser_state *p)
{
  return p->bidx;
}

#define IS_ARG() (p->lstate == EXPR_ARG || p->lstate == EXPR_CMDARG)
#define IS_END() (p->lstate == EXPR_END || p->lstate == EXPR_ENDARG || p->lstate == EXPR_ENDFN)
#define IS_BEG() (p->lstate == EXPR_BEG || p->lstate == EXPR_MID || p->lstate == EXPR_VALUE || p->lstate == EXPR_CLASS)
#define IS_SPCARG(c) (IS_ARG() && space_seen && !ISSPACE(c))
#define IS_LABEL_POSSIBLE() ((p->lstate == EXPR_BEG && !cmd_state) || IS_ARG())
#define IS_LABEL_SUFFIX(n) (peek_n(p, ':',(n)) && !peek_n(p, ':', (n)+1))

static int
scan_oct(const int *start, int len, int *retlen)
{
  const int *s = start;
  int retval = 0;

  /* mrb_assert(len <= 3) */
  while (len-- && *s >= '0' && *s <= '7') {
    retval <<= 3;
    retval |= *s++ - '0';
  }
  *retlen = s - start;

  return retval;
}

static int32_t
scan_hex(const int *start, int len, int *retlen)
{
  static const char hexdigit[] = "0123456789abcdef0123456789ABCDEF";
  const int *s = start;
  int32_t retval = 0;
  char *tmp;

  /* mrb_assert(len <= 8) */
  while (len-- && *s && (tmp = (char*)strchr(hexdigit, *s))) {
    retval <<= 4;
    retval |= (tmp - hexdigit) & 15;
    s++;
  }
  *retlen = s - start;

  return retval;
}

/* Return negative to indicate Unicode code point */
static int32_t
read_escape(parser_state *p)
{
  int32_t c;

  switch (c = nextc(p)) {
  case '\\':/* Backslash */
    return c;

  case 'n':/* newline */
    return '\n';

  case 't':/* horizontal tab */
    return '\t';

  case 'r':/* carriage-return */
    return '\r';

  case 'f':/* form-feed */
    return '\f';

  case 'v':/* vertical tab */
    return '\13';

  case 'a':/* alarm(bell) */
    return '\007';

  case 'e':/* escape */
    return 033;

  case '0': case '1': case '2': case '3': /* octal constant */
  case '4': case '5': case '6': case '7':
  {
    int buf[3];
    int i;

    buf[0] = c;
    for (i=1; i<3; i++) {
      buf[i] = nextc(p);
      if (buf[i] < 0) goto eof;
      if (buf[i] < '0' || '7' < buf[i]) {
        pushback(p, buf[i]);
        break;
      }
    }
    c = scan_oct(buf, i, &i);
  }
  return c;

  case 'x':     /* hex constant */
  {
    int buf[2];
    int i;

    for (i=0; i<2; i++) {
      buf[i] = nextc(p);
      if (buf[i] < 0) goto eof;
      if (!ISXDIGIT(buf[i])) {
        pushback(p, buf[i]);
        break;
      }
    }
    c = scan_hex(buf, i, &i);
    if (i == 0) {
      yyerror(p, "Invalid escape character syntax");
      return 0;
    }
  }
  return c;

  case 'u':     /* Unicode */
  {
    int buf[9];
    int i;

    /* Look for opening brace */
    i = 0;
    buf[0] = nextc(p);
    if (buf[0] < 0) goto eof;
    if (buf[0] == '{') {
      /* \u{xxxxxxxx} form */
      for (i=0; i<9; i++) {
        buf[i] = nextc(p);
        if (buf[i] < 0) goto eof;
        if (buf[i] == '}') {
          break;
        }
        else if (!ISXDIGIT(buf[i])) {
          yyerror(p, "Invalid escape character syntax");
          pushback(p, buf[i]);
          return 0;
        }
      }
    }
    else if (ISXDIGIT(buf[0])) {
      /* \uxxxx form */
      for (i=1; i<4; i++) {
        buf[i] = nextc(p);
        if (buf[i] < 0) goto eof;
        if (!ISXDIGIT(buf[i])) {
          pushback(p, buf[i]);
          break;
        }
      }
    }
    else {
      pushback(p, buf[0]);
    }
    c = scan_hex(buf, i, &i);
    if (i == 0) {
      yyerror(p, "Invalid escape character syntax");
      return 0;
    }
    if (c < 0 || c > 0x10FFFF || (c & 0xFFFFF800) == 0xD800) {
      yyerror(p, "Invalid Unicode code point");
      return 0;
    }
  }
  return -c;

  case 'b':/* backspace */
    return '\010';

  case 's':/* space */
    return ' ';

  case 'M':
    if ((c = nextc(p)) != '-') {
      yyerror(p, "Invalid escape character syntax");
      pushback(p, c);
      return '\0';
    }
    if ((c = nextc(p)) == '\\') {
      return read_escape(p) | 0x80;
    }
    else if (c < 0) goto eof;
    else {
      return ((c & 0xff) | 0x80);
    }

  case 'C':
    if ((c = nextc(p)) != '-') {
      yyerror(p, "Invalid escape character syntax");
      pushback(p, c);
      return '\0';
    }
  case 'c':
    if ((c = nextc(p))== '\\') {
      c = read_escape(p);
    }
    else if (c == '?')
      return 0177;
    else if (c < 0) goto eof;
    return c & 0x9f;

    eof:
  case -1:
  case -2:                      /* end of a file */
    yyerror(p, "Invalid escape character syntax");
    return '\0';

  default:
    return c;
  }
}

static int
parse_string(parser_state *p)
{
  int c;
  string_type type = (string_type)(intptr_t)p->lex_strterm->car;
  int nest_level = (intptr_t)p->lex_strterm->cdr->car;
  int beg = (intptr_t)p->lex_strterm->cdr->cdr->car;
  int end = (intptr_t)p->lex_strterm->cdr->cdr->cdr;
  parser_heredoc_info *hinf = (type & STR_FUNC_HEREDOC) ? parsing_heredoc_inf(p) : NULL;

  newtok(p);
  while ((c = nextc(p)) != end || nest_level != 0) {
    if (hinf && (c == '\n' || c < 0)) {
      mrb_bool line_head;
      tokadd(p, '\n');
      tokfix(p);
      p->lineno++;
      p->column = 0;
      line_head = hinf->line_head;
      hinf->line_head = TRUE;
      if (line_head) {
        /* check whether end of heredoc */
        const char *s = tok(p);
        int len = toklen(p);
        if (hinf->allow_indent) {
          while (ISSPACE(*s) && len > 0) {
            ++s;
            --len;
          }
        }
        if ((len-1 == hinf->term_len) && (strncmp(s, hinf->term, len-1) == 0)) {
          return tHEREDOC_END;
        }
      }
      if (c < 0) {
        char buf[256];
        snprintf(buf, sizeof(buf), "can't find heredoc delimiter \"%s\" anywhere before EOF", hinf->term);
        yyerror(p, buf);
        return 0;
      }
      yylval.nd = new_str(p, tok(p), toklen(p));
      return tHD_STRING_MID;
    }
    if (c < 0) {
      yyerror(p, "unterminated string meets end of file");
      return 0;
    }
    else if (c == beg) {
      nest_level++;
      p->lex_strterm->cdr->car = (node*)(intptr_t)nest_level;
    }
    else if (c == end) {
      nest_level--;
      p->lex_strterm->cdr->car = (node*)(intptr_t)nest_level;
    }
    else if (c == '\\') {
      c = nextc(p);
      if (type & STR_FUNC_EXPAND) {
        if (c == end || c == beg) {
          tokadd(p, c);
        }
        else if (c == '\n') {
          p->lineno++;
          p->column = 0;
          if (type & STR_FUNC_ARRAY) {
            tokadd(p, '\n');
          }
        }
        else if (type & STR_FUNC_REGEXP) {
          tokadd(p, '\\');
          tokadd(p, c);
        }
        else {
          pushback(p, c);
          tokadd(p, read_escape(p));
          if (hinf)
            hinf->line_head = FALSE;
        }
      }
      else {
        if (c != beg && c != end) {
          if (c == '\n') {
            p->lineno++;
            p->column = 0;
          }
          if (!(c == '\\' || ((type & STR_FUNC_ARRAY) && ISSPACE(c)))) {
            tokadd(p, '\\');
          }
        }
        tokadd(p, c);
      }
      continue;
    }
    else if ((c == '#') && (type & STR_FUNC_EXPAND)) {
      c = nextc(p);
      if (c == '{') {
        tokfix(p);
        p->lstate = EXPR_BEG;
        p->cmd_start = TRUE;
        yylval.nd = new_str(p, tok(p), toklen(p));
        if (hinf) {
          hinf->line_head = FALSE;
          return tHD_STRING_PART;
        }
        return tSTRING_PART;
      }
      tokadd(p, '#');
      pushback(p, c);
      continue;
    }
    if ((type & STR_FUNC_ARRAY) && ISSPACE(c)) {
      if (toklen(p) == 0) {
        do {
          if (c == '\n') {
            p->lineno++;
            p->column = 0;
            heredoc_treat_nextline(p);
            if (p->parsing_heredoc != NULL) {
              return tHD_LITERAL_DELIM;
            }
          }
          c = nextc(p);
        } while (ISSPACE(c));
        pushback(p, c);
        return tLITERAL_DELIM;
      }
      else {
        pushback(p, c);
        tokfix(p);
        yylval.nd = new_str(p, tok(p), toklen(p));
        return tSTRING_MID;
      }
    }
    tokadd(p, c);
  }

  tokfix(p);
  p->lstate = EXPR_END;
  end_strterm(p);

  if (type & STR_FUNC_XQUOTE) {
    yylval.nd = new_xstr(p, tok(p), toklen(p));
    return tXSTRING;
  }

  if (type & STR_FUNC_REGEXP) {
    int f = 0;
    int re_opt;
    char *s = strndup(tok(p), toklen(p));
    char flags[3];
    char *flag = flags;
    char enc = '\0';
    char *encp;
    char *dup;

    newtok(p);
    while (re_opt = nextc(p), re_opt >= 0 && ISALPHA(re_opt)) {
      switch (re_opt) {
      case 'i': f |= 1; break;
      case 'x': f |= 2; break;
      case 'm': f |= 4; break;
      case 'u': f |= 16; break;
      case 'n': f |= 32; break;
      default: tokadd(p, re_opt); break;
      }
    }
    pushback(p, re_opt);
    if (toklen(p)) {
      char msg[128];
      tokfix(p);
      snprintf(msg, sizeof(msg), "unknown regexp option%s - %s",
          toklen(p) > 1 ? "s" : "", tok(p));
      yyerror(p, msg);
    }
    if (f != 0) {
      if (f & 1) *flag++ = 'i';
      if (f & 2) *flag++ = 'x';
      if (f & 4) *flag++ = 'm';
      if (f & 16) enc = 'u';
      if (f & 32) enc = 'n';
    }
    if (flag > flags) {
      dup = strndup(flags, (size_t)(flag - flags));
    } else {
      dup = NULL;
    }
    if (enc) {
      encp = strndup(&enc, 1);
    } else {
      encp = NULL;
    }
    yylval.nd = new_regx(p, s, dup, encp);

    return tREGEXP;
  }

  yylval.nd = new_str(p, tok(p), toklen(p));
  return tSTRING;
}


static int
heredoc_identifier(parser_state *p)
{
  int c;
  int type = str_heredoc;
  mrb_bool indent = FALSE;
  mrb_bool quote = FALSE;
  node *newnode;
  parser_heredoc_info *info;

  c = nextc(p);
  if (ISSPACE(c) || c == '=') {
    pushback(p, c);
    return 0;
  }
  if (c == '-') {
    indent = TRUE;
    c = nextc(p);
  }
  if (c == '\'' || c == '"') {
    int term = c;
    if (c == '\'')
      quote = TRUE;
    newtok(p);
    while ((c = nextc(p)) >= 0 && c != term) {
      if (c == '\n') {
        c = -1;
        break;
      }
      tokadd(p, c);
    }
    if (c < 0) {
      yyerror(p, "unterminated here document identifier");
      return 0;
    }
  }
  else {
    if (c < 0) {
      return 0;                 /* missing here document identifier */
    }
    if (! identchar(c)) {
      pushback(p, c);
      if (indent) pushback(p, '-');
      return 0;
    }
    newtok(p);
    do {
      tokadd(p, c);
    } while ((c = nextc(p)) >= 0 && identchar(c));
    pushback(p, c);
  }
  tokfix(p);
  newnode = new_heredoc(p);
  info = (parser_heredoc_info*)newnode->cdr;
  info->term = strndup(tok(p), toklen(p));
  info->term_len = toklen(p);
  if (! quote)
    type |= STR_FUNC_EXPAND;
  info->type = (string_type)type;
  info->allow_indent = indent;
  info->line_head = TRUE;
  info->doc = NULL;
  p->heredocs_from_nextline = push(p->heredocs_from_nextline, newnode);
  p->lstate = EXPR_END;

  yylval.nd = newnode;
  return tHEREDOC_BEG;
}

static int
arg_ambiguous(parser_state *p)
{
  yywarning(p, "ambiguous first argument; put parentheses or even spaces");
  return 1;
}

#include "lex.def"

static int
parser_yylex(parser_state *p)
{
  int32_t c;
  int space_seen = 0;
  int cmd_state;
  enum mrb_lex_state_enum last_state;
  int token_column;

  if (p->lex_strterm) {
    if (is_strterm_type(p, STR_FUNC_HEREDOC)) {
      if (p->parsing_heredoc != NULL)
        return parse_string(p);
    }
    else
      return parse_string(p);
  }
  cmd_state = p->cmd_start;
  p->cmd_start = FALSE;
  retry:
  last_state = p->lstate;
  switch (c = nextc(p)) {
  case '\004':  /* ^D */
  case '\032':  /* ^Z */
  case '\0':    /* NUL */
  case -1:      /* end of script. */
    if (p->heredocs_from_nextline)
      goto maybe_heredoc;
    return 0;

  /* white spaces */
  case ' ': case '\t': case '\f': case '\r':
  case '\13':   /* '\v' */
    space_seen = 1;
    goto retry;

  case '#':     /* it's a comment */
    skip(p, '\n');
    /* fall through */
  case -2:      /* end of a file */
  case '\n':
    maybe_heredoc:
    heredoc_treat_nextline(p);
  switch (p->lstate) {
  case EXPR_BEG:
  case EXPR_FNAME:
  case EXPR_DOT:
  case EXPR_CLASS:
  case EXPR_VALUE:
    p->lineno++;
    p->column = 0;
    if (p->parsing_heredoc != NULL) {
      if (p->lex_strterm) {
        return parse_string(p);
      }
    }
    goto retry;
  default:
    break;
  }
  if (p->parsing_heredoc != NULL) {
    return '\n';
  }
  while ((c = nextc(p))) {
    switch (c) {
    case ' ': case '\t': case '\f': case '\r':
    case '\13': /* '\v' */
      space_seen = 1;
      break;
    case '.':
      if ((c = nextc(p)) != '.') {
        pushback(p, c);
        pushback(p, '.');
        goto retry;
      }
    case -1:                  /* EOF */
    case -2:                  /* end of a file */
      goto normal_newline;
    default:
      pushback(p, c);
      goto normal_newline;
    }
  }
  normal_newline:
  p->cmd_start = TRUE;
  p->lstate = EXPR_BEG;
  return '\n';

  case '*':
    if ((c = nextc(p)) == '*') {
      if ((c = nextc(p)) == '=') {
        yylval.id = intern("**",2);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      c = tPOW;
    }
    else {
      if (c == '=') {
        yylval.id = intern_c('*');
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      if (IS_SPCARG(c)) {
        yywarning(p, "'*' interpreted as argument prefix");
        c = tSTAR;
      }
      else if (IS_BEG()) {
        c = tSTAR;
      }
      else {
        c = '*';
      }
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return c;

  case '!':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
        return '!';
      }
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if (c == '=') {
      return tNEQ;
    }
    if (c == '~') {
      return tNMATCH;
    }
    pushback(p, c);
    return '!';

  case '=':
    if (p->column == 1) {
      static const char begin[] = "begin";
      static const char end[] = "\n=end";
      if (peeks(p, begin)) {
        c = peekc_n(p, sizeof(begin)-1);
        if (c < 0 || ISSPACE(c)) {
          do {
            if (!skips(p, end)) {
              yyerror(p, "embedded document meets end of file");
              return 0;
            }
            c = nextc(p);
          } while (!(c < 0 || ISSPACE(c)));
          if (c != '\n') skip(p, '\n');
          p->lineno++;
          p->column = 0;
          goto retry;
        }
      }
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if ((c = nextc(p)) == '=') {
      if ((c = nextc(p)) == '=') {
        return tEQQ;
      }
      pushback(p, c);
      return tEQ;
    }
    if (c == '~') {
      return tMATCH;
    }
    else if (c == '>') {
      return tASSOC;
    }
    pushback(p, c);
    return '=';

  case '<':
    c = nextc(p);
    if (c == '<' &&
        p->lstate != EXPR_DOT &&
        p->lstate != EXPR_CLASS &&
        !IS_END() &&
        (!IS_ARG() || space_seen)) {
      int token = heredoc_identifier(p);
      if (token)
        return token;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
      if (p->lstate == EXPR_CLASS) {
        p->cmd_start = TRUE;
      }
    }
    if (c == '=') {
      if ((c = nextc(p)) == '>') {
        return tCMP;
      }
      pushback(p, c);
      return tLEQ;
    }
    if (c == '<') {
      if ((c = nextc(p)) == '=') {
        yylval.id = intern("<<",2);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tLSHFT;
    }
    pushback(p, c);
    return '<';

  case '>':
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if ((c = nextc(p)) == '=') {
      return tGEQ;
    }
    if (c == '>') {
      if ((c = nextc(p)) == '=') {
        yylval.id = intern(">>",2);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tRSHFT;
    }
    pushback(p, c);
    return '>';

  case '"':
    p->lex_strterm = new_strterm(p, str_dquote, '"', 0);
    return tSTRING_BEG;

  case '\'':
    p->lex_strterm = new_strterm(p, str_squote, '\'', 0);
    return parse_string(p);

  case '`':
    if (p->lstate == EXPR_FNAME) {
      p->lstate = EXPR_ENDFN;
      return '`';
    }
    if (p->lstate == EXPR_DOT) {
      if (cmd_state)
        p->lstate = EXPR_CMDARG;
      else
        p->lstate = EXPR_ARG;
      return '`';
    }
    p->lex_strterm = new_strterm(p, str_xquote, '`', 0);
    return tXSTRING_BEG;

  case '?':
    if (IS_END()) {
      p->lstate = EXPR_VALUE;
      return '?';
    }
    c = nextc(p);
    if (c < 0) {
      yyerror(p, "incomplete character syntax");
      return 0;
    }
    if (ISSPACE(c)) {
      if (!IS_ARG()) {
        int c2;
        switch (c) {
        case ' ':
          c2 = 's';
          break;
        case '\n':
          c2 = 'n';
          break;
        case '\t':
          c2 = 't';
          break;
        case '\v':
          c2 = 'v';
          break;
        case '\r':
          c2 = 'r';
          break;
        case '\f':
          c2 = 'f';
          break;
        default:
          c2 = 0;
          break;
        }
        if (c2) {
          char buf[256];
          snprintf(buf, sizeof(buf), "invalid character syntax; use ?\\%c", c2);
          yyerror(p, buf);
        }
      }
      ternary:
      pushback(p, c);
      p->lstate = EXPR_VALUE;
      return '?';
    }
    newtok(p);
    /* need support UTF-8 if configured */
    if ((isalnum(c) || c == '_')) {
      int c2 = nextc(p);
      pushback(p, c2);
      if ((isalnum(c2) || c2 == '_')) {
        goto ternary;
      }
    }
    if (c == '\\') {
      c = read_escape(p);
      tokadd(p, c);
    }
    else {
      tokadd(p, c);
    }
    tokfix(p);
    yylval.nd = new_str(p, tok(p), toklen(p));
    p->lstate = EXPR_END;
    return tCHAR;

  case '&':
    if ((c = nextc(p)) == '&') {
      p->lstate = EXPR_BEG;
      if ((c = nextc(p)) == '=') {
        yylval.id = intern("&&",2);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tANDOP;
    }
    else if (c == '.') {
      p->lstate = EXPR_DOT;
      return tANDDOT;
    }
    else if (c == '=') {
      yylval.id = intern_c('&');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    pushback(p, c);
    if (IS_SPCARG(c)) {
      yywarning(p, "'&' interpreted as argument prefix");
      c = tAMPER;
    }
    else if (IS_BEG()) {
      c = tAMPER;
    }
    else {
      c = '&';
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return c;

  case '|':
    if ((c = nextc(p)) == '|') {
      p->lstate = EXPR_BEG;
      if ((c = nextc(p)) == '=') {
        yylval.id = intern("||",2);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tOROP;
    }
    if (c == '=') {
      yylval.id = intern_c('|');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '|';

  case '+':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
        return tUPLUS;
      }
      pushback(p, c);
      return '+';
    }
    if (c == '=') {
      yylval.id = intern_c('+');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous(p))) {
      p->lstate = EXPR_BEG;
      pushback(p, c);
      if (c >= 0 && ISDIGIT(c)) {
        c = '+';
        goto start_num;
      }
      return tUPLUS;
    }
    p->lstate = EXPR_BEG;
    pushback(p, c);
    return '+';

  case '-':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
        return tUMINUS;
      }
      pushback(p, c);
      return '-';
    }
    if (c == '=') {
      yylval.id = intern_c('-');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (c == '>') {
      p->lstate = EXPR_ENDFN;
      return tLAMBDA;
    }
    if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous(p))) {
      p->lstate = EXPR_BEG;
      pushback(p, c);
      if (c >= 0 && ISDIGIT(c)) {
        return tUMINUS_NUM;
      }
      return tUMINUS;
    }
    p->lstate = EXPR_BEG;
    pushback(p, c);
    return '-';

  case '.':
    p->lstate = EXPR_BEG;
    if ((c = nextc(p)) == '.') {
      if ((c = nextc(p)) == '.') {
        return tDOT3;
      }
      pushback(p, c);
      return tDOT2;
    }
    pushback(p, c);
    if (c >= 0 && ISDIGIT(c)) {
      yyerror(p, "no .<digit> floating literal anymore; put 0 before dot");
    }
    p->lstate = EXPR_DOT;
    return '.';

    start_num:
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  {
    int is_float, seen_point, seen_e, nondigit;

    is_float = seen_point = seen_e = nondigit = 0;
    p->lstate = EXPR_END;
    newtok(p);
    if (c == '-' || c == '+') {
      tokadd(p, c);
      c = nextc(p);
    }
    if (c == '0') {
#define no_digits() do {yyerror(p,"numeric literal without digits"); return 0;} while (0)
      int start = toklen(p);
      c = nextc(p);
      if (c == 'x' || c == 'X') {
        /* hexadecimal */
        c = nextc(p);
        if (c >= 0 && ISXDIGIT(c)) {
          do {
            if (c == '_') {
              if (nondigit) break;
              nondigit = c;
              continue;
            }
            if (!ISXDIGIT(c)) break;
            nondigit = 0;
            tokadd(p, tolower(c));
          } while ((c = nextc(p)) >= 0);
        }
        pushback(p, c);
        tokfix(p);
        if (toklen(p) == start) {
          no_digits();
        }
        else if (nondigit) goto trailing_uc;
        yylval.nd = new_int(p, tok(p), 16);
        return tINTEGER;
      }
      if (c == 'b' || c == 'B') {
        /* binary */
        c = nextc(p);
        if (c == '0' || c == '1') {
          do {
            if (c == '_') {
              if (nondigit) break;
              nondigit = c;
              continue;
            }
            if (c != '0' && c != '1') break;
            nondigit = 0;
            tokadd(p, c);
          } while ((c = nextc(p)) >= 0);
        }
        pushback(p, c);
        tokfix(p);
        if (toklen(p) == start) {
          no_digits();
        }
        else if (nondigit) goto trailing_uc;
        yylval.nd = new_int(p, tok(p), 2);
        return tINTEGER;
      }
      if (c == 'd' || c == 'D') {
        /* decimal */
        c = nextc(p);
        if (c >= 0 && ISDIGIT(c)) {
          do {
            if (c == '_') {
              if (nondigit) break;
              nondigit = c;
              continue;
            }
            if (!ISDIGIT(c)) break;
            nondigit = 0;
            tokadd(p, c);
          } while ((c = nextc(p)) >= 0);
        }
        pushback(p, c);
        tokfix(p);
        if (toklen(p) == start) {
          no_digits();
        }
        else if (nondigit) goto trailing_uc;
        yylval.nd = new_int(p, tok(p), 10);
        return tINTEGER;
      }
      if (c == '_') {
        /* 0_0 */
        goto octal_number;
      }
      if (c == 'o' || c == 'O') {
        /* prefixed octal */
        c = nextc(p);
        if (c < 0 || c == '_' || !ISDIGIT(c)) {
          no_digits();
        }
      }
      if (c >= '0' && c <= '7') {
        /* octal */
        octal_number:
        do {
          if (c == '_') {
            if (nondigit) break;
            nondigit = c;
            continue;
          }
          if (c < '0' || c > '9') break;
          if (c > '7') goto invalid_octal;
          nondigit = 0;
          tokadd(p, c);
        } while ((c = nextc(p)) >= 0);

        if (toklen(p) > start) {
          pushback(p, c);
          tokfix(p);
          if (nondigit) goto trailing_uc;
          yylval.nd = new_int(p, tok(p), 8);
          return tINTEGER;
        }
        if (nondigit) {
          pushback(p, c);
          goto trailing_uc;
        }
      }
      if (c > '7' && c <= '9') {
        invalid_octal:
        yyerror(p, "Invalid octal digit");
      }
      else if (c == '.' || c == 'e' || c == 'E') {
        tokadd(p, '0');
      }
      else {
        pushback(p, c);
        yylval.nd = new_int(p, "0", 10);
        return tINTEGER;
      }
    }

    for (;;) {
      switch (c) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        nondigit = 0;
        tokadd(p, c);
        break;

      case '.':
        if (nondigit) goto trailing_uc;
        if (seen_point || seen_e) {
          goto decode_num;
        }
        else {
          int c0 = nextc(p);
          if (c0 < 0 || !ISDIGIT(c0)) {
            pushback(p, c0);
            goto decode_num;
          }
          c = c0;
        }
        tokadd(p, '.');
        tokadd(p, c);
        is_float++;
        seen_point++;
        nondigit = 0;
        break;

      case 'e':
      case 'E':
        if (nondigit) {
          pushback(p, c);
          c = nondigit;
          goto decode_num;
        }
        if (seen_e) {
          goto decode_num;
        }
        tokadd(p, c);
        seen_e++;
        is_float++;
        nondigit = c;
        c = nextc(p);
        if (c != '-' && c != '+') continue;
        tokadd(p, c);
        nondigit = c;
        break;

      case '_':       /* '_' in number just ignored */
        if (nondigit) goto decode_num;
        nondigit = c;
        break;

      default:
        goto decode_num;
      }
      c = nextc(p);
    }

    decode_num:
    pushback(p, c);
    if (nondigit) {
      trailing_uc:
      yyerror_i(p, "trailing '%c' in number", nondigit);
    }
    tokfix(p);
    if (is_float) {
      double d;
      char *endp;

      errno = 0;
      d = strtod(tok(p), &endp);
      if (d == 0 && endp == tok(p)) {
        yywarning_s(p, "corrupted float value %s", tok(p));
      }
      else if (errno == ERANGE) {
        yywarning_s(p, "float %s out of range", tok(p));
        errno = 0;
      }
      yylval.nd = new_float(p, tok(p));
      return tFLOAT;
    }
    yylval.nd = new_int(p, tok(p), 10);
    return tINTEGER;
  }

  case ')':
  case ']':
    p->paren_nest--;
    /* fall through */
  case '}':
    COND_LEXPOP();
    CMDARG_LEXPOP();
    if (c == ')')
      p->lstate = EXPR_ENDFN;
    else
      p->lstate = EXPR_ENDARG;
    return c;

  case ':':
    c = nextc(p);
    if (c == ':') {
      if (IS_BEG() || p->lstate == EXPR_CLASS || IS_SPCARG(-1)) {
        p->lstate = EXPR_BEG;
        return tCOLON3;
      }
      p->lstate = EXPR_DOT;
      return tCOLON2;
    }
    if (IS_END() || ISSPACE(c)) {
      pushback(p, c);
      p->lstate = EXPR_BEG;
      return ':';
    }
    pushback(p, c);
    p->lstate = EXPR_FNAME;
    return tSYMBEG;

  case '/':
    if (IS_BEG()) {
      p->lex_strterm = new_strterm(p, str_regexp, '/', 0);
      return tREGEXP_BEG;
    }
    if ((c = nextc(p)) == '=') {
      yylval.id = intern_c('/');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    pushback(p, c);
    if (IS_SPCARG(c)) {
      p->lex_strterm = new_strterm(p, str_regexp, '/', 0);
      return tREGEXP_BEG;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return '/';

  case '^':
    if ((c = nextc(p)) == '=') {
      yylval.id = intern_c('^');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '^';

  case ';':
    p->lstate = EXPR_BEG;
    return ';';

  case ',':
    p->lstate = EXPR_BEG;
    return ',';

  case '~':
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      if ((c = nextc(p)) != '@') {
        pushback(p, c);
      }
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return '~';

  case '(':
    if (IS_BEG()) {
      c = tLPAREN;
    }
    else if (IS_SPCARG(-1)) {
      c = tLPAREN_ARG;
    }
    p->paren_nest++;
    COND_PUSH(0);
    CMDARG_PUSH(0);
    p->lstate = EXPR_BEG;
    return c;

  case '[':
    p->paren_nest++;
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if ((c = nextc(p)) == ']') {
        if ((c = nextc(p)) == '=') {
          return tASET;
        }
        pushback(p, c);
        return tAREF;
      }
      pushback(p, c);
      return '[';
    }
    else if (IS_BEG()) {
      c = tLBRACK;
    }
    else if (IS_ARG() && space_seen) {
      c = tLBRACK;
    }
    p->lstate = EXPR_BEG;
    COND_PUSH(0);
    CMDARG_PUSH(0);
    return c;

  case '{':
    if (p->lpar_beg && p->lpar_beg == p->paren_nest) {
      p->lstate = EXPR_BEG;
      p->lpar_beg = 0;
      p->paren_nest--;
      COND_PUSH(0);
      CMDARG_PUSH(0);
      return tLAMBEG;
    }
    if (IS_ARG() || p->lstate == EXPR_END || p->lstate == EXPR_ENDFN)
      c = '{';          /* block (primary) */
    else if (p->lstate == EXPR_ENDARG)
      c = tLBRACE_ARG;  /* block (expr) */
    else
      c = tLBRACE;      /* hash */
    COND_PUSH(0);
    CMDARG_PUSH(0);
    p->lstate = EXPR_BEG;
    return c;

  case '\\':
    c = nextc(p);
    if (c == '\n') {
      p->lineno++;
      p->column = 0;
      space_seen = 1;
      goto retry; /* skip \\n */
    }
    pushback(p, c);
    return '\\';

  case '%':
    if (IS_BEG()) {
      int term;
      int paren;

      c = nextc(p);
      quotation:
      if (c < 0 || !ISALNUM(c)) {
        term = c;
        c = 'Q';
      }
      else {
        term = nextc(p);
        if (isalnum(term)) {
          yyerror(p, "unknown type of %string");
          return 0;
        }
      }
      if (c < 0 || term < 0) {
        yyerror(p, "unterminated quoted string meets end of file");
        return 0;
      }
      paren = term;
      if (term == '(') term = ')';
      else if (term == '[') term = ']';
      else if (term == '{') term = '}';
      else if (term == '<') term = '>';
      else paren = 0;

      switch (c) {
      case 'Q':
        p->lex_strterm = new_strterm(p, str_dquote, term, paren);
        return tSTRING_BEG;

      case 'q':
        p->lex_strterm = new_strterm(p, str_squote, term, paren);
        return parse_string(p);

      case 'W':
        p->lex_strterm = new_strterm(p, str_dword, term, paren);
        return tWORDS_BEG;

      case 'w':
        p->lex_strterm = new_strterm(p, str_sword, term, paren);
        return tWORDS_BEG;

      case 'x':
        p->lex_strterm = new_strterm(p, str_xquote, term, paren);
        return tXSTRING_BEG;

      case 'r':
        p->lex_strterm = new_strterm(p, str_regexp, term, paren);
        return tREGEXP_BEG;

      case 's':
        p->lex_strterm = new_strterm(p, str_ssym, term, paren);
        return tSYMBEG;

      case 'I':
        p->lex_strterm = new_strterm(p, str_dsymbols, term, paren);
        return tSYMBOLS_BEG;

      case 'i':
        p->lex_strterm = new_strterm(p, str_ssymbols, term, paren);
        return tSYMBOLS_BEG;

      default:
        yyerror(p, "unknown type of %string");
        return 0;
      }
    }
    if ((c = nextc(p)) == '=') {
      yylval.id = intern_c('%');
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (IS_SPCARG(c)) {
      goto quotation;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '%';

  case '$':
    p->lstate = EXPR_END;
    token_column = newtok(p);
    c = nextc(p);
    if (c < 0) {
      yyerror(p, "incomplete global variable syntax");
      return 0;
    }
    switch (c) {
    case '_':     /* $_: last read line string */
      c = nextc(p);
      if (c >= 0 && identchar(c)) { /* if there is more after _ it is a variable */
        tokadd(p, '$');
        tokadd(p, c);
        break;
      }
      pushback(p, c);
      c = '_';
      /* fall through */
    case '~':     /* $~: match-data */
    case '*':     /* $*: argv */
    case '$':     /* $$: pid */
    case '?':     /* $?: last status */
    case '!':     /* $!: error string */
    case '@':     /* $@: error position */
    case '/':     /* $/: input record separator */
    case '\\':    /* $\: output record separator */
    case ';':     /* $;: field separator */
    case ',':     /* $,: output field separator */
    case '.':     /* $.: last read line number */
    case '=':     /* $=: ignorecase */
    case ':':     /* $:: load path */
    case '<':     /* $<: reading filename */
    case '>':     /* $>: default output handle */
    case '\"':    /* $": already loaded files */
      tokadd(p, '$');
      tokadd(p, c);
      tokfix(p);
      yylval.id = intern_cstr(tok(p));
      return tGVAR;

    case '-':
      tokadd(p, '$');
      tokadd(p, c);
      c = nextc(p);
      pushback(p, c);
      gvar:
      tokfix(p);
      yylval.id = intern_cstr(tok(p));
      return tGVAR;

    case '&':     /* $&: last match */
    case '`':     /* $`: string before last match */
    case '\'':    /* $': string after last match */
    case '+':     /* $+: string matches last pattern */
      if (last_state == EXPR_FNAME) {
        tokadd(p, '$');
        tokadd(p, c);
        goto gvar;
      }
      yylval.nd = new_back_ref(p, c);
      return tBACK_REF;

    case '1': case '2': case '3':
    case '4': case '5': case '6':
    case '7': case '8': case '9':
      do {
        tokadd(p, c);
        c = nextc(p);
      } while (c >= 0 && isdigit(c));
      pushback(p, c);
      if (last_state == EXPR_FNAME) goto gvar;
      tokfix(p);
      {
        unsigned long n = strtoul(tok(p), NULL, 10);
        if (n > INT_MAX) {
          yyerror_i(p, "capture group index must be <= %d", INT_MAX);
          return 0;
        }
        yylval.nd = new_nth_ref(p, (int)n);
      }
      return tNTH_REF;

    default:
      if (!identchar(c)) {
        pushback(p,  c);
        return '$';
      }
      /* fall through */
    case '0':
      tokadd(p, '$');
    }
    break;

    case '@':
      c = nextc(p);
      token_column = newtok(p);
      tokadd(p, '@');
      if (c == '@') {
        tokadd(p, '@');
        c = nextc(p);
      }
      if (c < 0) {
        if (p->bidx == 1) {
          yyerror(p, "incomplete instance variable syntax");
        }
        else {
          yyerror(p, "incomplete class variable syntax");
        }
        return 0;
      }
      else if (isdigit(c)) {
        if (p->bidx == 1) {
          yyerror_i(p, "'@%c' is not allowed as an instance variable name", c);
        }
        else {
          yyerror_i(p, "'@@%c' is not allowed as a class variable name", c);
        }
        return 0;
      }
      if (!identchar(c)) {
        pushback(p, c);
        return '@';
      }
      break;

    case '_':
      token_column = newtok(p);
      break;

    default:
      if (!identchar(c)) {
        yyerror_i(p,  "Invalid char '\\x%02X' in expression", c);
        goto retry;
      }

      token_column = newtok(p);
      break;
  }

  do {
    tokadd(p, c);
    c = nextc(p);
    if (c < 0) break;
  } while (identchar(c));
  if (token_column == 0 && toklen(p) == 7 && (c < 0 || c == '\n') &&
      strncmp(tok(p), "__END__", toklen(p)) == 0)
    return -1;

  switch (tok(p)[0]) {
  case '@': case '$':
    pushback(p, c);
    break;
  default:
    if ((c == '!' || c == '?') && !peek(p, '=')) {
      tokadd(p, c);
    }
    else {
      pushback(p, c);
    }
  }
  tokfix(p);
  {
    int result = 0;

    switch (tok(p)[0]) {
    case '$':
      p->lstate = EXPR_END;
      result = tGVAR;
      break;
    case '@':
      p->lstate = EXPR_END;
      if (tok(p)[1] == '@')
        result = tCVAR;
      else
        result = tIVAR;
      break;

    default:
      if (toklast(p) == '!' || toklast(p) == '?') {
        result = tFID;
      }
      else {
        if (p->lstate == EXPR_FNAME) {
          if ((c = nextc(p)) == '=' && !peek(p, '~') && !peek(p, '>') &&
              (!peek(p, '=') || (peek_n(p, '>', 1)))) {
            result = tIDENTIFIER;
            tokadd(p, c);
            tokfix(p);
          }
          else {
            pushback(p, c);
          }
        }
        if (result == 0 && ISUPPER(tok(p)[0])) {
          result = tCONSTANT;
        }
        else {
          result = tIDENTIFIER;
        }
      }

      if (IS_LABEL_POSSIBLE()) {
        if (IS_LABEL_SUFFIX(0)) {
          p->lstate = EXPR_BEG;
          nextc(p);
          tokfix(p);
          yylval.id = intern_cstr(tok(p));
          return tLABEL;
        }
      }
      if (p->lstate != EXPR_DOT) {
        const struct kwtable *kw;

        /* See if it is a reserved word.  */
        kw = mrb_reserved_word(tok(p), toklen(p));
        if (kw) {
          enum mrb_lex_state_enum state = p->lstate;
          yylval.num = p->lineno;
          p->lstate = kw->state;
          if (state == EXPR_FNAME) {
            yylval.id = intern_cstr(kw->name);
            return kw->id[0];
          }
          if (p->lstate == EXPR_BEG) {
            p->cmd_start = TRUE;
          }
          if (kw->id[0] == keyword_do) {
            if (p->lpar_beg && p->lpar_beg == p->paren_nest) {
              p->lpar_beg = 0;
              p->paren_nest--;
              return keyword_do_LAMBDA;
            }
            if (COND_P()) return keyword_do_cond;
            if (CMDARG_P() && state != EXPR_CMDARG)
              return keyword_do_block;
            if (state == EXPR_ENDARG || state == EXPR_BEG)
              return keyword_do_block;
            return keyword_do;
          }
          if (state == EXPR_BEG || state == EXPR_VALUE)
            return kw->id[0];
          else {
            if (kw->id[0] != kw->id[1])
              p->lstate = EXPR_BEG;
            return kw->id[1];
          }
        }
      }

      if (IS_BEG() || p->lstate == EXPR_DOT || IS_ARG()) {
        if (cmd_state) {
          p->lstate = EXPR_CMDARG;
        }
        else {
          p->lstate = EXPR_ARG;
        }
      }
      else if (p->lstate == EXPR_FNAME) {
        p->lstate = EXPR_ENDFN;
      }
      else {
        p->lstate = EXPR_END;
      }
    }
    {
      mrb_sym ident = intern_cstr(tok(p));

      yylval.id = ident;
#if 0
      if (last_state != EXPR_DOT && islower(tok(p)[0]) && lvar_defined(ident)) {
        p->lstate = EXPR_END;
      }
#endif
    }
    return result;
  }
}

static int
yylex(void *lval, parser_state *p)
{
  p->ylval = lval;
  return parser_yylex(p);
}

static void
parser_init_cxt(parser_state *p, mrbc_context *cxt)
{
  if (!cxt) return;
  if (cxt->filename) mrb_parser_set_filename(p, cxt->filename);
  if (cxt->lineno) p->lineno = cxt->lineno;
  if (cxt->syms) {
    int i;

    p->locals = cons(0,0);
    for (i=0; i<cxt->slen; i++) {
      local_add_f(p, cxt->syms[i]);
    }
  }
  p->capture_errors = cxt->capture_errors;
  p->no_optimize = cxt->no_optimize;
  if (cxt->partial_hook) {
    p->cxt = cxt;
  }
}

static void
parser_update_cxt(parser_state *p, mrbc_context *cxt)
{
  node *n, *n0;
  int i = 0;

  if (!cxt) return;
  if ((int)(intptr_t)p->tree->car != NODE_SCOPE) return;
  n0 = n = p->tree->cdr->car;
  while (n) {
    i++;
    n = n->cdr;
  }
  cxt->syms = (mrb_sym *)mrb_realloc(p->mrb, cxt->syms, i*sizeof(mrb_sym));
  cxt->slen = i;
  for (i=0, n=n0; n; i++,n=n->cdr) {
    cxt->syms[i] = sym(n->car);
  }
}

void mrb_codedump_all(mrb_state*, struct RProc*);
void mrb_parser_dump(mrb_state *mrb, node *tree, int offset);

MRB_API void
mrb_parser_parse(parser_state *p, mrbc_context *c)
{
  struct mrb_jmpbuf buf;
  p->jmp = &buf;

  MRB_TRY(p->jmp) {

    p->cmd_start = TRUE;
    p->in_def = p->in_single = 0;
    p->nerr = p->nwarn = 0;
    p->lex_strterm = NULL;

    parser_init_cxt(p, c);
    yyparse(p);
    if (!p->tree) {
      p->tree = new_nil(p);
    }
    parser_update_cxt(p, c);
    if (c && c->dump_result) {
      mrb_parser_dump(p->mrb, p->tree, 0);
    }

  }
  MRB_CATCH(p->jmp) {
    yyerror(p, "memory allocation error");
    p->nerr++;
    p->tree = 0;
    return;
  }
  MRB_END_EXC(p->jmp);
}

MRB_API parser_state*
mrb_parser_new(mrb_state *mrb)
{
  mrb_pool *pool;
  parser_state *p;
  static const parser_state parser_state_zero = { 0 };

  pool = mrb_pool_open(mrb);
  if (!pool) return NULL;
  p = (parser_state *)mrb_pool_alloc(pool, sizeof(parser_state));
  if (!p) return NULL;

  *p = parser_state_zero;
  p->mrb = mrb;
  p->pool = pool;

  p->s = p->send = NULL;
#ifndef MRB_DISABLE_STDIO
  p->f = NULL;
#endif

  p->cmd_start = TRUE;
  p->in_def = p->in_single = 0;

  p->capture_errors = FALSE;
  p->lineno = 1;
  p->column = 0;
#if defined(PARSER_TEST) || defined(PARSER_DEBUG)
  yydebug = 1;
#endif

  p->lex_strterm = NULL;
  p->all_heredocs = p->parsing_heredoc = NULL;
  p->lex_strterm_before_heredoc = NULL;

  p->current_filename_index = -1;
  p->filename_table = NULL;
  p->filename_table_length = 0;

  return p;
}

MRB_API void
mrb_parser_free(parser_state *p) {
  mrb_pool_close(p->pool);
}

MRB_API mrbc_context*
mrbc_context_new(mrb_state *mrb)
{
  return (mrbc_context *)mrb_calloc(mrb, 1, sizeof(mrbc_context));
}

MRB_API void
mrbc_context_free(mrb_state *mrb, mrbc_context *cxt)
{
  mrb_free(mrb, cxt->syms);
  mrb_free(mrb, cxt);
}

MRB_API const char*
mrbc_filename(mrb_state *mrb, mrbc_context *c, const char *s)
{
  if (s) {
    int len = strlen(s);
    char *p = (char *)mrb_alloca(mrb, len + 1);

    memcpy(p, s, len + 1);
    c->filename = p;
  }
  return c->filename;
}

MRB_API void
mrbc_partial_hook(mrb_state *mrb, mrbc_context *c, int (*func)(struct mrb_parser_state*), void *data)
{
  c->partial_hook = func;
  c->partial_data = data;
}

MRB_API void
mrb_parser_set_filename(struct mrb_parser_state *p, const char *f)
{
  mrb_sym sym;
  size_t i;
  mrb_sym* new_table;

  sym = mrb_intern_cstr(p->mrb, f);
  p->filename = mrb_sym2name_len(p->mrb, sym, NULL);
  p->lineno = (p->filename_table_length > 0)? 0 : 1;

  for (i = 0; i < p->filename_table_length; ++i) {
    if (p->filename_table[i] == sym) {
      p->current_filename_index = i;
      return;
    }
  }

  p->current_filename_index = p->filename_table_length++;

  new_table = (mrb_sym*)parser_palloc(p, sizeof(mrb_sym) * p->filename_table_length);
  if (p->filename_table) {
    memmove(new_table, p->filename_table, sizeof(mrb_sym) * p->filename_table_length);
  }
  p->filename_table = new_table;
  p->filename_table[p->filename_table_length - 1] = sym;
}

MRB_API char const*
mrb_parser_get_filename(struct mrb_parser_state* p, uint16_t idx) {
  if (idx >= p->filename_table_length) { return NULL; }
  else {
    return mrb_sym2name_len(p->mrb, p->filename_table[idx], NULL);
  }
}

#ifndef MRB_DISABLE_STDIO
MRB_API parser_state*
mrb_parse_file(mrb_state *mrb, FILE *f, mrbc_context *c)
{
  parser_state *p;

  p = mrb_parser_new(mrb);
  if (!p) return NULL;
  p->s = p->send = NULL;
  p->f = f;

  mrb_parser_parse(p, c);
  return p;
}
#endif

MRB_API parser_state*
mrb_parse_nstring(mrb_state *mrb, const char *s, int len, mrbc_context *c)
{
  parser_state *p;

  p = mrb_parser_new(mrb);
  if (!p) return NULL;
  p->s = s;
  p->send = s + len;

  mrb_parser_parse(p, c);
  return p;
}

MRB_API parser_state*
mrb_parse_string(mrb_state *mrb, const char *s, mrbc_context *c)
{
  return mrb_parse_nstring(mrb, s, strlen(s), c);
}

static mrb_value
load_exec(mrb_state *mrb, parser_state *p, mrbc_context *c)
{
  struct RClass *target = mrb->object_class;
  struct RProc *proc;
  mrb_value v;
  unsigned int keep = 0;

  if (!p) {
    return mrb_undef_value();
  }
  if (!p->tree || p->nerr) {
    if (p->capture_errors) {
      char buf[256];
      int n;

      n = snprintf(buf, sizeof(buf), "line %d: %s\n",
          p->error_buffer[0].lineno, p->error_buffer[0].message);
      mrb->exc = mrb_obj_ptr(mrb_exc_new(mrb, E_SYNTAX_ERROR, buf, n));
      mrb_parser_free(p);
      return mrb_undef_value();
    }
    else {
      mrb->exc = mrb_obj_ptr(mrb_exc_new_str_lit(mrb, E_SYNTAX_ERROR, "syntax error"));
      mrb_parser_free(p);
      return mrb_undef_value();
    }
  }
  proc = mrb_generate_code(mrb, p);
  mrb_parser_free(p);
  if (proc == NULL) {
    mrb->exc = mrb_obj_ptr(mrb_exc_new_str_lit(mrb, E_SCRIPT_ERROR, "codegen error"));
    return mrb_undef_value();
  }
  if (c) {
    if (c->dump_result) mrb_codedump_all(mrb, proc);
    if (c->no_exec) return mrb_obj_value(proc);
    if (c->target_class) {
      target = c->target_class;
    }
    if (c->keep_lv) {
      keep = c->slen + 1;
    }
    else {
      c->keep_lv = TRUE;
    }
  }
  proc->target_class = target;
  if (mrb->c->ci) {
    mrb->c->ci->target_class = target;
  }
  v = mrb_top_run(mrb, proc, mrb_top_self(mrb), keep);
  if (mrb->exc) return mrb_nil_value();
  return v;
}

#ifndef MRB_DISABLE_STDIO
MRB_API mrb_value
mrb_load_file_cxt(mrb_state *mrb, FILE *f, mrbc_context *c)
{
  return load_exec(mrb, mrb_parse_file(mrb, f, c), c);
}

MRB_API mrb_value
mrb_load_file(mrb_state *mrb, FILE *f)
{
  return mrb_load_file_cxt(mrb, f, NULL);
}
#endif

MRB_API mrb_value
mrb_load_nstring_cxt(mrb_state *mrb, const char *s, int len, mrbc_context *c)
{
  return load_exec(mrb, mrb_parse_nstring(mrb, s, len, c), c);
}

MRB_API mrb_value
mrb_load_nstring(mrb_state *mrb, const char *s, int len)
{
  return mrb_load_nstring_cxt(mrb, s, len, NULL);
}

MRB_API mrb_value
mrb_load_string_cxt(mrb_state *mrb, const char *s, mrbc_context *c)
{
  return mrb_load_nstring_cxt(mrb, s, strlen(s), c);
}

MRB_API mrb_value
mrb_load_string(mrb_state *mrb, const char *s)
{
  return mrb_load_string_cxt(mrb, s, NULL);
}

#ifndef MRB_DISABLE_STDIO

static void
dump_prefix(node *tree, int offset)
{
  printf("%05d ", tree->lineno);
  while (offset--) {
    putc(' ', stdout);
    putc(' ', stdout);
  }
}

static void
dump_recur(mrb_state *mrb, node *tree, int offset)
{
  while (tree) {
    mrb_parser_dump(mrb, tree->car, offset);
    tree = tree->cdr;
  }
}

#endif

void
mrb_parser_dump(mrb_state *mrb, node *tree, int offset)
{
#ifndef MRB_DISABLE_STDIO
  int nodetype;

  if (!tree) return;
  again:
  dump_prefix(tree, offset);
  nodetype = (int)(intptr_t)tree->car;
  tree = tree->cdr;
  switch (nodetype) {
  case NODE_BEGIN:
    printf("NODE_BEGIN:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_RESCUE:
    printf("NODE_RESCUE:\n");
    if (tree->car) {
      dump_prefix(tree, offset+1);
      printf("body:\n");
      mrb_parser_dump(mrb, tree->car, offset+2);
    }
    tree = tree->cdr;
    if (tree->car) {
      node *n2 = tree->car;

      dump_prefix(n2, offset+1);
      printf("rescue:\n");
      while (n2) {
        node *n3 = n2->car;
        if (n3->car) {
          dump_prefix(n2, offset+2);
          printf("handle classes:\n");
          dump_recur(mrb, n3->car, offset+3);
        }
        if (n3->cdr->car) {
          dump_prefix(n3, offset+2);
          printf("exc_var:\n");
          mrb_parser_dump(mrb, n3->cdr->car, offset+3);
        }
        if (n3->cdr->cdr->car) {
          dump_prefix(n3, offset+2);
          printf("rescue body:\n");
          mrb_parser_dump(mrb, n3->cdr->cdr->car, offset+3);
        }
        n2 = n2->cdr;
      }
    }
    tree = tree->cdr;
    if (tree->car) {
      dump_prefix(tree, offset+1);
      printf("else:\n");
      mrb_parser_dump(mrb, tree->car, offset+2);
    }
    break;

  case NODE_ENSURE:
    printf("NODE_ENSURE:\n");
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("ensure:\n");
    mrb_parser_dump(mrb, tree->cdr->cdr, offset+2);
    break;

  case NODE_LAMBDA:
    printf("NODE_BLOCK:\n");
    goto block;

  case NODE_BLOCK:
    block:
    printf("NODE_BLOCK:\n");
    tree = tree->cdr;
    if (tree->car) {
      node *n = tree->car;

      if (n->car) {
        dump_prefix(n, offset+1);
        printf("mandatory args:\n");
        dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n->car) {
        dump_prefix(n, offset+1);
        printf("optional args:\n");
        {
          node *n2 = n->car;

          while (n2) {
            dump_prefix(n2, offset+2);
            printf("%s=", mrb_sym2name(mrb, sym(n2->car->car)));
            mrb_parser_dump(mrb, n2->car->cdr, 0);
            n2 = n2->cdr;
          }
        }
      }
      n = n->cdr;
      if (n->car) {
        dump_prefix(n, offset+1);
        printf("rest=*%s\n", mrb_sym2name(mrb, sym(n->car)));
      }
      n = n->cdr;
      if (n->car) {
        dump_prefix(n, offset+1);
        printf("post mandatory args:\n");
        dump_recur(mrb, n->car, offset+2);
      }
      if (n->cdr) {
        dump_prefix(n, offset+1);
        printf("blk=&%s\n", mrb_sym2name(mrb, sym(n->cdr)));
      }
    }
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr->car, offset+2);
    break;

  case NODE_IF:
    printf("NODE_IF:\n");
    dump_prefix(tree, offset+1);
    printf("cond:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("then:\n");
    mrb_parser_dump(mrb, tree->cdr->car, offset+2);
    if (tree->cdr->cdr->car) {
      dump_prefix(tree, offset+1);
      printf("else:\n");
      mrb_parser_dump(mrb, tree->cdr->cdr->car, offset+2);
    }
    break;

  case NODE_AND:
    printf("NODE_AND:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    mrb_parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_OR:
    printf("NODE_OR:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    mrb_parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_CASE:
    printf("NODE_CASE:\n");
    if (tree->car) {
      mrb_parser_dump(mrb, tree->car, offset+1);
    }
    tree = tree->cdr;
    while (tree) {
      dump_prefix(tree, offset+1);
      printf("case:\n");
      dump_recur(mrb, tree->car->car, offset+2);
      dump_prefix(tree, offset+1);
      printf("body:\n");
      mrb_parser_dump(mrb, tree->car->cdr, offset+2);
      tree = tree->cdr;
    }
    break;

  case NODE_WHILE:
    printf("NODE_WHILE:\n");
    dump_prefix(tree, offset+1);
    printf("cond:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_UNTIL:
    printf("NODE_UNTIL:\n");
    dump_prefix(tree, offset+1);
    printf("cond:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_FOR:
    printf("NODE_FOR:\n");
    dump_prefix(tree, offset+1);
    printf("var:\n");
    {
      node *n2 = tree->car;

      if (n2->car) {
        dump_prefix(n2, offset+2);
        printf("pre:\n");
        dump_recur(mrb, n2->car, offset+3);
      }
      n2 = n2->cdr;
      if (n2) {
        if (n2->car) {
          dump_prefix(n2, offset+2);
          printf("rest:\n");
          mrb_parser_dump(mrb, n2->car, offset+3);
        }
        n2 = n2->cdr;
        if (n2) {
          if (n2->car) {
            dump_prefix(n2, offset+2);
            printf("post:\n");
            dump_recur(mrb, n2->car, offset+3);
          }
        }
      }
    }
    tree = tree->cdr;
    dump_prefix(tree, offset+1);
    printf("in:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    tree = tree->cdr;
    dump_prefix(tree, offset+1);
    printf("do:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    break;

  case NODE_SCOPE:
    printf("NODE_SCOPE:\n");
    {
      node *n2 = tree->car;
      mrb_bool first_lval = TRUE;

      if (n2 && (n2->car || n2->cdr)) {
        dump_prefix(n2, offset+1);
        printf("local variables:\n");
        dump_prefix(n2, offset+2);
        while (n2) {
          if (n2->car) {
            if (!first_lval) printf(", ");
            printf("%s", mrb_sym2name(mrb, sym(n2->car)));
            first_lval = FALSE;
          }
          n2 = n2->cdr;
        }
        printf("\n");
      }
    }
    tree = tree->cdr;
    offset++;
    goto again;

  case NODE_FCALL:
  case NODE_CALL:
    printf("NODE_CALL:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    dump_prefix(tree, offset+1);
    printf("method='%s' (%d)\n",
        mrb_sym2name(mrb, sym(tree->cdr->car)),
        (int)(intptr_t)tree->cdr->car);
    tree = tree->cdr->cdr->car;
    if (tree) {
      dump_prefix(tree, offset+1);
      printf("args:\n");
      dump_recur(mrb, tree->car, offset+2);
      if (tree->cdr) {
        dump_prefix(tree, offset+1);
        printf("block:\n");
        mrb_parser_dump(mrb, tree->cdr, offset+2);
      }
    }
    break;

  case NODE_DOT2:
    printf("NODE_DOT2:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    mrb_parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_DOT3:
    printf("NODE_DOT3:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    mrb_parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_COLON2:
    printf("NODE_COLON2:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    dump_prefix(tree, offset+1);
    printf("::%s\n", mrb_sym2name(mrb, sym(tree->cdr)));
    break;

  case NODE_COLON3:
    printf("NODE_COLON3: ::%s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_ARRAY:
    printf("NODE_ARRAY:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_HASH:
    printf("NODE_HASH:\n");
    while (tree) {
      dump_prefix(tree, offset+1);
      printf("key:\n");
      mrb_parser_dump(mrb, tree->car->car, offset+2);
      dump_prefix(tree, offset+1);
      printf("value:\n");
      mrb_parser_dump(mrb, tree->car->cdr, offset+2);
      tree = tree->cdr;
    }
    break;

  case NODE_SPLAT:
    printf("NODE_SPLAT:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_ASGN:
    printf("NODE_ASGN:\n");
    dump_prefix(tree, offset+1);
    printf("lhs:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("rhs:\n");
    mrb_parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_MASGN:
    printf("NODE_MASGN:\n");
    dump_prefix(tree, offset+1);
    printf("mlhs:\n");
    {
      node *n2 = tree->car;

      if (n2->car) {
        dump_prefix(tree, offset+2);
        printf("pre:\n");
        dump_recur(mrb, n2->car, offset+3);
      }
      n2 = n2->cdr;
      if (n2) {
        if (n2->car) {
          dump_prefix(n2, offset+2);
          printf("rest:\n");
          if (n2->car == (node*)-1) {
            dump_prefix(n2, offset+2);
            printf("(empty)\n");
          }
          else {
            mrb_parser_dump(mrb, n2->car, offset+3);
          }
        }
        n2 = n2->cdr;
        if (n2) {
          if (n2->car) {
            dump_prefix(n2, offset+2);
            printf("post:\n");
            dump_recur(mrb, n2->car, offset+3);
          }
        }
      }
    }
    dump_prefix(tree, offset+1);
    printf("rhs:\n");
    mrb_parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_OP_ASGN:
    printf("NODE_OP_ASGN:\n");
    dump_prefix(tree, offset+1);
    printf("lhs:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    tree = tree->cdr;
    dump_prefix(tree, offset+1);
    printf("op='%s' (%d)\n", mrb_sym2name(mrb, sym(tree->car)), (int)(intptr_t)tree->car);
    tree = tree->cdr;
    mrb_parser_dump(mrb, tree->car, offset+1);
    break;

  case NODE_SUPER:
    printf("NODE_SUPER:\n");
    if (tree) {
      dump_prefix(tree, offset+1);
      printf("args:\n");
      dump_recur(mrb, tree->car, offset+2);
      if (tree->cdr) {
        dump_prefix(tree, offset+1);
        printf("block:\n");
        mrb_parser_dump(mrb, tree->cdr, offset+2);
      }
    }
    break;

  case NODE_ZSUPER:
    printf("NODE_ZSUPER\n");
    break;

  case NODE_RETURN:
    printf("NODE_RETURN:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_YIELD:
    printf("NODE_YIELD:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_BREAK:
    printf("NODE_BREAK:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_NEXT:
    printf("NODE_NEXT:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_REDO:
    printf("NODE_REDO\n");
    break;

  case NODE_RETRY:
    printf("NODE_RETRY\n");
    break;

  case NODE_LVAR:
    printf("NODE_LVAR %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_GVAR:
    printf("NODE_GVAR %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_IVAR:
    printf("NODE_IVAR %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_CVAR:
    printf("NODE_CVAR %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_CONST:
    printf("NODE_CONST %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_MATCH:
    printf("NODE_MATCH:\n");
    dump_prefix(tree, offset + 1);
    printf("lhs:\n");
    mrb_parser_dump(mrb, tree->car, offset + 2);
    dump_prefix(tree, offset + 1);
    printf("rhs:\n");
    mrb_parser_dump(mrb, tree->cdr, offset + 2);
    break;

  case NODE_BACK_REF:
    printf("NODE_BACK_REF: $%c\n", (int)(intptr_t)tree);
    break;

  case NODE_NTH_REF:
    printf("NODE_NTH_REF: $%d\n", (int)(intptr_t)tree);
    break;

  case NODE_ARG:
    printf("NODE_ARG %s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_BLOCK_ARG:
    printf("NODE_BLOCK_ARG:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_INT:
    printf("NODE_INT %s base %d\n", (char*)tree->car, (int)(intptr_t)tree->cdr->car);
    break;

  case NODE_FLOAT:
    printf("NODE_FLOAT %s\n", (char*)tree);
    break;

  case NODE_NEGATE:
    printf("NODE_NEGATE\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_STR:
    printf("NODE_STR \"%s\" len %d\n", (char*)tree->car, (int)(intptr_t)tree->cdr);
    break;

  case NODE_DSTR:
    printf("NODE_DSTR\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_XSTR:
    printf("NODE_XSTR \"%s\" len %d\n", (char*)tree->car, (int)(intptr_t)tree->cdr);
    break;

  case NODE_DXSTR:
    printf("NODE_DXSTR\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_REGX:
    printf("NODE_REGX /%s/%s\n", (char*)tree->car, (char*)tree->cdr);
    break;

  case NODE_DREGX:
    printf("NODE_DREGX\n");
    dump_recur(mrb, tree->car, offset+1);
    dump_prefix(tree, offset);
    printf("tail: %s\n", (char*)tree->cdr->cdr->car);
    dump_prefix(tree, offset);
    printf("opt: %s\n", (char*)tree->cdr->cdr->cdr);
    break;

  case NODE_SYM:
    printf("NODE_SYM :%s\n", mrb_sym2name(mrb, sym(tree)));
    break;

  case NODE_SELF:
    printf("NODE_SELF\n");
    break;

  case NODE_NIL:
    printf("NODE_NIL\n");
    break;

  case NODE_TRUE:
    printf("NODE_TRUE\n");
    break;

  case NODE_FALSE:
    printf("NODE_FALSE\n");
    break;

  case NODE_ALIAS:
    printf("NODE_ALIAS %s %s:\n",
        mrb_sym2name(mrb, sym(tree->car)),
        mrb_sym2name(mrb, sym(tree->cdr)));
    break;

  case NODE_UNDEF:
    printf("NODE_UNDEF");
    {
      node *t = tree;
      while (t) {
        printf(" %s", mrb_sym2name(mrb, sym(t->car)));
        t = t->cdr;
      }
    }
    printf(":\n");
    break;

  case NODE_CLASS:
    printf("NODE_CLASS:\n");
    if (tree->car->car == (node*)0) {
      dump_prefix(tree, offset+1);
      printf(":%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    else if (tree->car->car == (node*)1) {
      dump_prefix(tree, offset+1);
      printf("::%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    else {
      mrb_parser_dump(mrb, tree->car->car, offset+1);
      dump_prefix(tree, offset+1);
      printf("::%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    if (tree->cdr->car) {
      dump_prefix(tree, offset+1);
      printf("super:\n");
      mrb_parser_dump(mrb, tree->cdr->car, offset+2);
    }
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr->cdr->car->cdr, offset+2);
    break;

  case NODE_MODULE:
    printf("NODE_MODULE:\n");
    if (tree->car->car == (node*)0) {
      dump_prefix(tree, offset+1);
      printf(":%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    else if (tree->car->car == (node*)1) {
      dump_prefix(tree, offset+1);
      printf("::%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    else {
      mrb_parser_dump(mrb, tree->car->car, offset+1);
      dump_prefix(tree, offset+1);
      printf("::%s\n", mrb_sym2name(mrb, sym(tree->car->cdr)));
    }
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr->car->cdr, offset+2);
    break;

  case NODE_SCLASS:
    printf("NODE_SCLASS:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr->car->cdr, offset+2);
    break;

  case NODE_DEF:
    printf("NODE_DEF:\n");
    dump_prefix(tree, offset+1);
    printf("%s\n", mrb_sym2name(mrb, sym(tree->car)));
    tree = tree->cdr;
    {
      node *n2 = tree->car;
      mrb_bool first_lval = TRUE;

      if (n2 && (n2->car || n2->cdr)) {
        dump_prefix(n2, offset+1);
        printf("local variables:\n");
        dump_prefix(n2, offset+2);
        while (n2) {
          if (n2->car) {
            if (!first_lval) printf(", ");
            printf("%s", mrb_sym2name(mrb, sym(n2->car)));
            first_lval = FALSE;
          }
          n2 = n2->cdr;
        }
        printf("\n");
      }
    }
    tree = tree->cdr;
    if (tree->car) {
      node *n = tree->car;

      if (n->car) {
        dump_prefix(n, offset+1);
        printf("mandatory args:\n");
        dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n->car) {
        dump_prefix(n, offset+1);
        printf("optional args:\n");
        {
          node *n2 = n->car;

          while (n2) {
            dump_prefix(n2, offset+2);
            printf("%s=", mrb_sym2name(mrb, sym(n2->car->car)));
            mrb_parser_dump(mrb, n2->car->cdr, 0);
            n2 = n2->cdr;
          }
        }
      }
      n = n->cdr;
      if (n->car) {
        dump_prefix(n, offset+1);
        printf("rest=*%s\n", mrb_sym2name(mrb, sym(n->car)));
      }
      n = n->cdr;
      if (n->car) {
        dump_prefix(n, offset+1);
        printf("post mandatory args:\n");
        dump_recur(mrb, n->car, offset+2);
      }
      if (n->cdr) {
        dump_prefix(n, offset+1);
        printf("blk=&%s\n", mrb_sym2name(mrb, sym(n->cdr)));
      }
    }
    mrb_parser_dump(mrb, tree->cdr->car, offset+1);
    break;

  case NODE_SDEF:
    printf("NODE_SDEF:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    tree = tree->cdr;
    dump_prefix(tree, offset+1);
    printf(":%s\n", mrb_sym2name(mrb, sym(tree->car)));
    tree = tree->cdr->cdr;
    if (tree->car) {
      node *n = tree->car;

      if (n->car) {
        dump_prefix(n, offset+1);
        printf("mandatory args:\n");
        dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n->car) {
        dump_prefix(n, offset+1);
        printf("optional args:\n");
        {
          node *n2 = n->car;

          while (n2) {
            dump_prefix(n2, offset+2);
            printf("%s=", mrb_sym2name(mrb, sym(n2->car->car)));
            mrb_parser_dump(mrb, n2->car->cdr, 0);
            n2 = n2->cdr;
          }
        }
      }
      n = n->cdr;
      if (n->car) {
        dump_prefix(n, offset+1);
        printf("rest=*%s\n", mrb_sym2name(mrb, sym(n->car)));
      }
      n = n->cdr;
      if (n->car) {
        dump_prefix(n, offset+1);
        printf("post mandatory args:\n");
        dump_recur(mrb, n->car, offset+2);
      }
      n = n->cdr;
      if (n) {
        dump_prefix(n, offset+1);
        printf("blk=&%s\n", mrb_sym2name(mrb, sym(n)));
      }
    }
    tree = tree->cdr;
    mrb_parser_dump(mrb, tree->car, offset+1);
    break;

  case NODE_POSTEXE:
    printf("NODE_POSTEXE:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_HEREDOC:
    printf("NODE_HEREDOC:\n");
    mrb_parser_dump(mrb, ((parser_heredoc_info*)tree)->doc, offset+1);
    break;

  default:
    printf("node type: %d (0x%x)\n", nodetype, (unsigned)nodetype);
    break;
  }
#endif
}
