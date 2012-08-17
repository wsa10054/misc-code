#ifndef MURADIN_NET_ENDPOINT_H_
#define MURADIN_NET_ENDPOINT_H_


#include <stdint.h>
#include <netinet/in.h>
#include <string>

namespace net
{

//typedef	sockaddr_storage	SockecAddress;
typedef	sockaddr_in			SockecAddressV4;	// same as struct sockaddr
//typedef	sockaddr_in6		SockecAddressV6;

/// POD class
class EndPointV4
{

public:
	EndPointV4();
	EndPointV4(uint16_t port);
	explicit EndPointV4(const std::string& ip);
	EndPointV4(const std::string& ip,uint16_t port);
	explicit EndPointV4(const SockecAddressV4& address );

	
	~EndPointV4();

	const SockecAddressV4&	Address()const;
	SockecAddressV4&		Address();
	const std::string		GetIP()const;
	uint16_t				GetPort()const;
	
	static std::string		AddressAny();
	static uint16_t			PortAny();
	
	const EndPointV4&		operator=(const SockecAddressV4& rh);
private:
	SockecAddressV4	address_;
	enum {kPortAny=0};
};

}//net

#endif // MURADIN_NET_ENDPOINT_H_
