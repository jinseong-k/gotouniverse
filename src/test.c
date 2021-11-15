#include <stdio.h>

#include "libcommon.h"

#define TEST_CNT 8

int stack_test() {
  JS_STACK_t *stack = NULL;
  int i;
  int a = 10;
  int result = 0;
  int count = TEST_CNT;

  js_enable_debug();
  stack = create_stack(sizeof(int), count);
  // Create Stack

  for (i=0; i<count+4; i++) {
    a = i;
    js_push(stack, &a);
    // Push Datas
  }

  for (i=0; i<count+4; i++) {
    js_pop(stack, (void *)&result);
    // Pop Datas
  }

  destroy_stack(stack);
  // Destroy Stack

  return 1;
}

int queue_test() {
  int i;
  int data = 0;
  JS_QUEUE_t *queue = NULL;
  int count = TEST_CNT;

  js_enable_debug();
  queue = create_queue(sizeof(int), count);

  for (i=0; i<count+4; i++) {
    data = i;
    js_enqueue(queue, (void *)&data);
  }

  for (i=0; i<count+4; i++) {
    js_dequeue(queue, (void *)&data);
  }

  return 1;
}

int main() {
#if 0
  stack_test();  // Stack Library Test
#else
  stack_test();  // Stack Library Test
  queue_test();  // Queue Library Test
#endif
}
