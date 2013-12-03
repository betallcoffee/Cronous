/*
 Author : Tina
 */

#ifndef __ET_BUFFER_H__
#define __ET_BUFFER_H__

#include <vector>
#include <string>
#include <stdint.h>
#include <stddef.h>

class ETBuffer
{
public:
	ETBuffer(void);
	~ETBuffer(void);
	
	size_t read(char *buf, size_t size);
	std::string read();
	int8_t readInt8();
	int16_t readInt16();
	int32_t readInt32();
	size_t write(const char *buf, size_t size);
	size_t write(const std::string &str);
	size_t write(int8_t a);
	size_t write(int16_t a);
	size_t write(int32_t a);

	size_t writeableSize();

	char *peek() { return &*(buffer_.begin() + readableIndex_); }

	size_t track(size_t size) {
		if (size <= 0) return 0;
		if (readableIndex_ + size <= writableIndex_) {
			readableIndex_ += size;
		} else {
			size = writableIndex_ - readableIndex_;
			readableIndex_ = writableIndex_;
		}
		return size;
	}

	void clear() {
		writableIndex_ = readableIndex_;
	}

	size_t size() {
		return writableIndex_ - readableIndex_;
	}
	

private:
	static const size_t kReserveMin = 8;
	void vertifySpace(size_t size);

	std::vector<char> buffer_;
	size_t readableIndex_;
	size_t writableIndex_;
};

#endif // __ET_BUFFER_H__
