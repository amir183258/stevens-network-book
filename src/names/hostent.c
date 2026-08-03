/******************************************************************************
 *
 * Project:  Stevens Book - Get Host By Name Project
 * Purpose:  This function returns the names of a host using gethostbyname().
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <netdb.h>

#include "unp.h"

int main(int argc, char **argv) {
	char *ptr, **pptr;
	char str[INET_ADDRSTRLEN];
	struct hostent *hptr;

	while (--argc > 0) {
		ptr = *++argv;
		if ( (hptr = gethostbyname(ptr)) == NULL) {
			err_msg("gethostbyname error for host: %s: %s", ptr,
					hstrerror(h_errno));
			continue;
		}
		printf("official hostname: %s\n", hptr->h_name);

		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("\talias: %s\n", *pptr);

		switch (hptr->h_addrtype) {
		case AF_INET:
			pptr = hptr->h_addr_list;
			for ( ; *pptr != NULL; pptr++)
				printf("\taddress: %s\n",
						Inet_ntop(hptr->h_addrtype,
							*pptr, str, sizeof(str)));
			break;
		default:
			err_ret("unknown address type");
		}
	}

	exit(0);
}
