#include <stdio.h>
#include <stdint.h>

#include "libcommon.h"
#include "xxhash.h"

#define TEST_CNT 8

typedef struct _TEST {
  uint32_t a;
  uint32_t b;
} TEST;

/**
 * Stack API test
 */
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

/**
 * Queue API test
 */
int queue_test() {
  int i;
  TEST data;
  TEST result;
  JS_QUEUE_t *queue = NULL;
  int count = TEST_CNT;

  queue = create_queue(sizeof(TEST), count);
  // Create Queue

  for (i=0; i<count+4; i++) {
    data.a = i;
    data.b = i+3;
    js_enqueue(queue, (void *)&data);
    // Enqueue
  }

  for (i=0; i<count+4; i++) {
    if (QUEUE_OK == js_dequeue(queue, (void *)&result)) {
      // Dequeue
      fprintf(stderr, "DEQ a : [%u] b : [%u]\n",
          result.a, result.b);
    }
  }

  destroy_queue(queue);
  // Destroy Queue

  return 1;
}

/**
 * Linked list API test
 */
uint32_t print_test_data(void *data) {
  TEST *t_data;
  t_data = (TEST *)data;
  fprintf(stderr, "data a : [%d] b : [%d]\n", t_data->a, t_data->b);

  return 1;
}

uint32_t list_cmp_func(void *a, void *b) {
  TEST *data_a = (TEST *)a;
  TEST *data_b = (TEST *)b;

  return data_a->a == data_b->a ? LIST_OK : LIST_FAIL;
}

int linked_list_test() {
  TEST data;
  JS_LIST *list;
  int count = TEST_CNT;
  int i;
  list = js_create_linked_list(sizeof(TEST), list_cmp_func, LIST_NORM);
  // Create Linked list

  for (i=0; i<count; i++) {
    data.a = i+1;
    data.b = i+12;
    js_add_list(list, &data);
    // Add Data
  }
  js_apply(list, print_test_data);
  // Callback function for all data
  fprintf(stderr, "list count : [%d]\n", js_list_elements(list));

  for (i=count-1; i>=0; i--) {
    data.a = i+1;
    data.b = i+12;
    js_remove_list(list, &data);
    // Remove Data
  }
  js_apply(list, print_test_data);
  fprintf(stderr, "list count : [%d]\n", js_list_elements(list));

  js_destroy_linked_list(list);
  // Destroy Linked list

  return 1;
}

int hash_table_test() {
  HASH_TABLE *hash_table;
  uint32_t max_count = 10;
  uint32_t data_size = sizeof(TEST);
  uint32_t key_size = sizeof(uint32_t);
  uint32_t hv;
  uint32_t ret;
  uint32_t count;
  TEST out_data;

  TEST data;
  data.a = 1;
  data.b = 2;

  /* Create Hash Table */
  hash_table = create_jshash(max_count,
                             data_size,
                             key_size,
                             NULL);
  if (hash_table == NULL) {
    fprintf(stderr, "Fail to create Hash table\n");
    return 0;
  }

  /* Get Hash value */
  hv = js_get_hv(hash_table, &data);

  /* No data check */
  ret = is_exist_data_by_hv(hash_table, hv, &data);
  fprintf(stderr, "[%s:%d] Exist? : [%d]\n",
                  __func__, __LINE__, ret);

  ret = find_data_by_hv(hash_table, hv, &data, &out_data);
  fprintf(stderr, "[%s:%d] Find? : [%d]\n",
                  __func__, __LINE__, ret);

  count = get_element_hash(hash_table);
  fprintf(stderr, "[%s:%d] Elements : [%d]\n",
                  __func__, __LINE__, count);
  fprintf(stderr, "==========================\n");

  /* Insert Data test */
  ret = insert_data_by_hv(hash_table, hv, &data);
  fprintf(stderr, "[%s:%d] Insert? : [%d]\n",
                  __func__, __LINE__, ret);

  ret = is_exist_data_by_hv(hash_table, hv, &data);
  fprintf(stderr, "[%s:%d] Exist? : [%d]\n",
                  __func__, __LINE__, ret);

  ret = find_data_by_hv(hash_table, hv, &data, &out_data);
  fprintf(stderr, "[%s:%d] Find? : [%d]\n",
                  __func__, __LINE__, ret);

  count = get_element_hash(hash_table);
  fprintf(stderr, "[%s:%d] Elements : [%d]\n",
                  __func__, __LINE__, count);
  fprintf(stderr, "==========================\n");

  /* Insert Same data */
  ret = insert_data_by_hv(hash_table, hv, &data);
  fprintf(stderr, "[%s:%d] Insert? : [%d]\n",
                  __func__, __LINE__, ret);

  ret = is_exist_data_by_hv(hash_table, hv, &data);
  fprintf(stderr, "[%s:%d] Exist? : [%d]\n",
                  __func__, __LINE__, ret);

  ret = find_data_by_hv(hash_table, hv, &data, &out_data);
  fprintf(stderr, "[%s:%d] Find? : [%d]\n",
                  __func__, __LINE__, ret);

  count = get_element_hash(hash_table);
  fprintf(stderr, "[%s:%d] Elements : [%d]\n",
                  __func__, __LINE__, count);
  fprintf(stderr, "==========================\n");

  /* Remove Data */
  ret = remove_data_by_hv(hash_table, hv, &data);
  fprintf(stderr, "[%s:%d] Remove? : [%d]\n",
                  __func__, __LINE__, ret);

  ret = is_exist_data_by_hv(hash_table, hv, &data);
  fprintf(stderr, "[%s:%d] Exist? : [%d]\n",
                  __func__, __LINE__, ret);

  ret = find_data_by_hv(hash_table, hv, &data, &out_data);
  fprintf(stderr, "[%s:%d] Find? : [%d]\n",
                  __func__, __LINE__, ret);

  count = get_element_hash(hash_table);
  fprintf(stderr, "[%s:%d] Elements : [%d]\n",
                  __func__, __LINE__, count);
  fprintf(stderr, "==========================\n");
  
  /* Remove Not exist data */
  ret = remove_data_by_hv(hash_table, hv, &data);
  fprintf(stderr, "[%s:%d] Remove? : [%d]\n",
                  __func__, __LINE__, ret);

  /* Destroy Hash Table */
  destroy_jshash(hash_table);

  return 1;
}

/**
 * Main
 */
int main() {
  js_print_version();
  js_enable_debug();
#if 1
  stack_test();  // Stack Library Test
  queue_test();  // Queue Library Test
  linked_list_test();  // Linked-list Library Test
  hash_table_test();  // Hash table Library Test
#else
  hash_table_test();  // Hash table Library Test
#endif
}
