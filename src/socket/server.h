#pragma once

#include "socket.h"

#include <string>

namespace sock
{
  namespace server
  {

    class Socket
    {
    public:
      Socket(const std::string &serverAddress, const uint16_t serverPort);
      const std::string receiveMessage();
      void sendMessage(const std::string &message);

    private:
      sock::Socket mAcceptSocket;
    };
  }
}