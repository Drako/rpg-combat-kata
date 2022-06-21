#include <gtest/gtest.h>

#include "character.hxx"
#include "health.hxx"

struct CharacterTests: testing::Test
{
  rpg::Character character{};
};

TEST_F(CharacterTests, characterStartsAliveWithFullHealthAtLevel1)
{
  int const fullHealth = static_cast<int>(rpg::Health{});
  EXPECT_EQ(fullHealth, character.health());
  EXPECT_EQ(1, character.level());
  EXPECT_TRUE(character.alive());
}
