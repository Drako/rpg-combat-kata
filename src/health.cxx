#include "health.hxx"

namespace rpg {
Health::operator int() const noexcept
{
  return value;
}

Health &Health::operator-=(int const damage)
{
  value -= damage;
  return *this;
}
}
