#include <gtest/gtest.h>

#include "health.hxx"

TEST(HealthTest, healthStartsAt1000)
{
  rpg::Health health;
  EXPECT_EQ(1000, health);
}
