#pragma once

#include <winsock2.h>
#include <string>

namespace client
{

  class Socket
  {
  public:
    Socket(const std::string &serverAddress, const uint16_t serverPort);
    const std::string send(const std::string &request);

  private:
    SOCKET mClientSocket;
  };

}