#ifndef __JS_HASH_TABLE_HDR_
#define __JS_HASH_TABLE_HDR_
#include <stdio.h>
#include <stdint.h>

#include "xxhash.h"
#include "js_linked_list.h"

#define XXH32_HASH_SEED 0xF30AABE1

typedef struct _HASH_DATA {
  uint32_t col_count;
  JS_LIST *list;
} HASH_BUCKET;

typedef struct _HASH_TABLE {
  uint32_t max_count;
  uint32_t data_size;
  uint32_t key_size;
  uint32_t (*h_func)(uint8_t *, uint32_t);
  HASH_BUCKET *bucket;
  uint32_t cur_data_count;
} HASH_TABLE;

uint32_t js_hash_func(uint8_t *buffer, uint32_t len);
HASH_TABLE *create_jshash(uint32_t max_count,
                          uint32_t data_size,
                          uint32_t key_size,
                          uint32_t(*h_func)(uint8_t *, uint32_t));
uint32_t js_get_hv(HASH_TABLE *hash_t, void *data);
uint32_t is_exist_data_by_hv(HASH_TABLE *hash_t,
                             uint32_t hv,
                             void *data);
uint32_t insert_data_by_hv(HASH_TABLE *hash_t, uint32_t hv, void *data);
uint32_t get_data_by_hv(HASH_TABLE *hash_t,
                        uint32_t hv,
                        void *data);
uint32_t find_data_by_hv(HASH_TABLE *hash_t,
                         uint32_t hv,
                         void *data,
                         void *out_data);
uint32_t remove_data_by_hv(HASH_TABLE *hash_t,
                         uint32_t hv,
                         void *data);
void destroy_jshash(HASH_TABLE *table);
uint32_t get_element_hash(HASH_TABLE *hash_t);

#endif  // __JS_HASH_TABLE_HDR_
