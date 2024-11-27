#pragma once

#include <memory>
#include <string>
#include <future>

namespace sock
{
  class IClientSocket;
}

namespace ui
{
  class IOutput;
}

namespace messaging
{

  class Client
  {
  public:
    Client(std::unique_ptr<sock::IClientSocket>, const std::string &username);
    void sendMessage(const std::string &message);
    void startReceivingMessages(std::function<void(std::string)> outputMessage);

  private:
    std::unique_ptr<sock::IClientSocket> mClientSocket;
    const std::string mUsername;

    std::thread mReceiveThread;
  };

  std::unique_ptr<Client> createClient(const std::string &serverAddress, const uint16_t serverPort, const std::string &username);
}
