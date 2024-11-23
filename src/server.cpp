#include "server.h"

#include <iostream>

int main()
{
  try
  {
    server::Socket serverSocket{"127.0.0.1", 5000};
    serverSocket.receive();
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }


  return 0;
}
