#ifndef MURADIN_BASE_SIGNAL_ACT_H_
#define MURADIN_BASE_SIGNAL_ACT_H_

#include <signal.h>
#include <sys/wait.h>

typedef	void (sig_callback_func)(int);

namespace base{

sig_callback_func*	set_sig_func(int sig_no,sig_callback_func* func);


};//base
#endif//MURADIN_BASE_SIGNAL_ACT_H_