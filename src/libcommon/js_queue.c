#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "js_queue.h"
#include "js_debug.h"

uint32_t check_cnt(JS_QUEUE_t *queue) {
  if (queue_elements(queue) >= queue->max_num) {
    return QUEUE_FAIL;
  }
  return QUEUE_OK;
}

JS_QUEUE_t *create_queue(uint32_t size, uint32_t num) {
  JS_QUEUE_t *queue;

  queue = (JS_QUEUE_t *)malloc(sizeof(JS_QUEUE_t));
  if (queue == NULL) return NULL;
  memset(queue, 0x00, sizeof(JS_QUEUE_t));

  queue->max_num = num;
  queue->data_size = size;
  queue->data = malloc(size * num);
  memset(queue->data, 0x00, size*num);
  queue->head = &queue->data[0];
  queue->tail = &queue->data[0];

  return queue;
}

uint32_t js_enqueue(JS_QUEUE_t *queue, void *data) {
  if (check_cnt(queue) == QUEUE_FAIL) {
    js_print_debug("[%s:%d] Queue Full\n", __func__, __LINE__);
    return QUEUE_FAIL;
  }

  memcpy(queue->head, data, queue->data_size);
  queue->num_of_elements++;
  queue->head_idx++;

  if (queue->head_idx >= queue->max_num) {
    queue->head_idx = 0;
    queue->head = &queue->data[0];
  } else {
    queue->head += queue->data_size;
  }

  return QUEUE_OK;
}

uint32_t js_dequeue(JS_QUEUE_t *queue, void *data) {
  if (queue_elements(queue) == 0) {
    js_print_debug("[%s:%d] Queue Empty\n", __func__, __LINE__);
    return QUEUE_NONE;
  }

  memcpy(data, queue->tail, queue->data_size);
  queue->num_of_elements--;
  queue->tail_idx++;

  if (queue->tail_idx >= queue->max_num) {
    queue->tail_idx = 0;
    queue->tail = &queue->data[0];
  } else {
    queue->tail += queue->data_size;
  }

  return QUEUE_OK;
}

uint32_t queue_elements(JS_QUEUE_t *queue) {
  if (queue) return queue->num_of_elements;
  return 0;
}
