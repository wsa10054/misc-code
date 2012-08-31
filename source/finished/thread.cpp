#include "thread.h"

#include <assert.h>
#include <stdlib.h>

#include <exception>
#include <iostream>

#include <boost/bind.hpp>

int thread::g_created_count = 0;

thread::thread(const thread_func_t& thread_func,const std::string& name)
:m_running(false),m_thread_func(thread_func),m_name(name),m_thread(NULL)
{
	g_created_count++;
}

thread::~thread(void)
{
	//do nothing
}
bool	thread::running()
{
	return m_running;
}
void	thread::run()
{
	assert(!m_running && !m_thread);
	m_running=true;
	m_thread = new boost::thread(boost::bind (&thread::start_thread_func,this));
}
void	thread::join()
{
	assert(m_running && m_thread);
	m_thread->join ();
	delete m_thread;
	m_thread=NULL;
}
void*	thread::start_thread_func(void* para)
{
	thread* p_this= static_cast<thread*>(para);
	p_this->run_func();
	return NULL;
}
void	thread::run_func()
{
	boost::thread::id tid= boost::this_thread::get_id ();
	try{
		m_thread_func();
	}catch (const std::exception& e){
		std::cerr<< "exception caught in Thread : "<< tid << std::endl;
		std::cerr<< "what : "<< e.what() << std::endl;
		abort();	
	}catch (...){
		std::cerr<< "unknown exception caught in Thread : "<< tid << std::endl;
		throw; 
	}

}