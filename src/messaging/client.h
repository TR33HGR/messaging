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
    Client(std::unique_ptr<sock::IClientSocket>, std::unique_ptr<ui::IOutput>);
    void sendMessage(const std::string &message);
    void startReceivingMessages();

  private:
    std::unique_ptr<sock::IClientSocket> mClientSocket;
    std::unique_ptr<ui::IOutput> mOutput;

    std::thread mReceiveThread;
  };
}