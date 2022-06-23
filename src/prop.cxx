#include "prop.hxx"

namespace {
  std::unordered_set<std::string> const NO_FACTIONS{};
}

namespace rpg {
  Prop::Prop(int fullHealth, Position const& position)
      :_health{fullHealth}, _position{position}
  {
  }

  Health Prop::health() const noexcept
  {
    return _health;
  }

  void Prop::takeDamage(int damage)
  {
    _health -= damage;
  }

  std::unordered_set<std::string> const& Prop::factions() const noexcept
  {
    return NO_FACTIONS;
  }

  Position Prop::position() const noexcept
  {
    return _position;
  }

  bool Prop::destroyed() const noexcept
  {
    return _health==0;
  }
}
