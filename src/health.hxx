#ifndef RPG_HEALTH_HXX
#define RPG_HEALTH_HXX

#include <cstdint>

namespace RPG {

/// <summary>
/// Represents the health of an entity in an RPG.
/// </summary>
class Health
{
public:
	/// <summary>
	/// The maximum value of health.
	/// </summary>
	static constexpr std::uint32_t Maximum{ 1000U };

	std::uint32_t Amount() const noexcept;

	void Decrease(std::uint32_t amount) noexcept;

	void Increase(std::uint32_t amount) noexcept;

private:
	/// <summary>
	/// The current amount of health.
	/// </summary>
	std::uint32_t _amount{ Maximum };
};

}

#endif // !RPG_HEALTH_HXX