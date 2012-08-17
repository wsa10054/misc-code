/*
#include <iostream>

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
*/
#include "end_point.h"
#include "endian.h"
#include "tcp_socket.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	std::string	ip_str="192.168.0.1";
	uint16_t	port=5001;
	
	
	net::EndPointV4 addr_1("192.168.0.1",port);
	net::EndPointV4 addr_2("192.168.0.1");
	net::EndPointV4 addr_3(port);
	net::EndPointV4 addr_4;
	
	::printf("%s:%d\n", addr_1.GetIP().c_str(), addr_1.GetPort());
	::printf("%s:%d\n", addr_2.GetIP().c_str(), addr_2.GetPort());
	::printf("%s:%d\n", addr_3.GetIP().c_str(), addr_3.GetPort());
	::printf("%s:%d\n", addr_4.GetIP().c_str(), addr_4.GetPort());
	
	assert(addr_1.GetIP() == ip_str);
	assert(addr_1.GetPort() == port);
	
	assert(addr_2.GetIP() == ip_str);
	assert(addr_2.GetPort() == net::EndPointV4::PortAny());
	
	assert(addr_3.GetIP() == net::EndPointV4::AddressAny());
	assert(addr_3.GetPort() == port);
	
	assert(addr_4.GetIP() == net::EndPointV4::AddressAny());
	assert(addr_4.GetPort() == net::EndPointV4::PortAny());
	
	uint16_t l16=0x1234,b16=0x3412;
	uint32_t l32=0x12345678,b32=0x78563412;
	uint32_t test= net::reverse_four_bytes(l32);

	assert(net::reverse_two_bytes(l16) == b16); 
	assert(net::reverse_four_bytes(l32) == b32); 
	//net::tcp_nbsocket_create_coe();
	//net::tcp_socket_bind(1,addr_4);
	::printf("hello world\n");
	return 0;
}
