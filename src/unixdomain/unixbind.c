/******************************************************************************
 *
 * Project:  Stevens Book - Unix Domain Sockets
 * Purpose:  This program creates a Unix domain socket, binds a pathname to
 * 	     it, and then calls getsockname and prints the bound pathname.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "unp.h"

int main(int argc, char **argv) {
	int sockfd;
	socklen_t len;
	struct sockaddr_un addr1, addr2;

	if (argc != 2)
		err_quit("usage: unixbind <pathname>");

	sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	unlink(argv[1]); // OK if this fails

	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = AF_LOCAL;
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) - 1);
	Bind(sockfd, (SA *) &addr1, SUN_LEN(&addr1));

	len = sizeof(addr2);
	Getsockname(sockfd, (SA *) &addr2, &len);
	printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);

	return 0;
}
