#pragma once

#include "socket.h"

#include <string>
#include <memory>

namespace sock
{
  class IConnection;

  class IServerSocket
  {
  public:
    virtual ~IServerSocket() = default;

    virtual std::shared_ptr<IConnection> acceptConnection() = 0;
  };

  class ServerSocket: public IServerSocket
  {
  public:
    ServerSocket(const std::string &serverAddress, const uint16_t serverPort, std::unique_ptr<ISocket>);

    std::shared_ptr<IConnection> acceptConnection() override;

  private:
    std::unique_ptr<ISocket> mServerSocket;
  };

  class IConnection
  {
  public:
    virtual ~IConnection() = default;

    virtual const std::string receiveMessage() = 0;
    virtual void sendMessage(const std::string &request) = 0;
  };

  class Connection: public IConnection
  {
  public:
    Connection(std::unique_ptr<ISocket>);
    const std::string receiveMessage() override;
    void sendMessage(const std::string &message) override;

  private:
    std::unique_ptr<ISocket> mAcceptSocket;
  };

  std::unique_ptr<ServerSocket> createServerSocket(const std::string &serverAddress, const uint16_t serverPort);
}