/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function reads data from a socket descriptor and write it
 * 	     on the same socket again. This function is used for echo server
 * 	     program.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>

#include <errno.h>

#include "unp.h"

void str_echo(int sockfd) {
	ssize_t n;
	char buf[MAXLINE];

again:
	while ( (n = read(sockfd, buf, MAXLINE)) > 0)
		Writen(sockfd, buf, n);

	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("str_echo: read error");
}
