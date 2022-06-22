#pragma once

#include <ostream>

namespace rpg
{
struct Position final
{
  float x{0.f};
  float y{0.f};
};

inline std::ostream &operator<<(std::ostream &os, Position const &pos) noexcept
{
  return os << "{ x: " << pos.x << ", y: " << pos.y << " }";
}
}
