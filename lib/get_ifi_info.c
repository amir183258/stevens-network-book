/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This is the implementation for get_ifi_info() function which is a
 * 	     miniature version of the ifconfig program.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdib.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <errno.h>

#include "unpifi.h"

struct ifi_info* get_ifi_info(int family, int doaliases) {
	struct ifi_info *ifi, *ifihead, **ifipnext;
	int sockfd, len, lastlen, flags, myflags, idx = 0, hlen = 0;
	char *ptr, *buf, lastname[IFNAMSIZ], *cptr, *haddr, *sdlname;
	struct ifconf ifc;
	struct ifreq *ifr, ifrcopy;
	struct sockaddr_in *sinptr;
	struct sockaddr_in6 *sin6ptr;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	lastlen = 0;
	len = 100 * sizeof(struct ifreq); // initial buffer size guess
	for ( ; ; ) {
		buf = Malloc(len);
		ifc.ifc_len = len;
		ifc.ifc_buf = buf;
		if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) {
			if (errno != EINVAL || lastlen != 0)
				err_sys("ioctl error");
		}
		else {
			if (ifc.ifc_len == lastlen)
				break; // success, len has not changed
			lastlen = ifc.ifc_len;
		}
		len += 10 * sizeof(struct ifreq); // increment
		free(buf);
	}
	ifihead = NULL;
	ifipnext = &ifihead;
	lastname[0] = 0;
	sdlname = NULL;

	for (ptr = buf; ptr < buf + ifc.ifc_len;) {
		ifr = (struct ifreq *) ptr;
#ifdef HAVE_SOCKADDR_SA_LEN
		len = max(sizeof(struct sockaddr), ifr->ifr_addr.sa_len);
#else
		switch (ifr->ifr_addr.sa_family) {
#ifdef IPV6
		case AF_INET6:
			len = sizeof(struct sockaddr_in6);
			break;
#endif
		case AF_INET:
		default:
			len = sizeof(struct sockaddr);
			break;
		}
#endif // HAVE_SOCKADDR_SA_LEN
       		ptr += sizeof(ifr->ifr_name) + len; // for next one in buffer

#ifdef HAVE_SOCKADDR_DL_STRUCT
		// assumes that AF_LINK precedes AF_INET or AF_INET6
		if (ifr->ifr_addr.sa_family = AF_LINK) {
			struct sockaddr_dl *sdl = (struct sockaddr_dl *) &ifr->ifr_addr;
			sdlname = ifr->ifr_name;
			idx = sdl->sdl_index;
			haddr = sdl->sdl_data + sdl->sdl_nlen;
			hlen = sdl->sdl_alen;
		}
#endif

		if (ifr->ifr_addr.sa_family != family)
			continue; // ignore if not desired family

		myflags = 0;
		if ( (cptr = strchr(ifr->ifr_name, ':')) != NULL)
			*cptr = 0; // replace colon with null
		if (strncmp(lastname, ifr->ifr_name, IFNAMSIZ) == 0) {
			if (doaliases == 0)
				continue;
			myflags = IFI_ALIAS;
		}
		memcpy(lastname, ifr->ifr_name, IFNAMSIZ);

		ifrcopy = *ifr;
		Ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy);
		flags = ifrcopy.ifr_flags;
		if ((flags & IFF_UP) == 0)
			continue; // ignore if interface not up
	}

}
