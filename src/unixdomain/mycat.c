/******************************************************************************
 *
 * Project:  Stevens Book - Unix Domain Sockets
 * Purpose:  This program copies a file to standard output. In this program
 * 	     we send a file descriptor from one process to another one.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include "unp.h"

int my_open(const char *, int);

int main(int argc, char **argv) {
	int fd, n;
	char buff[BUFFSIZE];

	if (argc != 2)
		err_quit("usage: mycat <pathname>");

	if ( (fd = my_open(argv[1], O_RDONLY)) < 0)
		err_sys("cannot open %s", argv[1]);

	while ( (n = Read(fd, buff, BUFFSIZE)) > 0)
		Write(STDOUT_FILENO, buff, n);

	exit(0);
}
