#ifndef MURADIN_NET_SOCKETADDR_H
#define MURADIN_NET_SOCKETADDR_H

#include <stdint.h>
#include <sys/types.h>

namespace net
{

// 将IP地址字符串转换成二进制值
// 如果是IPV6地址 dest至少16字节
// 如果是IPV4地址 dest至少4字节
// 成功返回 1
// 返回0表示ip_str不是有效的格式
// 出错返回 -1 ,错误信息通过errno获取
int	net_pton(int family,const char* ip_str,void* dest );

// 将二进制值IP地址转换成字符串( xxx.xxx.xxx.xxx 或者 xxxx::xxxx:xxxx:xxxx:xxxx%xx )
// 如果是IPV6地址 dest至少16字节,包含结束符
// 如果是IPV4地址 dest至少46字节,包含结束符
// 成功返回由dest指向的字符串
// 失败返回NULL (dest空间不足)
const char*	net_ntop(int family,const void* ip,char* dest,size_t dest_bytes );


}

#endif // MURADIN_NET_SOCKETADDR_H
