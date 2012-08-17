#include "str_helper.h"
#include <string.h>

namespace detail{
	
/// hex字符串转BCD码
/**
 *
 * @param[IN]    hexstr_array      输入
 * @param[IN]    hexstr_bytes      需要转换的长度
 * @param[OUT]   out_buffer        输出
 * 
 * @retval   成功 
 * @retval   失败,含有非HEX字符
 *
 * @note
 *     - 如果输入字符长度是奇数,返回失败
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
	
/// hex字符串转BCD码
/**
 *
 * @param[IN]    sz_src      输入
 * @param[OUT]   dest        输出
 * @param[IN]    dest_len    要求输出的长度
 * @param[IN]    pad_char    填充字符
 * 
 * @retval   成功 
 * @retval   失败,含有非HEX字符
 *
 * @note
 *     - 如果输入字符长度是奇数,函数高位补0(如输入123输出为0x01,0x23) 
 *     - 如果dest_len大于sz_src提供的数据,则输出部分用pad_char在前面填充
 */
bool			asc2bcd_with_apdding(const char *sz_src,void *dest,int dest_len ,unsigned char pad_char)
{
	unsigned char tmp,c;
	bool bDataOK;
	int  outindex;

	char* pDest=( char*)dest;
	memset(pDest,0,dest_len);

	// 检查输入长度
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

/// BCD码转字符串 
/**
 *
 * @param[IN]    hexdata      输入
 * @param[OUT]   sz_dest      输出
 * @param[IN]    hexdata_len  转换的字节数
 * @param[IN]    append_eof   输出结果是否补字符串结束符
 * 
 * @retval   返回转换后的字符串 
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
/* 杂项函数                                                             */
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
