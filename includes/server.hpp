#ifndef SERVER_HPP
#define SERVER_HPP

#include "../includes/message.hpp"

#include <cstddef>
#include <fcntl.h>
#include <functional>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

class Server {
  int idCounter = 0;
  int serverSocket = 0;
  std::map<Message::Type,
           std::function<void(long long &clientID, const Message &msg)>>
      actions;
  std::map<long long, int> clientSockets; // clientID -> socket
  using pollfd = struct pollfd;
  std::vector<pollfd> pollFDs;

  void acceptClient();
  void closeClients(const std::vector<int> &clientIDs);

public:
  Server() = default;
  Server(const Server &rhs) = delete;
  Server(Server &&rhs) = delete;
  auto operator=(Server &&rhs) -> Server & = delete;
  auto operator=(const Server &rhs) -> Server & = delete;
  ~Server() = default;

  void start(const size_t &p_port);
  void defineAction(const Message::Type &messageType,
                    const std::function<void(long long &clientID,
                                             const Message &msg)> &action);
  void sendTo(const Message &msg, long long &clientID);
  void sendToArray(const Message &message,
                   const std::vector<long long> &clientIDs);
  void sendToAll(const Message &message);
  void update();
};

#endif // !SERVER_HPP
