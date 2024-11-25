#include "client.h"

#include "../socket/mockClientSocket.h"

#include <gtest/gtest.h>

namespace messaging
{
  namespace test
  {
    using ::testing::Return;

    TEST(a_client, waits_for_ok_from_server_on_creation)
    {
      std::unique_ptr<sock::test::MockClientSocket> clientSocket = std::make_unique<sock::test::MockClientSocket>();
      sock::test::MockClientSocket *mockClientSocket = clientSocket.get();
      const std::string ok{"Ok"};

      EXPECT_CALL(*mockClientSocket, receiveMessage()).Times(1).WillOnce(Return(ok));
      
      Client client{std::move(clientSocket)};
    }

  }

}