/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  I think this function sets a sockaddress address to local host.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <sys/socket.h>
#include <netinet/in.h>

#include "unp.h"

void sock_set_wild(struct sockaddr *sa, socklen_t salen) {
	const void *wildptr;

	switch (sa->sa_family) {
	case AF_INET:
		static struct in_addr in4addr_any;

		in4addr_any.s_addr = htonl(INADDR_ANY);
		wildptr = &in4addr_any;
		break;

#ifdef IPV6
	case AF_INET6:
		wildptr = &in6addr_any;
		break;
#endif

	default:
		return;
	}
	sock_set_addr(sa, salen, wildptr);

	return;
}
