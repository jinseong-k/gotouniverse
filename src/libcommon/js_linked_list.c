#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "js_linked_list.h"

uint32_t js_list_elements(JS_LIST *list) {
  return list->num_of_elements;
}

uint32_t default_comp_func(void *data_a, void *data_b) {
  return *((uint32_t *)data_a) == *((uint32_t *)data_b) ? LIST_OK : LIST_FAIL;
}

uint32_t js_add_func(JS_LIST *list, void *data) {
  JS_NODE *node;
  node = (JS_NODE *)malloc(sizeof(JS_NODE));

  if (list->head) {
    node->next = list->head;
  } else {
    node->next = NULL;
  }
  list->head = node;

  node->data = malloc(list->data_size);
  memcpy(node->data, data, list->data_size);

  return LIST_OK;
}

void js_node_free(JS_NODE *node) {
  if (node) {
    free(node->data);
    free(node);
  }
}

uint32_t js_apply(JS_LIST *list, uint32_t (*cb_func)(void *)) {
  JS_NODE *node;
  if (list->head == NULL) return LIST_NONE;

  node = list->head;
  while (node) {
    cb_func(node->data);
    node = node->next;
  }

  return LIST_OK;
}

JS_LIST *js_create_linked_list(uint32_t data_size,
                          uint32_t (*comp_func)(void *, void *),
                          uint32_t mode) {
  JS_LIST *list;
  list = (JS_LIST *)malloc(sizeof(JS_LIST));
  if (list == NULL) return NULL;
  memset(list, 0x00, sizeof(JS_LIST));

  list->data_size = data_size;

  if (comp_func) {
    list->comp_func = comp_func;
  } else {
    list->comp_func = default_comp_func;
  }

  list->add_func = js_add_func;

  return list;
}

uint32_t js_destroy_linked_list(JS_LIST *list) {
  JS_NODE *node;
  JS_NODE *next;

  node = list->head;
  next = NULL;
  while(node) {
    if (node->next) {
      next = node->next;
    }
    js_node_free(node);
    node = next;
  }

  free(list);

  return LIST_OK;
}

uint32_t js_add_list(JS_LIST *list, void *data) {
  list->num_of_elements++;
  return list->add_func(list, data);
}

uint32_t js_remove_list(JS_LIST *list, void *data) {
  JS_NODE *node;
  JS_NODE *prev_node;

  node = list->head;
  prev_node = NULL;
  while(node) {
    if (list->comp_func(node->data, data)) {
      if (prev_node) {
        prev_node->next = node->next;
      } else {
        if (node->next) list->head = node->next;
        else list->head = NULL;
      }
      list->num_of_elements--;
      js_node_free(node);

      return LIST_OK;
    }
    prev_node = node;
    node = node->next;
  }

  return LIST_OK;
}
