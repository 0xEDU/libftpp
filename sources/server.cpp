#include "../includes/server.hpp"

void Server::start(const size_t &p_port) {
  // Create socket
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    perror("socket");
    return;
  }

  fcntl(serverSocket, F_SETFL, O_NONBLOCK);

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
  // Check for new connections
  sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int clientSocket =
      accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
  if (clientSocket >= 0) {
    long long clientID = clientSockets.size();
    clientSockets[clientID] = clientSocket;
  } else if (errno != EAGAIN && errno != EWOULDBLOCK) {
    perror("accept");
    return;
  }

  // Check for messages from clients
  for (auto it = clientSockets.begin(); it != clientSockets.end();) {
    long long clientID = it->first;
    int socket = it->second;

    Message msg;
    ssize_t bytesReceived = recv(socket, &msg, sizeof(msg), 0);
    if (bytesReceived > 0) {
      auto actionIt = actions.find(msg.type());
      if (actionIt != actions.end()) {
        actionIt->second(clientID, msg);
      }
    } else if (bytesReceived == 0) {
      // Client disconnected
      close(socket);
      it = clientSockets.erase(it);
      continue;
    } else if (errno != EAGAIN && errno != EWOULDBLOCK) {
      perror("recv");
      close(socket);
      it = clientSockets.erase(it);
      continue;
    }
    ++it;
  }
}
