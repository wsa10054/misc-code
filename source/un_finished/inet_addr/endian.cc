#include "endian.h"
#ifndef	NO_SOCKET_HEADER_INCLUDE_  // for someone who do not want to use in.h
#include <netinet/in.h>
#endif

namespace net{
	
uint16_t	uint16_hton(uint16_t val)
{
#ifndef	NO_SOCKET_HEADER_INCLUDE_
	return ::htons(val);
#else
	return is_big_endianess() ? val : reverse_two_bytes(val);
#endif
}

uint16_t	uint16_ntoh(uint16_t val)
{
#ifndef	NO_SOCKET_HEADER_INCLUDE_
	return ::ntohs(val);
#else
	return is_big_endianess() ? val : reverse_two_bytes(val);
#endif

}

uint32_t	uint32_hton(uint32_t val)
{
#ifndef	NO_SOCKET_HEADER_INCLUDE_
	return ::htonl(val);
#else
	return is_big_endianess() ? val : reverse_four_bytes(val);
#endif
}

uint32_t	uint32_ntoh(uint32_t val)
{
#ifndef	NO_SOCKET_HEADER_INCLUDE_
	return ::ntohl(val);
#else
	return is_big_endianess() ? val : reverse_four_bytes(val);
#endif
}


};