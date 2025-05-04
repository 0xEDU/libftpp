#include "../includes/message.hpp"

std::mutex ThreadSafeIOStream::mtx;
thread_local ThreadSafeIOStream threadSafeCout;

Message::Message(const Message &rhs) { *this = rhs; }

Message &Message::operator=(const Message &rhs) {
  if (this != &rhs) {
    m_type = rhs.m_type;
    m_dataBuffer = rhs.m_dataBuffer;
  }
  return *this;
}

Message::Message(int type) : m_type(type) {}

int Message::type() { return m_type; }

int Message::type() const { return m_type; }
