#ifndef SERVER_HPP
#define SERVER_HPP

#include "../includes/message.hpp"

#include <cstddef>
#include <fcntl.h>
#include <functional>
#include <map>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Server {
  int serverSocket;
  std::map<Message::Type,
           std::function<void(long long &clientID, const Message &msg)>>
      actions;
  std::map<long long, int> clientSockets; // clientID -> socket

public:
  Server() = default;
  ~Server() = default;

  void start(const size_t &p_port);
  void defineAction(const Message::Type &messageType,
                    const std::function<void(long long &clientID,
                                             const Message &msg)> &action);
  void sendTo(const Message &msg, long long &clientID);
  void sendToArray(const Message &message, std::vector<long long> clientIDs);
  void sendToAll(const Message &message);
  void update();
};

#endif // !SERVER_HPP
