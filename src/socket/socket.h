#pragma once

#include <winsock2.h>
#include <string>
#include <memory>

namespace sock
{
  class ISocket
  {
  public:
    virtual ~ISocket() = default;

    virtual const std::string receiveMessage() = 0;
    virtual void sendMessage(const std::string &message) = 0;

    // client
    virtual void connectToServer(const std::string &address, const uint16_t port) = 0;

    // server
    virtual void bindAsServer(const std::string &serverAddress, const uint16_t serverPort) = 0;
    virtual std::unique_ptr<ISocket> acceptConnection() = 0;
  };

  class Socket: public ISocket
  {
  public:
    Socket();
    Socket(SOCKET);

    const std::string receiveMessage() override;
    void sendMessage(const std::string &message) override;

    // client
    void connectToServer(const std::string &address, const uint16_t port) override;

    // server
    void bindAsServer(const std::string &serverAddress, const uint16_t serverPort) override;
    std::unique_ptr<ISocket> acceptConnection() override;

  private:
    SOCKET mSocket;
  };

}
