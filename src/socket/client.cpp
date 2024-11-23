#include "client.h"
#include "socket.h"

#include <iostream>
#include <sstream>

namespace
{

  void connectToServer(const std::string &address, const uint16_t port, SOCKET *clientSocket)
  {
    sockaddr_in clientService{sock::socketAddress(address, port)};

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
    sock::sendMessage(request, clientSocket);
  }

  const std::string receiveResponse(SOCKET *clientSocket)
  {
    return sock::receiveMessage(clientSocket);
  }

}

namespace client
{

  Socket::Socket(const std::string &serverAddress, const uint16_t serverPort)
      : mClientSocket{INVALID_SOCKET}
  {
    sock::initialiseWebsocket(&mClientSocket);
    connectToServer(serverAddress, serverPort, &mClientSocket);
  }

  const std::string Socket::send(const std::string &request)
  {
    sendRequest(request, &mClientSocket);
    return receiveResponse(&mClientSocket);
  }

}