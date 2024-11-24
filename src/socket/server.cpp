#include "server.h"
#include "socket.h"

namespace sock
{
  namespace server
  {

    Socket::Socket(const std::string &serverAddress, const uint16_t serverPort)
    {
      sock::Socket serverSocket{};
      serverSocket.bindAsServer(serverAddress, serverPort);
      mAcceptSocket = serverSocket.acceptConnections();
    }

    const std::string Socket::receiveMessage()
    {
      return mAcceptSocket.receiveMessage();
    }

    void Socket::sendMessage(const std::string &message)
    {
      mAcceptSocket.sendMessage(message);
    }

  }
}