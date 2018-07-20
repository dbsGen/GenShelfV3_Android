/*
** print.c - Kernel.#p
**
** See Copyright Notice in mruby.h
*/

#include <mruby.h>
#include <mruby/string.h>
#include <mruby/variable.h>
#ifdef __ANDROID__
#include <android/log.h>
#endif

#ifndef MRB_DISABLE_STDIO
static void
printstr(mrb_value obj, FILE *stream)
{
  if (mrb_string_p(obj)) {
#ifdef __ANDROID__
    __android_log_print(ANDROID_LOG_INFO, "GRender", "%s", RSTRING_PTR(obj));
#else
    fwrite(RSTRING_PTR(obj), RSTRING_LEN(obj), 1, stream);
    putc('\n', stream);
#endif
  }
}
#else
# define printstr(obj, stream) (void)0
#endif

MRB_API void
mrb_p(mrb_state *mrb, mrb_value obj)
{
  printstr(mrb_inspect(mrb, obj), stdout);
}

MRB_API void
mrb_print_error(mrb_state *mrb)
{
  mrb_print_backtrace(mrb);
  printstr(mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0), stderr);
}

MRB_API void
mrb_show_version(mrb_state *mrb)
{
  printstr(mrb_const_get(mrb, mrb_obj_value(mrb->object_class), mrb_intern_lit(mrb, "MRUBY_DESCRIPTION")), stdout);
}

MRB_API void
mrb_show_copyright(mrb_state *mrb)
{
  printstr(mrb_const_get(mrb, mrb_obj_value(mrb->object_class), mrb_intern_lit(mrb, "MRUBY_COPYRIGHT")), stdout);
}
