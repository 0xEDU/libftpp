#include "../includes/data_buffer.hpp"

DataBuffer::DataBuffer() = default;
DataBuffer::~DataBuffer() = default;

DataBuffer::DataBuffer(const DataBuffer &rhs) { *this = rhs; }

auto DataBuffer::operator=(const DataBuffer &rhs) -> DataBuffer & {
  if (this != &rhs) {
    dataBuffer = rhs.dataBuffer;
  }
  return *this;
}

// std::string is weird
auto DataBuffer::operator<<(const std::string &str) -> DataBuffer & {
  size_t length = str.size();
  *this << length;
  dataBuffer.insert(dataBuffer.end(), str.begin(), str.end());
  return *this;
}

auto DataBuffer::operator>>(std::string &str) -> DataBuffer & {
  size_t length;
  *this >> length;

  if (dataBuffer.size() < length) {
    throw std::runtime_error("Not enough data to deserialize string");
  }
  str.assign(reinterpret_cast<const char *>(dataBuffer.data()), length);
  dataBuffer.erase(dataBuffer.begin(), dataBuffer.begin() + length);
  return *this;
}

auto DataBuffer::size() const -> uint32_t {
  return static_cast<uint32_t>(dataBuffer.size());
}

auto DataBuffer::data() -> uint8_t * { return dataBuffer.data(); }

void DataBuffer::load(const uint8_t *data, uint32_t size) {
  dataBuffer.assign(data, data + size);
}
