/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function waits for a descriptor to become readable using
 * 	     select().
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>

#include <sys/select.h>

#include "unp.h"

int readable_timeo(int fd, int sec) {
	fd_set rset;
	struct timeval tv;

	FD_ZERO(&rset);
	FD_SET(fd, &rset);

	tv.tv_sec = sec;
	tv.tv_usec = 0;

	// > 0 if descriptor is readable
	return select(fd + 1, &rset, NULL, NULL, &tv);
}

int Readable_timeo(int fd, int sec) {
	int n;
	if ( (n = readable_timeo(fd, sec)) < 0)
		err_sys("readable_timeo error");
	return n;
}
