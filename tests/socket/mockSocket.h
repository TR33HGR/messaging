#include "socket.h"

#include <gmock/gmock.h>

namespace sock
{
  namespace test
  {

    class MockSocket : public ISocket
    {
    public:
      MOCK_METHOD(const std::string, receiveMessage, (), (override));
      MOCK_METHOD(void, sendMessage, (const std::string &), (override));

      // client
      MOCK_METHOD(void, connectToServer, (const std::string &, const uint16_t), (override));

      // server
      MOCK_METHOD(void, bindAsServer, (const std::string &, const uint16_t), (override));
      MOCK_METHOD(std::unique_ptr<ISocket>, acceptConnection, (), (override));
    };
  }
}