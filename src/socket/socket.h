#pragma once

#include <winsock2.h>
#include <string>

namespace sock
{
  class Socket
  {
  public:
    Socket();
    Socket(SOCKET);

    const std::string receiveMessage();
    void sendMessage(const std::string message);

    // client
    void connectToServer(const std::string &address, const uint16_t port);

    // server
    void bindAsServer(const std::string &serverAddress, const uint16_t serverPort);
    Socket acceptConnection();

  private:
    SOCKET mSocket;
  };

}
