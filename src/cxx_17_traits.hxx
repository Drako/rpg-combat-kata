#pragma once

namespace rpg {
  template<bool... Values>
  class conjunction final {
    static bool constexpr combine() noexcept
    {
      bool result{true};
      for (bool const v: {Values...})
        result = result && v;
      return result;
    }

  public:
    static bool constexpr value = combine();
  };

  template<bool... Values>
  static bool constexpr conjunction_v = conjunction<Values...>::value;
}
