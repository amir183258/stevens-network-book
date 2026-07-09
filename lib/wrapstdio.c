/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This file contains standard I/O wrapper functions.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "unp.h"

void Fclose(FILE *fp) {
	if (fclose(fp) != 0)
		err_sys("fclose error");
}

char* Fgets(char *ptr, int n, FILE *stream) {
	char *rptr;

	if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		err_sys("fgets error");

	return rptr;
}

void Fputs(const char *ptr, FILE *stream) {
	if (fputs(ptr, stream) == EOF)
		err_sys("fputs error");
}
