#include <gtest/gtest.h>

#include "character.hxx"
#include "health.hxx"

struct CharacterTests: testing::Test
{
  rpg::Character character{};
};

TEST_F(CharacterTests, characterStartsAliveWithFullHealthAtLevel1)
{
  int const fullHealth = rpg::Health{};
  EXPECT_EQ(fullHealth, character.health());
  EXPECT_EQ(1, character.level());
  EXPECT_TRUE(character.alive());
}

TEST_F(CharacterTests, charactersCanTakeDamage)
{
  int const oldHealth = character.health();
  character.takeDamage(42);
  EXPECT_EQ(oldHealth - 42, character.health());
}

TEST_F(CharacterTests, characterDiesIfTakingTooMuchDamage)
{
  character.takeDamage(character.health());
  EXPECT_FALSE(character.alive());
}
