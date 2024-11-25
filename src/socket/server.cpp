#include "server.h"
#include "socket.h"

namespace sock
{

  Server::Server(const std::string &serverAddress, const uint16_t serverPort, std::unique_ptr<ISocket> s)
      : mServerSocket{std::move(s)}
  {
    mServerSocket->bindAsServer(serverAddress, serverPort);
  }

  Connection Server::acceptConnection()
  {
    return {mServerSocket->acceptConnection()};
  }

  Connection::Connection(std::unique_ptr<sock::ISocket> s) : mAcceptSocket{std::move(s)} {}

  const std::string Connection::receiveMessage()
  {
    return mAcceptSocket->receiveMessage();
  }

  void Connection::sendMessage(const std::string &message)
  {
    mAcceptSocket->sendMessage(message);
  }

  std::unique_ptr<Server> createServer(const std::string &serverAddress, const uint16_t serverPort)
  {
    return std::make_unique<Server>(serverAddress, serverPort, std::make_unique<Socket>());
  }
}