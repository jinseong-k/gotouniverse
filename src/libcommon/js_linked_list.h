#ifndef __JS_LINKED_LIST_HDR_
#define __JS_LINKED_LIST_HDR_
#include <stdint.h>

#define LIST_FAIL 0
#define LIST_OK 1
#define LIST_NONE 2

#define LIST_NORM 1
#define LIST_SORT 2

typedef struct _JS_NODE_t {
  void *data;
  struct _JS_NODE_t *next;
} JS_NODE;

typedef struct _JS_LIST_t {
  uint32_t num_of_elements;
  uint32_t data_size;
  uint32_t (*comp_func)(void *, void *);
  uint32_t (*add_func)(struct _JS_LIST_t *, void *);
  JS_NODE *head;
} JS_LIST;

JS_LIST *js_create_linked_list(uint32_t data_size, uint32_t (*comp_func)(void *, void *), uint32_t mode);
uint32_t js_destroy_linked_list(JS_LIST *list);
uint32_t js_add_list(JS_LIST *list, void *data);
uint32_t js_remove_list(JS_LIST *list, void *data);
uint32_t js_list_elements(JS_LIST *list);
void *js_find_data(JS_LIST *list, void *data);
void *js_get_data(JS_LIST *list, void *data);
uint32_t js_apply(JS_LIST *list, uint32_t (*cb_func)(void *));

#endif  // __JS_LINKED_LIST_HDR_
