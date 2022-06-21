#include "health.hxx"

#include <stdexcept>

namespace rpg {
Health::operator int() const noexcept
{
  return value;
}

Health &Health::operator-=(int const damage)
{
  if (damage < 0) {
    throw std::invalid_argument{"damage must not be negative"};
  }
  value -= damage;
  return *this;
}
}
