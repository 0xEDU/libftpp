#include "../includes/server.hpp"

// Pollfd operator overloads
auto operator==(const pollfd &lhs, const pollfd &rhs) -> bool {
  return (lhs.events == rhs.events && lhs.fd == rhs.fd &&
          lhs.revents == rhs.revents);
};

auto operator==(const pollfd &pollfd, const int &clientFd) -> bool {
  return (pollfd.fd == clientFd);
}

void Server::start(const size_t &p_port) {
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    perror("socket");
    return;
  }

  const int ENABLE = 1;
  if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &ENABLE, sizeof(int)) <
      0) {
    throw std::runtime_error("Failed to set socket options");
  }

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1) {
    throw std::runtime_error(
        "Failed to set the non-blocking mode on socket file descriptor");
  }

  sockaddr_in serverAddr = {};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(p_port);

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) <
      0) {
    perror("bind");
    close(serverSocket);
    return;
  }

  if (listen(serverSocket, SOMAXCONN) < 0) {
    perror("listen");
    close(serverSocket);
    return;
  }

  pollFDs.push_back({serverSocket, POLLIN, 0});
}

void Server::defineAction(
    const Message::Type &messageType,
    const std::function<void(long long &clientID, const Message &msg)>
        &action) {
  actions[messageType] = action;
}

void Server::sendTo(const Message &msg, long long &clientID) {
  auto clientSocket = clientSockets.find(clientID);
  if (clientSocket == clientSockets.end()) {
    return;
  }
  int socket = clientSocket->second;
  std::vector<uint8_t> payload = msg.serialize();
  uint32_t msgSize = payload.size();

  if (::send(socket, &msgSize, sizeof(msgSize), 0) == -1) {
    perror("send");
    return;
  }

  if (::send(socket, payload.data(), payload.size(), 0) == -1) {
    perror("send");
    return;
  }
}

void Server::sendToArray(const Message &message,
                         const std::vector<long long> &clientIDs) {
  for (auto clientID : clientIDs) {
    auto clientSocket = clientSockets.find(clientID);
    if (clientSocket == clientSockets.end()) {
      // Client not found
      continue;
    }
    int socket = clientSocket->second;
    std::vector<uint8_t> payload = message.serialize();
    uint32_t msgSize = payload.size();

    if (::send(socket, &msgSize, sizeof(msgSize), 0) == -1) {
      perror("send");
      return;
    }

    if (::send(socket, payload.data(), payload.size(), 0) == -1) {
      perror("send");
      return;
    }
  }
}

void Server::sendToAll(const Message &message) {
  for (auto &clientSocket : clientSockets) {
    int socket = clientSocket.second;
    std::vector<uint8_t> payload = message.serialize();
    uint32_t msgSize = payload.size();

    if (::send(socket, &msgSize, sizeof(msgSize), 0) == -1) {
      perror("send");
      return;
    }

    if (::send(socket, payload.data(), payload.size(), 0) == -1) {
      perror("send");
      return;
    }
  }
}

void Server::acceptClient() {
  sockaddr_in clientAddr = {};
  socklen_t clientAddrLen = sizeof(clientAddr);
  int clientSocket =
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
      accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
  if (clientSocket >= 0) {
    long long clientID = clientSockets.size(); // NOLINT
    clientSockets[clientID] = clientSocket;
    pollFDs.push_back({clientSocket, POLLIN, 0});
  } else if (errno != EAGAIN && errno != EWOULDBLOCK) {
    perror("accept");
    return;
  }
}

void Server::closeClients(const std::vector<int> &clientIDs) {
  for (auto clientID : clientIDs) {
    auto clientSocket = clientSockets.find(clientID);
    if (clientSocket != clientSockets.end()) {
      close(clientSocket->second);
      clientSockets.erase(clientSocket);
      pollFDs.erase(std::remove_if(pollFDs.begin(), pollFDs.end(),
                                   [clientID](const pollfd &pfd) {
                                     return pfd.fd == clientID;
                                   }),
                    pollFDs.end());
    }
  }
}

void Server::update() {
  std::vector<int> shouldCloseClients;

  if (poll(pollFDs.data(), pollFDs.size(), 0) < 0) {
    perror("poll");
    return;
  }

  if ((pollFDs[0].revents & POLLIN) == POLLIN) {
    acceptClient();
  }

  for (auto it = clientSockets.begin(); it != clientSockets.end(); it++) {
    auto pollIt = std::find(pollFDs.begin(), pollFDs.end(), it->second);
    if ((pollIt->revents & POLLIN) == POLLIN) {
      long long clientID = it->first;
      int socket = it->second;

      std::array<uint8_t, 4> sizeBuffer = {};
      ssize_t bytesReceived =
          recv(socket, sizeBuffer.data(), sizeof(sizeBuffer), 0);
      if (bytesReceived < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
          perror("recv");
          shouldCloseClients.push_back(clientID);
        }
        continue;
      }
      uint32_t msgSize = 0;
      std::memcpy(&msgSize, sizeBuffer.data(), 4);
      std::vector<uint8_t> rawBuffer(msgSize);

      while (true) {
        ssize_t bytesRead = recv(socket, rawBuffer.data(), msgSize, 0);
        if (bytesRead <= 0 || bytesRead == msgSize) {
          break;
        }
      }

      Message msg;
      msg.deserialize(rawBuffer);

      auto actionIt = actions.find(msg.type());
      if (actionIt != actions.end()) {
        actionIt->second(clientID, msg);
      }
    }
    closeClients(shouldCloseClients);
  }
}
