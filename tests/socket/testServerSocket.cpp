#include "serverSocket.h"

#include "mockSocket.h"

#include <gtest/gtest.h>

namespace sock
{
  namespace test
  {
    using ::testing::Return;

    TEST(a_server, binds_a_server_socket_on_creation)
    {
      std::unique_ptr<MockSocket> socket = std::make_unique<MockSocket>();
      MockSocket *mockSocket = socket.get();
      const std::string serverAddress{"127.0.0.1"};
      const uint16_t serverPort{5000};

      EXPECT_CALL(*mockSocket, bindAsServer(serverAddress, serverPort)).Times(1);

      ServerSocket server{serverAddress, serverPort, std::move(socket)};
    }

    TEST(a_server, receives_a_Connection_when_a_socket_connection_is_accepted)
    {
      std::unique_ptr<MockSocket> socket = std::make_unique<MockSocket>();
      MockSocket *mockSocket = socket.get();
      ServerSocket server{"127.0.0.1", 5000, std::move(socket)};

      EXPECT_CALL(*mockSocket, acceptConnection()).Times(1).WillOnce(Return(std::make_unique<MockSocket>()));

      std::shared_ptr<IConnection> connection = server.acceptConnection();
    }

    TEST(a_connection, sends_messages_to_the_socket_on_sendMessage)
    {
      std::unique_ptr<MockSocket> socket = std::make_unique<MockSocket>();
      MockSocket *mockSocket = socket.get();
      Connection connection{std::move(socket)};
      const std::string message{"test message"};

      EXPECT_CALL(*mockSocket, sendMessage(message)).Times(1);

      connection.sendMessage(message);
    }

    TEST(a_connection, reads_message_from_socket_on_receiveMessage)
    {
      std::unique_ptr<MockSocket> socket = std::make_unique<MockSocket>();
      MockSocket *mockSocket = socket.get();
      Connection connection{std::move(socket)};
      const std::string message{"test message"};

      EXPECT_CALL(*mockSocket, receiveMessage()).Times(1).WillOnce(Return(message));

      const auto receivedMessage = connection.receiveMessage();

      EXPECT_EQ(message, receivedMessage);
    }

  }

}