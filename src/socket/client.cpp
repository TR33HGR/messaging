#include "client.h"

#include <iostream>
#include <sstream>

namespace
{

  void initialiseWebsocket(SOCKET *clientSocket)
  {
    WSADATA wsaData;
    int wserr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wserr = WSAStartup(wVersionRequested, &wsaData);

    if (wserr != 0)
    {
      throw std::runtime_error{"The winsock dll not found"};
    }
    std::cout << "The Winsock dll found" << std::endl;
    std::cout << "The status: " << wsaData.szSystemStatus << std::endl;

    *clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (*clientSocket == INVALID_SOCKET)
    {
      std::ostringstream error;
      error << "Error at socket(): " << WSAGetLastError();
      WSACleanup();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Socket is OK!" << std::endl;
  }

  void connectToServer(const std::string &address, const uint16_t port, SOCKET *clientSocket)
  {
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(address.c_str());
    clientService.sin_port = htons(port);

    if (connect(*clientSocket, reinterpret_cast<SOCKADDR *>(&clientService), sizeof(clientService)) == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "Client: connect() - Failed to connect: " << WSAGetLastError();
      WSACleanup();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Client: Connect() is OK!" << std::endl;
    std::cout << "Client: Can start sending and receiving data..." << std::endl;
  }

  void sendRequest(const std::string &request, SOCKET *clientSocket)
  {
    int sbyteCount = send(*clientSocket, request.c_str(), request.length(), 0);
    if (sbyteCount == SOCKET_ERROR)
    {
      std::ostringstream error;
      error << "Client send error: " << WSAGetLastError();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Client: Sent " << sbyteCount << " bytes" << std::endl;
  }

  const std::string receiveResponse(SOCKET *clientSocket)
  {
    char receiveBuffer[200];
    int rbyteCount = recv(*clientSocket, receiveBuffer, 200, 0);
    if (rbyteCount < 0)
    {
      std::ostringstream error;
      error << "Client recv error: " << WSAGetLastError();
      throw std::runtime_error{error.str()};
    }
    std::cout << "Client: Received data: " << receiveBuffer << std::endl;

    return {receiveBuffer, (uint16_t)rbyteCount};
  }

}

namespace client
{

  Socket::Socket(const std::string &serverAddress, const uint16_t serverPort)
      : mClientSocket{INVALID_SOCKET}
  {
    initialiseWebsocket(&mClientSocket);
    connectToServer(serverAddress, serverPort, &mClientSocket);
  }

  const std::string Socket::send(const std::string &request)
  {
    sendRequest(request, &mClientSocket);
    return receiveResponse(&mClientSocket);
  }

}