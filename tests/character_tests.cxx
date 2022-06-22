#include <gtest/gtest.h>

#include <character.hxx>

namespace RPG_Test
{
	using namespace RPG;

	struct CharacterTests : testing::Test
	{
		Character character{};
	};

	TEST_F(CharacterTests, defaultCharacterHasDefaultAttributes)
	{
		EXPECT_EQ(character.GetHealth().Amount(), 1000U);
		EXPECT_EQ(character.GetLevel(), 1U);
		EXPECT_TRUE(character.IsAlive());
	}

	TEST_F(CharacterTests, characterCanTakeDamage)
	{
		character.TakeDamage(500U);
		EXPECT_EQ(character.GetHealth().Amount(), 500U);
	}

	TEST_F(CharacterTests, characterDiesWhenHealthBelowZero)
	{
		character.TakeDamage(1000U);
		EXPECT_FALSE(character.IsAlive());
	}

	TEST_F(CharacterTests, characterCanBeHealed)
	{
		character.TakeDamage(500U);
		character.Heal(200U);
		EXPECT_EQ(character.GetHealth().Amount(),700U);
	}

	TEST_F(CharacterTests, characterCanNotBeHealedIfDead)
	{
		character.TakeDamage(1000U);
		character.Heal(200U);
		EXPECT_EQ(character.GetHealth().Amount(), 0U);
		EXPECT_FALSE(character.IsAlive());
	}


}
