#include<gtest/gtest.h>
#include<health.hxx>

namespace RPG_Test
{
	struct HealthTest : testing::Test
	{
		static std::uint32_t constexpr MAX_HEALTH{ 1000U };

		RPG::Health health{};
	};

	TEST_F(HealthTest, HealthShouldDefaultTo1000)
	{
		EXPECT_EQ(health.Amount(), MAX_HEALTH);
	}

	TEST_F(HealthTest, HealthCanBeDecreased)
	{
		health.Decrease(MAX_HEALTH / 2);
		EXPECT_EQ(health.Amount(), MAX_HEALTH / 2);
	}

	TEST_F(HealthTest, HealthCannotFallNotFallBelowZeroAndNotWrapAround)
	{
		health.Decrease(MAX_HEALTH + 1U);
		EXPECT_EQ(health.Amount(), 0U);
	}

	TEST_F(HealthTest, HealthCannotGoBeyond1000)
	{
		health.Increase(1U);
		EXPECT_EQ(health.Amount(), MAX_HEALTH);
	}

	TEST_F(HealthTest, HealthCanBeIncreased)
	{
		health.Decrease(2U);
		health.Increase(1U);
		EXPECT_EQ(health.Amount(), MAX_HEALTH -1U);
	}
}