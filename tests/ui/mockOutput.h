#include "output.h"

#include <gmock/gmock.h>

namespace ui
{
  namespace test
  {

    class MockOutput : public IOutput
    {
    public:
      MOCK_METHOD(void, printMessage, (const std::string &), (override));
    };
  }
}