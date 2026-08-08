cmake_minimum_required(VERSION 3.16)
project(unp_examples C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

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
	lib/dg_echo.c
	lib/dg_cli.c
	lib/host_serv.c
	lib/tcp_connect.c
	lib/tcp_listen.c
	lib/udp_client.c
	lib/udp_connect.c
	lib/udp_server.c
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

##

add_executable(tcpservselect01
	src/tcpdiserv/tcpservselect01.c
)
target_link_libraries(tcpservselect01
	unp
)
set_target_properties(tcpservselect01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tcpdiserv
)

##

add_executable(tcpservpoll01
	src/tcpdiserv/tcpservpoll01.c
)
target_link_libraries(tcpservpoll01
	unp
)
set_target_properties(tcpservpoll01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tcpdiserv
)

##

add_executable(checkopts
	src/sockopt/checkopts.c
)
target_link_libraries(checkopts
	unp
)
set_target_properties(checkopts PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sockopt
)

##

add_executable(exercise_7_1
	src/exercises/exercise_7_1.c
)
target_link_libraries(exercise_7_1
	unp
)
set_target_properties(exercise_7_1 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/exercises
)

##

add_executable(exercise_7_2_client
	src/exercises/exercise_7_2/exercise_7_2_client.c
)
target_link_libraries(exercise_7_2_client
	unp
)
set_target_properties(exercise_7_2_client PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/exercises/exercise_7_2
)

##

add_executable(exercise_7_3_tcpcli01
	src/exercises/exercise_7_3/exercise_7_3_tcpcli01.c
)
target_link_libraries(exercise_7_3_tcpcli01
	unp
)
set_target_properties(exercise_7_3_tcpcli01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/exercises/exercise_7_3
)

##

add_executable(udpserv01
	src/udpcliserv/udpserv01.c
)
target_link_libraries(udpserv01
	unp
)
set_target_properties(udpserv01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/udpcliserv
)

##

add_executable(udpcli01
	src/udpcliserv/udpcli01.c
)
target_link_libraries(udpcli01
	unp
)
set_target_properties(udpcli01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/udpcliserv
)

##

add_executable(udpcli02
	src/udpcliserv/udpcli01.c
	src/udpcliserv/dgcliaddr.c
)
target_link_libraries(udpcli02
	unp
)
set_target_properties(udpcli02 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/udpcliserv
)

##

add_executable(udpcli04
	src/udpcliserv/udpcli01.c
	src/udpcliserv/dgcliconnect.c
)
target_link_libraries(udpcli04
	unp
)
set_target_properties(udpcli04 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/udpcliserv
)

##

add_executable(udpcli06
	src/udpcliserv/udpcli01.c
	src/udpcliserv/dgcliloop.c
)
target_link_libraries(udpcli06
	unp
)
set_target_properties(udpcli06 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/udpcliserv
)

##

add_executable(udpserv06
	src/udpcliserv/udpserv01.c
	src/udpcliserv/dgecholoop1.c
)
target_link_libraries(udpserv06
	unp
)
set_target_properties(udpserv06 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/udpcliserv
)

##

add_executable(udpservselect01
	src/udpcliserv/udpservselect01.c
	src/udpcliserv/sigchldwaitpid.c
)
target_link_libraries(udpservselect01
	unp
)
set_target_properties(udpservselect01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/udpcliserv
)

##

add_executable(sctpserv01
	src/sctp/sctpserv01.c
	src/sctp/sctp_getnostrm.c
	src/sctp/sctp_addr_to_associd.c
	src/sctp/sctp_wrapper.c
)
target_link_libraries(sctpserv01 PRIVATE
	unp
	sctp
)
set_target_properties(sctpserv01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sctp
)

##

add_executable(sctpclient01
	src/sctp/sctpclient01.c
	src/sctp/sctp_wrapper.c
	src/sctp/sctp_strcli.c
	src/sctp/sctp_strcliecho2.c
)
target_link_libraries(sctpclient01 PRIVATE
	unp
	sctp
)
set_target_properties(sctpclient01 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sctp
)

##

add_executable(sctpserv02
	src/sctp/sctpserv02.c
	src/sctp/sctp_getnostrm.c
	src/sctp/sctp_addr_to_associd.c
	src/sctp/sctp_wrapper.c
)
target_link_libraries(sctpserv02 PRIVATE
	unp
	sctp
)
set_target_properties(sctpserv02 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sctp
)

##

add_executable(sctpserv03
	src/sctp/sctpserv03.c
	src/sctp/sctp_getnostrm.c
	src/sctp/sctp_addr_to_associd.c
	src/sctp/sctp_wrapper.c
)
target_link_libraries(sctpserv03 PRIVATE
	unp
	sctp
)
set_target_properties(sctpserv03 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sctp
)

##

add_executable(sctpclient02
	src/sctp/sctpclient02.c
	src/sctp/sctp_wrapper.c
	src/sctp/sctp_strcli.c
	src/sctp/sctp_strcliecho2.c
)
target_link_libraries(sctpclient02 PRIVATE
	unp
	sctp
)
set_target_properties(sctpclient02 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sctp
)

##

add_executable(hostent
	src/names/hostent.c
)
target_link_libraries(hostent PRIVATE
	unp
)
set_target_properties(hostent PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/names
)

##

add_executable(daytimetcpcli1
	src/names/daytimetcpcli1.c
)
target_link_libraries(daytimetcpcli1 PRIVATE
	unp
)
set_target_properties(daytimetcpcli1 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/names
)

##

add_executable(daytimetcpcli_1_2
	src/names/daytimetcpcli_1_2.c
)
target_link_libraries(daytimetcpcli_1_2 PRIVATE
	unp
)
set_target_properties(daytimetcpcli_1_2 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/names
)

##

add_executable(daytimetcpsrv1_2
	src/names/daytimetcpsrv1_2.c
)
target_link_libraries(daytimetcpsrv1_2 PRIVATE
	unp
)
set_target_properties(daytimetcpsrv1_2 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/names
)

##

add_executable(daytimetcpsrv2
	src/names/daytimetcpsrv2.c
)
target_link_libraries(daytimetcpsrv2 PRIVATE
	unp
)
set_target_properties(daytimetcpsrv2 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/names
)

##

add_executable(daytimeudpcli1
	src/names/daytimeudpcli1.c
)
target_link_libraries(daytimeudpcli1 PRIVATE
	unp
)
set_target_properties(daytimeudpcli1 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/names
)
