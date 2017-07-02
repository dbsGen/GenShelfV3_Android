/*
** tempfile.c - Tempfile
**
** See Copyright Notice in mruby.h
*/
#include "mruby.h"
#include "mruby/class.h"
#include "mruby/value.h"
#include "mruby/variable.h"
#include "mruby/string.h"
#include "mruby/data.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static void mrb_tempfile_path_free(mrb_state *, void *);

struct tempfile_path {
  char *pathname;
};

const static struct mrb_data_type mrb_tempfile_path_type = { "TempfilePath", mrb_tempfile_path_free };

static void
mrb_tempfile_path_free(mrb_state *mrb, void *self)
{
  struct tempfile_path *tp = self;

  if (tp->pathname != NULL) {
    (void)unlink(tp->pathname);
    mrb_free(mrb, tp->pathname);
    tp->pathname = NULL;
  }
  mrb_free(mrb, self);
}

mrb_value
mrb_tempfile_path_init(mrb_state *mrb, mrb_value self)
{
  mrb_value path;
  struct tempfile_path *tp;
  char *cp;

  tp = (struct tempfile_path *)mrb_malloc(mrb, sizeof(struct tempfile_path));
  tp->pathname = NULL;
  DATA_TYPE(self) = &mrb_tempfile_path_type;
  DATA_PTR(self)  = tp;

  mrb_get_args(mrb, "S", &path);
  cp = (char *)mrb_malloc(mrb, (size_t)RSTRING_LEN(path) + 1);
  memcpy(cp, RSTRING_PTR(path), RSTRING_LEN(path));
  cp[RSTRING_LEN(path)] = '\0';
  tp->pathname = cp;

  return self;
}

mrb_value
mrb_tempfile_getpid(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(getpid());
}

void
mrb_init_tempfile_path(mrb_state *mrb)
{
  struct RClass *tempfile_path_class;

  tempfile_path_class = mrb_define_class(mrb, "TempfilePath", mrb->object_class);
  MRB_SET_INSTANCE_TT(tempfile_path_class, MRB_TT_DATA);

  mrb_define_method(mrb, tempfile_path_class, "initialize", mrb_tempfile_path_init, MRB_ARGS_REQ(1));
}

void
mrb_mruby_tempfile_gem_init(mrb_state *mrb)
{
  struct RClass *tempfile_class;
  struct RClass *file;

  file = mrb_class_get(mrb, "File");
  tempfile_class = mrb_define_class(mrb, "Tempfile", file);

  MRB_SET_INSTANCE_TT(tempfile_class, MRB_TT_DATA);

  mrb_define_class_method(mrb, tempfile_class, "_getpid", mrb_tempfile_getpid, MRB_ARGS_NONE());

  mrb_init_tempfile_path(mrb);
}

void
mrb_mruby_tempfile_gem_final(mrb_state* mrb) {
}
