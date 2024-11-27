#include "server.h"
#include "serverSocket.h"

#include <iostream>

namespace messaging
{

  Server::Server(std::unique_ptr<sock::IServerSocket> s)
      : mServerSocket{std::move(s)}
  {
  }

  void Server::startAcceptingConnections()
  {
    while (true)
    {
      std::future<std::shared_ptr<sock::IConnection>> connectionMade = std::async([&]
                                                                                  { return mServerSocket->acceptConnection(); });

      std::shared_ptr<sock::IConnection> connection = connectionMade.get();
      mConnectionThread.emplace(connection, [&, connection]
                                { startReceivingMessagesThread(connection); });
    }
  }

  void Server::startReceivingMessagesThread(std::shared_ptr<sock::IConnection> connection)
  {
    try
    {
      while (true)
      {
        std::future<std::string> messageReceived = std::async([&]
                                                              { return connection->receiveMessage(); });
        const std::string message = messageReceived.get();
        std::async([&, message]
                   { sendMessageToClients(message); });
      }
    }
    catch (std::runtime_error e)
    {
      std::cerr << e.what();
    };
  }

  void Server::sendMessageToClients(const std::string &message)
  {
    for (const auto &[connection, thread] : mConnectionThread)
    {
      std::async([&]
                 { return connection->sendMessage(message); });
    }
  }

  std::unique_ptr<Server> createServer(const std::string &serverAddress, const uint16_t serverPort)
  {
    return std::make_unique<Server>(sock::createServerSocket(serverAddress, serverPort));
  }

}