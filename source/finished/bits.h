#ifndef		MURADIN_BASE_BITS_H_
#define		MURADIN_BASE_BITS_H_
#include <assert.h>
#include <stdio.h>

namespace muradin{
namespace bits{

/// get bit value ,offset = [1,8]
inline unsigned char bit_of_int8(unsigned char to_check,int offset)
{
   /*
	* bits   : XXXXXXXX
	* offset : 87654321
	*/

	assert(offset>=1 && offset <= 8);
	return ( to_check  >> (offset-1) )& 0x1;
}

/// get binary-formated string,e.g "10001101"
static const char* binary_itoa(unsigned char val,char* buff,size_t bufflen)
{
	if(bufflen<9) return NULL;
	for (int i=0;i<8;++i)
		buff[i]= '0' + bit_of_int8(val,8-i);
	
	buff[8]='\0';
	return buff;
}



/// get integer value form binary-formated string,e.g "00001000" => 0x8
/// return false when: len>8 ,Neither character is '1' nor '0';
static bool binary_atoi(const char* buff,size_t offset,size_t len,unsigned char* out_val)
{
	static const unsigned char mask_tab_8bits[8]={1,2,4,8,16,32,64,128};
	if(len > 8) return false;
	*out_val=0;
	for (size_t i=0;i<len;++i){
		if( buff[offset + len - i -1] == '1')
			*out_val +=(1<<i) ;
		else {
			if(buff[offset + len - i -1] != '0')
				return false;
		}
	}
	return true;
}


};//bits
};//muradin

#endif//MURADIN_BASE_BITS_H_