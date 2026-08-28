/******************************************************************************
 *
 * Project:  Stevens Book - Advanced I/O
 * Purpose:  This is the str_echo() function recoded to use standard I/O.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "unp.h"

void str_echo(int sockfd) {
	char line[MAXLINE];
	FILE *fpin, *fpout;

	fpin = Fdopen(sockfd, "r");
	fpout = Fdopen(sockfd, "w");

	// be careful here; client may need to read bytes from server
	// and it will be blocked here because server use buffer.
	// so the results are not exactly what in the book.
	while (Fgets(line, MAXLINE, fpin) != NULL) {
		Fputs(line, fpout);

		// the standard I/O functions are fully buffered for sockets.
		// so we have to use fflush().
		//fflush(fpout);
	}
}
