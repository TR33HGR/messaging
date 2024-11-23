#pragma once

#include <winsock2.h>
#include <string>

namespace server
{

  class Socket
  {
  public:
    Socket(const std::string &serverAddress, const uint16_t serverPort);
    void receive();

  private:
    SOCKET mAcceptSocket;
  };

}