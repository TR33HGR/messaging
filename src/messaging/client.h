#pragma once

#include <memory>

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

  private:
  };
}