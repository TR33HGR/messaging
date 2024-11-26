#include "client.h"
#include "clientSocket.h"
#include "output.h"

#include <iostream>

namespace messaging
{

  using namespace std::chrono_literals;

  Client::Client(std::unique_ptr<sock::IClientSocket> s, std::unique_ptr<ui::IOutput> o)
      : mClientSocket{std::move(s)}, mOutput{std::move(o)}
  {
  }

  void Client::sendMessage(const std::string &message)
  {
    std::async([&] { mClientSocket->sendMessage(message); });
  }

  void Client::startReceivingMessages()
  {
    mReceiveThread = std::thread{[&]{
      try
      {
        while (true)
        {
          std::future<std::string> messageReceived = std::async(std::launch::async, [&]
                                                                { return mClientSocket->receiveMessage(); });
          mOutput->printMessage(messageReceived.get());
        }
      }
      catch (std::runtime_error e)
      {
        std::cerr << e.what();
      }
    }};
  }

}