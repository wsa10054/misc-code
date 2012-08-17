#include "socket_addr.h"


#include <arpa/inet.h>
#include <assert.h>

namespace net
{

int	net_pton(int family,const char* ip_str,void* dest )
{
	return ::inet_pton(family, ip_str, dest);
}


const char*	net_ntop(int family,const void* ip,char* dest,size_t dest_bytes )
{
	assert( (AF_INET6 == family ? ( INET6_ADDRSTRLEN <= dest_bytes):(true) ));
	assert( (AF_INET  == family ? ( INET_ADDRSTRLEN  <= dest_bytes):(true) ));
	return ::inet_ntop(family,ip,dest,dest_bytes);
}


}

