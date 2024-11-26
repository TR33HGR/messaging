#include "serverSocket.h"
#include "socket.h"

namespace sock
{

  ServerSocket::ServerSocket(const std::string &serverAddress, const uint16_t serverPort, std::unique_ptr<ISocket> s)
      : mServerSocket{std::move(s)}
  {
    mServerSocket->bindAsServer(serverAddress, serverPort);
  }

  std::shared_ptr<IConnection> ServerSocket::acceptConnection()
  {
    return std::make_shared<Connection>(mServerSocket->acceptConnection());
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

  std::unique_ptr<ServerSocket> createServerSocket(const std::string &serverAddress, const uint16_t serverPort)
  {
    return std::make_unique<ServerSocket>(serverAddress, serverPort, std::make_unique<Socket>());
  }
}