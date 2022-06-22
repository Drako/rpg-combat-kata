#include "character.hxx"

namespace RPG {

Health Character::GetHealth() const noexcept
{
	return _health;
}
std::uint32_t Character::GetLevel() const noexcept
{
	return 1U;
}

bool Character::IsAlive() const noexcept
{
	return _alive;
}

void Character::TakeDamage(std::uint32_t const amount) noexcept
{
	_health.Decrease(amount);
	if(_health.Amount()==0)
	{
		_alive = false;
	}
}

void Character::Heal(std::uint32_t const amount) noexcept
{
	if (_alive)
	{
		_health.Increase(amount);
	}
}

}