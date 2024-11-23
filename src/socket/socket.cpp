#include "socket.h"

#include <iostream>
#include <sstream>

namespace sock
{
  void initialiseWebsocket(SOCKET *s)
  {
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    if (wsaerr != 0)
    {
      throw std::runtime_error{"The Winsock dll not found!"};
    }
    std::cout << "The Winsock dll found" << std::endl;
    std::cout << "The status: " << wsaData.szSystemStatus << std::endl;

    *s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (*s == INVALID_SOCKET)
    {
      std::ostringstream error;
      error << "Error at socket(): " << WSAGetLastError();
      WSACleanup();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Socket is OK!" << std::endl;
  }

  const std::string receiveMessage(SOCKET *s)
  {
    char receiveBuffer[200];
    int rbyteCount = recv(*s, receiveBuffer, 200, 0);
    if (rbyteCount < 0)
    {
      std::ostringstream error;
      error << "Server recv error: " << WSAGetLastError();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Received data: " << receiveBuffer << std::endl;

    return {receiveBuffer, (uint16_t)rbyteCount};
  }

  void sendMessage(const std::string message, SOCKET *s)
  {
    int sbyteCount = send(*s, message.c_str(), message.length(), 0);
    if (sbyteCount == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "Server send error: " << WSAGetLastError();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Server: Sent " << sbyteCount << " bytes" << std::endl;
  }

  const sockaddr_in socketAddress(const std::string &address, const uint16_t port)
  {
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(address.c_str());
    service.sin_port = htons(port);
    return service;
  }

}