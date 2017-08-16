#pragma once

#include "Core/BasicType.h"
#include "Math/Vector.h"

namespace X
{

	class Color
	{
	public:
		V4F32 v;

		constexpr Color() noexcept = default;
		constexpr Color(float32 r, float32 g, float32 b, float32 a) noexcept : v(r, g, b, a) {}

		constexpr explicit Color(V4F32 const& v) noexcept : v(v) {}

		constexpr float32 R() const noexcept { return v.X(); }
		constexpr float32& R() noexcept { return v.X(); }
		constexpr float32 G() const noexcept { return v.Y(); }
		constexpr float32& G() noexcept { return v.Y(); }
		constexpr float32 B() const noexcept { return v.Z(); }
		constexpr float32& B() noexcept { return v.Z(); }
		constexpr float32 A() const noexcept { return v.W(); }
		constexpr float32& A() noexcept { return v.W(); }


		constexpr Color const& operator+() const noexcept { return *this; }
		constexpr Color operator-() const noexcept { return Color(-v); }

		constexpr Color& operator+=(Color const& r) noexcept { v += r.v; return *this; }
		constexpr Color& operator-=(Color const& r) noexcept { v -= r.v; return *this; }
		constexpr Color& operator*=(Color const& r) noexcept { v *= r.v; return *this; }
		constexpr Color& operator*=(float32 r) noexcept { v *= r; return *this; }
		constexpr Color& operator/=(float32 r) noexcept { v /= r; return *this; }

		constexpr V4F32 const& Value() const noexcept { return v; }

		float32 const* Data() const noexcept { return v.Data(); }

	};

	constexpr bool operator==(Color const& l, Color const& r) noexcept { return l.Value() == r.Value(); }
	constexpr bool operator!=(Color const& l, Color const& r) noexcept { return l.Value() != r.Value(); }

	constexpr Color operator+(Color const& l, Color const& r) noexcept { return Color(l.Value() + r.Value()); }
	constexpr Color operator-(Color const& l, Color const& r) noexcept { return Color(l.Value() - r.Value()); }
	constexpr Color operator*(Color const& l, Color const& r) noexcept { return Color(l.Value() * r.Value()); }
	constexpr Color operator*(Color const& l, float32 r) noexcept { return Color(l.Value() * r); }
	constexpr Color operator*(float32 l, Color const& r) noexcept { return Color(l * r.Value()); }
	constexpr Color operator/(Color const& l, float32 r) noexcept { return Color(l.Value() / r); }
}
