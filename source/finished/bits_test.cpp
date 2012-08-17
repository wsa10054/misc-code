
#include "bits.h"
#include <stdlib.h>
#include <string.h>
typedef struct binary_describ 
{
	unsigned char val;
	char str[9];
}BIN_DSB;

int   itoa_b(int   val,   int   size,   char   *rsult)  {
	int  j = 0;
	for (int i = size * 8  -1;i >=  0; i--)
		if (val& (1<< i))  rsult[j++]=  '1';
		else rsult[j++] = '0';

		rsult[j]=0;
		return j;
} 

int main()
{
	static const unsigned char cmp_size=0xff;
	BIN_DSB test_data[cmp_size]={'0'};
	for (unsigned char i=0;i<cmp_size;++i){
		test_data[i].val= i;
		itoa_b(i,1,test_data[i].str);
	}

	char buf[100]={0};
	for (int i=0;i< cmp_size;++i){
		muradin::bits::binary_itoa(test_data[i].val,buf,sizeof(buf));
		::printf("0x%02X (%s) => %s\r\n",test_data[i].val ,test_data[i].str,buf);
		assert(memcmp (test_data[i].str,buf ,strlen(test_data[i].str) ) == 0);
		unsigned char n_val;
		assert(  muradin::bits::binary_atoi(buf,0,strlen(buf),&n_val));
		assert( test_data[i].val == n_val);
	}
	return 0;
}


