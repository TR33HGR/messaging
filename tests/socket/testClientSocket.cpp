#include "clientSocket.h"

#include "mockSocket.h"

#include <gtest/gtest.h>

namespace sock
{
  namespace test
  {
    using ::testing::Return;

    TEST(a_client, connects_to_specified_server_on_creation)
    {
      std::unique_ptr<MockSocket> socket = std::make_unique<MockSocket>();
      MockSocket *mockSocket = socket.get();
      const std::string serverAddress{"127.0.0.1"};
      const uint16_t serverPort{5000};

      EXPECT_CALL(*mockSocket, connectToServer(serverAddress, serverPort)).Times(1);

      ClientSocket client{serverAddress, serverPort, std::move(socket)};
    }

    TEST(a_client, sends_messages_to_the_socket_on_sendMessage)
    {
      std::unique_ptr<MockSocket> socket = std::make_unique<MockSocket>();
      MockSocket *mockSocket = socket.get();
      ClientSocket client{"127.0.0.1", 5000, std::move(socket)};
      const std::string message{"test message"};

      EXPECT_CALL(*mockSocket, sendMessage(message)).Times(1);

      client.sendMessage(message);
    }

    TEST(a_client, reads_message_from_socket_on_receiveMessage)
    {
      std::unique_ptr<MockSocket> socket = std::make_unique<MockSocket>();
      MockSocket *mockSocket = socket.get();
      ClientSocket client{"127.0.0.1", 5000, std::move(socket)};
      const std::string message{"test message"};

      EXPECT_CALL(*mockSocket, receiveMessage()).Times(1).WillOnce(Return(message));

      const auto receivedMessage = client.receiveMessage();

      EXPECT_EQ(message, receivedMessage);
    }
  }

}