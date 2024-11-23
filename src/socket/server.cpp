#include "server.h"
#include "socket.h"

#include <iostream>
#include <sstream>

namespace
{

  void bindSocket(const std::string &serverAddress, const uint16_t serverPort, SOCKET *serverSocket)
  {
    sockaddr_in service{sock::socketAddress(serverAddress, serverPort)};

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
    return sock::receiveMessage(acceptSocket);
  }

  void sendResponse(const std::string response, SOCKET *acceptSocket)
  {
    sock::sendMessage(response, acceptSocket);
  }

}

namespace server
{

  Socket::Socket(const std::string &serverAddress, const uint16_t serverPort)
  {
    SOCKET serverSocket{INVALID_SOCKET};
    sock::initialiseWebsocket(&serverSocket);
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