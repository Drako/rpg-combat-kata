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

TEST_F(HealthTests, thereCanBeAnAlternativeMaximumHealth)
{
  rpg::Health customHealth{2000};

  customHealth -= 200;
  EXPECT_EQ(1800, customHealth);

  customHealth += 100;
  EXPECT_EQ(1900, customHealth);

  customHealth += 200;
  EXPECT_EQ(2000, customHealth);
}

TEST_F(HealthTests, customHealthMaximumsMustBeGreaterThanZero)
{
  auto const constructZeroHealth = [this] {
    rpg::Health h{0};
  };
  EXPECT_THROW(constructZeroHealth(), std::invalid_argument);

  auto const constructNegativeHealth = [this] {
    rpg::Health h{-10};
  };
  EXPECT_THROW(constructNegativeHealth(), std::invalid_argument);
}
