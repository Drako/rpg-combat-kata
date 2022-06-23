#include <gtest/gtest.h>

#include "damageable.hxx"
#include "character.hxx"

#include <type_traits>

TEST(DamageableTests, charactersAreDamageable)
{
  EXPECT_TRUE(std::is_polymorphic<rpg::Character>::value);
  EXPECT_TRUE((std::is_base_of<rpg::Damageable, rpg::Character>::value));
}
