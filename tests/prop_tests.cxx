#include <gtest/gtest.h>

#include "prop.hxx"

struct PropTests : testing::Test {
  rpg::Prop tree{2000};
};

TEST_F(PropTests, newPropsAreNotDestroyed)
{
  EXPECT_FALSE(tree.destroyed());
}

TEST_F(PropTests, propsWithZeroHealthAreDestroyed)
{
  tree.takeDamage(2000);
  EXPECT_TRUE(tree.destroyed());
}

TEST_F(PropTests, propsBelongToNoFactions)
{
  EXPECT_TRUE(tree.factions().empty());
}
