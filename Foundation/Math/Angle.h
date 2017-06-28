#pragma once
#include "Core/BasicType.h"
#include <type_traits>

namespace X
{
	template <class T>
	class Degree;
	template <class T>
	class Radian;

	template <class T>
	class Degree
	{
	public:
		T value = 0;

		constexpr Degree() = default;

		constexpr explicit Degree(T v) : value(v) {}

		constexpr Degree(Radian<T> radian);

		friend constexpr bool operator==(Degree l, Degree r) { return l.value == r.value; }
		friend constexpr bool operator!=(Degree l, Degree r) { return l.value != r.value; }
		friend constexpr bool operator<(Degree l, Degree r) { return l.value < r.value; }
		friend constexpr bool operator<=(Degree l, Degree r) { return l.value <= r.value; }
		friend constexpr bool operator>(Degree l, Degree r) { return l.value > r.value; }
		friend constexpr bool operator>=(Degree l, Degree r) { return l.value >= r.value; }

		friend constexpr Degree operator+(Degree l, Degree r) { return Degree(l.value + r.value); }
		friend constexpr Degree operator-(Degree l, Degree r) { return Degree(l.value - r.value); }
		friend constexpr Degree operator*(Degree l, T r) { return Degree(l.value * r); }
		friend constexpr Degree operator*(T l, Degree r) { return Degree(l * r.value); }

		constexpr Degree operator+() const { return *this; }
		constexpr Degree operator-() const { return Degree(-value); }

		Degree& operator+=(Degree other) { value += other.value; return *this; }
		Degree& operator-=(Degree other) { value -= other.value; return *this; }
		Degree& operator*=(T other) { value *= other; return *this; }
		Degree& operator/=(T other) { value /= other; return *this; }

	private:
		static constexpr float64 D_PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620;
		static constexpr T RadianToDegree = static_cast<T>(180.0 / D_PI);
	};

	template <class T>
	class Radian
	{
	public:
		T value = 0;

		constexpr Radian() = default;

		constexpr explicit Radian(T v) : value(v) {}

		constexpr Radian(Degree<T> degree);

		friend constexpr bool operator==(Radian l, Radian r) { return l.value == r.value; }
		friend constexpr bool operator!=(Radian l, Radian r) { return l.value != r.value; }
		friend constexpr bool operator<(Radian l, Radian r) { return l.value < r.value; }
		friend constexpr bool operator<=(Radian l, Radian r) { return l.value <= r.value; }
		friend constexpr bool operator>(Radian l, Radian r) { return l.value > r.value; }
		friend constexpr bool operator>=(Radian l, Radian r) { return l.value >= r.value; }

		friend constexpr Radian operator+(Radian l, Radian r) { return Radian(l.value + r.value); }
		friend constexpr Radian operator-(Radian l, Radian r) { return Radian(l.value - r.value); }
		friend constexpr Radian operator*(Radian l, T r) { return Radian(l.value * r); }
		friend constexpr Radian operator*(T l, Radian r) { return Radian(l * r.value); }

		constexpr Radian operator+() const { return *this; }
		constexpr Radian operator-() const { return Radian(-value); }

		Radian& operator+=(Radian  other) { value += other.value; return *this; }
		Radian& operator-=(Radian  other) { value -= other.value; return *this; }
		Radian& operator*=(T other) { value *= other; return *this; }
		Radian& operator/=(T other) { value /= other; return *this; }

	private:
		static constexpr float64 D_PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620;
		static constexpr T DegreeToRadian = static_cast<T>(D_PI / 180.0);
	};

	template <class T>
	constexpr Degree<T>::Degree(Radian<T> r) : value(r.value * RadianToDegree) {}
	template <class T>
	constexpr Radian<T>::Radian(Degree<T> d) : value(d.value * DegreeToRadian) {}

	using RadianF32 = Radian<float32>;
	using DegreeF32 = Degree<float32>;
}