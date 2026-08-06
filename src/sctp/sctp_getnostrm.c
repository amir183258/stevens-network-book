/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in SCTP
 * Purpose:  This function reutrns the number of stream in a SCTP association.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

// this has to be here
#include "unp.h"

#include <sys/socket.h>
#include <netinet/sctp.h>

int sctp_get_no_strms(int sock_fd, int assoc_id, struct sockaddr *to, socklen_t tolen) {
	int retsz;
	struct sctp_status status;
	retsz = sizeof(status);
	bzero(&status, sizeof(status));

	sctp_assoc_t sctp_address_to_associd(int, struct sockaddr*, socklen_t);

	// WARNING: the book used below codes to get status. They do not work.
	// I took asso_id as a parameter in this function. Also, Getosockopt()
	// does not work with STCP on my system.
	//
	//status.sstat_assoc_id = sctp_address_to_associd(sock_fd, to, tolen);
	//Getsockopt(sock_fd, IPPROTO_SCTP, SCTP_STATUS, &status, &retsz);

	sctp_opt_info(sock_fd, assoc_id,
			SCTP_STATUS, &status, &retsz);

	return status.sstat_outstrms;
}
