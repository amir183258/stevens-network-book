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

	while (Fgets(line, MAXLINE, fpin) != NULL) {
		Fputs(line, fpout);

		// the standar I/O functions are fully buffered for sockets.
		// so we have to use fflush().
		//fflush(fpout);
	}
}
