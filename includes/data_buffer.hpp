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

	DataBuffer &operator<<(const std::string &str);
	DataBuffer &operator>>(std::string &str);
};
