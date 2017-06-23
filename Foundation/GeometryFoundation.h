#pragma once
#include "BasicType.h"
#include <array>

namespace X
{
	template <typename T, uint32_t Dimension>
	struct Size
	{
		std::array<T, Dimension> data;

		constexpr Size() noexcept
		{
			data.fill(T(0));
		}

		explicit constexpr Size(std::array<T, Dimension> const& data) noexcept
			: data(data)
		{
		}
		constexpr Size(T const& x) noexcept
		{
			static_assert(Dimension == 1, "");
			data[0] = x;
		}
		constexpr Size(T const& x, T const& y) noexcept
		{
			static_assert(Dimension == 2, "");
			data[0] = x;
			data[1] = y;
		}
		constexpr Size(T const& x, T const& y, T const& z) noexcept
		{
			static_assert(Dimension == 3, "");
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}

		constexpr T const& X() const noexcept
		{
			static_assert(Dimension >= 1, "");
			return data[0];
		}
		constexpr T const& Y() const noexcept
		{
			static_assert(Dimension >= 2, "");
			return data[1];
		}
		constexpr T const& Z() const noexcept
		{
			static_assert(Dimension >= 3, "");

			return data[2];
		}

		T& operator [](uint32_t index) noexcept
		{
			assert(index < Dimension);
			return data[index];
		}
		constexpr T const& operator [](uint32_t index) const noexcept
		{
			assert(index < Dimension);
			return data[index];
		}
	};

	using Size2UI = Size<uint32, 2>;
	using Size2SI = Size<sint32, 2>;
}
