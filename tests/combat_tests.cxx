#include <gtest/gtest.h>

#include "character.hxx"
#include "combat.hxx"

static void setLevel(rpg::Character& character, int const level)
{
  int const currentLevel = character.level();
  if (level>currentLevel) {
    for (int n = level-currentLevel; n--;)
      character.levelUp();
  }
}

static int constexpr LEVEL_THRESHOLD = 5;

TEST(CombatTests, charactersCanAttackEachOther)
{
  int const fullHealth = rpg::Health{};
  rpg::Character ernie{};
  rpg::Character bert{};
  rpg::Combat::attack(ernie, bert, 42);
  rpg::Combat::attack(bert, ernie, 23);
  EXPECT_EQ(fullHealth-42, bert.health());
  EXPECT_EQ(fullHealth-23, ernie.health());
}

TEST(CombatTests, charactersCannotAttackThemselves)
{
  rpg::Character bob{};
  int const oldHealth = bob.health();
  rpg::Combat::attack(bob, bob, 10);
  EXPECT_EQ(oldHealth, bob.health());
}

TEST(CombatTests, charactersCannotHealOtherCharacters)
{
  rpg::Character adrian{};
  adrian.join("Team Aqua");

  rpg::Character marc{};
  marc.join("Team Magma");

  int const oldHealth = marc.health();
  marc.takeDamage(250);
  rpg::Combat::heal(adrian, marc, 100);
  EXPECT_EQ(oldHealth-250, marc.health());
}

TEST(CombatTests, charactersCanHealThemselves)
{
  rpg::Character heinz{};
  int const oldHealth = heinz.health();
  heinz.takeDamage(250);
  rpg::Combat::heal(heinz, heinz, 100);
  EXPECT_EQ(oldHealth-150, heinz.health());
}

TEST(CombatTests, charactersCanHealAllies)
{
  rpg::Character jessy{};
  jessy.join("Team Rocket");

  rpg::Character james{};
  james.join("Team Rocket");

  int const oldHealth = james.health();
  james.takeDamage(250);
  rpg::Combat::heal(jessy, james, 100);
  EXPECT_EQ(oldHealth-150, james.health());
}

TEST(CombatTests, charactersTake50PercentMoreDamageFromStrongEnemies)
{
  rpg::Character strong{};
  ::setLevel(strong, 1+LEVEL_THRESHOLD);
  rpg::Character weak{};
  int const oldHealth = weak.health();

  rpg::Combat::attack(strong, weak, 10);
  EXPECT_EQ(oldHealth-15, weak.health());
}

TEST(CombatTests, charactersTake50PercentLessDamageFromWeakEnemies)
{
  rpg::Character weak{};
  rpg::Character strong{};
  ::setLevel(strong, 1+LEVEL_THRESHOLD);
  int const oldHealth = strong.health();

  rpg::Combat::attack(weak, strong, 10);
  EXPECT_EQ(oldHealth-5, strong.health());
}

struct CombatRangeTestParams final {
  rpg::CharacterType attackerType;
  rpg::Position targetPosition;
  bool shouldHit;
};

std::ostream& operator<<(std::ostream& os, CombatRangeTestParams const& params) noexcept
{
  return os << "{ attackerType: " << params.attackerType
            << ", targetPosition: " << params.targetPosition
            << ", shouldHit: " << std::boolalpha << params.shouldHit << " }";
}

struct CombatRangeTests : testing::TestWithParam<CombatRangeTestParams> {
};

TEST_P(CombatRangeTests, attackersCanOnlyHitTargetsInRange)
{
  auto const params = GetParam();
  rpg::Character const attacker{params.attackerType};
  rpg::Character target{params.targetPosition};
  int const oldHealth = target.health();
  rpg::Combat::attack(attacker, target, 42);
  bool const hit = (oldHealth>target.health());

  EXPECT_EQ(params.shouldHit, hit);
}

INSTANTIATE_TEST_SUITE_P(Range, CombatRangeTests, testing::Values(
    CombatRangeTestParams{rpg::CharacterType::Melee, {1.f, 0.f}, true},
    CombatRangeTestParams{rpg::CharacterType::Melee, {2.f, 0.f}, true},
    CombatRangeTestParams{rpg::CharacterType::Melee, {3.f, 0.f}, false},
    CombatRangeTestParams{rpg::CharacterType::Melee, {1.f, 1.f}, true},
    CombatRangeTestParams{rpg::CharacterType::Melee, {2.f, 2.f}, false},
    CombatRangeTestParams{rpg::CharacterType::Ranged, {10.f, 0.f}, true},
    CombatRangeTestParams{rpg::CharacterType::Ranged, {20.f, 0.f}, true},
    CombatRangeTestParams{rpg::CharacterType::Ranged, {30.f, 0.f}, false},
    CombatRangeTestParams{rpg::CharacterType::Ranged, {10.f, 10.f}, true},
    CombatRangeTestParams{rpg::CharacterType::Ranged, {20.f, 20.f}, false}
));

TEST(CombatTests, charactersWithNoCommonFactionsAreNoAllies)
{
  rpg::Character jessy{};
  jessy.join("Team Rocket");

  rpg::Character ash{};

  EXPECT_FALSE(rpg::Combat::areAllies(jessy, ash));
}

TEST(CombatTests, charactersWithCommonFactionsAreAllies)
{
  rpg::Character tony{};
  tony.join("Avengers");

  rpg::Character steve{};
  steve.join("Avengers");

  EXPECT_TRUE(rpg::Combat::areAllies(tony, steve));
}
