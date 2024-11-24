#include "client.h"

namespace sock
{

  Client::Client(const std::string &serverAddress, const uint16_t serverPort)
      : mClientSocket{std::make_unique<Socket>()}
  {
    mClientSocket->connectToServer(serverAddress, serverPort);
  }

  void Client::sendMessage(const std::string &message)
  {
    mClientSocket->sendMessage(message);
  }

  const std::string Client::receiveMessage()
  {
    return mClientSocket->receiveMessage();
  }

}