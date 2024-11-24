#include "client.h"

namespace sock
{
  namespace client
  {

    Socket::Socket(const std::string &serverAddress, const uint16_t serverPort)
        : mClientSocket{}
    {
      mClientSocket.connectToServer(serverAddress, serverPort);
    }

    void Socket::sendMessage(const std::string &message)
    {
      mClientSocket.sendMessage(message);
    }

    const std::string Socket::receiveMessage()
    {
      return mClientSocket.receiveMessage();
    }

  }
}