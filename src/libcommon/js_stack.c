#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "js_stack.h"
#include "js_debug.h"

JS_STACK_t *create_stack(uint32_t data_size, uint32_t max_cnt) {
  JS_STACK_t *stack = NULL;
  stack = (JS_STACK_t *)malloc(sizeof(JS_STACK_t));
  memset(stack, 0x00, sizeof(JS_STACK_t));

  stack->data = (void *)malloc(data_size * max_cnt);
  stack->head = &stack->data[0];
  stack->max_num = max_cnt;
  stack->data_size = data_size;

  return stack;
}

void destroy_stack(JS_STACK_t *stack) {
  if (stack) {
    free(stack->data);
    stack->data = NULL;
    free(stack);
    stack = NULL;
  }
}

uint32_t stack_elements(JS_STACK_t *stack) {
  if (stack) return stack->num_of_elements;
  return 0;
}

uint32_t check_data_count(JS_STACK_t *stack) {
  if (stack_elements(stack) >= stack->max_num) return STACK_FAIL;
  else return STACK_OK;
}

uint32_t js_push(JS_STACK_t *stack, void *data) {
  if (stack == NULL || data == NULL) {
    return STACK_FAIL;
  }

  if (check_data_count(stack) == STACK_FAIL) {
    js_print_debug("[%s:%d] Stack full\n", __func__, __LINE__);
    return STACK_FAIL;
  }

  stack->head+=stack->data_size;
  memcpy(stack->head, data, stack->data_size);
  stack->num_of_elements++;

  return STACK_OK;
}

uint32_t js_pop(JS_STACK_t *stack, void *data) {
  if (stack == NULL) return STACK_FAIL;
  if (stack->num_of_elements <= 0) {
    js_print_debug("[%s:%d] Stack empty\n", __func__, __LINE__);
    return STACK_NONE;
  }

  memcpy(data, stack->head, stack->data_size);
  stack->head-=stack->data_size;
  stack->num_of_elements--;

  return STACK_OK;
}
