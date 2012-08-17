
/*!
 * 
 *  @file       Buff.h 	
 *  @author     ChenJun
 *  @date       2011-7-3
 *  
 *  @brief      buff��
 *  @remark     NONE  
 *  @note    
 *              [2011-7-3 19:04]  created this file.
 * 
 *
 */


#ifndef Buff_h__
#define Buff_h__



#include <vector>
#include <string>





/************************************************************************/
/*                                                                      */
/************************************************************************/

/// Taken from muduo net/buffer.h
///
/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode

class myBuff
{
public:
	static const size_t kCheapPrepend = 8;
	static const size_t kInitialSize =  1024;

	myBuff();

	// default copy-ctor, dtor and assignment are fine

	//! ������������
	void swap(myBuff& rhs);

	//! ���ؿɶ����ݵ�����
	size_t readableBytes() const;

	//! ���ؿ�д�ռ��С
	size_t writableBytes() const;

	//! ���ر��������С
	size_t prependableBytes() const;

	//! ���ص�ǰ��ָ��.��ָ�벻�ɳ��ڳ���.
	const char* peek() const;

	//! ���ص�ǰ��ָ��.��ָ�벻�ɳ��ڳ���.
	char*		read_ptr();

	//! ����ָ���ƶ�һ�ξ���
	void retrieve(size_t len);

	//! ����ָ���ƶ���end ��,end�����������ڲ��������ڵ�ָ��
	void retrieveUntil(const char* end);

	//! ����ָ���ƶ�һ��intλ��
	void retrieveInt32();

	//! ֱ�Ӹ�λ��дλ��
	void retrieveAll();

	//! ������ȡ��,��Ϊstring����,����λ��дλ��
	std::string retrieveAsString();


	//! ������������
	template <class T>
	void	append_integer(T val)
	{
		append(&val,sizeof(T));
	};

	//! ����һ���ַ���������
    void append(const std::string& str);

	//! ����myBuff����
	void append(const myBuff& another);

    //! ����char������
	void append(const char* /*restrict*/ data, size_t len);

    //! ������������
	void append(const void* /*restrict*/ data, size_t len);

	//! ���ݿ�д����,������������len��С�������д.
	void ensureWritableBytes(size_t len);

	//! ����дָ��,��ָ�벻�ɳ��ڳ���
	char* beginWrite();

	//! ����дָ��,��ָ�벻�ɳ��ڳ���
	const char* beginWrite() const;

	//! ��дָ���ƶ�һ�ξ���
	void hasWritten(size_t len);

	//! ��ǰд������(�����ݱ��浽��ǰ��ָ���ǰ��)
	void prepend(const void* /*restrict*/ data, size_t len);

	//! �����ڴ�
	void shrink(size_t reserve);

    //! ���һ��Żس�����
    const char* findCRLF() const;

    //! ��start ����ʼ,���һ��Żس�����
    const char* findCRLF(const char* start) const;

private:
	

	char* begin();

	const char* begin() const;

	void makeSpace(size_t len);

private:
	std::vector<char> buffer_;
	size_t readerIndex_;
	size_t writerIndex_;
	static const char kCRLF[];

};

#endif // Buff_h__
