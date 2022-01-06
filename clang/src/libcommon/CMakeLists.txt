CMAKE_MINIMUM_REQUIRED (VERSION 3.19)

PROJECT ("GotoUnivers")

ADD_DEFINITIONS("-g -O3 -Wall")

INCLUDE_DIRECTORIES( . )

ADD_LIBRARY (common STATIC
    js_stack.c
    js_queue.c
    js_linked_list.c
    js_hash_table.c
    xxhash.c
    libcommon.c
    version.c
    js_debug.c)
