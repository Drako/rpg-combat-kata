#include "health.hxx"

namespace rpg {
Health::operator int() const noexcept
{
  return 1000;
}
}
