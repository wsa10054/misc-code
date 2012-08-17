#include "str_helper.h"
#include <string.h>

namespace detail{
	
/// hex�ַ���תBCD��
/**
 *
 * @param[IN]    hexstr_array      ����
 * @param[IN]    hexstr_bytes      ��Ҫת���ĳ���
 * @param[OUT]   out_buffer        ���
 * 
 * @retval   �ɹ� 
 * @retval   ʧ��,���з�HEX�ַ�
 *
 * @note
 *     - ��������ַ�����������,����ʧ��
 */
bool			asc2bcd(const void* hexstr_array,int hexstr_bytes,void* out_buffer )
{
	if (hexstr_bytes%2){
		return false;
	}
	const unsigned char* start= (const unsigned char*)hexstr_array;
	unsigned char* out= (unsigned char*)out_buffer;

	for (int i=0;i< hexstr_bytes;i+=2){
		unsigned char hi=0,lo=0;
		if ( hex_value(start[i],hi) && hex_value(start[i+1],lo)){
			*out++ = (unsigned char)(hi*16 + lo);
		}else{
			return false;
		}
	}
	return true;
}
	
/// hex�ַ���תBCD��
/**
 *
 * @param[IN]    sz_src      ����
 * @param[OUT]   dest        ���
 * @param[IN]    dest_len    Ҫ������ĳ���
 * @param[IN]    pad_char    ����ַ�
 * 
 * @retval   �ɹ� 
 * @retval   ʧ��,���з�HEX�ַ�
 *
 * @note
 *     - ��������ַ�����������,������λ��0(������123���Ϊ0x01,0x23) 
 *     - ���dest_len����sz_src�ṩ������,�����������pad_char��ǰ�����
 */
bool			asc2bcd_with_apdding(const char *sz_src,void *dest,int dest_len ,unsigned char pad_char)
{
	unsigned char tmp,c;
	bool bDataOK;
	int  outindex;

	char* pDest=( char*)dest;
	memset(pDest,0,dest_len);

	// ������볤��
	int inlen = (int)strlen(sz_src);
	if( inlen > 2*dest_len )
		inlen = 2*dest_len;

	bDataOK  = false;
	outindex = dest_len - 1;
	for(int i=inlen-1; i>=0; i--)
	{
		c = sz_src[i];

		if( (c>='0') && (c<='9') )
			tmp = c - '0';
		else if( (c>='a') && (c<='f') )
			tmp = c - 'a' + 10;
		else if( (c>='A') && (c<='F') )
			tmp = c - 'A' + 10;
		else    return false;

		if( bDataOK )
		{
			pDest[outindex] = (tmp<<4) | pDest[outindex];
			outindex--;
		}
		else
		{
			pDest[outindex] = tmp;
		}
		bDataOK = !bDataOK;
	}
	return true;
}

/// BCD��ת�ַ��� 
/**
 *
 * @param[IN]    hexdata      ����
 * @param[OUT]   sz_dest      ���
 * @param[IN]    hexdata_len  ת�����ֽ���
 * @param[IN]    append_eof   �������Ƿ��ַ���������
 * 
 * @retval   ����ת������ַ��� 
 *
 */
char*		bcd2asc(const void *hexdata, char* sz_dest,int hexdata_len,bool upcase=true,bool append_eof=true)
{
	const char* pHexData=(const char*)hexdata;
	int  i;
	unsigned char c,c1;
	char* t = sz_dest;
	unsigned char mod_char= upcase? 'A':'a';
	for(i=0;i<hexdata_len;i++)
	{
		c  = *pHexData++;

		c1 = (c >> 4)&0xf;
		if( c1 >= 0xa )
			c1 = c1 + mod_char - 0xa;
		else c1 = c1 + '0';
		*t++ = c1;

		c1 = c & 0xf;
		if( c1 >= 0xa )
			c1 = c1 + mod_char - 0xa;
		else c1 = c1 + '0';
		*t++ = c1;
	}
	if(append_eof)
		*t = '\0';
	return sz_dest;
}

};


/************************************************************************/
/* �����                                                             */
/************************************************************************/
bool	is_string_hex_format(const void* hexstr_array,int start_offset, int bytes_to_check)
{
	if(start_offset < 0 || bytes_to_check <= 0) return false;

	const char* p_start = ((const char*)hexstr_array) + start_offset;
	const char* p_end   = ((const char*)hexstr_array) + start_offset + bytes_to_check;
	for ( ;p_start != p_end;++p_start ){
		if( !is_degital(*p_start) && !is_a2f(*p_start) )
			return false;
	}
	return true;
}
char*	array_hex_to_asc(const void* hex_array,int hex_bytes,char* out_buffer,bool upcase,bool append_eof)
{
	return detail::bcd2asc(hex_array,out_buffer,hex_bytes,upcase,append_eof);
}


bool	array_hexstr_to_hex(const void* hexstr_array,int hexstr_bytes,void* out_buffer)
{
	if (hexstr_bytes % 2 ){
		return false;
	}
	if ( !is_string_hex_format(hexstr_array,0,hexstr_bytes)){
		return false;
	}
	return detail::asc2bcd(hexstr_array,hexstr_bytes,out_buffer);
}

bool	is_string_digital_format(const void* str_array,int start_offset, int bytes_to_check)
{
	if(start_offset < 0 || bytes_to_check <= 0) return false;

	const char* p_start = ((const char*)str_array) + start_offset;
	const char* p_end   = ((const char*)str_array) + start_offset + bytes_to_check;
	for ( ;p_start != p_end;++p_start ){
		if( !is_degital(*p_start) )
			return false;
	}
	return true;
}
