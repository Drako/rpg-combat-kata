#include <gtest/gtest.h>

#include "character.hxx"
#include "combat.hxx"

TEST(CombatTests, charactersCanAttackEachOther)
{
  int const fullHealth = rpg::Health{};
  rpg::Character ernie{};
  rpg::Character bert{};
  rpg::Combat::attack(ernie, bert, 42);
  rpg::Combat::attack(bert, ernie, 23);
  EXPECT_EQ(fullHealth - 42, bert.health());
  EXPECT_EQ(fullHealth - 23, ernie.health());
}

TEST(CombatTests, charactersCannotAttackThemselves)
{
  rpg::Character bob{};
  int const oldHealth = bob.health();
  rpg::Combat::attack(bob, bob, 10);
  EXPECT_EQ(oldHealth, bob.health());
}
