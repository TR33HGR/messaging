#pragma once

#include "socket.h"

#include <string>

namespace sock
{
  class Connection;

  class Server
  {
  public:
    Server(const std::string &serverAddress, const uint16_t serverPort);

    Connection acceptConnection();

  private:
    sock::Socket mServerSocket;
  };

  class Connection
  {
  public:
    Connection(sock::Socket);
    const std::string receiveMessage();
    void sendMessage(const std::string &message);

  private:
    sock::Socket mAcceptSocket;
  };
}