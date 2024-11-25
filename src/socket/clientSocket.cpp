#include "clientSocket.h"

namespace sock
{

  ClientSocket::ClientSocket(const std::string &serverAddress, const uint16_t serverPort, std::unique_ptr<ISocket> s)
      : mClientSocket{std::move(s)}
  {
    mClientSocket->connectToServer(serverAddress, serverPort);
  }

  void ClientSocket::sendMessage(const std::string &message)
  {
    mClientSocket->sendMessage(message);
  }

  const std::string ClientSocket::receiveMessage()
  {
    return mClientSocket->receiveMessage();
  }

  std::unique_ptr<IClientSocket> createClientSocket(const std::string &serverAddress, const uint16_t serverPort)
  {
    return std::make_unique<ClientSocket>(serverAddress, serverPort, std::make_unique<Socket>());
  }

}