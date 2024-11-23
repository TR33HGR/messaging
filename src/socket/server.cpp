#include "server.h"

#include <iostream>
#include <sstream>

namespace
{
  void initialiseWebsocket(SOCKET *serverSocket)
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

    *serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (*serverSocket == INVALID_SOCKET)
    {
      std::ostringstream error;
      error << "Error at socket(): " << WSAGetLastError();
      WSACleanup();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Socket is OK!" << std::endl;
  }

  void bindSocket(const std::string &serverAddress, const uint16_t serverPort, SOCKET *serverSocket)
  {
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(serverAddress.c_str());
    service.sin_port = htons(serverPort);

    if (bind(*serverSocket, reinterpret_cast<SOCKADDR *>(&service), sizeof(service)) == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "bind() failed: " << WSAGetLastError();
      closesocket(*serverSocket);
      WSACleanup();
      throw std::runtime_error{error.str()};
    }
    std::cout << "bind() is OK!" << std::endl;

    if (listen(*serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "listen() failed: " << WSAGetLastError();
      closesocket(*serverSocket);
      throw std::runtime_error{error.str()};
    }
    std::cout << "listen() is OK!" << std::endl;
  }

  SOCKET acceptConnections(SOCKET *serverSocket)
  {
    SOCKET acceptSocket;
    acceptSocket = accept(*serverSocket, nullptr, nullptr);

    if (acceptSocket == INVALID_SOCKET)
    {
      std::ostringstream error;
      error << "accept failed: " << WSAGetLastError();
      WSACleanup();
      throw std::runtime_error{error.str()};
    }
    std::cout << "accept() is OK!" << std::endl;
    return acceptSocket;
  }

  const std::string receiveRequest(SOCKET *acceptSocket)
  {
    char receiveBuffer[200];
    int rbyteCount = recv(*acceptSocket, receiveBuffer, 200, 0);
    if (rbyteCount < 0)
    {
      std::ostringstream error;
      error << "Server recv error: " << WSAGetLastError();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Received data: " << receiveBuffer << std::endl;

    return {receiveBuffer, (uint16_t)rbyteCount};
  }

  void sendResponse(const std::string response, SOCKET *acceptSocket)
  {
    int sbyteCount = send(*acceptSocket, response.c_str(), response.length(), 0);
    if (sbyteCount == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "Server send error: " << WSAGetLastError();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Server: Sent " << sbyteCount << " bytes" << std::endl;
  }

}

namespace server
{

  Socket::Socket(const std::string &serverAddress, const uint16_t serverPort)
  {
    SOCKET serverSocket{INVALID_SOCKET};
    initialiseWebsocket(&serverSocket);
    bindSocket(serverAddress, serverPort, &serverSocket);
    mAcceptSocket = acceptConnections(&serverSocket);
  }

  void Socket::receive()
  {
    const std::string request{receiveRequest(&mAcceptSocket)};
    std::cout << "Request " << request << std::endl;

    const std::string response{"OK"};
    sendResponse(response, &mAcceptSocket);
  }

}