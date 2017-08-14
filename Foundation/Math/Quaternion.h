#pragma once

#include "Math/Vector.h"

namespace X
{

	template <typename T>
	class Quaternion
	{
	public:
		static uint32 const Count = 4;

		static Quaternion const Zero;
		static Quaternion const Identity;

		union
		{
			T v[Count];

			struct
			{
				union
				{
					Vector<T, 3> axis;
					struct
					{
						T x;
						T y;
						T z;
					};
				};
				T w;
			};
		};

		constexpr Quaternion() noexcept = default;

		constexpr Quaternion(T const& x, T const& y, T const& z, T const& w) noexcept : v{ x, y, z, w } {}
		constexpr Quaternion(Vector<T, 3> const& axis, T const& w) noexcept : v{ axis[0], axis[1], axis[2], w } {}

		template <typename U>
		constexpr explicit Quaternion(Quaternion<U> const& r) noexcept : v{ r.x, r.y, r.z, r.w } {}

		constexpr T const& operator[](uint32 index) const noexcept { assert(index < Count); return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { assert(index < Count); return v[index]; }

		constexpr T const& X() const noexcept { return v[0]; }
		constexpr T& X() noexcept { return v[0]; }
		constexpr T const& Y() const noexcept { return v[1]; }
		constexpr T& Y() noexcept { return v[1]; }
		constexpr T const& Z() const noexcept { return v[2]; }
		constexpr T& Z() noexcept { return v[2]; }
		constexpr T const& W() const noexcept { return v[3]; }
		constexpr T& W() noexcept { return v[3]; }
		
		Vector<T, 3> const& V() const noexcept { return axis; } // TODO how to make this constexpr?
		Vector<T, 3>& V() noexcept { return axis; }


		constexpr Quaternion const& operator+() const noexcept { return *this; }
		constexpr Quaternion operator-() const noexcept { return Quaternion(-v[0], -v[1], -v[2], -v[3]); }

		constexpr Quaternion& operator+=(Quaternion const& r) noexcept { v[0] += r.v[0]; v[1] += r.v[1]; v[2] += r.v[2]; v[3] += r.v[3]; return *this; }
		constexpr Quaternion& operator-=(Quaternion const& r) noexcept { v[0] -= r.v[0]; v[1] -= r.v[1]; v[2] -= r.v[2]; v[3] -= r.v[3]; return *this; }
		constexpr Quaternion& operator*=(Quaternion const& r) noexcept { return *this = *this * r; }
		constexpr Quaternion& operator*=(T const& r) noexcept { v[0] *= r; v[1] *= r; v[2] *= r; v[3] *= r; return *this; }
		constexpr Quaternion& operator/=(T const& r) noexcept { v[0] /= r; v[1] /= r; v[2] /= r; v[3] /= r; return *this; }


		constexpr Quaternion Normalized() const noexcept { return *this / Length(); }

		constexpr Quaternion Conjugate() const noexcept { return Quaternion(-v[0], -v[1], -v[2], v[3]); }

		constexpr Quaternion Inverse() const noexcept { return Quaternion(Conjugate() * (T(1) / LengthSquared())); }

		constexpr T Length() const noexcept { return std::sqrt(LengthSquared()); }

		constexpr T LengthSquared() const noexcept { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]; }
	};

	template <typename T>
	Quaternion<T> const Quaternion<T>::Zero = Quaternion(Vector<T, 3>(T(0)), T(0));

	template <typename T>
	Quaternion<T> const Quaternion<T>::Identity = Quaternion(Vector<T, 3>(T(0)), T(1));


	template <typename T>
	constexpr Quaternion<T> operator+(Quaternion<T> const& l, Quaternion<T> const& r) noexcept { Quaternion<T> v = l; v += r; return v; }

	template <typename T>
	constexpr Quaternion<T> operator-(Quaternion<T> const& l, Quaternion<T> const& r) noexcept { Quaternion<T> v = l; v -= r; return v; }

	template <typename T>
	constexpr Quaternion<T> operator*(Quaternion<T> const& l, Quaternion<T> const& r) noexcept
	{
		return Quaternion<T>(
			l.v[3] * r.v[0] + l.v[0] * r.v[3] + l.v[1] * r.v[2] - l.v[2] * r.v[1],
			l.v[3] * r.v[1] + l.v[1] * r.v[3] + l.v[2] * r.v[0] - l.v[0] * r.v[2],
			l.v[3] * r.v[2] + l.v[2] * r.v[3] + l.v[0] * r.v[1] - l.v[1] * r.v[0],
			l.v[3] * r.v[3] - l.v[0] * r.v[0] - l.v[1] * r.v[1] - l.v[2] * r.v[2]);
	}

	template <typename T>
	constexpr Quaternion<T> operator*(Quaternion<T> const& l, T const& r) noexcept { Quaternion<T> v = l; v *= r; return v; }
	template <typename T>
	constexpr Quaternion<T> operator*(T const& l, Quaternion<T> const& r) noexcept { Quaternion<T> v = r; v *= l; return v; }

	template <typename T>
	constexpr Quaternion<T> operator/(Quaternion<T> const& l, T const& r) noexcept { Quaternion<T> v = l; v /= r; return v; }

	template <typename T>
	constexpr bool operator==(Quaternion<T> const& l, Quaternion<T> const& r) noexcept { return l.v[0] == r.v[0] && l.v[1] == r.v[1] && l.v[2] == r.v[2] && l.v[3] == r.v[3]; }

	template <typename T>
	constexpr bool operator!=(Quaternion<T> const& l, Quaternion<T> const& r) noexcept { return l.v[0] != r.v[0] || l.v[1] != r.v[1] || l.v[2] != r.v[2] || l.v[3] != r.v[3]; }

	using QF32 = Quaternion<float32>;
	using QF64 = Quaternion<float64>;
}
