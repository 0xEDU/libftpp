#include "../includes/client.hpp"

void Client::cleanup() {
  isConnected = false;
  if (clientSocket != -1) {
    if (close(clientSocket) == -1) {
      perror("close");
    }
    clientSocket = -1;
  }
  actions.clear();
}

void Client::connect(const std::string &address, const size_t port) {
  if (clientSocket = socket(AF_INET, SOCK_STREAM, 0); clientSocket == -1) {
    perror("socket");
    cleanup();
    return;
  }

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1) {
    throw std::runtime_error(
        "Failed to set the non-blocking mode on socket file descriptor");
  }

  sockaddr_in serverAddress = {};
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(port);

  hostent *host = gethostbyname(address.c_str());
  if (host == nullptr) {
    perror("gethostbyname");
    cleanup();
    return;
  }

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
  serverAddress.sin_addr = *(struct in_addr *)*host->h_addr_list;

  if (::connect(clientSocket, (struct sockaddr *)&serverAddress,
                sizeof(serverAddress)) < 0 &&
      errno != EINPROGRESS) {
    perror("connect");
    cleanup();
    return;
  }

  isConnected = true;
}

void Client::disconnect() {
  if (clientSocket != -1 && close(clientSocket) == -1) {
    perror("close");
    cleanup();
    return;
  }
  isConnected = false;
  clientSocket = -1;
  actions.clear();
}

void Client::defineAction(
    const Message::Type &messageType,
    const std::function<void(const Message &msg)> &action) {
  actions[messageType] = action;
}

void Client::send(const Message &msg) {
  if (!isConnected) {
    return;
  }
  std::vector<uint8_t> payload = msg.serialize();

  uint32_t msgSize = payload.size();

  if (::send(clientSocket, &msgSize, sizeof(msgSize), 0) == -1) {
    perror("send");
    cleanup();
    return;
  }

  if (::send(clientSocket, payload.data(), payload.size(), 0) == -1) {
    perror("send");
    cleanup();
    return;
  }
}

void Client::update() {
  if (!isConnected) {
    return;
  }
  std::array<uint8_t, 4> sizeBuffer = {};
  ssize_t bytesReceived =
      ::recv(clientSocket, sizeBuffer.data(), sizeof(uint32_t), 0);

  if (bytesReceived > 0) {
    uint32_t msgSize = 0;
    std::memcpy(&msgSize, sizeBuffer.data(), 4);
    std::vector<uint8_t> rawBuffer(msgSize);

    while (true) {
      ssize_t bytesRead = ::recv(clientSocket, rawBuffer.data(), msgSize, 0);
      if (bytesRead <= 0 || bytesRead == msgSize) {
        break;
      }
    }

    Message msg;
    msg.deserialize(rawBuffer);

    auto actionIt = actions.find(msg.type());
    if (actionIt != actions.end()) {
      actionIt->second(msg);
    }
  } else if (bytesReceived == 0) {
    // Server disconnected
    disconnect();
    return;
  }
}
