#include "health.hxx"

#include <algorithm>
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

  value -= std::min(value, damage);
  return *this;
}

Health &Health::operator+=(int const restoration)
{
  if (restoration < 0) {
    throw std::invalid_argument{"restoration must not be negative"};
  }

  value += restoration;
  return *this;
}
}
