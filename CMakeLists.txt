cmake_minimum_required(VERSION 3.16)
project(unp_examples C)

set(CMAKE_C_STANDARD 11)

# unp library
add_library(unp STATIC
	lib/error.c
	lib/wrapsock.c
	lib/wrapunix.c
	lib/sock_ntop.c
	lib/sock_bind_wild.c
	lib/sock_cmp_addr.c
	lib/sock_cmp_port.c
	lib/sock_get_port.c
	lib/sock_ntop_host.c
	lib/sock_set_addr.c
)

target_include_directories(unp PUBLIC
	${CMAKE_SOURCE_DIR}/lib
)

# executables
add_executable(daytimetcpcli
	src/intro/daytimetcpcli.c
)
target_link_libraries(daytimetcpcli
	unp
)
set_target_properties(daytimetcpcli PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/intro
)

##

add_executable(daytimetcpcliv6
	src/intro/daytimetcpcliv6.c
)
target_link_libraries(daytimetcpcliv6
	unp
)
set_target_properties(daytimetcpcliv6 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/intro
)

##

add_executable(daytimetcpsrv
	src/intro/daytimetcpsrv.c
)
target_link_libraries(daytimetcpsrv
	unp
)
set_target_properties(daytimetcpsrv PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/intro
)

##

add_executable(byteorder
	src/intro/byteorder.c
)
target_link_libraries(byteorder
	unp
)
set_target_properties(byteorder PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/intro
)
