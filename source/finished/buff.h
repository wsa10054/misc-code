
/*!
 * 
 *  @file       Buff.h 	
 *  @author     ChenJun
 *  @date       2011-7-3
 *  
 *  @brief      buff类
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

	//! 交换两个对象
	void swap(myBuff& rhs);

	//! 返回可读数据的数量
	size_t readableBytes() const;

	//! 返回可写空间大小
	size_t writableBytes() const;

	//! 返回保留区域大小
	size_t prependableBytes() const;

	//! 返回当前读指针.该指针不可长期持有.
	const char* peek() const;

	//! 返回当前读指针.该指针不可长期持有.
	char*		read_ptr();

	//! 将读指针移动一段距离
	void retrieve(size_t len);

	//! 将读指针移动到end 处,end必须是属于内部缓冲区内的指针
	void retrieveUntil(const char* end);

	//! 将读指针移动一个int位置
	void retrieveInt32();

	//! 直接复位读写位置
	void retrieveAll();

	//! 将数据取出,作为string返回,并复位读写位置
	std::string retrieveAsString();


	//! 保存整型数据
	template <class T>
	void	append_integer(T val)
	{
		append(&val,sizeof(T));
	};

	//! 保存一个字符串的数据
    void append(const std::string& str);

	//! 保存myBuff对象
	void append(const myBuff& another);

    //! 保存char型数据
	void append(const char* /*restrict*/ data, size_t len);

    //! 保存任意数据
	void append(const void* /*restrict*/ data, size_t len);

	//! 扩容可写区域,以满足至少有len大小的区域可写.
	void ensureWritableBytes(size_t len);

	//! 返回写指针,该指针不可长期持有
	char* beginWrite();

	//! 返回写指针,该指针不可长期持有
	const char* beginWrite() const;

	//! 将写指针移动一段距离
	void hasWritten(size_t len);

	//! 向前写入数据(将数据保存到当前读指针的前面)
	void prepend(const void* /*restrict*/ data, size_t len);

	//! 缩减内存
	void shrink(size_t reserve);

    //! 查找换号回车符号
    const char* findCRLF() const;

    //! 从start 出开始,查找换号回车符号
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
