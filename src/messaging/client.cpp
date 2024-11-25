#include "client.h"
#include "clientSocket.h"

namespace messaging
{

  Client::Client(std::unique_ptr<sock::IClientSocket> s)
  {
    s->receiveMessage();
  }

}