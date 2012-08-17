
#include "file_writer.h"
#include "known_env.h"
#include <iostream>
#include <stdio.h>	

#ifdef _ENV_WIN
#include <Windows.h>	// for GetLastError
#define		last_error		(::GetLastError())
#else
#include <errno.h>
#define		last_error		(errno)
#endif // _MSC_VER

file_writer::file_writer(const std::string& file_name,const std::string& open_flag):m_fp(NULL)
{
	m_fp= ::fopen (file_name.c_str (),open_flag.c_str ());
	if (!m_fp){
		std::cout<<"fopen fail " <<std::endl;
		std::cout<<"file : " << file_name<<std::endl;
		std::cout<<"error : " <<  last_error<< std::endl;
	}
}

file_writer::~file_writer(void)
{
	if(m_fp) ::fclose(m_fp);
	m_fp=NULL;
}
void	file_writer::flush()
{
	if( m_fp ) ::fflush(m_fp);
}
int		file_writer::write(const void* data,int data_len)
{
	int result = 0;
	if( m_fp == NULL) return result;
	result = ::fwrite(data,data_len,1,m_fp);
	if (result == 1 ){
		return data_len;
	}else{
		std::cout<<"fwrite fail " <<std::endl;
		std::cout<<"error : " <<  last_error<< std::endl;
		return -1;
	}
}

int		file_writer::read(void* data,int max_read_len)
{
	int result = 0;
	if( m_fp == NULL) return result;
	result = ::fread(data,1,max_read_len,m_fp);
	if (result > 0 ){
		return result;
	}else{
		std::cout<<"fread fail " <<std::endl;
		std::cout<<"error : " <<  last_error << std::endl;
		return -1;
	}
}

#ifdef _FILE_WRITER_MT_

blocking_file_writer::blocking_file_writer(const std::string& file_name,const std::string& open_flag)
	:m_impl(new file_writer(file_name,open_flag))
{
}
blocking_file_writer::~blocking_file_writer(void)
{
}

int		blocking_file_writer::write(const void* data,int data_len)
{
	boost::mutex::scoped_lock lock(m_io_mutex);
	return m_impl->write (data,data_len);
}
int		blocking_file_writer::read(void* data,int max_read_len)
{
	boost::mutex::scoped_lock lock(m_io_mutex);
	return m_impl->read (data,max_read_len);
}

void blocking_file_writer::flush()
{
	boost::mutex::scoped_lock lock(m_io_mutex);
	m_impl->flush ();
}

#endif // _FILE_WRITER_MT_


