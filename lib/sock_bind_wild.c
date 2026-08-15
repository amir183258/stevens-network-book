/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This file binds an ephemeral port (random port) to a socket file
 * 	     descriptor;
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "./unp.h"

int sock_bind_wild(int sockfd, int family) {
	socklen_t len;

	switch (family) {
	case AF_INET:
		struct sockaddr_in sin;

		bzero(&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = htonl(INADDR_ANY);

		/* bind ephemeral port */
		sin.sin_port = htons(0);

		if (bind(sockfd, (SA *) &sin, sizeof(sin)) < 0)
			return -1;
		len = sizeof(sin);
		if (getsockname(sockfd, (SA *) &sin, &len) < 0)
			return  -1;
		return sin.sin_port;

#ifdef IPV6
	case AF_INET6:
		struct sockaddr_in6 sin6;

		bzero(&sin6, sizeof(sin6));
		sin6.sin6_family = AF_INET6;
		sin6.sin6_addr = in6addr_any;
		sin6.sin6_port = htons(0);

		if (bind(sockfd, (SA *) &sin6, sizeof(sin6)) < 0)
			return -1;
		len = sizeof(sin6);
		if (getsockname(sockfd, (SA *) &sin6, &len) < 0)
			return -1;
		return sin6.sin6_port;

#endif
	}

	return -1;
}

int Sock_bind_wild(int sockfd, int family) {
	int port;

	if ( (port = sock_bind_wild(sockfd, family)) < 0)
		err_sys("sock_bind_wild error");

	return port;
}
