#include "server.h"

#include <iostream>

int main()
{
  try
  {
    server::Socket serverSocket{"192.168.0.249", 5000};
    serverSocket.receive();
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }


  return 0;
}
