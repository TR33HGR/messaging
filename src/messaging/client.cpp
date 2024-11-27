#include "client.h"
#include "clientSocket.h"
#include "output.h"

#include <iostream>

namespace messaging
{

  using namespace std::chrono_literals;

  Client::Client(std::unique_ptr<sock::IClientSocket> s, const std::string &username)
      : mClientSocket{std::move(s)}, mUsername{username}
  {
  }

  void Client::sendMessage(const std::string &message)
  {
    std::async([&] {
      mClientSocket->sendMessage({mUsername + ": " + message});
    });
  }

  void Client::startReceivingMessages(std::function<void(std::string)> outputMessage)
  {
    if (mReceiveThread.joinable())
    {
      std::cerr << "Already receiving messages";
      return;
    }
    mReceiveThread = std::thread{[&, outputMessage]{
      try
      {
        while (true)
        {
          std::future<std::string> messageReceived = std::async(std::launch::async, [&]
                                                                { return mClientSocket->receiveMessage(); });
          outputMessage(messageReceived.get());
        }
      }
      catch (std::runtime_error e)
      {
        std::cerr << e.what();
      }
    }};
  }

  std::unique_ptr<Client> createClient(const std::string &serverAddress, const uint16_t serverPort, const std::string &username)
  {
    return std::make_unique<Client>(sock::createClientSocket(serverAddress, serverPort), username);
  }
}