#pragma once

#include <memory>
#include <string>
#include <future>
#include <map>

namespace sock
{
  class IServerSocket;
  class IConnection;
}

namespace messaging
{

  class Server
  {
  public:
    Server(std::unique_ptr<sock::IServerSocket>);
    void startAcceptingConnections();

  private:
    std::unique_ptr<sock::IServerSocket> mServerSocket;
    std::map<std::shared_ptr<sock::IConnection>, std::thread> mConnectionThread;

    void startReceivingMessagesThread(std::shared_ptr<sock::IConnection>);
    void sendMessageToClients(const std::string &message);
  };

  std::unique_ptr<Server> createServer(const std::string &serverAddress, const uint16_t serverPort);
}