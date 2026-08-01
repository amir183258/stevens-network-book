/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in SCTP
 * Purpose:  This is the server file of the SCTP iterative server. Server
 * 	     creates association and receive and send messages in different
 * 	     streams. In this file, the server terminates the association on
 * 	     reply.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/sctp.h>

#include "unp.h"

int main(int argc, char **argv) {
	int sock_fd, msg_flags;
	char readbuf [BUFFSIZE];
	struct sockaddr_in servaddr, cliaddr;
	struct sctp_sndrcvinfo sri;
	struct sctp_event_subscribe evnts;
	int stream_increment = 1;
	socklen_t len;
	size_t rd_sz;
	struct sctp_initmsg initm;

	// declare functions
	int sctp_get_no_strms(int, int, struct sockaddr*, socklen_t);
	int Sctp_recvmsg(int, void*, size_t, struct sockaddr*, socklen_t*,
			struct sctp_sndrcvinfo*, int*);
	int Sctp_sendmsg(int, void*, size_t, struct sockaddr*, socklen_t,
			uint32_t, uint32_t, uint16_t, uint32_t, uint32_t);

	if (argc == 2)
		stream_increment = atoi(argv[1]);
	sock_fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
	
	bzero(&initm, sizeof(initm));
	initm.sinit_num_ostreams = SERV_MORE_STRMS_SCTP;
	Setsockopt(sock_fd, IPPROTO_SCTP, SCTP_INITMSG, &initm, sizeof(initm));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(sock_fd, (SA *) &servaddr, sizeof(servaddr));

	bzero(&evnts, sizeof(evnts));
	evnts.sctp_data_io_event = 1;
	Setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &evnts, sizeof(evnts));

	Listen(sock_fd, LISTENQ);
	for ( ; ; ) {
		len = sizeof(struct sockaddr_in);
		rd_sz = Sctp_recvmsg(sock_fd, readbuf, sizeof(readbuf),
				(SA *) &cliaddr, &len, &sri, &msg_flags);
		if (stream_increment) {
			sri.sinfo_stream++;
			if (sri.sinfo_stream >=
					sctp_get_no_strms(sock_fd, sri.sinfo_assoc_id, (SA *) &cliaddr, len))
				sri.sinfo_stream = 0;
		}

		Sctp_sendmsg(sock_fd, readbuf, rd_sz,
				(SA *) &cliaddr, len,
				sri.sinfo_ppid,
				sri.sinfo_flags | MSG_FIN, sri.sinfo_stream, 0, 0);
	}
}
