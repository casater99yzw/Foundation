#pragma once
#include "Core/BasicType.h"
#include "Math/Vector.h"
#include <array>

namespace X
{

	template <class T, uint32 N>
	struct Position;
	template <class T, uint32 N>
	struct Offset;


	template <class T, uint32 N>
	struct Position
	{
		static constexpr uint32 Dimension = N;

		VectorT<T, Dimension> v;

		constexpr Position() noexcept = default;

		constexpr Position(T const& x) noexcept : v{ x } { static_assert(Dimension == 1, "For Dimension 1 Only."); }
		constexpr Position(T const& x, T const& y) noexcept : v{ x, y } { static_assert(Dimension == 2, "For Dimension 2 Only."); }
		constexpr Position(T const& x, T const& y, T const& z) noexcept : v{ x, y, z } { static_assert(Dimension == 3, "For Dimension 3 Only."); }

		template <class U>
		constexpr explicit Position(Position<U, Dimension> const& r) noexcept : v{ r.v } {}

		constexpr Position(VectorT<T, Dimension> const& r) noexcept : v{ r } {}


		template <class U>
		constexpr Position& operator=(Position<U, Dimension> const& r) noexcept { v = r.v; return *this; }

		constexpr T const& X() const { return v.X(); }
		constexpr T& X() { return v.X(); }
		constexpr T const& Y() const { return v.Y(); }
		constexpr T& Y() { return v.Y(); }
		constexpr T const& Z() const { return v.Z(); }
		constexpr T& Z() { return v.Z(); }

		constexpr T const& operator[](uint32 index) const noexcept { return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { return v[index]; }

		constexpr Position const& operator+() const noexcept { return *this; }
		constexpr Position operator-() const noexcept { return Position(-v); }

		constexpr Position& operator+=(Offset<T, Dimension> const& r) noexcept { v += r.v; return *this; }
		constexpr Position& operator-=(Offset<T, Dimension> const& r) noexcept { v -= r.v; return *this; }
		constexpr Position& operator*=(T const& r) noexcept { v *= r; return *this; }
		constexpr Position& operator/=(T const& r) noexcept { v /= r; return *this; }

		T const* Data() const noexcept { return v; }

	};

	template <class T, uint32 N>
	struct Offset
	{
		static constexpr uint32 Dimension = N;

		VectorT<T, Dimension> v;

		constexpr Offset() noexcept = default;

		constexpr Offset(T const& x) noexcept : v{ x } { static_assert(Dimension == 1, "For Dimension 1 Only."); }
		constexpr Offset(T const& x, T const& y) noexcept : v{ x, y } { static_assert(Dimension == 2, "For Dimension 2 Only."); }
		constexpr Offset(T const& x, T const& y, T const& z) noexcept : v{ x, y, z } { static_assert(Dimension == 3, "For Dimension 3 Only."); }

		template <class U>
		constexpr explicit Offset(Offset<U, Dimension> const& r) noexcept : v{ r.v } {}

		template <class U>
		constexpr Offset& operator=(Offset<U, Dimension> const& r) noexcept { v = r.v; return *this; }

		constexpr T const& X() const { return v.X(); }
		constexpr T& X() { return v.X(); }
		constexpr T const& Y() const { return v.Y(); }
		constexpr T& Y() { return v.Y(); }
		constexpr T const& Z() const { return v.Z(); }
		constexpr T& Z() { return v.Z(); }

		constexpr T const& operator[](uint32 index) const noexcept { return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { return v[index]; }

		constexpr Offset const& operator+() const noexcept { return *this; }
		constexpr Offset operator-() const noexcept { return Offset(-v); }

		constexpr Offset& operator+=(Offset const& r) noexcept { v += r.v; return *this; }
		constexpr Offset& operator-=(Offset const& r) noexcept { v -= r.v; return *this; }
		constexpr Offset& operator*=(T const& r) noexcept { v *= r; return *this; }
		constexpr Offset& operator/=(T const& r) noexcept { v /= r; return *this; }

		constexpr T Length() const noexcept { return v.Length(); }

		constexpr T LengthSquared() const noexcept { return v.LengthSquared(); }

		T const* Data() const noexcept { return v; }
	};

	template <class T, uint32 Dimension>
	constexpr bool operator==(Position<T, Dimension> const& l, Position<T, Dimension> const& r) noexcept { return l.v == r.v; }
	template <class T, uint32 Dimension>
	constexpr bool operator!=(Position<T, Dimension> const& l, Position<T, Dimension> const& r) noexcept { return l.v != r.v; }

	template <class T, uint32 Dimension>
	constexpr bool operator==(Offset<T, Dimension> const& l, Offset<T, Dimension> const& r) noexcept { return l.v == r.v; }
	template <class T, uint32 Dimension>
	constexpr bool operator!=(Offset<T, Dimension> const& l, Offset<T, Dimension> const& r) noexcept { return l.v != r.v; }


	template <class T, uint32 Dimension>
	constexpr Offset<T, Dimension> operator+(Offset<T, Dimension> const& l, Offset<T, Dimension> const& r) noexcept { return Offset<T, Dimension>(l.v + r.v); }
	template <class T, uint32 Dimension>
	constexpr Position<T, Dimension> operator+(Offset<T, Dimension> const& l, Position<T, Dimension> const& r) noexcept { return Position<T, Dimension>(l.v + r.v); }
	template <class T, uint32 Dimension>
	constexpr Position<T, Dimension> operator+(Position<T, Dimension> const& l, Offset<T, Dimension> const& r) noexcept { return Position<T, Dimension>(l.v + r.v); }
	template <class T, uint32 Dimension>
	constexpr Offset<T, Dimension> operator-(Position<T, Dimension> const& l, Position<T, Dimension> const& r) noexcept { return Offset<T, Dimension>(l.v - r.v); }
	template <class T, uint32 Dimension>
	constexpr Offset<T, Dimension> operator-(Offset<T, Dimension> const& l, Offset<T, Dimension> const& r) noexcept { return Offset<T, Dimension>(l.v - r.v); }
	template <class T, uint32 Dimension>
	constexpr Position<T, Dimension> operator-(Position<T, Dimension> const& l, Offset<T, Dimension> const& r) noexcept { return Position<T, Dimension>(l.v - r.v); }


	template <class T, uint32 Dimension>
	constexpr Position<T, Dimension> operator*(Position<T, Dimension> const& l, T const& r) noexcept { return Position<T, Dimension>(l.v * r); }
	template <class T, uint32 Dimension>
	constexpr Position<T, Dimension> operator*(T const& l, Position<T, Dimension> const& r) noexcept { return Position<T, Dimension>(l * r.v); }
	template <class T, uint32 Dimension>
	constexpr Position<T, Dimension> operator/(Position<T, Dimension> const& l, T const& r) noexcept { return Position<T, Dimension>(l.v / r); }

	template <class T, uint32 Dimension>
	constexpr Offset<T, Dimension> operator*(Offset<T, Dimension> const& l, T const& r) noexcept { return Offset<T, Dimension>(l.v * r); }
	template <class T, uint32 Dimension>
	constexpr Offset<T, Dimension> operator*(T const& l, Offset<T, Dimension> const& r) noexcept { return Offset<T, Dimension>(l * r.v); }
	template <class T, uint32 Dimension>
	constexpr Offset<T, Dimension> operator/(Offset<T, Dimension> const& l, T const& r) noexcept { return Offset<T, Dimension>(l.v / r); }


	using Size1UI = Offset<uint32, 1>;
	using Size1SI = Offset<sint32, 1>;
	using Size2UI = Offset<uint32, 2>;
	using Size2SI = Offset<sint32, 2>;
	using Size3UI = Offset<uint32, 3>;
	using Size3SI = Offset<sint32, 3>;

	using Index1UI = Position<uint32, 1>;
	using Index1SI = Position<sint32, 1>;
	using Index2UI = Position<uint32, 2>;
	using Index2SI = Position<sint32, 2>;
	using Index3UI = Position<uint32, 3>;
	using Index3SI = Position<sint32, 3>;
}