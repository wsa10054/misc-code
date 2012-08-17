#ifndef MURADIN_NET_SOCKETADDR_H
#define MURADIN_NET_SOCKETADDR_H

#include <stdint.h>
#include <sys/types.h>

namespace net
{

// ��IP��ַ�ַ���ת���ɶ�����ֵ
// �����IPV6��ַ dest����16�ֽ�
// �����IPV4��ַ dest����4�ֽ�
// �ɹ����� 1
// ����0��ʾip_str������Ч�ĸ�ʽ
// ������ -1 ,������Ϣͨ��errno��ȡ
int	net_pton(int family,const char* ip_str,void* dest );

// ��������ֵIP��ַת�����ַ���( xxx.xxx.xxx.xxx ���� xxxx::xxxx:xxxx:xxxx:xxxx%xx )
// �����IPV6��ַ dest����16�ֽ�,����������
// �����IPV4��ַ dest����46�ֽ�,����������
// �ɹ�������destָ����ַ���
// ʧ�ܷ���NULL (dest�ռ䲻��)
const char*	net_ntop(int family,const void* ip,char* dest,size_t dest_bytes );


}

#endif // MURADIN_NET_SOCKETADDR_H
