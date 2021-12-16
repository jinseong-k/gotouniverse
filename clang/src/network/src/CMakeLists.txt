CMAKE_MINIMUM_REQUIRED (VERSION 3.19)

PROJECT ("GotoUnivers")

ADD_DEFINITIONS("-g -O3 -Wall")

INCLUDE_DIRECTORIES( . )
LINK_DIRECTORIES( . )

ADD_EXECUTABLE ( socket_server tcp_socket_server.c )
ADD_EXECUTABLE ( socket_client tcp_socket_client.c )
#TARGET_LINK_LIBRARIES( test common )
