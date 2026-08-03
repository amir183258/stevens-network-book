/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  Wrapper functions for our own library functions. Most are
 * 	     included in the source file for the function itself.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>

#include <arpa/inet.h>

#include "unp.h"

const char* Inet_ntop(int family, const void *addrptr, char *strptr, size_t len) {
	const char *ptr;

	if (strptr == NULL) // check for old code
		err_quit("NULL 3rd argument to inet_ntop");
	if ( (ptr = inet_ntop(family, addrptr, strptr, len)) == NULL) // sets errno
		err_sys("inet_ntop error");

	return ptr;
}

void Inet_pton(int family, const char *strptr, void *addrptr) {
	int n;

	if ( (n = inet_pton(family, strptr, addrptr)) < 0)
		err_sys("inet_pton error for %s", strptr); // errno set
	else if (n == 0)
		err_quit("inet_ptrn error for %s", strptr); // errno not set

	// nothing to return
}
