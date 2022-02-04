#ifndef __JS_STACK_HDR_
#define __JS_STACK_HDR_

#include <stdint.h>

#define STACK_FAIL 0
#define STACK_OK 1
#define STACK_NONE 2

typedef struct _JS_STACK_t {
  uint32_t num_of_elements;
  uint32_t max_num;
  uint32_t data_size;
  void *data;
  void *head;
} JS_STACK_t;

JS_STACK_t *create_stack(uint32_t size, uint32_t num);
void destroy_stack(JS_STACK_t *stack);
uint32_t js_push(JS_STACK_t *stack, void *data);
uint32_t js_pop(JS_STACK_t *stack, void *data);
uint32_t stack_elements(JS_STACK_t *stack);

#endif  // __JS_STACK_HDR_
