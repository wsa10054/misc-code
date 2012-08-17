#include "timestamp.h"
#include <iostream>
using namespace base;
int main(void)
{
	Timestamp tm_now=Timestamp::now();
	std::cout<< tm_now.toFormattedString()<<std::endl;
	std::cout<< tm_now.toString()<<std::endl;
	return 0;
}