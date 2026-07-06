/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  Returns address in host representation.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "unp.h"

char* sock_ntop_host(const struct sockaddr *sa, socklen_t salen) {
	// Unix domain is largest
	static char str[128];

	switch (sa->sa_family) {
	case AF_INET:
		struct sockaddr_in *sin = (struct sockaddr_in *) sa; // <netinet/in.h>

		if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL) // <arpa/inet.h>
			return NULL;
		return str;

#ifdef IPV6
	case AF_INET6:
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa; // <netinet/in.h>

		if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL) // <arpa/inet.h>
			return NULL;
		return str;
#endif

		/* TODO: there are other families here in main code; Maybe neede for future chapters of the book */
	}

	return NULL;
}

char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen) {
	char *ptr;

	if ( (ptr = sock_ntop_host(sa, salen)) == NULL)
		err_sys("sock_ntop_host error"); // inet_ntop() sets errno
	return ptr;
}
