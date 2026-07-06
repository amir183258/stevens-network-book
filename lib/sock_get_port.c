/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function extracts port from a socket address structure and
 * 	     returns it in network representation.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <sys/socket.h>
#include <netinet/in.h>

#include "unp.h"

int sock_get_port(const struct sockaddr *sa, socklen_t salen) {
	switch (sa->sa_family) {
	case AF_INET:
		struct sockaddr_in *sin = (struct sockaddr_in *) sa; // <netinet/in.h>
		return sin->sin_port;

#ifdef IPV6
	case AF_INET6:
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa; // <netinet/in.h>
		return sin6->sin6_port;
#endif
	}

	return -1;
}
