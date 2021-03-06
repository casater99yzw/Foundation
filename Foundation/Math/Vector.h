#pragma once
#include "Core/BasicType.h"
#include "Core/Utility.h"
#include <cassert>


namespace X
{
	struct SwizzleTag {};
	struct _X : SwizzleTag { static constexpr uint32 Index = 0; };
	struct _Y : SwizzleTag { static constexpr uint32 Index = 1; };
	struct _Z : SwizzleTag { static constexpr uint32 Index = 2; };
	struct _W : SwizzleTag { static constexpr uint32 Index = 3; };

	template <class T, uint32 Count>
	class Vector;

	template <class T>
	class Vector<T, 1>
	{
	public:
		static constexpr uint32 Count = 1;

		static Vector const Zero;

		union
		{
			T v[Count];
			struct
			{
				T x;
			};
		};
		constexpr Vector() noexcept = default;

		constexpr Vector(T const& x) noexcept : v{ x } {}

		template <class U>
		constexpr explicit Vector(Vector<U, Count> const& r) noexcept : v{ T(r.v[0]) } {}

		constexpr T const& X() const { return v[0]; }
		constexpr T& X() { return v[0]; }

		constexpr T const& operator[](uint32 index) const noexcept { assert(index < Count); return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { assert(index < Count); return v[index]; }

		template <class Swizzle0>
		constexpr Vector<T, 1> _() { return Vector<T, 1>(v[Swizzle0::Index]); }

		constexpr Vector const& operator+() const noexcept { return *this; }
		constexpr Vector operator-() const noexcept { return Vector(-v[0]); }

		constexpr Vector& operator+=(Vector const& r) noexcept { v[0] += r.v[0]; return *this; }
		constexpr Vector& operator-=(Vector const& r) noexcept { v[0] -= r.v[0]; return *this; }
		constexpr Vector& operator*=(Vector const& r) noexcept { v[0] *= r.v[0]; return *this; }
		constexpr Vector& operator*=(T const& r) noexcept { v[0] *= r; return *this; }
		constexpr Vector& operator/=(Vector const& r) noexcept { v[0] /= r.v[0]; return *this; }
		constexpr Vector& operator/=(T const& r) noexcept { v[0] /= r; return *this; }

		constexpr Vector Normalized() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return *this / Length(); }

		constexpr T Length() const noexcept { static_assert(std::is_floating_point_v<T>, "Length() for floating point types only."); return std::sqrt(LengthSquared()); }

		constexpr T LengthSquared() const noexcept { return Dot(*this, *this); }

		T const* Data() const noexcept { return v; }

		constexpr operator T() const noexcept { return v[0]; }
	};

	template <class T>
	Vector<T, 1> const Vector<T, 1>::Zero = Vector(T(0));

	template <class T>
	constexpr bool operator==(Vector<T, 1> const& l, Vector<T, 1> const& r) noexcept { return l.v[0] == r.v[0]; }
	template <class T>
	constexpr bool operator!=(Vector<T, 1> const& l, Vector<T, 1> const& r) noexcept { return l.v[0] != r.v[0]; }

	template <class T>
	constexpr T Dot(Vector<T, 1> const& l, Vector<T, 1> const& r) noexcept { return l.v[0] * r.v[0]; }

	template <class T>
	class Vector<T, 2>
	{
	public:
		static constexpr uint32 Count = 2;

		static Vector const Zero;

		union
		{
			T v[Count];
			struct
			{
				T x;
				T y;
			};
		};

		constexpr Vector() noexcept = default;

		constexpr explicit Vector(T const& v) noexcept : v{ v, v } {}

		constexpr Vector(T const& x, T const& y) noexcept : v{ x, y } {}

		template <class U>
		constexpr explicit Vector(Vector<U, Count> const& r) noexcept : v{ T(r.v[0]), T(r.v[1]) } {}

		constexpr T const& X() const { return v[0]; }
		constexpr T const& Y() const { return v[1]; }
		constexpr T& X() { return v[0]; }
		constexpr T& Y() { return v[1]; }

		constexpr T const& operator[](uint32 index) const noexcept { assert(index < Count); return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { assert(index < Count); return v[index]; }

		template <class Swizzle0>
		constexpr Vector<T, 1> _() { return Vector<T, 1>(v[Swizzle0::Index]); }
		template <class Swizzle0, class Swizzle1>
		constexpr Vector<T, 2> _() { return Vector<T, 2>(v[Swizzle0::Index], v[Swizzle1::Index]); }


		constexpr Vector const& operator+() const noexcept { return *this; }
		constexpr Vector operator-() const noexcept { return Vector(-v[0], -v[1]); }

		constexpr Vector& operator+=(Vector const& r) noexcept { v[0] += r.v[0]; v[1] += r.v[1]; return *this; }
		constexpr Vector& operator-=(Vector const& r) noexcept { v[0] -= r.v[0]; v[1] -= r.v[1]; return *this; }
		constexpr Vector& operator*=(Vector const& r) noexcept { v[0] *= r.v[0]; v[1] *= r.v[1]; return *this; }
		constexpr Vector& operator*=(T const& r) noexcept { v[0] *= r; v[1] *= r; return *this; }
		constexpr Vector& operator/=(Vector const& r) noexcept { v[0] /= r.v[0]; v[1] /= r.v[1]; return *this; }
		constexpr Vector& operator/=(T const& r) noexcept { v[0] /= r; v[1] /= r; return *this; }

		constexpr Vector Normalized() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return *this / Length(); }

		constexpr T Length() const noexcept { static_assert(std::is_floating_point_v<T>, "Length() for floating point types only."); return std::sqrt(LengthSquared()); }

		constexpr T LengthSquared() const noexcept { return Dot(*this, *this); }

		T const* Data() const noexcept { return v; }
	};

	template <class T>
	Vector<T, 2> const Vector<T, 2>::Zero = Vector(T(0), T(0));

	template <class T>
	constexpr bool operator==(Vector<T, 2> const& l, Vector<T, 2> const& r) noexcept { return l.v[0] == r.v[0] && l.v[1] == r.v[1]; }
	template <class T>
	constexpr bool operator!=(Vector<T, 2> const& l, Vector<T, 2> const& r) noexcept { return l.v[0] != r.v[0] || l.v[1] != r.v[1]; }

	template <class T>
	constexpr T Dot(Vector<T, 2> const& l, Vector<T, 2> const& r) noexcept { return l.v[0] * r.v[0] + l.v[1] * r.v[1]; }

	template <class T>
	class Vector<T, 3>
	{
	public:
		static constexpr uint32 Count = 3;

		static Vector const Zero;

		union
		{
			T v[Count];
			struct
			{
				T x;
				T y;
				T z;
			};
		};

		constexpr Vector() noexcept = default;

		constexpr explicit Vector(T const& v) noexcept : v{ v, v, v } {}

		constexpr Vector(T const& x, T const& y, T const& z) noexcept : v{ x, y, z } {}
		constexpr Vector(Vector<T, 2> const& xy, T const& z) noexcept : v{ xy.v[0], xy.v[1], z } {}
		constexpr Vector(T const& x, Vector<T, 2> const& yz) noexcept : v{ x, yz.v[0], yz.v[1] } {}

		template <class U>
		constexpr explicit Vector(Vector<U, Count> const& r) noexcept : v{ T(r.v[0]), T(r.v[1]), T(r.v[2]) } {}

		constexpr T const& X() const { return v[0]; }
		constexpr T const& Y() const { return v[1]; }
		constexpr T const& Z() const { return v[2]; }
		constexpr T& X() { return v[0]; }
		constexpr T& Y() { return v[1]; }
		constexpr T& Z() { return v[2]; }

		constexpr T const& operator[](uint32 index) const noexcept { assert(index < Count); return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { assert(index < Count); return v[index]; }

		template <class Swizzle0>
		constexpr Vector<T, 1> _() { return Vector<T, 1>(v[Swizzle0::Index]); }
		template <class Swizzle0, class Swizzle1>
		constexpr Vector<T, 2> _() { return Vector<T, 2>(v[Swizzle0::Index], v[Swizzle1::Index]); }
		template <class Swizzle0, class Swizzle1, class Swizzle2>
		constexpr Vector<T, 3> _() { return Vector<T, 3>(v[Swizzle0::Index], v[Swizzle1::Index], v[Swizzle2::Index]); }

		constexpr Vector const& operator+() const noexcept { return *this; }
		constexpr Vector operator-() const noexcept { return Vector(-v[0], -v[1], -v[2]); }

		constexpr Vector& operator+=(Vector const& r) noexcept { v[0] += r.v[0]; v[1] += r.v[1]; v[2] += r.v[2]; return *this; }
		constexpr Vector& operator-=(Vector const& r) noexcept { v[0] -= r.v[0]; v[1] -= r.v[1]; v[2] -= r.v[2]; return *this; }
		constexpr Vector& operator*=(Vector const& r) noexcept { v[0] *= r.v[0]; v[1] *= r.v[1]; v[2] *= r.v[2]; return *this; }
		constexpr Vector& operator*=(T const& r) noexcept { v[0] *= r; v[1] *= r; v[2] *= r; return *this; }
		constexpr Vector& operator/=(Vector const& r) noexcept { v[0] /= r.v[0]; v[1] /= r.v[1]; v[2] /= r.v[2]; return *this; }
		constexpr Vector& operator/=(T const& r) noexcept { v[0] /= r; v[1] /= r; v[2] /= r; return *this; }

		constexpr Vector Normalized() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return *this / Length(); }

		constexpr T Length() const noexcept { static_assert(std::is_floating_point_v<T>, "Length() for floating point types only."); return std::sqrt(LengthSquared()); }

		constexpr T LengthSquared() const noexcept { return Dot(*this, *this); }

		T const* Data() const noexcept { return v; }
	};

	template <class T>
	Vector<T, 3> const Vector<T, 3>::Zero = Vector(T(0), T(0), T(0));

	template <class T>
	constexpr bool operator==(Vector<T, 3> const& l, Vector<T, 3> const& r) noexcept { return l.v[0] == r.v[0] && l.v[1] == r.v[1] && l.v[2] == r.v[2]; }
	template <class T>
	constexpr bool operator!=(Vector<T, 3> const& l, Vector<T, 3> const& r) noexcept { return l.v[0] != r.v[0] || l.v[1] != r.v[1] || l.v[2] != r.v[2]; }

	template <class T>
	constexpr T Dot(Vector<T, 3> const& l, Vector<T, 3> const& r) noexcept { return l.v[0] * r.v[0] + l.v[1] * r.v[1] + l.v[2] * r.v[2]; }
	template <class T>
	constexpr Vector<T, 3> Cross(Vector<T, 3> const& l, Vector<T, 3> const& r) noexcept { return Vector<T, 3>(l.v[1] * r.v[2] - l.v[2] * r.v[1], l.v[2] * r.v[0] - l.v[0] * r.v[2], l.v[0] * r.v[1] - l.v[1] * r.v[0]); }

	template <class T>
	class Vector<T, 4>
	{
	public:
		static constexpr uint32 Count = 4;

		static Vector const Zero;

		union
		{
			T v[Count];
			struct
			{
				T x;
				T y;
				T z;
				T w;
			};
		};

		constexpr Vector() noexcept = default;

		constexpr explicit Vector(T const& v) noexcept : v{ v, v, v, v } {}

		constexpr Vector(T const& x, T const& y, T const& z, T const& w) noexcept : v{ x, y, z, w } {}
		constexpr Vector(Vector<T, 2> const& xy, T const& z, T const& w) noexcept : v{ xy.v[0], xy.v[1], z, w } {}
		constexpr Vector(T const& x, Vector<T, 2> const& yz, T const& w) noexcept : v{ x, yz.v[0], yz.v[1], w } {}
		constexpr Vector(T const& x, T const& y, Vector<T, 2> const& zw) noexcept : v{ x, y, zw.v[0], zw.v[1] } {}
		constexpr Vector(Vector<T, 2> const& xy, Vector<T, 2> const& zw) noexcept : v{ xy.v[0], xy.v[1], zw.v[0], zw.v[1] } {}
		constexpr Vector(Vector<T, 3> const& xyz, T const& w) noexcept : v{ xyz.v[0], xyz.v[1], xyz.v[2], w } {}
		constexpr Vector(T const& x, Vector<T, 3> const& yzw) noexcept : v{ x, yzw.v[0], yzw.v[1], yzw.v[2] } {}

		template <class U>
		constexpr explicit Vector(Vector<U, Count> const& r) noexcept : v{ T(r.v[0]), T(r.v[1]), T(r.v[2]), T(r.v[3]) } {}

		constexpr T const& X() const { return v[0]; }
		constexpr T const& Y() const { return v[1]; }
		constexpr T const& Z() const { return v[2]; }
		constexpr T const& W() const { return v[3]; }
		constexpr T& X() { return v[0]; }
		constexpr T& Y() { return v[1]; }
		constexpr T& Z() { return v[2]; }
		constexpr T& W() { return v[3]; }

		constexpr T const& operator[](uint32 index) const noexcept { assert(index < Count); return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { assert(index < Count); return v[index]; }

		template <class Swizzle0>
		constexpr Vector<T, 1> _() { return Vector<T, 1>(v[Swizzle0::Index]); }
		template <class Swizzle0, class Swizzle1>
		constexpr Vector<T, 2> _() { return Vector<T, 2>(v[Swizzle0::Index], v[Swizzle1::Index]); }
		template <class Swizzle0, class Swizzle1, class Swizzle2>
		constexpr Vector<T, 3> _() { return Vector<T, 3>(v[Swizzle0::Index], v[Swizzle1::Index], v[Swizzle2::Index]); }
		template <class Swizzle0, class Swizzle1, class Swizzle2, class Swizzle3>
		constexpr Vector<T, 4> _() { return Vector<T, 4>(v[Swizzle0::Index], v[Swizzle1::Index], v[Swizzle2::Index], v[Swizzle3::Index]); }

		constexpr Vector const& operator+() const noexcept { return *this; }
		constexpr Vector operator-() const noexcept { return Vector(-v[0], -v[1], -v[2], -v[3]); }

		constexpr Vector& operator+=(Vector const& r) noexcept { v[0] += r.v[0]; v[1] += r.v[1]; v[2] += r.v[2]; v[3] += r.v[3]; return *this; }
		constexpr Vector& operator-=(Vector const& r) noexcept { v[0] -= r.v[0]; v[1] -= r.v[1]; v[2] -= r.v[2]; v[3] -= r.v[3]; return *this; }
		constexpr Vector& operator*=(Vector const& r) noexcept { v[0] *= r.v[0]; v[1] *= r.v[1]; v[2] *= r.v[2]; v[3] *= r.v[3]; return *this; }
		constexpr Vector& operator*=(T const& r) noexcept { v[0] *= r; v[1] *= r; v[2] *= r; v[3] *= r; return *this; }
		constexpr Vector& operator/=(Vector const& r) noexcept { v[0] /= r.v[0]; v[1] /= r.v[1]; v[2] /= r.v[2]; v[3] /= r.v[3]; return *this; }
		constexpr Vector& operator/=(T const& r) noexcept { v[0] /= r; v[1] /= r; v[2] /= r; v[3] /= r; return *this; }

		constexpr Vector Normalized() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return *this / Length(); }

		constexpr T Length() const noexcept { static_assert(std::is_floating_point_v<T>, "Length() for floating point types only."); return std::sqrt(LengthSquared()); }

		constexpr T LengthSquared() const noexcept { return Dot(*this, *this); }

		T const* Data() const noexcept { return v; }
	};

	template <class T>
	Vector<T, 4> const Vector<T, 4>::Zero = Vector(T(0), T(0), T(0), T(0));

	template <class T>
	constexpr bool operator==(Vector<T, 4> const& l, Vector<T, 4> const& r) noexcept { return l.v[0] == r.v[0] && l.v[1] == r.v[1] && l.v[2] == r.v[2]&& l.v[3] == r.v[3]; }
	template <class T>
	constexpr bool operator!=(Vector<T, 4> const& l, Vector<T, 4> const& r) noexcept { return l.v[0] != r.v[0] || l.v[1] != r.v[1] || l.v[2] != r.v[2] || l.v[3] != r.v[3]; }
	template <class T>
	constexpr T Dot(Vector<T, 4> const& l, Vector<T, 4> const& r) noexcept { return l.v[0] * r.v[0] + l.v[1] * r.v[1] + l.v[2] * r.v[2] + l.v[3] * r.v[3]; }


	template <class T, uint32 Count>
	constexpr Vector<T, Count> operator+(Vector<T, Count> const& l, Vector<T, Count> const& r) noexcept { Vector<T, Count> v = l; v += r; return v; }
	template <class T, uint32 Count>
	constexpr Vector<T, Count> operator-(Vector<T, Count> const& l, Vector<T, Count> const& r) noexcept { Vector<T, Count> v = l; v -= r; return v; }
	template <class T, uint32 Count>
	constexpr Vector<T, Count> operator*(Vector<T, Count> const& l, Vector<T, Count> const& r) noexcept { Vector<T, Count> v = l; v *= r; return v; }

	template <class T, uint32 Count>
	constexpr Vector<T, Count> operator*(Vector<T, Count> const& l, T const& r) noexcept { Vector<T, Count> v = l; v *= r; return v; }
	template <class T, uint32 Count>
	constexpr Vector<T, Count> operator*(T const& l, Vector<T, Count> const& r) noexcept { Vector<T, Count> v = r; v *= l; return v; }
	template <class T, uint32 Count>
	constexpr Vector<T, Count> operator/(Vector<T, Count> const& l, Vector<T, Count> const& r) noexcept { Vector<T, Count> v = l; v /= r; return v; }
	template <class T, uint32 Count>
	constexpr Vector<T, Count> operator/(Vector<T, Count> const& l, T const& r) noexcept { Vector<T, Count> v = l; v /= r; return v; }


	using V1F32 = Vector<float32, 1>;
	using V2F32 = Vector<float32, 2>;
	using V3F32 = Vector<float32, 3>;
	using V4F32 = Vector<float32, 4>;

	using V1F64 = Vector<float64, 1>;
	using V2F64 = Vector<float64, 2>;
	using V3F64 = Vector<float64, 3>;
	using V4F64 = Vector<float64, 4>;

	using V1S32 = Vector<sint32, 1>;
	using V2S32 = Vector<sint32, 2>;
	using V3S32 = Vector<sint32, 3>;
	using V4S32 = Vector<sint32, 4>;

	using V1U32 = Vector<uint32, 1>;
	using V2U32 = Vector<uint32, 2>;
	using V3U32 = Vector<uint32, 3>;
	using V4U32 = Vector<uint32, 4>;

}
