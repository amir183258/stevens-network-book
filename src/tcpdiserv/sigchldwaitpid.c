/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project
 * Purpose:  This file contains the function to handle SIGCHLD signal in 
 * 	     server. It manages children in a better way than sigchldwait.c.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>

#include <sys/wait.h>
#include <signal.h>

#include "unp.h"

void sig_chld(int signo) {
	pid_t pid;
	int stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}
