#pragma once

#include "health.hxx"
#include "position.hxx"

#include <unordered_set>
#include <string>

namespace rpg {
  struct Target {
    virtual ~Target() noexcept = default;

    virtual Health health() const noexcept = 0;

    virtual void takeDamage(int damage) = 0;

    virtual std::unordered_set<std::string> const& factions() const noexcept = 0;

    virtual Position position() const noexcept = 0;
  };
}
