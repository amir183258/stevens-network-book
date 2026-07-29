/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in SCTP
 * Purpose:  This function reutrns the number of stream in a SCTP association.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <sys/socket.h>
#include <netinet/sctp.h>

#include "unp.h"

int sctp_get_no_strms(int sock_fd, struct sockaddr *to, socklen_t tolen) {
	int retsz;
	struct sctp_status status;
	retsz = sizeof(status);
	bzero(&status, sizeof(status));

	sctp_assoc_t sctp_address_to_associd(int, struct sockaddr*, socklen_t);

	status.sstat_assoc_id = sctp_address_to_associd(sock_fd, to, tolen);
	Getsockopt(sock_fd, IPPROTO_SCTP, SCTP_STATUS, &status, &retsz);

	return status.sstat_outstrms;
}
