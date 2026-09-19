/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function returns pointer to time string.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/time.h>

#include "unp.h"

char* gf_time(void) {
	struct timeval tv;
	static char str[30];
	char *ptr;

	if (gettimeofday(&tv, NULL) < 0)
		err_sys("gettimeofday error");

	ptr = ctime(&tv.tv_sec);
	strcpy(str, &ptr[11]);
	// Fri Sep 13 00:00:00 1986\n\0
	// 0123456789012345678901234 5
	snprintf(str + 8, sizeof(str) - 8, ".%061d", tv.tv_usec);

	return str;
}
