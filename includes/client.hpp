#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../includes/message.hpp"

#include <arpa/inet.h>
#include <cstddef>
#include <cstdint>
#include <fcntl.h>
#include <functional>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class Client {
  int clientSocket = 0;
  std::map<Message::Type, std::function<void(const Message &msg)>> actions;

public:
  Client() = default;
  Client(const Client &rhs) = delete;
  auto operator=(const Client &rhs) -> Client & = delete;
  Client(Client &&rhs) = delete;
  ~Client() = default;

  void connect(const std::string &address, const size_t port);
  void disconnect();
  void defineAction(const Message::Type &messageType,
                    const std::function<void(const Message &msg)> &action);
  void send(const Message &msg) const;
  void update();
};

#endif // !CLIENT_HPP
