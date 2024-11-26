#include "client.h"

#include "../socket/mockClientSocket.h"
#include "../ui/mockOutput.h"

#include <gtest/gtest.h>

namespace messaging
{
  namespace test
  {
    using ::testing::Return;
    using ::testing::InSequence;

    TEST(a_client, forwards_messages_to_the_client_socket_on_sendMessage)
    {
      std::unique_ptr<sock::test::MockClientSocket> clientSocket = std::make_unique<sock::test::MockClientSocket>();
      sock::test::MockClientSocket *mockClientSocket = clientSocket.get();

      Client client{std::move(clientSocket), std::make_unique<ui::test::MockOutput>()};

      const std::string ok{"Ok"};

      EXPECT_CALL(*mockClientSocket, sendMessage(ok)).Times(1);

      client.sendMessage(ok);      
    }

    //TEST(a_client, outputs_messages_it_receives_to_the_output_ui)
    //{
      //std::unique_ptr<sock::test::MockClientSocket> clientSocket = std::make_unique<sock::test::MockClientSocket>();
      //sock::test::MockClientSocket *mockClientSocket = clientSocket.get();
      //std::unique_ptr<ui::test::MockOutput> output = std::make_unique<ui::test::MockOutput>();
      //ui::test::MockOutput *mockOutput = output.get();
      //Client client{std::move(clientSocket), std::move(output)};
      //const std::string ok{"Ok"};

      //InSequence s;

      //EXPECT_CALL(*mockClientSocket, receiveMessage()).WillRepeatedly(Return(ok));
      //EXPECT_CALL(*mockOutput, printMessage(ok));

      //client.startReceivingMessages();
    //}

  }

}