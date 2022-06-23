#include <gtest/gtest.h>

#include "damageable.hxx"
#include "character.hxx"

TEST(DamageableTests, damageableThingsHaveHealth)
{
  EXPECT_TRUE((std::is_same<decltype(std::declval<rpg::Damageable const&>().health()), rpg::Health>::value));
}

TEST(DamageableTests, damageableThingsCanTakeDamage)
{
  EXPECT_TRUE((std::is_same<decltype(std::declval<rpg::Damageable&>().takeDamage(std::declval<int>())), void>::value));
}

TEST(DamageableTests, damageableThingsMayBeInFactions)
{
  EXPECT_TRUE(
      (std::is_same<decltype(std::declval<rpg::Damageable&>().factions()), std::unordered_set<std::string> const&>::value));
}
