#include <gtest/gtest.h>

#include "health.hxx"

#include <stdexcept>

static int constexpr FULL_HEALTH = 1000;

struct HealthTests : testing::Test {
  rpg::Health health{};
};

TEST_F(HealthTests, healthStartsAt1000)
{
  EXPECT_EQ(FULL_HEALTH, health);
}

TEST_F(HealthTests, healthCanBeReduced)
{
  health -= 10;
  EXPECT_EQ(FULL_HEALTH-10, health);
}

TEST_F(HealthTests, healthReductionByNegativeValueThrowsException)
{
  auto const reduceHealthByNegativeValue = [this] {
    health -= (-10);
  };
  EXPECT_THROW(reduceHealthByNegativeValue(), std::invalid_argument);
}

TEST_F(HealthTests, healthCannotFallBelow0)
{
  health -= (FULL_HEALTH+10);
  EXPECT_EQ(0, health);
}

TEST_F(HealthTests, healthCanBeRestored)
{
  health -= 50;
  health += 25;
  EXPECT_EQ(FULL_HEALTH-25, health);
}

TEST_F(HealthTests, healthRestorationByNegativeValueThrowsException)
{
  auto const restoreHealthByNegativeValue = [this] {
    health += (-10);
  };
  EXPECT_THROW(restoreHealthByNegativeValue(), std::invalid_argument);
}

TEST_F(HealthTests, healthCannotBeRaisedOver1000)
{
  health += 10;
  EXPECT_EQ(FULL_HEALTH, health);
}
