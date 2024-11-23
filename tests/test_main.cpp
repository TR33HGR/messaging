#include "Thing.h"
#include "MockLogger.h"
#include "Timeout.h"
#include <gtest/gtest.h>

using namespace std::chrono_literals;

TEST(the_thing, logs_on_contruction)
{
  std::unique_ptr<MockLogger> logger = std::make_unique<MockLogger>();

  EXPECT_CALL(*logger, log).Times(1);

  TEST_TIMEOUT_BEGIN
    // assertion that might hang
    int i = 1;
    i++;
  TEST_TIMEOUT_END(100ms)

  Thing thing{std::move(logger)};
}
