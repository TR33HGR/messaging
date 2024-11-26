#pragma once

#include <memory>
#include <string>
#include <future>

namespace sock
{
  class IClientSocket;
}

namespace messaging
{

  class Client
  {
  public:
    Client(std::unique_ptr<sock::IClientSocket>);
    void sendMessage(const std::string &message);

  private:
    std::unique_ptr<sock::IClientSocket> mClientSocket;
    std::future<void> mMessagesSent;
  };
}