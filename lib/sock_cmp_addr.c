/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function compares 2 sockaddr and return the result.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "unp.h"

int sock_cmp_addr(const struct sockaddr *sa1, const struct sockaddr *sa2, socklen_t salen) {
	if (sa1->sa_family != sa2->sa_family)
		return -1;

	switch (sa1->sa_family) {
	case AF_INET:
		return (memcmp( &((struct sockaddr_in *) sa1)->sin_addr,
					&((struct sockaddr_in *) sa2)->sin_addr,
					sizeof(struct in_addr)));

#ifdef IPV6
	case AF_INET6:
		return (memcmp( &((struct sockaddr_in6 *) sa1)->sin6_addr,
					&((struct sockaddr_in6 *) sa2)->sin6_addr,
					sizeof(struct in6_addr)));

#endif
	}

	/* there are other code here in main files, but we don't need it right now */

	return -1;
}
