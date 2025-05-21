#include "../includes/server.hpp"
#include "../includes/thread_safe_iostream.hpp"
#include <string>

auto main() -> int {
  Server server;
  const int SERVER_PORT = 8080;

  // Define an action for messages of type 1 (int)
  server.defineAction(1, [&server](long long &clientID, const Message &msg) {
    int value = 0;
    msg >> value;
    threadSafeCout << "Received an int " << value << " from client " << clientID
                   << '\n';

    // Send back a message of type 3 with double the value
    Message replyMsg(3);
    replyMsg << (value * 2);
    server.sendTo(replyMsg, clientID);
  });

  // Define an action for messages of type 2 (size_t followed by characters)
  server.defineAction(2, [](long long &clientID, const Message &msg) {
    size_t length = 0;
    std::string text;
    msg >> length;
    text.reserve(length);
    for (size_t i = 0; i < length; ++i) {
      char chr = 0;
      msg >> chr;
      text.push_back(chr);
    }
    threadSafeCout << "Received a string '" << text << "' of length " << length
                   << " from client " << clientID << '\n';
  });

  // Start the server on port 8080
  server.start(SERVER_PORT);

  bool quit = false;

  while (!quit) {
    server.update();

    threadSafeCout << "Server updated." << '\n';
    threadSafeCout << "Available operations :" << '\n';
    threadSafeCout << " - [Q]uit : close the program" << '\n';
    threadSafeCout << " - Any other input to continue updating the server"
                   << '\n';

    std::string input;
    std::getline(std::cin, input);

    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char chr) { return std::tolower(chr); });

    if (input == "quit" || (input.length() == 1 && input[0] == 'q')) {
      quit = true;
    }
  }

  return 0;
}
