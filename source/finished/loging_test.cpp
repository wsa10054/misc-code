#include "log_warper.h"
#include "file_writer.h"


file_writer log_file("log.log","w");

void log_to_file(const char* msg, int len)
{
	log_file.write (msg,len);
}

void	test_log();

int main(int argc, char* argv[])
{
	loging::log_warper::setLogLevel (loging::ll_debug);

	loging::log_warper::setOutput (log_to_file);
	test_log();

	loging::log_warper::setOutput (NULL);
	test_log();

	return 0;
}

void	test_log()
{
	{
		debug_loger.stream ()<< "debug_loger"<<std::endl ;
	}

	{
		debug_err_loger.stream ()<< "debug_err_loger"<<std::endl ;
	}

	{
		info_loger.stream ()<< "info_loger"<<std::endl ;
	}

	{
		warn_loger.stream ()<< "warn_loger"<<std::endl ;
	}

	{
		err_loger.stream ()<< "err_loger"<<std::endl ;
	}

	{
		//fata_loger.stream ()<< "fata_loger"<<std::endl ;
	}
}