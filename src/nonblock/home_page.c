/******************************************************************************
 *
 * Project:  Stevens Book - Non-blocking Sockets
 * Purpose:  This function starts a TCP connection to a web server. Then it
 * 	     sends a GET request to get the homepage. Finally it closes the
 * 	     file descriptor.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>

#include "web.h"
#include "unp.h"

void home_page(const char *host, const char *fname) {
	int fd, n;
	char line[MAXLINE];

	fd = Tcp_connect(host, SERV); // blocking connect()

	n = snprintf(line, sizeof(line), GET_CMD, fname);
	Writen(fd, line, n);

	for ( ; ; ) {
		if ( (n = Read(fd, line, MAXLINE)) == 0)
			break; // server closed connection

		printf("read %d bytes of home page\n", n);
		// do whatever with data
	}

	printf("end-of-file on home page\n");
	Close(fd);
}
