/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in SCTP
 * Purpose:  This function reads data from stdin and send it to a SCTP socket.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/sctp.h>

#include "unp.h"

void sctpstr_cli(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen) {
	struct sockaddr_in peeraddr;
	struct sctp_sndrcvinfo sri;
	char sendline[MAXLINE], recvline[MAXLINE];
	socklen_t len;
	int out_sz, rd_sz;
	int msg_flags;

	// declare functions
	int Sctp_recvmsg(int, void*, size_t, struct sockaddr*, socklen_t*,
			struct sctp_sndrcvinfo*, int*);
	int Sctp_sendmsg(int, void*, size_t, struct sockaddr*, socklen_t,
			uint32_t, uint32_t, uint16_t, uint32_t, uint32_t);

	bzero(&sri, sizeof(sri));
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if (sendline[0] != '[') {
			printf("Error, line must be of the form '[streamnum] text '\n");
			continue;
		}
		sri.sinfo_stream = strtol(&sendline[1], NULL, 0);
		out_sz = strlen(sendline);
		Sctp_sendmsg(sock_fd, sendline, out_sz,
				to, tolen, 0, 0, sri.sinfo_stream, 0, 0);

		len = sizeof(peeraddr);
		rd_sz = Sctp_recvmsg(sock_fd, recvline, sizeof(recvline),
				(SA *) &peeraddr, &len, &sri, &msg_flags);
		printf("From str:%d seq:%d (assoc:0x%x): ",
				sri.sinfo_stream, sri.sinfo_ssn,
				(unsigned int) sri.sinfo_assoc_id);
		printf("%.*s", rd_sz, recvline);
	}
}
