#include "server.h"
#include "socket.h"

namespace sock
{

  Server::Server(const std::string &serverAddress, const uint16_t serverPort)
      : mServerSocket{}
  {
    mServerSocket.bindAsServer(serverAddress, serverPort);
  }

  Connection Server::acceptConnection()
  {
    return {mServerSocket.acceptConnection()};
  }

  Connection::Connection(sock::Socket s) : mAcceptSocket{s} {}

  const std::string Connection::receiveMessage()
  {
    return mAcceptSocket.receiveMessage();
  }

  void Connection::sendMessage(const std::string &message)
  {
    mAcceptSocket.sendMessage(message);
  }
}