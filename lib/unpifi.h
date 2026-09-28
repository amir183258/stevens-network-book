/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This is the header file for get_ifi_info() function which is a
 * 	     miniature version of the ifconfig program.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

// our own header for the programs that need interface configuration info.
// include this file, instead of "unp.h"

#ifndef __unp_ifi_h
#define __unp_ifi_h

#include <sys/socket.h>
#include <net/if.h>

#include "unp.h"

#define IFI_NAME 	16		// same as IFNAMSIZ in <net/if.h>
#define IFI_HADDR 	8		// allow for 64-bit EUI-64 in future

struct ifi_info {
	char	ifi_name[IFI_NAME];	// interface name, null-terminated
	short	ifi_index;		// interface index
	short	ifi_mtu;		// interface MTU
	u_char	ifi_haddr[IFI_HADDR];	// hardware address
	u_short ifi_hlen;		// # bytes in hardware address: 0, 6, 8
	short	ifi_flags;		// IFF_xxx constants from <net/if.h>
	short	ifi_myflags;		// our own IFI_xxx flags
	struct sockaddr *ifi_addr;	// primary address
	struct sockaddr *ifi_brdaddr;	// broadcast address
	struct sockaddr *ifi_dstaddr;	// destination address
	struct ifi_info *ifi_next;	// next of these structures
};

#define IFI_ALIAS	1

// function prototypes
struct ifi_info* get_ifi_info(int, int);
struct ifi_info* Get_ifi_info(int, int);
void free_ifi_info(struct ifi_info*);

#endif
