#pragma once

#include "health.hxx"

namespace rpg
{
class Character final
{
public:
  [[nodiscard]] Health health() const noexcept;

  [[nodiscard]] int level() const noexcept;

  [[nodiscard]] bool alive() const noexcept;

  void takeDamage(int damage);

  void restore(int restoration);

  void levelUp() noexcept;

private:
  Health _health{};
  int _level{1};
  bool _alive{true};
};
}
