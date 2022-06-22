#pragma once

#include "health.hxx"

namespace rpg
{
enum class CharacterType
{
  Melee,
  Ranged,
};

class Character final
{
public:
  explicit Character(CharacterType type = CharacterType::Melee) noexcept;

  Character(Character const &) noexcept = default;
  Character &operator=(Character const &) noexcept = default;

  [[nodiscard]] Health health() const noexcept;

  [[nodiscard]] int level() const noexcept;

  [[nodiscard]] bool alive() const noexcept;

  [[nodiscard]] CharacterType type() const noexcept;

  [[nodiscard]] float range() const noexcept;

  void takeDamage(int damage);

  void restore(int restoration);

  void levelUp() noexcept;

private:
  Health _health{};
  int _level{1};
  bool _alive{true};
  CharacterType _type;
};
}
