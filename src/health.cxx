#include "health.hxx"

#include <algorithm>
#include <stdexcept>

namespace rpg {
  Health::Health(int fullHealth)
      :_fullHealth{fullHealth}, _value{fullHealth}
  {
    if (fullHealth<=0) {
      throw std::invalid_argument{"full health must be greater than 0"};
    }
  }

  Health::operator int() const noexcept
  {
    return _value;
  }

  Health& Health::operator-=(int const damage)
  {
    if (damage<0) {
      throw std::invalid_argument{"damage must not be negative"};
    }

    _value -= std::min(_value, damage);
    return *this;
  }

  Health& Health::operator+=(int const restoration)
  {
    if (restoration<0) {
      throw std::invalid_argument{"restoration must not be negative"};
    }

    _value += std::min(_fullHealth-_value, restoration);
    return *this;
  }
}
