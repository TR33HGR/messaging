#pragma once

#include <winsock2.h>
#include <string>

namespace sock
{

  void initialiseWebsocket(SOCKET *);
  const std::string receiveMessage(SOCKET *);
  void sendMessage(const std::string message, SOCKET *);

  const sockaddr_in socketAddress(const std::string &address, const uint16_t port);

}
