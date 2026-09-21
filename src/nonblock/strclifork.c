/******************************************************************************
 *
 * Project:  Stevens Book - Non-blocking Sockets
 * Purpose:  This version of client uses fork() syscall.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "unp.h"

void str_cli(FILE *fp, int sockfd) {
	pid_t pid;
	char sendline[MAXLINE], recvline[MAXLINE];

	// child: server -> stdout
	if ( (pid = Fork()) == 0) {
		while (Readline(sockfd, recvline, MAXLINE) > 0)
			Fputs(recvline, stdout);

		kill(getppid(), SIGTERM); // in case parent still running
		exit(0);
	}

	// parent: stdin -> server
	while (Fgets(sendline, MAXLINE, fp) != NULL)
		Writen(sockfd, sendline, strlen(sendline));

	Shutdown(sockfd, SHUT_WR); // EOF on stdin, send FIN

	pause();

	return;
}
