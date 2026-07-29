/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in SCTP
 * Purpose:  This function reutrns the association ID of a SCTP address.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/
#include <string.h>

#include <sys/socket.h>
#include <netinet/sctp.h>

#include "unp.h"

sctp_assoc_t sctp_address_to_associd(int sock_fd, struct sockaddr *sa, socklen_t salen) {
	struct sctp_paddrparams sp;
	int siz;

	siz = sizeof(struct sctp_paddrparams);
	bzero(&sp, siz);
	memcpy(&sp.spp_address, sa, salen);
	sctp_opt_info(sock_fd, 0, SCTP_PEER_ADDR_PARAMS, &sp, &siz);

	return sp.spp_assoc_id;
}
