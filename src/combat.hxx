#pragma once

namespace rpg
{
class Character;

struct Combat final
{
  static void attack(rpg::Character const &attacker, rpg::Character &target, int damage);
};
}
