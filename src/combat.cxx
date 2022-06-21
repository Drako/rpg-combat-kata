#include "combat.hxx"
#include "character.hxx"

#include <utility>

namespace rpg
{
void Combat::attack(const rpg::Character &attacker, rpg::Character &target, int const damage)
{
  if (std::addressof(target) != std::addressof(attacker))
    target.takeDamage(damage);
}

void Combat::heal(Character &healer, int const restoration)
{
  healer.restore(restoration);
}
}
