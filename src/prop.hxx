#pragma once

#include "target.hxx"

namespace rpg {
  class Prop final : public Target {
  public:
    explicit Prop(int fullHealth, Position const& position = {});

    Prop(Prop const&) noexcept = default;

    Prop& operator=(Prop const&) noexcept = default;

    Health health() const noexcept override;

    void takeDamage(int damage) override;

    std::unordered_set<std::string> const& factions() const noexcept override;

    Position position() const noexcept override;

    bool destroyed() const noexcept;

  private:
    Health _health;
    Position _position;
  };
}
