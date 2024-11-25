#pragma once

#include "socket.h"

#include <string>

namespace sock
{

  class Client
  {
  public:
    Client(const std::string &serverAddress, const uint16_t serverPort, std::unique_ptr<ISocket>);
    void sendMessage(const std::string &request);
    const std::string receiveMessage();

  private:
    std::unique_ptr<ISocket> mClientSocket;
  };

  std::unique_ptr<Client> createClient(const std::string &serverAddress, const uint16_t serverPort);
}