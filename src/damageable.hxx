#pragma once

#include "health.hxx"

#include <unordered_set>
#include <string>

namespace rpg {
  struct Damageable {
    virtual ~Damageable() noexcept = default;

    virtual Health health() const = 0;

    virtual void takeDamage(int damage) = 0;

    virtual std::unordered_set<std::string> const& factions() const noexcept = 0;
  };
}
