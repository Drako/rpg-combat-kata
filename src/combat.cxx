#include "combat.hxx"
#include "character.hxx"

namespace rpg
{
void Combat::attack(const rpg::Character &attacker, rpg::Character &target, int damage)
{
  (void)attacker;
  target.takeDamage(damage);
}
}
