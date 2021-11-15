#include <stdio.h>
#include <stdint.h>

#include "libcommon.h"

#define TEST_CNT 8

typedef struct _TEST {
  uint32_t a;
  uint32_t b;
} TEST;

int stack_test() {
  JS_STACK_t *stack = NULL;
  int i;
  TEST data;
  TEST result;
  int count = TEST_CNT;

  stack = create_stack(sizeof(TEST), count);
  // Create Stack

  for (i=0; i<count+4; i++) {
    data.a = i;
    data.b = i+1;
    js_push(stack, &data);
    // Push Datas
  }

  for (i=0; i<count+4; i++) {
    if (STACK_OK == js_pop(stack, (void *)&result)) {
      fprintf(stderr, "POP a : [%u] b : [%u]\n",
          result.a, result.b);
    }
  }

  destroy_stack(stack);
  // Destroy Stack

  return 1;
}

int queue_test() {
  int i;
  TEST data;
  TEST result;
  JS_QUEUE_t *queue = NULL;
  int count = TEST_CNT;

  queue = create_queue(sizeof(TEST), count);

  for (i=0; i<count+4; i++) {
    data.a = i;
    data.b = i+3;
    js_enqueue(queue, (void *)&data);
  }

  for (i=0; i<count+4; i++) {
    if (QUEUE_OK == js_dequeue(queue, (void *)&result)) {
      fprintf(stderr, "DEQ a : [%u] b : [%u]\n",
          result.a, result.b);
    }
  }

  return 1;
}

int main() {
  js_enable_debug();
#if 0
  stack_test();  // Stack Library Test
#else
  stack_test();  // Stack Library Test
  queue_test();  // Queue Library Test
#endif
}
