#include "client.h"

#include <iostream>

int main()
{
  const std::string rpcRequest{R"({"jsonrpc": "2.0", "method": "echo", "params": {"message": "Hello World!"}, "id": 1})"};

  client::Socket clientSocket{"192.168.0.71", 5000};
  const std::string rpcResponse{clientSocket.send(rpcRequest)};
  std::cout << "Response: " << rpcResponse << std::endl;

  return 0;
}
