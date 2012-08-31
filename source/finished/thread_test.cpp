
#include "thread.h"
#include <iostream>

void add_local()
{
	int i=0;
	int count =5000;// 100*10000;
	for (;i<count;++i){
		for (int n=0;n<count;++n){
		}
	}
	std::cout<< "add_local end : "<<  i <<std::endl;
	//throw std::exception("sdfasdfasdf");
}

void test_03();
int main()
{
	test_03();
	return 0;
}


void test_03()
{
	thread td1(add_local,"thread_1");
	thread td2(add_local,"thread_2");
	thread td3(add_local,"thread_3");
	td1.run();
	td2.run();
	td3.run();

	td1.join();
	td2.join();
	td3.join();
}