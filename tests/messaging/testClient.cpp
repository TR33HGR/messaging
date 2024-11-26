#include "client.h"

#include "../socket/mockClientSocket.h"

#include <gtest/gtest.h>

namespace messaging
{
  namespace test
  {
    using ::testing::Return;

    TEST(a_client, forwards_messages_to_the_client_socket_on_sendMessage)
    {
      std::unique_ptr<sock::test::MockClientSocket> clientSocket = std::make_unique<sock::test::MockClientSocket>();
      sock::test::MockClientSocket *mockClientSocket = clientSocket.get();
      Client client{std::move(clientSocket)};
      const std::string ok{"Ok"};

      EXPECT_CALL(*mockClientSocket, sendMessage(ok)).Times(1);

      client.sendMessage(ok);      
    }

  }

}