#include "serverSocket.h"
#include "server.h"

#include <iostream>
#include <regex>


int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "No arguments found: Please provide arguments in the form: <server ip>:<server port>";
    return 1;
  }

  std::string address;
  uint16_t port;

  std::string argument{argv[1]};
  std::regex pattern(R"((.*?):(\d+))");
  std::smatch match;

  if (std::regex_match(argument, match, pattern))
  {
    address = match[1];
    port = std::stoul(match[2]);
  }
  else
  {
    std::cerr << "Address or port malformed: Please provide arguments in the form: <server ip>:<server port>";
    return 1;
  }

  std::cout << "Address: " << address << std::endl;
  std::cout << "Port: " << port << std::endl;

  try
  {
    std::unique_ptr<messaging::Server> server = messaging::createServer(address, port);

    server->startAcceptingConnections();
  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }

  return 0;
}
