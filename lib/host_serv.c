/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function initializes a hints structure, calls getaddrinfo(),
 * 	     and returns a null pointer if an error occurs.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>

#include <netdb.h>

#include "unp.h"

struct addrinfo* host_serv(const char *host, const char *serv, int family, int socktype) {
	int n;
	struct addrinfo hints, *res;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_CANONNAME; // always return canonical name
	hints.ai_family = family; // AF_UNSPECT, AF_INET, AF_INET6, etc.
	hints.ai_socktype= socktype; // 0, SOCK_STREAM, SOCK_DGRAM, etc.

	if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		return NULL;

	return res; // return pointer to first on linked list
}
