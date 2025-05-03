#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "../includes/data_buffer.hpp"

class Message {
	using Type = int;

	Type m_type;
	DataBuffer m_dataBuffer;

public:

	Message() = default;
	Message(const Message&) = default;
	Message& operator=(const Message&) = default;
	~Message() = default;

	Message(Type type);
	int type();

	template<typename T>
	DataBuffer& operator<<(const T& object) {
		m_dataBuffer << object;
		return m_dataBuffer;
	}

	template<typename T>
	DataBuffer& operator>>(T& object) {
		m_dataBuffer >> object;
		return m_dataBuffer;
	}
};

#endif // !MESSAGE_HPP
