#include "character.hxx"

namespace rpg
{
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
}
}
