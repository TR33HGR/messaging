#include "client.h"

#include <iostream>

int main()
{
  const std::string rpcRequest{R"({"jsonrpc": "2.0", "method": "echo", "params": {"message": "Hello World!"}, "id": 1})"};

  sock::client::Socket clientSocket{"127.0.0.1", 5000};
  clientSocket.sendMessage(rpcRequest);
  const std::string rpcResponse{clientSocket.receiveMessage()};
  std::cout << "Response: " << rpcResponse << std::endl;

  return 0;
}
