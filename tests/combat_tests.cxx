#include <gtest/gtest.h>

#include "character.hxx"
#include "combat.hxx"

static void setLevel(rpg::Character &character, int const level)
{
  struct CharacterData final
  {
    rpg::Health health;
    int level;
    bool alive;
  };
  reinterpret_cast<CharacterData &>(character).level = level;
}

static int constexpr LEVEL_THRESHOLD = 5;

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

TEST(CombatTests, charactersCanHealThemselves)
{
  rpg::Character heinz{};
  int const oldHealth = heinz.health();
  heinz.takeDamage(250);
  rpg::Combat::heal(heinz, 100);
  EXPECT_EQ(oldHealth - 150, heinz.health());
}

TEST(CombatTests, charactersTake50PercentMoreDamageFromStrongEnemies)
{
  rpg::Character strong{};
  ::setLevel(strong, 1 + LEVEL_THRESHOLD);
  rpg::Character weak{};
  int const oldHealth = weak.health();

  rpg::Combat::attack(strong, weak, 10);
  EXPECT_EQ(oldHealth - 15, weak.health());
}

TEST(CombatTests, charactersTake50PercentLessDamageFromWeakEnemies)
{
  rpg::Character weak{};
  rpg::Character strong{};
  ::setLevel(strong, 1 + LEVEL_THRESHOLD);
  int const oldHealth = strong.health();

  rpg::Combat::attack(weak, strong, 10);
  EXPECT_EQ(oldHealth - 5, weak.health());
}
