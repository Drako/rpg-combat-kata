#include <gtest/gtest.h>

#include "target.hxx"

TEST(TargetTests, targetsHaveHealth)
{
  EXPECT_TRUE((std::is_same<decltype(std::declval<rpg::Target const&>().health()), rpg::Health>::value));
}

TEST(TargetTests, targetsCanTakeDamage)
{
  EXPECT_TRUE((std::is_same<decltype(std::declval<rpg::Target&>().takeDamage(std::declval<int>())), void>::value));
}

TEST(TargetTests, targetsMayBeInFactions)
{
  EXPECT_TRUE(
      (std::is_same<decltype(std::declval<rpg::Target&>().factions()), std::unordered_set<std::string> const&>::value));
}
