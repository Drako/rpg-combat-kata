#include "character.hxx"

namespace rpg {
  std::ostream& operator<<(std::ostream& os, CharacterType const type) noexcept
  {
    switch (type) {
    case CharacterType::Melee:
      return os << "CharacterType::Melee";
    case CharacterType::Ranged:
      return os << "CharacterType::Ranged";
    default:
      return os << "CharacterType::[Invalid]";
    }
  }

  Character::Character(CharacterType const type) noexcept
      :Character{Position{}, type}
  {
  }

  Character::Character(Position const& position, CharacterType const type) noexcept
      :_type{type}, _position{position}
  {
  }

  Health Character::health() const noexcept
  {
    return _health;
  }

  int Character::level() const noexcept
  {
    return _level;
  }

  bool Character::alive() const noexcept
  {
    return _alive;
  }

  void Character::takeDamage(int const damage)
  {
    _health -= damage;
    if (_health==0)
      _alive = false;
  }

  void Character::restore(int restoration)
  {
    if (_alive)
      _health += restoration;
  }

  void Character::levelUp() noexcept
  {
    ++_level;
  }

  CharacterType Character::type() const noexcept
  {
    return _type;
  }

  float Character::range() const noexcept
  {
    switch (_type) {
    default:
    case CharacterType::Melee:
      return MELEE_RANGE;
    case CharacterType::Ranged:
      return RANGED_RANGE;
    }
  }

  Position Character::position() const noexcept
  {
    return _position;
  }

  void Character::moveTo(Position const& newPosition) noexcept
  {
    _position = newPosition;
  }

  std::unordered_set<std::string> const& Character::factions() const noexcept
  {
    return _factions;
  }
}
