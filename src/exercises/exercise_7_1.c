#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "unp.h"

int main() {
	int fd;
	int len;

	socklen_t rcv_buf_size;
	socklen_t snd_buf_size;

	// tcp
	fd = Socket(AF_INET, SOCK_STREAM, 0);

	len = sizeof(int);
	if (getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcv_buf_size, &len) < 0)
		err_ret("getsockopt error");
	else
		printf("TCP receive buffer size: %d\n", rcv_buf_size);

	if (getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &snd_buf_size, &len) < 0)
		err_ret("getsockopt error");
	else
		printf("TCP send buffer size: %d\n", snd_buf_size);

	Close(fd);

	// udp
	fd = Socket(AF_INET, SOCK_DGRAM, 0);

	len = sizeof(int);
	if (getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcv_buf_size, &len) < 0)
		err_ret("getsockopt error");
	else
		printf("UDP receive buffer size: %d\n", rcv_buf_size);

	if (getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &snd_buf_size, &len) < 0)
		err_ret("getsockopt error");
	else
		printf("UDP send buffer size: %d\n", snd_buf_size);

	Close(fd);

	// sctp
	//fd = Socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
	fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);

	len = sizeof(int);
	if (getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcv_buf_size, &len) < 0)
		err_ret("getsockopt error");
	else
		printf("SCTP receive buffer size: %d\n", rcv_buf_size);

	if (getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &snd_buf_size, &len) < 0)
		err_ret("getsockopt error");
	else
		printf("SCTP send buffer size: %d\n", snd_buf_size);

	Close(fd);

	return 0;
}
