#ifndef file_writer_h__
#define file_writer_h__

#include <stdio.h>
#include <string>

#ifdef _FILE_WRITER_MT_
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#endif // _FILE_WRITER_MT_


class file_writer
{
public:
	file_writer(const std::string& file_name,const std::string& open_flag);
	virtual ~file_writer(void);
	int		write(const void* data,int data_len);
	int		read(void* data,int max_read_len);
	void	flush();
private:
	FILE*	m_fp;
};

#ifdef _FILE_WRITER_MT_

class blocking_file_writer
{
	typedef	boost::scoped_ptr<file_writer>	file_ptr;
public:
	blocking_file_writer(const std::string& file_name,const std::string& open_flag);
	virtual ~blocking_file_writer(void);

	int		write(const void* data,int data_len);
	int		read(void* data,int max_read_len);
	void	flush();
private:
	file_ptr	m_impl;
	boost::mutex	m_io_mutex;
};

#endif // _FILE_WRITER_MT_

#endif // file_writer_h__
