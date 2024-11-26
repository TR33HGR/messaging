#include "client.h"
#include "clientSocket.h"

#include <iostream>

namespace messaging
{

  using namespace std::chrono_literals;

  Client::Client(std::unique_ptr<sock::IClientSocket> s)
      : mClientSocket{std::move(s)}
  {
  }

  void Client::sendMessage(const std::string &message)
  {
    std::async([&] { mClientSocket->sendMessage(message); });
  }

}