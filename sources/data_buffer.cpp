#include "../includes/data_buffer.hpp"

DataBuffer::DataBuffer() = default;
DataBuffer::~DataBuffer() = default;

DataBuffer::DataBuffer(const DataBuffer &rhs) {
	*this = rhs;
}

DataBuffer &DataBuffer::operator=(const DataBuffer &rhs) {
	if (this != &rhs) {}
	return *this;
}
