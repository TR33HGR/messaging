#include "client.h"

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main()
{
  const std::string rpcRequest{R"({"jsonrpc": "2.0", "method": "echo", "params": {"message": "Hello World!"}, "id": 1})"};

  try
  {
    sock::Client clientSocket{"192.168.0.249", 5000, std::make_unique<sock::Socket>()};
    while (true)
    {
      clientSocket.sendMessage(rpcRequest);
      std::future<std::string> requestResponse = std::async(std::launch::async, [&]
                                                            { return clientSocket.receiveMessage(); });
      requestResponse.wait();
      std::cout << "Response: " << requestResponse.get() << std::endl;

      std::this_thread::sleep_for(2s);
    }
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }

  return 0;
}
