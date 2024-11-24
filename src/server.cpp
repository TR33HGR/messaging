#include "server.h"

#include <iostream>

int main()
{
  try
  {
    sock::server::Socket serverSocket{"127.0.0.1", 5000};
    const std::string request{serverSocket.receiveMessage()};
    std::cout << "Request: " << request << std::endl;

    serverSocket.sendMessage("Ok");
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }


  return 0;
}
