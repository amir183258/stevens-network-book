/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function sets the sockaddr address to a pointer.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "unp.h"

void sock_set_addr(struct sockaddr *sa, socklen_t salen, const void *addr) {
	switch (sa->sa_family) {
	case AF_INET:
		struct sockaddr_in *sin = (struct sockaddr_in *) sa;

		memcpy(&sin->sin_addr, addr, sizeof(struct in_addr));

		return;
#ifdef IPV6
	case AF_INET6:
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa;

		memcpy(&sin6->sin6_addr, addr, sizeof(struct in6_addr));
		return;
#endif
	}

	return;
}
