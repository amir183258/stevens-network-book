/******************************************************************************
 *
 * Project:  Stevens Book - Non-blocking Sockets
 * Purpose:  This function sends request to the server and waits for the reply
 * 	     from the server.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>

#include "web.h"
#include "unp.h"

void write_get_cmd(struct file *fptr) {
	int n;
	char line[MAXLINE];

	n = snprintf(line, sizeof(line), GET_CMD, fptr->f_name);
	Writen(fptr->f_fd, line, n);
	printf("wrote %d bytes for %s\n", n, fptr->f_name);

	fptr->f_flags = F_READING; // clears F_CONNECTING
	FD_SET(fptr->f_fd, &rset); // will read server's reply
	if (fptr->f_fd > maxfd)
		maxfd = fptr->f_fd;
}
