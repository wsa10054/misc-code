#ifndef thread_name_win_h__
#define thread_name_win_h__


class thread_name_win
{
public:
	thread_name_win(const char* name);

	/// �����߳�����,���31���ַ�.����ض�
	static void		set_thread_name_win(const char* name);
};

#endif // thread_name_win_h__
