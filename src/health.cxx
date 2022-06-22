#include "health.hxx"

#include <algorithm>

namespace RPG
{
	std::uint32_t Health::Amount() const noexcept
	{
		return _amount;
	}

	void Health::Decrease(std::uint32_t const amount) noexcept
	{
		_amount -= std::min(amount, _amount);
	}

	void Health::Increase(std::uint32_t const amount) noexcept
	{
		_amount += std::min(amount, Maximum - _amount);
	}

}
