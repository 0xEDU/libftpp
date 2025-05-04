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
  DataBuffer(const DataBuffer &);
  DataBuffer &operator=(const DataBuffer &);
  ~DataBuffer();

	template<typename T>
	DataBuffer &operator<<(const T& object) {
		const uint8_t *data = reinterpret_cast<const uint8_t*>(&object);
		dataBuffer.insert(dataBuffer.end(), data, data + sizeof(T));
		return *this;
	}

	template<typename T>
	DataBuffer &operator>>(T& object) {
		if (dataBuffer.size() < sizeof(T)) {
			throw std::runtime_error("Not enough data to deserialize");
		}
		std::memcpy(&object, dataBuffer.data(), sizeof(T));
		dataBuffer.erase(dataBuffer.begin(), dataBuffer.begin() + sizeof(T));
		return *this;
	};

	template<typename T>
	friend const DataBuffer &operator<<(const DataBuffer &buffer, const T &object);

	template<typename T>
	friend const DataBuffer &operator>>(const DataBuffer &buffer, T &object);

	DataBuffer &operator<<(const std::string &str);
	DataBuffer &operator>>(std::string &str);
};

template<typename T>
const DataBuffer &operator<<(const DataBuffer &buffer, const T &object) {
	buffer << object;
	return buffer;
}

template<typename T>
const DataBuffer &operator>>(const DataBuffer &buffer, T &object) {
	buffer >> object;
	return buffer;
}

#endif // !DATA_BUFFER_HPP
