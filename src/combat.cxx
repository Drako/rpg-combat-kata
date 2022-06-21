#include "combat.hxx"
#include "character.hxx"

#include <utility>

static int constexpr LEVEL_THRESHOLD = 5;

namespace rpg
{
void Combat::attack(const rpg::Character &attacker, rpg::Character &target, int const damage)
{
  if (std::addressof(target) != std::addressof(attacker)) {
    int const levelDifference = attacker.level() - target.level();
    if (levelDifference >= LEVEL_THRESHOLD)
      target.takeDamage(damage + (damage >> 1U));
    else
      target.takeDamage(damage);
  }
}

void Combat::heal(Character &healer, int const restoration)
{
  healer.restore(restoration);
}
}
