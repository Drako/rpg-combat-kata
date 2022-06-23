#pragma once

namespace rpg {
  class Character;

  struct Combat final {
    static void attack(rpg::Character const& attacker, rpg::Character& target, int damage);

    static void heal(rpg::Character const& healer, rpg::Character& target, int restoration);

    static bool areAllies(rpg::Character const& a, rpg::Character const& b) noexcept;
  };
}
