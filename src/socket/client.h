#pragma once

#include "socket.h"

#include <string>

namespace sock
{
  namespace client
  {

    class Socket
    {
    public:
      Socket(const std::string &serverAddress, const uint16_t serverPort);
      void sendMessage(const std::string &request);
      const std::string receiveMessage();

    private:
      sock::Socket mClientSocket;
    };

  }
}