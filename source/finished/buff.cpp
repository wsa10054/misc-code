#include "buff.h"
#include <algorithm>
#include <assert.h>



/************************************************************************/
/*                                                                      */
/************************************************************************/


const char myBuff::kCRLF[] = "\r\n";


myBuff::myBuff()
: buffer_(kCheapPrepend + kInitialSize),
readerIndex_(kCheapPrepend),
writerIndex_(kCheapPrepend)
{
	assert(readableBytes() == 0);
	assert(writableBytes() == kInitialSize);
	assert(prependableBytes() == kCheapPrepend);
	
}

// default copy-ctor, dtor and assignment are fine

void 	myBuff::swap(myBuff& rhs)
{
	buffer_.swap(rhs.buffer_);
	std::swap(readerIndex_, rhs.readerIndex_);
	std::swap(writerIndex_, rhs.writerIndex_);
}

size_t 	myBuff::readableBytes() const
{ return writerIndex_ - readerIndex_; }

size_t 	myBuff::writableBytes() const
{ return buffer_.size() - writerIndex_; }

size_t 	myBuff::prependableBytes() const
{ return readerIndex_; }

const char* 	myBuff::peek() const
{ return begin() + readerIndex_; }

char*			myBuff::read_ptr()
{ return begin() + readerIndex_; }

const char* 	myBuff::findCRLF() const
{
	const char* crlf = std::search(peek(), beginWrite(), kCRLF, kCRLF+2);
	return crlf == beginWrite() ? NULL : crlf;
}

const char* 	myBuff::findCRLF(const char* start) const
{
	assert(peek() <= start);
	assert(start <= beginWrite());
	const char* crlf = std::search(start, beginWrite(), kCRLF, kCRLF+2);
	return crlf == beginWrite() ? NULL : crlf;
}

// retrieve returns void, to prevent
// string str(retrieve(readableBytes()), readableBytes());
// the evaluation of two functions are unspecified
void 	myBuff::retrieve(size_t len)
{
	assert(len <= readableBytes());
	readerIndex_ += len;
}

void 	myBuff::retrieveUntil(const char* end)
{
	assert(peek() <= end);
	assert(end <= beginWrite());
	retrieve(end - peek());
}

void 	myBuff::retrieveInt32()
{
	retrieve(sizeof(int));
}


void	myBuff::append(const myBuff& another)
{
	if(another.readableBytes () > 0)
		append (another.peek (),another.readableBytes ());
}

void 	myBuff::retrieveAll()
{
	readerIndex_ = kCheapPrepend;
	writerIndex_ = kCheapPrepend;
}

std::string 	myBuff::retrieveAsString()
{
	std::string str(peek(), readableBytes());
	retrieveAll();
	return str;
}

void 	myBuff::append(const std::string& str)
{
	append(str.data(), str.length());
}

void 	myBuff::append(const char* /*restrict*/ data, size_t len)
{
	ensureWritableBytes(len);
	std::copy(data, data+len, beginWrite());
	hasWritten(len);
}


void 	myBuff::append(const void* /*restrict*/ data, size_t len)
{
	append(static_cast<const char*>(data), len);
}

void 	myBuff::ensureWritableBytes(size_t len)
{
	if (writableBytes() < len)
	{
		makeSpace(len);
	}
	assert(writableBytes() >= len);
}

char* 	myBuff::beginWrite()
{ return begin() + writerIndex_; }

const char* 	myBuff::beginWrite() const
{ return begin() + writerIndex_; }

void 	myBuff::hasWritten(size_t len)
{ writerIndex_ += len; }


void 	myBuff::prepend(const void* /*restrict*/ data, size_t len)
{
	assert(len <= prependableBytes());
	readerIndex_ -= len;
	const char* d = static_cast<const char*>(data);
	std::copy(d, d+len, begin()+readerIndex_);
}



void 	myBuff::shrink(size_t reserve)
{
	std::vector<char> buf(kCheapPrepend+readableBytes()+reserve);
	std::copy(peek(), peek()+readableBytes(), buf.begin()+kCheapPrepend);
	buf.swap(buffer_);
}



char*	myBuff::begin()
{ return &*buffer_.begin(); }

const char* 	myBuff::begin() const
{ return &*buffer_.begin(); }


void 	myBuff::makeSpace(size_t len)
{
    if (writableBytes() + prependableBytes() < len + kCheapPrepend)
    {
        buffer_.resize(writerIndex_+len);
    }
    else
    {
        // move readable data to the front, make space inside buffer
        assert(kCheapPrepend < readerIndex_);
        size_t readable = readableBytes();
        std::copy(begin()+readerIndex_,
            begin()+writerIndex_,
            begin()+kCheapPrepend);
        readerIndex_ = kCheapPrepend;
        writerIndex_ = readerIndex_ + readable;
        assert(readable == readableBytes());
    }
}
