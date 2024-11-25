#include "socket.h"

#include <iostream>
#include <sstream>

namespace
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

  const sockaddr_in socketAddress(const std::string &address, const uint16_t port)
  {
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(address.c_str());
    service.sin_port = htons(port);
    return service;
  }

}

namespace sock
{

  Socket::Socket()
      : mSocket{INVALID_SOCKET}
  {
    initialiseWebsocket(&mSocket);
  }

  Socket::Socket(SOCKET s)
      : mSocket{s}
  {
  }

  void Socket::connectToServer(const std::string &address, const uint16_t port)
  {
    sockaddr_in clientService{socketAddress(address, port)};

    if (connect(mSocket, reinterpret_cast<SOCKADDR *>(&clientService), sizeof(clientService)) == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "Client: connect() - Failed to connect: " << WSAGetLastError();
      WSACleanup();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Client: Connect() is OK!" << std::endl;
    std::cout << "Client: Can start sending and receiving data..." << std::endl;
  }

  void Socket::bindAsServer(const std::string &serverAddress, const uint16_t serverPort)
  {
    sockaddr_in service{socketAddress(serverAddress, serverPort)};

    if (bind(mSocket, reinterpret_cast<SOCKADDR *>(&service), sizeof(service)) == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "bind() failed: " << WSAGetLastError();
      closesocket(mSocket);
      WSACleanup();
      throw std::runtime_error{error.str()};
    }
    std::cout << "bind() is OK!" << std::endl;

    if (listen(mSocket, SOMAXCONN) == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "listen() failed: " << WSAGetLastError();
      closesocket(mSocket);
      throw std::runtime_error{error.str()};
    }
    std::cout << "listen() is OK!" << std::endl;
  }

  std::unique_ptr<ISocket> Socket::acceptConnection()
  {
    SOCKET acceptSocket;
    acceptSocket = accept(mSocket, nullptr, nullptr);

    if (acceptSocket == INVALID_SOCKET)
    {
      std::ostringstream error;
      error << "accept failed: " << WSAGetLastError();
      WSACleanup();
      throw std::runtime_error{error.str()};
    }
    std::cout << "accept() is OK!" << std::endl;
    return std::make_unique<Socket>(acceptSocket);
  }

  const std::string Socket::receiveMessage()
  {
    char receiveBuffer[200];
    int rbyteCount = recv(mSocket, receiveBuffer, 200, 0);
    if (rbyteCount < 0)
    {
      std::ostringstream error;
      error << "Server recv error: " << WSAGetLastError();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Received data: " << receiveBuffer << std::endl;

    return {receiveBuffer, (uint16_t)rbyteCount};
  }

  void Socket::sendMessage(const std::string &message)
  {
    int sbyteCount = send(mSocket, message.c_str(), message.length(), 0);
    if (sbyteCount == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "Server send error: " << WSAGetLastError();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Server: Sent " << sbyteCount << " bytes" << std::endl;
  }

}