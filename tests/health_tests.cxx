#include <gtest/gtest.h>

#include "health.hxx"

static int constexpr FULL_HEALTH = 1000;

TEST(HealthTest, healthStartsAt1000)
{
  rpg::Health health;
  EXPECT_EQ(FULL_HEALTH, health);
}
