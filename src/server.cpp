#include "serverSocket.h"

#include <future>
#include <iostream>
#include <thread>

void readMessages(sock::Connection connection)
{
  try
  {
    while (true)
    {
      std::future<std::string> requestReceived = std::async(std::launch::async, [&]
                                                            { return connection.receiveMessage(); });
      requestReceived.wait();
      std::cout << "Request: " << requestReceived.get() << std::endl;

      connection.sendMessage("Ok");
    }
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
    return;
  }
}

int main()
{
  std::vector<std::thread> threadPool;
  try
  {
    std::unique_ptr<sock::ServerSocket> serverSocket = sock::createServerSocket("192.168.0.249", 5000);
    while (true)
    {
      std::future<sock::Connection> connectionMade = std::async(std::launch::async, [&]
                                                                { return serverSocket->acceptConnection(); });

      connectionMade.wait();
      threadPool.emplace_back([&]()
                              { readMessages(connectionMade.get()); });
    }
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }

  for (auto &t : threadPool)
  {
    t.join();
  }

  return 0;
}
