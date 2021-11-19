CMAKE_MINIMUM_REQUIRED (VERSION 3.19)

PROJECT ("GotoUnivers")

ADD_DEFINITIONS("-Wall")

INCLUDE_DIRECTORIES( ../libcommon/ )

ADD_LIBRARY (common STATIC
    js_stack.c
    js_queue.c
    js_linked_list.c
    js_debug.c)
