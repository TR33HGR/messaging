#pragma once

#include "socket.h"

#include <string>
#include <memory>

namespace sock
{
  class Connection;

  class Server
  {
  public:
    Server(const std::string &serverAddress, const uint16_t serverPort, std::unique_ptr<ISocket>);

    Connection acceptConnection();

  private:
    std::unique_ptr<ISocket> mServerSocket;
  };

  class Connection
  {
  public:
    Connection(std::unique_ptr<ISocket>);
    const std::string receiveMessage();
    void sendMessage(const std::string &message);

  private:
    std::unique_ptr<ISocket> mAcceptSocket;
  };

  std::unique_ptr<Server> createServer(const std::string &serverAddress, const uint16_t serverPort);
}