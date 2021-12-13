#ifndef __JS_QUEUE_HDR_
#define __JS_QUEUE_HDR_
#include <stdint.h>

#define QUEUE_FAIL 0
#define QUEUE_OK 1
#define QUEUE_NONE 2

typedef struct _JS_QUEUE_t {
  uint32_t num_of_elements;
  uint32_t max_num;
  uint32_t data_size;
  uint32_t head_idx;
  uint32_t tail_idx;
  void *data;
  void *head;
  void *tail;
} JS_QUEUE_t;

JS_QUEUE_t *create_queue(uint32_t size, uint32_t num);
void destroy_queue(JS_QUEUE_t *queue);
uint32_t js_enqueue(JS_QUEUE_t *queue, void *data);
uint32_t js_dequeue(JS_QUEUE_t *queue, void *data);
uint32_t queue_elements(JS_QUEUE_t *queue);

#endif  // __JS_QUEUE_HDR_
