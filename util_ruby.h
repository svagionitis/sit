#ifndef UTIL_RUBY_H_INCLUDED
#define UTIL_RUBY_H_INCLUDED

#include "ruby.h"
#include <stdbool.h>

typedef struct value_holder {
	VALUE val;
  struct value_holder *next;
} value_holder;

void *
vwrap(VALUE value);

VALUE
vunwrap(void *vp);

void 
markall();

VALUE
rbc_isTestMode(VALUE class);

VALUE
rbc_setTestMode(VALUE class, VALUE val);

#endif
