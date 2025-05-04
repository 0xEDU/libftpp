#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "../includes/data_buffer.hpp"
#include "../includes/thread_safe_iostream.hpp"

class Message {
	int m_type;
	mutable DataBuffer m_dataBuffer;

public:
	using Type = int;

	Message() = default;
	Message(const Message&);
	Message& operator=(const Message&);
	~Message() = default;

	Message(Type type);
	int type();
	int type() const;

	template<typename T>
	friend const Message& operator<<(const Message&, const T& object);

	template<typename T>
	friend const Message& operator>>(const Message&, T& object);

	void serialize(DataBuffer& buffer) const {
		buffer << m_type;
		buffer << m_dataBuffer;
	}

	void deserialize(DataBuffer& buffer) {
		buffer >> m_type;
		buffer >> m_dataBuffer;
	}
};

template<typename T>
const Message& operator<<(const Message& msg, const T& object) {
	msg.m_dataBuffer << object;
	return msg;
}

template<typename T>
const Message& operator>>(const Message& msg, T& object) {
	msg.m_dataBuffer >> object;
	return msg;
}

#endif // !MESSAGE_HPP
