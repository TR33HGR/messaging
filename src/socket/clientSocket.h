#pragma once

#include "socket.h"

#include <string>

namespace sock
{

  class IClientSocket
  {
  public:
    virtual ~IClientSocket() = default;
    virtual void sendMessage(const std::string &request) = 0;
    virtual const std::string receiveMessage() = 0;
  };

  class ClientSocket: public IClientSocket
  {
  public:
    ClientSocket(const std::string &serverAddress, const uint16_t serverPort, std::unique_ptr<ISocket>);
    void sendMessage(const std::string &request) override;
    const std::string receiveMessage() override;

  private:
    std::unique_ptr<ISocket> mClientSocket;
  };

  std::unique_ptr<IClientSocket> createClientSocket(const std::string &serverAddress, const uint16_t serverPort);
}