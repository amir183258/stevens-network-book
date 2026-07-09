/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project
 * Purpose:  This file contains the function to handle SIGCHLD signal in 
 * 	     server.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>

#include <sys/wait.h>
#include <signal.h>

void sig_chld(int signo) {
	pid_t pid;
	int stat;

	pid = wait(&stat);
	printf("child %d terminated\n", pid);

	return;
}
