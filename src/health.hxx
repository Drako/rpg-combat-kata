#pragma once

namespace rpg
{
class Health final
{
  static int constexpr FULL_HEALTH = 1000;

public:
  Health &operator-=(int damage);

  operator int() const noexcept;

private:
  int value{FULL_HEALTH};
};
}
