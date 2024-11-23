#include "Log.h"

#include <gmock/gmock.h>

class MockLogger: public ILogger
{
public:
    MOCK_METHOD(void, log, (const char*), (override));
};