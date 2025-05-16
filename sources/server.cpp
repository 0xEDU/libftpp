#include "../includes/server.hpp"

// Pollfd operator overloads
bool operator==(const pollfd &lhs, const pollfd &rhs) {
	return (lhs.events == rhs.events && lhs.fd == rhs.fd && lhs.revents == rhs.revents);
};

bool operator==(const pollfd &pollfd, const int &clientFd) {
	return (pollfd.fd == clientFd);
}


void Server::start(const size_t &p_port) {
  // Create socket
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    perror("socket");
    return;
  }

  const int ENABLE = 1;
  if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &ENABLE, sizeof(int)) <
      0)
    throw std::runtime_error("Failed to set socket options");

  if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
    throw std::runtime_error(
        "Failed to set the non-blocking mode on socket file descriptor");

  // Bind socket to port
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(p_port);

  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) <
      0) {
    perror("bind");
    close(serverSocket);
    return;
  }

  // Listen for incoming connections
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
  (void)clientID;
  (void)msg;
}

void Server::sendToArray(const Message &message,
                         std::vector<long long> clientIDs) {
  (void)message;
  (void)clientIDs;
}

void Server::sendToAll(const Message &message) { (void)message; }

// Server should handle multiple clients
// Clients will send a message to the server
// This should check:
// - If a new client is connected
// - If a client has disconnected
// - If a client has sent a message
void Server::update() {
  if (poll(pollFDs.data(), pollFDs.size(), 0) < 0) {
    perror("poll");
    return;
  }

  if ((pollFDs[0].revents & POLLIN) == POLLIN) {
    // New connection
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket =
        accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket >= 0) {
      long long clientID = clientSockets.size();
      clientSockets[clientID] = clientSocket;
      pollFDs.push_back({clientSocket, POLLIN, 0});
    } else if (errno != EAGAIN && errno != EWOULDBLOCK) {
      perror("accept");
      return;
    }
  }

  // Check for messages from clients
  for (auto it = clientSockets.begin(); it != clientSockets.end(); it++) {
    auto pollIt = std::find(pollFDs.begin(), pollFDs.end(), it->second);
    if ((pollIt->revents & POLLIN) == POLLIN) {
      long long clientID = it->first;
      int socket = it->second;

      uint8_t sizeBuffer[4];
      ssize_t bytesReceived = recv(socket, &sizeBuffer, sizeof(uint32_t), 0);
      if (bytesReceived > 0) {
        uint32_t msgSize;
        std::memcpy(&msgSize, sizeBuffer, 4);
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
      } else if (bytesReceived == 0) {
        // Client disconnected
        close(socket);
        it = clientSockets.erase(it);
        continue;
      }
    }
  }
}
