#include "../includes/message.hpp"

Message::Message(const Message &rhs) { *this = rhs; }

auto Message::operator=(const Message &rhs) -> Message & {
  if (this != &rhs) {
    m_type = rhs.m_type;
    m_dataBuffer = rhs.m_dataBuffer;
  }
  return *this;
}

Message::Message(Type type) : m_type(type) {}

auto Message::type() -> int { return m_type; }

auto Message::type() const -> int { return m_type; }
