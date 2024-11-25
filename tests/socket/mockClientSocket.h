#include "clientSocket.h"

#include <gmock/gmock.h>

namespace sock
{
  namespace test
  {

    class MockClientSocket : public IClientSocket
    {
    public:
      MOCK_METHOD(const std::string, receiveMessage, (), (override));
      MOCK_METHOD(void, sendMessage, (const std::string &), (override));
    };
  }
}