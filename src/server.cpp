#include "serverSocket.h"
#include "server.h"

#include <future>
#include <iostream>
#include <thread>


int main()
{
  try
  {
    messaging::Server server{sock::createServerSocket("192.168.0.249", 5000)};
    server.startAcceptingConnections();
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }

  return 0;
}
