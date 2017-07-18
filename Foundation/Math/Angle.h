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
	constexpr bool operator==(Degree<T> l, Degree<T> r) { return l.value == r.value; }
	template <class T>
	constexpr bool operator!=(Degree<T> l, Degree<T> r) { return l.value != r.value; }
	template <class T>
	constexpr bool operator<(Degree<T> l, Degree<T> r) { return l.value < r.value; }
	template <class T>
	constexpr bool operator<=(Degree<T> l, Degree<T> r) { return l.value <= r.value; }
	template <class T>
	constexpr bool operator>(Degree<T> l, Degree<T> r) { return l.value > r.value; }
	template <class T>
	constexpr bool operator>=(Degree<T> l, Degree<T> r) { return l.value >= r.value; }

	template <class T>
	constexpr Degree<T> operator+(Degree<T> l, Degree<T> r) { return Degree<T>(l.value + r.value); }
	template <class T>
	constexpr Degree<T> operator-(Degree<T> l, Degree<T> r) { return Degree<T>(l.value - r.value); }
	template <class T>
	constexpr Degree<T> operator*(Degree<T> l, T r) { return Degree<T>(l.value * r); }
	template <class T>
	constexpr Degree<T> operator*(T l, Degree<T> r) { return Degree<T>(l * r.value); }


	template <class T>
	class Radian
	{
	public:
		T value = 0;

		constexpr Radian() = default;

		constexpr explicit Radian(T v) : value(v) {}

		constexpr Radian(Degree<T> degree);

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
	constexpr bool operator==(Radian<T> l, Radian<T> r) { return l.value == r.value; }
	template <class T>
	constexpr bool operator!=(Radian<T> l, Radian<T> r) { return l.value != r.value; }
	template <class T>
	constexpr bool operator<(Radian<T> l, Radian<T> r) { return l.value < r.value; }
	template <class T>
	constexpr bool operator<=(Radian<T> l, Radian<T> r) { return l.value <= r.value; }
	template <class T>
	constexpr bool operator>(Radian<T> l, Radian<T> r) { return l.value > r.value; }
	template <class T>
	constexpr bool operator>=(Radian<T> l, Radian<T> r) { return l.value >= r.value; }

	template <class T>
	constexpr Radian<T> operator+(Radian<T> l, Radian<T> r) { return Radian<T>(l.value + r.value); }
	template <class T>
	constexpr Radian<T> operator-(Radian<T> l, Radian<T> r) { return Radian<T>(l.value - r.value); }
	template <class T>
	constexpr Radian<T> operator*(Radian<T> l, T r) { return Radian<T>(l.value * r); }
	template <class T>
	constexpr Radian<T> operator*(T l, Radian<T> r) { return Radian<T>(l * r.value); }


	template <class T>
	constexpr Degree<T>::Degree(Radian<T> r) : value(r.value * RadianToDegree) {}
	template <class T>
	constexpr Radian<T>::Radian(Degree<T> d) : value(d.value * DegreeToRadian) {}

	using RadianF32 = Radian<float32>;
	using DegreeF32 = Degree<float32>;
}