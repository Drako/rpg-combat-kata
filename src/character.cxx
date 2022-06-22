#include "character.hxx"

namespace rpg
{
Character::Character(CharacterType const type) noexcept
  : _type{type}
{
}

Health Character::health() const noexcept
{
  return _health;
}

int Character::level() const noexcept
{
  return _level;
}

bool Character::alive() const noexcept
{
  return _alive;
}

void Character::takeDamage(int const damage)
{
  _health -= damage;
  if (_health == 0)
    _alive = false;
}

void Character::restore(int restoration)
{
  if (_alive)
    _health += restoration;
}

void Character::levelUp() noexcept
{
  ++_level;
}

CharacterType Character::type() const noexcept
{
  return _type;
}

float Character::range() const noexcept
{
  switch (_type) {
  default:
  case CharacterType::Melee:
    return MELEE_RANGE;
  case CharacterType::Ranged:
    return RANGED_RANGE;
  }
}
}
