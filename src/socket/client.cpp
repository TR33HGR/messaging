#include "client.h"

namespace sock
{

  Client::Client(const std::string &serverAddress, const uint16_t serverPort, std::unique_ptr<ISocket> s)
      : mClientSocket{std::move(s)}
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