/*
 Author : betallcoffee
 */

#ifdef WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif

#include <algorithm>

#include "ETBuffer.h"


ETBuffer::ETBuffer(void)
	: readableIndex_(kReserveMin),
	writableIndex_(kReserveMin)
{
	buffer_.resize(kReserveMin);
}


ETBuffer::~ETBuffer(void)
{
}

size_t ETBuffer::read(char *buf, size_t size) {
	size_t t = buffer_.size();
	size = std::min(size, t);
	char *st = peek();
	std::copy(st, st + size, buf);
	return size;
}

std::string ETBuffer::read() {
	return std::string(peek(), size());
}

int8_t ETBuffer::readInt8() {
	char *p = peek();
	track(sizeof(int8_t));
	return *(reinterpret_cast<int8_t *>(p));
}

int16_t ETBuffer::readInt16() {
	char *p = peek();
	track(sizeof(int16_t));
	int16_t a = *(reinterpret_cast<int16_t *>(p));
	a = ntohs(a);
	return a;
}
int32_t ETBuffer::readInt32() {
	char *p = peek();
	track(sizeof(int32_t));
	int32_t a = *(reinterpret_cast<int32_t *>(p));
	a = ntohl(a);
	return a;
}

size_t ETBuffer::write(const char *buf, size_t size) {
	vertifySpace(size);
	std::copy_n(buf, size, buffer_.begin() + writableIndex_);
	writableIndex_ += size;
	return size;
}

size_t ETBuffer::write(const std::string &str) {
	vertifySpace(str.size());
	return write(str.c_str(), str.size());
}

size_t ETBuffer::write(int8_t a) {
	size_t size = sizeof(a);
	write((reinterpret_cast<const char *>(&a)), size);
	return size;
}

size_t ETBuffer::write(int16_t a) {
	size_t size = sizeof(a);
	a = htons(a);
	write((reinterpret_cast<const char *>(&a)), size);
	return size;
}

size_t ETBuffer::write(int32_t a) {
	size_t size = sizeof(a);
	a = htonl(a);
	write((reinterpret_cast<const char *>(&a)), size);
	return size;
}

size_t ETBuffer::writeableSize() {
	return buffer_.size() - kReserveMin - (writableIndex_ - readableIndex_);
}

void ETBuffer::vertifySpace(size_t size) {
	if (writeableSize() < size) {
		if (readableIndex_ - kReserveMin >= size) {
			std::copy(buffer_.begin() + readableIndex_,
				buffer_.begin() + writableIndex_,
				buffer_.begin() + kReserveMin);
			readableIndex_ = kReserveMin;
			writableIndex_ -= size;
		} else {
			buffer_.resize(writableIndex_ + size);
		}
	}
}
