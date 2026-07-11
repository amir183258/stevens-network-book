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
	lib/sock_set_port.c
	lib/sock_set_wild.c
	lib/readn.c
	lib/writen.c
	lib/readline.c
	lib/sockfd_to_family.c
	lib/str_echo.c
	lib/wraplib.c
	lib/wrapstdio.c
	lib/str_cli.c
	lib/signal.c
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

##

add_executable(daytimetcpsrv1
	src/intro/daytimetcpsrv1.c
)
target_link_libraries(daytimetcpsrv1
	unp
)
set_target_properties(daytimetcpsrv1 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/intro
)

##

add_executable(tcpserv01
	src/tcpdiserv/tcpserv01.c
	src/tcpdiserv/sigchldwait.c
)
target_link_libraries(tcpserv01
	unp
)
set_target_properties(tcpserv01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tcpdiserv
)

##

add_executable(tcpcli01
	src/tcpdiserv/tcpcli01.c
)
target_link_libraries(tcpcli01
	unp
)
set_target_properties(tcpcli01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tcpdiserv
)

##

add_executable(tcpcli04
	src/tcpdiserv/tcpcli04.c

	#for sum client
	#src/tcpdiserv/str_cli09.c

	# for using select()
	# src/select/strcliselect01.c

	# for using shutdown()
	src/select/strcliselect02.c
)
target_link_libraries(tcpcli04
	unp
)
set_target_properties(tcpcli04 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tcpdiserv
)

##

add_executable(tcpserv04
	src/tcpdiserv/tcpserv04.c
	src/tcpdiserv/sigchldwaitpid.c

	# for sum server
	# src/tcpdiserv/str_ech08.c
	# src/tcpdiserv/str_ech09.c
)
target_link_libraries(tcpserv04
	unp
)
set_target_properties(tcpserv04 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tcpdiserv
)
