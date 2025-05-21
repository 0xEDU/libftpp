#ifndef DATA_BUFFER_HPP
#define DATA_BUFFER_HPP

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

class DataBuffer {
  std::vector<uint8_t> dataBuffer;

public:
  DataBuffer();
  DataBuffer(const DataBuffer &rhs);
  DataBuffer(DataBuffer &&rhs) = delete;
  DataBuffer &operator=(const DataBuffer &rhs);
  ~DataBuffer();

  template <typename T> auto operator<<(const T &object) -> DataBuffer & {
    const uint8_t *data = reinterpret_cast<const uint8_t *>(&object);
    dataBuffer.insert(dataBuffer.end(), data, data + sizeof(T));
    return *this;
  }

  template <typename T> auto operator>>(T &object) -> DataBuffer & {
    if (dataBuffer.size() < sizeof(T)) {
      throw std::runtime_error("Not enough data to deserialize");
    }
    std::memcpy(&object, dataBuffer.data(), sizeof(T));
    dataBuffer.erase(dataBuffer.begin(), dataBuffer.begin() + sizeof(T));
    return *this;
  };

  auto operator<<(const std::string &str) -> DataBuffer &;
  auto operator>>(std::string &str) -> DataBuffer &;

  auto size() const -> uint32_t;
  auto data() -> uint8_t *;
  void load(const uint8_t *data, uint32_t size);
};

#endif // !DATA_BUFFER_HPP
