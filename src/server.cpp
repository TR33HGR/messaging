#include "server.h"

#include <iostream>

int main()
{
  try
  {
    sock::Server serverSocket{"127.0.0.1", 5000};
    sock::Connection connection{serverSocket.acceptConnection()};
    const std::string request{connection.receiveMessage()};
    std::cout << "Request: " << request << std::endl;

    connection.sendMessage("Ok");
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }


  return 0;
}
