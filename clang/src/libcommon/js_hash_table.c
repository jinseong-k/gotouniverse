#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "xxhash.h"
#include "js_linked_list.h"
#include "js_hash_table.h"

#define KJS_DEBUG
#ifdef KJS_DEBUG
static uint64_t g_collision = 0;
#endif  // KJS_DEBUG

XXH32_hash_t seed = XXH32_HASH_SEED;

uint32_t js_hash_func(uint8_t *buffer, uint32_t len) {
  return XXH32(buffer, len, seed);
}

HASH_TABLE *create_jshash(uint32_t max_count,
                          uint32_t data_size,
                          uint32_t key_size,
                          uint32_t(*h_func)(uint8_t *, uint32_t)) {
  HASH_TABLE *hash_t;

  if ((max_count == 0) || (data_size == 0) || (key_size == 0)) {
    return NULL;
  }

  hash_t = (HASH_TABLE *)malloc(sizeof(HASH_TABLE));
  if (hash_t == NULL) return NULL;
  memset(hash_t, 0x00, sizeof(HASH_TABLE));

  fprintf(stderr, "[%s:%d]\tCreate js hash table\n"
                  "\t\t\tmax count : [%u]\n"
                  "\t\t\tdata size : [%u]\n"
                  "\t\t\tkey sie : [%u]\n",
                  __func__, __LINE__,
                  max_count, data_size, key_size);
  hash_t->bucket = (HASH_BUCKET *)malloc(sizeof(HASH_BUCKET)*max_count);
  if (hash_t->bucket == NULL) {
    free(hash_t);
    return NULL;
  }
  memset(hash_t->bucket, 0x00, sizeof(HASH_BUCKET)*max_count);

  if (h_func) {
    hash_t->h_func = h_func;
  } else {
    hash_t->h_func = js_hash_func;
  }

  hash_t->max_count = max_count;
  hash_t->data_size = data_size;
  hash_t->key_size = key_size;
  hash_t->cur_data_count = 0;

  return hash_t;
}

uint32_t is_exist_data_by_hv(HASH_TABLE *hash_t,
                             uint32_t hv,
                             void *data) {
  uint32_t idx;
  HASH_BUCKET *bucket;

  idx = hv%(hash_t->max_count);
  bucket = &hash_t->bucket[idx];

  if (bucket->col_count) {
    if (js_find_data(bucket->list, data)) {
      // Exist data in hash table
      return 1;
    }
  }
  return 0;
}

uint32_t js_get_hv(HASH_TABLE *hash_t, void *data) {
  return hash_t->h_func(data, hash_t->data_size);
}

uint32_t find_data_by_hv(HASH_TABLE *hash_t,
                         uint32_t hv,
                         void *data,
                         void *out_data) {
  uint32_t idx;
  HASH_BUCKET *bucket;
  void *ret_data;

  idx = hv%(hash_t->max_count);
  bucket = &hash_t->bucket[idx];
  if (bucket->col_count) {
    ret_data = js_find_data(bucket->list, data);
    if (ret_data) {
      memcpy(out_data, ret_data, hash_t->data_size);
      return 1;
    }
  }

  return 0;
}

uint32_t insert_data_by_hv(HASH_TABLE *hash_t, uint32_t hv, void *data) {
  uint32_t idx;
  HASH_BUCKET *bucket;
  void *ret_data;
  
  idx = hv%(hash_t->max_count);
  bucket = &(hash_t->bucket[idx]);

  if (get_element_hash(hash_t) > hash_t->max_count) {
    // TODO remove some data
    return 0;
  }

  if (bucket->col_count) {
    ret_data = js_find_data(bucket->list, data);
    if (ret_data) {
      // Already exist in hash.
      // Do nothing.
      return 0;
    } else {
      bucket->col_count++;
      hash_t->cur_data_count++;
#ifdef KJS_DEBUG
      g_collision++;
#endif  // KJS_DEBUG
      js_add_list(bucket->list, data);
    }
  } else {
    bucket->col_count++;
    hash_t->cur_data_count++;
    bucket->list = js_create_linked_list(hash_t->data_size, NULL, LIST_NORM);
    js_add_list(bucket->list, data);
  }

  return 1;
}

uint32_t remove_data_by_hv(HASH_TABLE *hash_t, uint32_t hv, void *data) {
  uint32_t idx;
  HASH_BUCKET *bucket;

  idx = hv%(hash_t->max_count);
  bucket = &(hash_t->bucket[idx]);
  if (bucket->col_count) {
    js_remove_list(bucket->list, data);
    bucket->col_count--;
    hash_t->cur_data_count--;

    return 1;
  }

  return 0;
}

void destroy_jshash(HASH_TABLE *hash_t) {
  uint32_t i=0;
  if (hash_t) {
    for (i=0; i<hash_t->max_count; i++){
      if (hash_t->bucket[i].list) {
        js_destroy_linked_list(hash_t->bucket[i].list);
      }
    }
    free(hash_t);
  }
}

uint32_t get_element_hash(HASH_TABLE *hash_t) {
  return hash_t->cur_data_count;
}
