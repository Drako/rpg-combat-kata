#include <gtest/gtest.h>

#include "damageable.hxx"
#include "character.hxx"

TEST(DamageableTests, damageableThingsHaveHealth)
{
  EXPECT_TRUE((std::is_same<decltype(rpg::Damageable::health()), rpg::Health>));
}
