#include <gtest/gtest.h>

#include "health.hxx"

static int constexpr FULL_HEALTH = 1000;

TEST(HealthTests, healthStartsAt1000)
{
  rpg::Health health;
  EXPECT_EQ(FULL_HEALTH, health);
}

TEST(HealthTests, healthCanBeReduced)
{
  rpg::Health health;
  health -= 10;
  EXPECT_EQ(FULL_HEALTH - 10, health);
}
