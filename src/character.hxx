#pragma once

#include "cxx_17_traits.hxx"
#include "target.hxx"
#include "position.hxx"

#include <ostream>
#include <utility>

namespace rpg {
  enum class CharacterType {
    Melee,
    Ranged,
  };

  std::ostream& operator<<(std::ostream& os, CharacterType type) noexcept;

  class Character final : public Target {
    static float constexpr MELEE_RANGE = 2.f;
    static float constexpr RANGED_RANGE = 20.f;

  public:
    explicit Character(CharacterType type = CharacterType::Melee) noexcept;

    explicit Character(Position const& position, CharacterType type = CharacterType::Melee) noexcept;

    Character(Character const&) noexcept = default;

    Character& operator=(Character const&) noexcept = default;

    Health health() const noexcept override;

    int level() const noexcept;

    bool alive() const noexcept;

    CharacterType type() const noexcept;

    float range() const noexcept;

    Position position() const noexcept override;

    std::unordered_set<std::string> const& factions() const noexcept override;

    void takeDamage(int damage) override;

    void restore(int restoration);

    void levelUp() noexcept;

    void moveTo(Position const& newPosition) noexcept;

    template<typename... StringTypes>
    auto join(StringTypes&& ... factions)
    -> std::enable_if_t<conjunction_v<std::is_convertible<StringTypes, std::string>::value...>>
    {
      auto const f = {std::string{std::forward<StringTypes>(factions)}...};
      for (auto const& faction: f)
        _factions.insert(faction);
    }

    template<typename... StringTypes>
    auto leave(StringTypes&& ... factions)
    -> std::enable_if_t<conjunction_v<std::is_convertible<StringTypes, std::string>::value...>>
    {
      auto const f = {std::string{std::forward<StringTypes>(factions)}...};
      for (auto const& faction: f)
        _factions.erase(faction);
    }

  private:
    Health _health{};
    int _level{1};
    bool _alive{true};
    CharacterType _type;
    Position _position;
    std::unordered_set<std::string> _factions{};
  };
}
