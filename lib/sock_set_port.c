/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function sets the port of a socket address.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <sys/socket.h>
#include <netinet/in.h>

#include "unp.h"

void sock_set_port(struct sockaddr *sa, socklen_t salen, int port) {
	switch (sa->sa_family) {
	case AF_INET:
		struct sockaddr_in *sin = (struct sockaddr_in *) sa; // <netinet/in.h>

		sin->sin_port = port;
		return;

#ifdef IPV6
	case AF_INET6:
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa; // <netinet/in.h>

		sin6->sin6_port = port;
		return;
#endif
	}

	return;
}
