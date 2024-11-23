#include <gtest/gtest.h>

using namespace std::chrono_literals;

TEST(zero, is_false)
{
  ASSERT_FALSE(0);
}
