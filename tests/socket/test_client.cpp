#include "client.h"

#include "mockSocket.h"

#include <gtest/gtest.h>

namespace sock
{
  namespace test
  {

    TEST(a_client, connects_to_specified_server_on_creation)
    {
      std::unique_ptr<MockSocket> socket = std::make_unique<MockSocket>();
      MockSocket *mockSocket = socket.get();
      const std::string serverAddress{"127.0.0.1"};
      const uint16_t serverPort{5000};

      EXPECT_CALL(*mockSocket, connectToServer(serverAddress, serverPort)).Times(1);

      Client client{serverAddress, serverPort, std::move(socket)};
    }
  }

}