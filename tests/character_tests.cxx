#include <gtest/gtest.h>

#include "character.hxx"
#include "health.hxx"

#include <sstream>
#include <type_traits>

struct CharacterTypeOutputParams final {
  rpg::CharacterType type;
  std::string expected;
};

std::ostream& operator<<(std::ostream& os, CharacterTypeOutputParams const& params)
{
  return os << "{ type: " << static_cast<std::underlying_type_t<rpg::CharacterType>>(params.type) << ", expected: \""
            << params.expected << "\"}";
}

using CharacterTypeTests = testing::TestWithParam<CharacterTypeOutputParams>;

TEST_P(CharacterTypeTests, streamingOperatorShouldYieldExpectedOutput)
{
  auto const param = GetParam();
  std::ostringstream stream;
  stream << param.type;
  EXPECT_EQ(param.expected, stream.str());
}

INSTANTIATE_TEST_SUITE_P(Output, CharacterTypeTests, testing::Values(
    CharacterTypeOutputParams{rpg::CharacterType::Melee, "CharacterType::Melee"},
    CharacterTypeOutputParams{rpg::CharacterType::Ranged, "CharacterType::Ranged"},
    CharacterTypeOutputParams{static_cast<rpg::CharacterType>(42), "CharacterType::[Invalid]"}
));

struct CharacterTests : testing::Test {
  rpg::Character character{};

  static void kill(rpg::Character& c)
  {
    c.takeDamage(c.health());
  }
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
  EXPECT_EQ(oldHealth-42, character.health());
}

TEST_F(CharacterTests, characterDiesIfTakingTooMuchDamage)
{
  kill(character);
  EXPECT_FALSE(character.alive());
}

TEST_F(CharacterTests, charactersCanBeHealed)
{
  int const oldHealth = character.health();
  character.takeDamage(42);
  character.restore(23);
  EXPECT_EQ(oldHealth-19, character.health());
}

TEST_F(CharacterTests, deadCharactersCannotBeHealed)
{
  kill(character);
  character.restore(23);
  EXPECT_EQ(0, character.health());
  EXPECT_FALSE(character.alive());
}

TEST_F(CharacterTests, charactersAreMeleeByDefault)
{
  EXPECT_EQ(rpg::CharacterType::Melee, character.type());
  EXPECT_FLOAT_EQ(2.f, character.range());
}

TEST_F(CharacterTests, charactersCanBeCreatedWithExplicitType)
{
  rpg::Character const fighter{rpg::CharacterType::Melee};
  EXPECT_EQ(rpg::CharacterType::Melee, fighter.type());
  EXPECT_FLOAT_EQ(2.f, fighter.range());

  rpg::Character const ranger{rpg::CharacterType::Ranged};
  EXPECT_EQ(rpg::CharacterType::Ranged, ranger.type());
  EXPECT_FLOAT_EQ(20.f, ranger.range());
}

TEST_F(CharacterTests, charactersStartAtCenterOfWorldByDefault)
{
  auto const position = character.position();
  EXPECT_FLOAT_EQ(0.f, position.x);
  EXPECT_FLOAT_EQ(0.f, position.y);
}

struct CharacterStartingPositionTests : CharacterTests, testing::WithParamInterface<rpg::Position> {
};

TEST_P(CharacterStartingPositionTests, charactersCanStartAtDifferentPosition)
{
  auto const expected = GetParam();
  rpg::Character const bob{expected};
  auto const position = bob.position();
  EXPECT_FLOAT_EQ(expected.x, position.x);
  EXPECT_FLOAT_EQ(expected.y, position.y);
}

INSTANTIATE_TEST_SUITE_P(StartingPosition, CharacterStartingPositionTests, testing::Values(
    rpg::Position{1.f, 0.f},
    rpg::Position{-1.f, 0.f},
    rpg::Position{0.f, 1.f},
    rpg::Position{0.f, -1.f}
));

TEST_F(CharacterTests, charactersShouldBeAbleToMove)
{
  character.moveTo({23.f, 42.f});
  auto const position = character.position();
  EXPECT_FLOAT_EQ(23.f, position.x);
  EXPECT_FLOAT_EQ(42.f, position.y);
}

TEST_F(CharacterTests, charactersBelongToNoFactionsByDefault)
{
  EXPECT_TRUE(character.factions().empty());
}

TEST_F(CharacterTests, charactersMayJoinOrLeaveMultipleFactions)
{
  character.join("A-Team");
  std::unordered_set<std::string> const onlyATeam{"A-Team"};
  EXPECT_EQ(onlyATeam, character.factions());

  character.join("Mystery Inc.", "Ghostbusters");
  std::unordered_set<std::string> const all{"A-Team", "Mystery Inc.", "Ghostbusters"};
  EXPECT_EQ(all, character.factions());

  character.leave("A-Team", "Ghostbusters");
  std::unordered_set<std::string> const onlyMysteryInc{"Mystery Inc."};
  EXPECT_EQ(onlyMysteryInc, character.factions());

  character.leave("Mystery Inc.");
  EXPECT_TRUE(character.factions().empty());
}

TEST_F(CharacterTests, charactersAreTargets)
{
  rpg::Character bob{};
  bob.join("Network");

  rpg::Target& target = bob;

  auto const oldHealth = target.health();
  EXPECT_EQ(bob.health(), oldHealth);

  target.takeDamage(42);
  EXPECT_EQ(oldHealth-42, target.health());

  EXPECT_EQ(bob.factions(), target.factions());
}
