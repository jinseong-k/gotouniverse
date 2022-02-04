#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "js_debug.h"

int g_enable_debug = 0;

void js_enable_debug() {
  g_enable_debug = 1;
}

void js_print_debug(char *fmt, ...) {
  va_list vl;
  if (g_enable_debug != 1) return;

  va_start(vl, fmt);
  vprintf(fmt, vl);
  va_end(vl);
}
