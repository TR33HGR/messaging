#pragma once

#include "socket.h"

#include <string>

namespace sock
{

  class Client
  {
  public:
    Client(const std::string &serverAddress, const uint16_t serverPort);
    void sendMessage(const std::string &request);
    const std::string receiveMessage();

  private:
    std::unique_ptr<sock::ISocket> mClientSocket;
  };

}