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
  Message(const Message &rhs);
  Message(Message &&rhs) = delete;
  auto operator=(const Message &rhs) -> Message &;
  ~Message() = default;

  Message(Type type);
  auto type() -> int;
  auto type() const -> int;

  template <typename T>
  friend auto operator<<(const Message &, const T &) -> const Message &;

  template <typename T>
  friend auto operator>>(const Message &, T &) -> const Message &;

  auto serialize() const -> std::vector<uint8_t> {
    // Squash type and data in a single buffer
    std::vector<uint8_t> buffer;

    buffer.reserve(sizeof(m_type) + m_dataBuffer.size());
    buffer.insert(buffer.end(), reinterpret_cast<const uint8_t *>(&m_type),
                  reinterpret_cast<const uint8_t *>(&m_type) + sizeof(m_type));
    buffer.insert(buffer.end(), m_dataBuffer.data(),
                  m_dataBuffer.data() + m_dataBuffer.size());
    return buffer;
  }

  void deserialize(std::vector<uint8_t> &buffer) {
    // Unpack type and data from a single buffer
    if (buffer.size() < sizeof(m_type)) {
      throw std::runtime_error("Not enough data to deserialize message");
    }
    std::memcpy(&m_type, buffer.data(), sizeof(m_type));
    buffer.erase(buffer.begin(), buffer.begin() + sizeof(m_type));

    m_dataBuffer.load(buffer.data(), buffer.size());
    buffer.clear();
  }
};

template <typename T>
auto operator<<(const Message &msg, const T &object) -> const Message & {
  msg.m_dataBuffer << object;
  return msg;
}

template <typename T>
auto operator>>(const Message &msg, T &object) -> const Message & {
  msg.m_dataBuffer >> object;
  return msg;
}

#endif // !MESSAGE_HPP
