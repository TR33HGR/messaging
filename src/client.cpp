#include "clientSocket.h"
#include "client.h"

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main()
{
  try
  {
    messaging::Client client{sock::createClientSocket("192.168.0.249", 5000)};
    while(true)
    {
      client.sendMessage("PING");
      std::this_thread::sleep_for(1s);
    }
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }

  return 0;
}
