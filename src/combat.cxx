#include "combat.hxx"
#include "character.hxx"

#include <cmath>
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
  if (std::addressof(target) == std::addressof(attacker))
    return;

  if (::distanceBetween(attacker, target) > attacker.range())
    return;

  int const levelDifference = attacker.level() - target.level();
  if (levelDifference >= LEVEL_THRESHOLD)
    target.takeDamage(damage + (damage >> 1U));
  else if (levelDifference <= -LEVEL_THRESHOLD)
    target.takeDamage(damage >> 1U);
  else
    target.takeDamage(damage);
}

void Combat::heal(Character &healer, int const restoration)
{
  healer.restore(restoration);
}
}
