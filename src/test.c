#include <stdio.h>

#include "libcommon.h"

int stack_test() {
  JS_STACK_t *stack = NULL;
  int i;
  int a = 10;
  int result = 0;

  js_enable_debug();
  stack = create_stack(sizeof(int), 32);
  // Create Stack

  for (i=0; i<10; i++) {
    a = i;
    js_push(stack, &a);
    // Push Datas
  }
  fprintf(stderr, "num of elements : [%d]\n", get_data_count(stack));

  for (i=0; i<10; i++) {
    js_pop(stack, (void *)&result);
    // Pop Datas
  }
  fprintf(stderr, "num of elements : [%d]\n", get_data_count(stack));

  destroy_stack(stack);
  // Destroy Stack

  return 1;
}

int main() {
  stack_test();  // Stack Library Test
}
