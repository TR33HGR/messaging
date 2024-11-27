#include "clientSocket.h"
#include "client.h"
#include "output.h"
#include "input.h"

#include <iostream>
#include <regex>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "No arguments found: Please provide arguments in the form: <username> <server ip>:<server port>";
    return 1;
  }

  const std::string username{argv[1]};
  std::string address;
  uint16_t port;

  std::string argument{argv[2]};
  std::regex pattern(R"((.*?):(\d+))");
  std::smatch match;

  if (std::regex_match(argument, match, pattern))
  {
    address = match[1];
    port = std::stoul(match[2]);
  }
  else
  {
    std::cerr << "Address or port malformed: Please provide arguments in the form: <username> <server ip>:<server port>";
    return 1;
  }

  std::cout << "Username: " << username << std::endl;
  std::cout << "Address: " << address << std::endl;
  std::cout << "Port: " << port << std::endl;

  try
  {
    std::unique_ptr<messaging::Client> client = messaging::createClient(address, port, username);
    std::unique_ptr<ui::IOutput> standardOutput = std::make_unique<ui::Output>();
    std::unique_ptr<ui::IInput> standardInput = std::make_unique<ui::Input>();

    client->startReceivingMessages([&](const std::string &m)
                                   { standardOutput->printMessage(m); });

    standardInput->startReceivingInput([&](const std::string &m)
                                       { client->sendMessage(m); });

  }
  catch (std::runtime_error e)
  {
    std::cerr << e.what();
  }

  return 0;
}
