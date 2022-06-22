#include "combat.hxx"
#include "character.hxx"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <utility>

static int constexpr LEVEL_THRESHOLD = 5;

namespace
{
float distanceBetween(rpg::Character const &a, rpg::Character const &b) noexcept
{
  auto const posA = a.position();
  auto const posB = b.position();
  auto const xDist = std::abs(posB.x - posA.x);
  auto const yDist = std::abs(posB.y - posA.y);
  return std::sqrt(xDist * xDist + yDist * yDist);
}
}

namespace rpg
{
void Combat::attack(const rpg::Character &attacker, rpg::Character &target, int const damage)
{
  bool const attackingSelf = std::addressof(target) == std::addressof(attacker);

  if (attackingSelf || ::distanceBetween(attacker, target) > attacker.range())
    return;

  int const levelDifference = attacker.level() - target.level();
  if (levelDifference >= LEVEL_THRESHOLD)
    target.takeDamage(damage + (damage >> 1U));
  else if (levelDifference <= -LEVEL_THRESHOLD)
    target.takeDamage(damage >> 1U);
  else
    target.takeDamage(damage);
}

void Combat::heal(Character const &healer, rpg::Character &target, int const restoration)
{
  bool const healingSelf = std::addressof(healer) == std::addressof(target);

  if (healingSelf || areAllies(healer, target))
    target.restore(restoration);
}

bool Combat::areAllies(Character const &a, Character const &b) noexcept
{
  auto const &aFactions = a.factions();
  auto const &bFactions = b.factions();
  return std::any_of(std::cbegin(aFactions), std::cend(aFactions), [&bFactions](std::string const &faction)
  {
    return bFactions.count(faction) == 1U;
  });
}
}
