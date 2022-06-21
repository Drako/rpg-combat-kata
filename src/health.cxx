#include "health.hxx"

static int constexpr FULL_HEALTH = 1000;

namespace rpg {
Health::operator int() const noexcept
{
  return FULL_HEALTH;
}
}
