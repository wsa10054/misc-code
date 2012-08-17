#include "signal_act.h"

namespace base{
	sig_callback_func*	set_sig_func(int sig_no,sig_callback_func* func)
	{
		struct sigaction act,old_act;
		act.sa_handler=func;
		::sigemptyset(&act.sa_mask);
		act.sa_flags=0;
		if( ::sigaction(sig_no,&act,&old_act) < 0  ){
			//::perror(NULL);
			return SIG_ERR;
		}else{
			return old_act.sa_handler;
		}
	}
};//base