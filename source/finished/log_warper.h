#ifndef log_warper_h__
#define log_warper_h__

#include "known_env.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <string.h> // for strrchr strerror

#ifdef _ENV_WIN
#include <Windows.h> // for GetLastError
#define		last_error		(::GetLastError())
#else
#include <errno.h>
#define		last_error		(errno)
#endif // _MSC_VER

namespace loging
{
class	loger;

enum	loging_level{
	ll_debug,
	ll_info,
	ll_warning,
	ll_error,
	ll_fatal_err,
	ll_end_palce_
};

typedef void (*OutputFunc)(const char* msg, int len);
typedef void (*FlushFunc)();

class log_warper
{
public:
	explicit	log_warper(loging_level log_lvl);
	log_warper(loging_level log_lvl,const std::string& source_file,const std::string& func_name,int line_number);
	log_warper(loging_level log_lvl,const std::string& source_file,const std::string& func_name,int line_number,int error_code);
	std::ostream&	stream();
	void		finish();
	void		flush();
	loger&		get_impl();
	~log_warper(void);
	
	static loging_level logLevel();
	static void setLogLevel(loging_level level);

	static void setOutput(OutputFunc func);
	static void setFlush(FlushFunc func);
	
private:
	log_warper(const log_warper&);
	log_warper&	operator=(const log_warper&);
private:
	loger*		impl_;
};

};//loging

#define		debug_loger					(loging::log_warper(loging::ll_debug,__FILE__,__FUNCTION__,__LINE__))
#define		debug_err_loger				(loging::log_warper(loging::ll_debug,__FILE__,__FUNCTION__,__LINE__,(last_error)))
#define		info_loger					(loging::log_warper(loging::ll_info,__FILE__,__FUNCTION__,__LINE__))
#define		warn_loger					(loging::log_warper(loging::ll_warning,__FILE__,__FUNCTION__,__LINE__))
#define		err_loger					(loging::log_warper(loging::ll_error,__FILE__,__FUNCTION__,__LINE__))
// write log and call abort()
#define		fata_loger					(loging::log_warper(loging::ll_fatal_err,__FILE__,__FUNCTION__,__LINE__))

#define		end_line_win				("\r\n")

#endif // log_warper_h__
