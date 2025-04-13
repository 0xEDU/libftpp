#include "../includes/data_buffer.hpp"

DataBuffer::DataBuffer() = default;
DataBuffer::~DataBuffer() = default;

DataBuffer::DataBuffer(const DataBuffer &rhs) {
	*this = rhs;
}

DataBuffer &DataBuffer::operator=(const DataBuffer &rhs) {
	if (this != &rhs) {
		dataBuffer = rhs.dataBuffer;
	}
	return *this;
}

// std::string is weird
DataBuffer &DataBuffer::operator<<(const std::string &str) {
	size_t length = str.size();
	*this << length;
	dataBuffer.insert(dataBuffer.end(), str.begin(), str.end());
	return *this;
}

DataBuffer &DataBuffer::operator>>(std::string &str) {
	size_t length;
	*this >> length;

	if (dataBuffer.size() < length) {
		throw std::runtime_error("Not enough data to deserialize string");
	}
	str.assign(reinterpret_cast<const char *>(dataBuffer.data()), length);
	dataBuffer.erase(dataBuffer.begin(), dataBuffer.begin() + length);
	return *this;
}
