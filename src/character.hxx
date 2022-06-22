#pragma once

#include "health.hxx"

namespace RPG
{
	class Character final
	{
	public:
		Health GetHealth() const noexcept;

		std::uint32_t GetLevel() const noexcept;

		bool IsAlive() const noexcept;

		void TakeDamage(std::uint32_t const amount) noexcept;

		void Heal(std::uint32_t const amount) noexcept;

	private:
		Health _health{};
		bool _alive{ true };
	};
}
