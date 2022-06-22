#pragma once

#include "health.hxx"
#include "position.hxx"

#include <ostream>

namespace rpg
{
enum class CharacterType
{
  Melee,
  Ranged,
};

std::ostream &operator<<(std::ostream &os, CharacterType type) noexcept;

class Character final
{
  static float constexpr MELEE_RANGE = 2.f;
  static float constexpr RANGED_RANGE = 20.f;

public:
  explicit Character(CharacterType type = CharacterType::Melee) noexcept;
  explicit Character(Position const &position, CharacterType type = CharacterType::Melee) noexcept;

  Character(Character const &) noexcept = default;
  Character &operator=(Character const &) noexcept = default;

  [[nodiscard]] Health health() const noexcept;

  [[nodiscard]] int level() const noexcept;

  [[nodiscard]] bool alive() const noexcept;

  [[nodiscard]] CharacterType type() const noexcept;

  [[nodiscard]] float range() const noexcept;

  [[nodiscard]] Position position() const noexcept;

  void takeDamage(int damage);

  void restore(int restoration);

  void levelUp() noexcept;

private:
  Health _health{};
  int _level{1};
  bool _alive{true};
  CharacterType _type;
  Position _position;
};
}
