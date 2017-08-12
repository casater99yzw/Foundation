#pragma once
#include "Core/BasicType.h"

#include "Math/Angle.h"

#include <limits>
#include <cmath>

namespace X
{
	struct BasicMath
	{
		static constexpr float64 D_PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620;
		static constexpr float32 PI = static_cast<float32>(D_PI);

		template <class T>
		static constexpr T Sin(Radian<T> v) { return std::sin(v.value); }
		template <class T>
		static constexpr T Cos(Radian<T> v) { return std::cos(v.value); }
		template <class T>
		static constexpr T Tan(Radian<T> v) { return std::tan(v.value); }

		template <class T>
		static constexpr Radian<T> ASin(T v) { return Radian<T>(std::asin(v)); }
		template <class T>
		static constexpr Radian<T> ACos(T v) { return Radian<T>(std::acos(v)); }
		template <class T>
		static constexpr Radian<T> ATan(T v) { return Radian<T>(std::atan(v)); }
		template <class T>
		static constexpr Radian<T> ATan2(T x, T y) { return Radian<T>(std::atan2(x, y)); }

		template <class T>
		static constexpr bool Equal(T const& l, T const& r) { return l == r; }
		template <>
		static bool Equal<float32>(float32 const& l, float32 const& r) { return std::abs(l - r) <= std::numeric_limits<float32>::epsilon(); }
		template <>
		static bool Equal<float64>(float64 const& l, float64 const& r) { return std::abs(l - r) <= std::numeric_limits<float64>::epsilon(); }

		template <class T>
		static bool Equal(Radian<T> const& l, Radian<T> const& r) { return std::abs(l.value - r.value) <= std::numeric_limits<T>::epsilon(); }
		template <class T>
		static bool Equal(Degree<T> const& l, Degree<T> const& r) { return std::abs(l.value - r.value) <= std::numeric_limits<T>::epsilon(); }

		template <class T>
		static constexpr T Square(T v) { return v * v; }
		template <class T>
		static constexpr T Cube(T v) { return v * v * v; }


		// used for constexpr only

		template <class T>
		static constexpr T CAbs(T const& v) { return v < 0 ? -v : v; }

		template <class T>
		static constexpr bool CEqual(T const& l, T const& r) { return l == r; }
		template <>
		static constexpr bool CEqual<float32>(float32 const& l, float32 const& r) { return CAbs(l - r) <= std::numeric_limits<float32>::epsilon(); }
		template <>
		static constexpr bool CEqual<float64>(float64 const& l, float64 const& r) { return CAbs(l - r) <= std::numeric_limits<float64>::epsilon(); }
		template <class T>
		static bool CEqual(Radian<T> const& l, Radian<T> const& r) { return CAbs(l.value - r.value) <= std::numeric_limits<T>::epsilon(); }
		template <class T>
		static bool CEqual(Degree<T> const& l, Degree<T> const& r) { return CAbs(l.value - r.value) <= std::numeric_limits<T>::epsilon(); }

	};
}
