/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function returns socket family of a socket descriptor.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <sys/socket.h>

#include "unp.h"

int sockfd_to_family(int sockfd) {
	struct sockaddr_storage ss;
	socklen_t len;

	len = sizeof(ss);
	if (getsockname(sockfd, (SA *) &ss, &len) < 0)
		return -1;
	return ss.ss_family;
}

int Sockfd_to_family(int sockfd) {
	int rc;

	if ( (rc = sockfd_to_family(sockfd)) < 0)
		err_sys("sockfd_to_family error");

	return rc;
}
