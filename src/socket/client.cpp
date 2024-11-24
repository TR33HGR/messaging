#include "client.h"

namespace sock
{

  Client::Client(const std::string &serverAddress, const uint16_t serverPort)
      : mClientSocket{}
  {
    mClientSocket.connectToServer(serverAddress, serverPort);
  }

  void Client::sendMessage(const std::string &message)
  {
    mClientSocket.sendMessage(message);
  }

  const std::string Client::receiveMessage()
  {
    return mClientSocket.receiveMessage();
  }

}