#pragma once

namespace rpg {
  class Character;

  struct Target;

  struct Combat final {
    static void attack(rpg::Character const& attacker, rpg::Target& target, int damage);

    static void heal(rpg::Character const& healer, rpg::Character& target, int restoration);

    static bool areAllies(rpg::Target const& a, rpg::Target const& b) noexcept;
  };
}
