#include <stdio.h>

#include "libcommon.h"

/*****************************************
 공용 라이브러리 구현

 - Stack
 - Queue (Circle)
 - Linked List (One way)
 - Hash table (XXH32 hash function)

 *****************************************/

void js_print_version() {
  fprintf(stderr,
      "JS Common Library Version : [%s]\n",
      JS_CLIB_VERSION);
}
