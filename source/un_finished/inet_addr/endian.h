#ifndef MURADIN_NET_ENDIAN_H_
#define MURADIN_NET_ENDIAN_H_


#include <stdint.h>

namespace net
{

// 主机字节序转网络字节序(16位整数)
uint16_t	uint16_hton(uint16_t val);

// 网络字节序转主机字节序(16位整数)
uint16_t	uint16_ntoh(uint16_t val);

// 主机字节序转网络字节序(32位整数)
uint32_t	uint32_hton(uint32_t val);

// 网络字节序转主机字节序(32位整数)
uint32_t	uint32_ntoh(uint32_t val);



inline uint16_t	reverse_two_bytes(uint16_t val)
{
	return (val<<8 | val>>8);
}
inline uint32_t	reverse_four_bytes(uint32_t val)
{
	//return (val<<24 | (val<<8)&0x00FF0000 | (val>>8)&0x0000FF00 | val>>24 );
	return (val<<24 | (val<<8)&0x00FF0000 | (val>>8)&0x0000FF00 | val>>24 );
}


// 当前环境是否是大尾字节序
inline bool		is_big_endianess()
{
	uint16_t n16=0x1234;
	return ((uint8_t*)(&n16))[0] == 0x12 ;	
}

// 当前环境是否是小尾字节序
inline bool		is_lit_endianess()
{
	return !is_big_endianess();
}

// 当前环境是否是网络字节序
inline bool		is_net_endianess()
{
	return is_big_endianess();
}

}//net

#endif // MURADIN_NET_ENDIAN_H_
