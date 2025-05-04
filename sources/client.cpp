#include "../includes/client.hpp"

void Client::connect(const std::string &address, const size_t port) {
  if (clientSocket = socket(AF_INET, SOCK_STREAM, 0); clientSocket == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(port);

	hostent *host = gethostbyname(address.c_str());
	if (host == nullptr) {
		herror("gethostbyname");
		exit(EXIT_FAILURE);
	}
	serverAddress.sin_addr = *(struct in_addr *)*host->h_addr_list;

  if (::connect(clientSocket, (struct sockaddr *)&serverAddress,
                sizeof(serverAddress)) == -1) {
    perror("connect");
    exit(EXIT_FAILURE);
  }
}

void Client::disconnect() {
  if (close(clientSocket) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }
  clientSocket = -1;
}

void Client::defineAction(
    const Message::Type &messageType,
    const std::function<void(const Message &msg)> &action) {
  actions[messageType] = action;
}

void Client::send(const Message &msg) {
	DataBuffer msgData;
	msg.serialize(msgData);

	DataBuffer payload;
	payload << msgData.size();
	payload << msgData.data();
	if (::send(clientSocket, payload.data(), payload.size(), 0) == -1) {
		perror("send");
		exit(EXIT_FAILURE);
	}
}

void Client::update() {
	Message msg;
	if (recv(clientSocket, &msg, sizeof(msg), 0) == -1) {
		perror("recv");
		exit(EXIT_FAILURE);
	}

	auto it = actions.find(msg.type());
	if (it != actions.end()) {
		it->second(msg);
	}
}
