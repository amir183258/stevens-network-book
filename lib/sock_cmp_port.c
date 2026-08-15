/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function compares 2 sockaddr ports and return the result.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <sys/socket.h>
#include <netinet/in.h>

#include "unp.h"

int sock_cmp_port(const struct sockaddr *sa1, const struct sockaddr *sa2, socklen_t salen) {
	if (sa1->sa_family != sa2->sa_family)
		return -1;

	switch (sa1->sa_family) {
	case AF_INET:
		return ( ((struct sockaddr_in *) sa1)->sin_port ==
				((struct sockaddr_in *) sa2)->sin_port);
#ifdef IPV6
	case AF_INET6:
		return ( ((struct sockaddr_in6 *) sa1)->sin6_port ==
				((struct sockaddr_in6 *) sa2)->sin6_port);
#endif
	}

	return -1;
}
