#pragma once

namespace rpg {
  class Health final {
    static int constexpr DEFAULT_FULL_HEALTH = 1000;

  public:
    explicit Health(int fullHealth = DEFAULT_FULL_HEALTH);

    Health(Health const&) noexcept = default;

    Health& operator=(Health const&) noexcept = default;

    Health& operator-=(int damage);

    Health& operator+=(int restoration);

    operator int() const noexcept;

  private:
    int _fullHealth;
    int _value;
  };
}
