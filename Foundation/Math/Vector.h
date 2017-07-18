#pragma once
#include "Core/BasicType.h"
#include "Core/Utility.h"
#include "Math/MathHelper.h"
#include <cassert>


namespace X
{
	struct SwizzleTag {};
	struct _X : SwizzleTag { static constexpr uint32 Index = 0; };
	struct _Y : SwizzleTag { static constexpr uint32 Index = 1; };
	struct _Z : SwizzleTag { static constexpr uint32 Index = 2; };
	struct _W : SwizzleTag { static constexpr uint32 Index = 3; };

	template <class T, uint32 Count>
	class VectorT;

	template <class T>
	class VectorT<T, 1>
	{
	public:
		static constexpr uint32 Count = 1;

		static VectorT const Zero;

		union
		{
			T v[Count];
			struct
			{
				T x;
			};
		};
		constexpr VectorT() noexcept = default;

		constexpr VectorT(T const& x) noexcept : v{ x } {}

		constexpr VectorT(VectorT const& r) noexcept : v{ r.v[0] } {}
		template <class U>
		constexpr explicit VectorT(VectorT<U, Count> const& r) noexcept : v{ T(r.v[0]) } {}

		constexpr VectorT& operator=(VectorT const& r) noexcept { v[0] = r.v[0]; return *this; }
		template <class U>
		constexpr VectorT& operator=(VectorT<U, Count> const& r) noexcept { v[0] = T(r.v[0]); return *this; }

		constexpr T const& X() const { return v[0]; }
		constexpr T& X() { return v[0]; }

		constexpr T const& operator[](uint32 index) const noexcept { assert(index < Count); return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { assert(index < Count); return v[index]; }

		template <class Swizzle0>
		constexpr VectorT<T, 1> _() { return VectorT<T, 1>(v[Swizzle0::Index]); }

		constexpr VectorT const& operator+() const noexcept { return *this; }
		constexpr VectorT operator-() const noexcept { return VectorT(-v[0]); }

		constexpr VectorT Normalized() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return *this / Length(); }

		constexpr T Length() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return std::sqrt(LengthSquared()); }

		constexpr T LengthSquared() const noexcept { return Dot(*this, *this); }

		constexpr T const* GetData() const noexcept { return v; }

		constexpr operator T() const noexcept { return v[0]; }
	};

	template <class T>
	VectorT<T, 1> const VectorT<T, 1>::Zero = VectorT(T(0));

	template <class T>
	constexpr VectorT<T, 1> operator+(VectorT<T, 1> const& l, VectorT<T, 1> const& r) noexcept { return VectorT<T, 1>(l.v[0] + r.v[0]); }
	template <class T>
	constexpr VectorT<T, 1> operator-(VectorT<T, 1> const& l, VectorT<T, 1> const& r) noexcept { return VectorT<T, 1>(l.v[0] - r.v[0]); }
	template <class T>
	constexpr VectorT<T, 1> operator*(VectorT<T, 1> const& l, VectorT<T, 1> const& r) noexcept { return VectorT<T, 1>(l.v[0] * r.v[0]); }
	template <class T>
	constexpr VectorT<T, 1> operator*(VectorT<T, 1> const& l, T const& r) noexcept { return VectorT<T, 1>(l.v[0] * r); }
	template <class T>
	constexpr VectorT<T, 1> operator*(T const& l, VectorT<T, 1> const& r) noexcept { return VectorT<T, 1>(l * r.v[0]); }
	template <class T>
	constexpr VectorT<T, 1> operator/(VectorT<T, 1> const& l, VectorT<T, 1> const& r) noexcept { return VectorT<T, 1>(l.v[0] / r.v[0]); }
	template <class T>
	constexpr VectorT<T, 1> operator/(VectorT<T, 1> const& l, T const& r) noexcept { return VectorT<T, 1>(l.v[0] / r); }

	template <class T>
	constexpr bool operator==(VectorT<T, 1> const& l, VectorT<T, 1> const& r) noexcept { return l.v[0] == r.v[0]; }
	template <class T>
	constexpr bool operator!=(VectorT<T, 1> const& l, VectorT<T, 1> const& r) noexcept { return l.v[0] != r.v[0]; }

	template <class T>
	constexpr T Dot(VectorT<T, 1> const& l, VectorT<T, 1> const& r) noexcept { return l.v[0] * r.v[0]; }

	template <class T>
	class VectorT<T, 2>
	{
	public:
		static constexpr uint32 Count = 2;

		static VectorT const Zero;

		union
		{
			T v[Count];
			struct
			{
				T x;
				T y;
			};
		};

		constexpr VectorT() noexcept = default;

		constexpr VectorT(T const& x, T const& y) noexcept : v{ x, y } {}

		constexpr VectorT(VectorT const& r) noexcept : v{ r.v[0], r.v[1] } {}
		template <class U>
		constexpr explicit VectorT(VectorT<U, Count> const& r) noexcept : v{ T(r.v[0]), T(r.v[1]) } {}

		constexpr VectorT& operator=(VectorT const& r) noexcept { v[0] = r.v[0]; v[1] = r.v[1]; return *this; }
		template <class U>
		constexpr VectorT& operator=(VectorT<U, Count> const& r) noexcept { v[0] = T(r.v[0]); v[1] = T(r.v[1]); return *this; }

		constexpr T const& X() const { return v[0]; }
		constexpr T const& Y() const { return v[1]; }
		constexpr T& X() { return v[0]; }
		constexpr T& Y() { return v[1]; }

		constexpr T const& operator[](uint32 index) const noexcept { assert(index < Count); return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { assert(index < Count); return v[index]; }

		template <class Swizzle0>
		constexpr VectorT<T, 1> _() { return VectorT<T, 1>(v[Swizzle0::Index]); }
		template <class Swizzle0, class Swizzle1>
		constexpr VectorT<T, 2> _() { return VectorT<T, 2>(v[Swizzle0::Index], v[Swizzle1::Index]); }


		constexpr VectorT const& operator+() const noexcept { return *this; }
		constexpr VectorT operator-() const noexcept { return VectorT(-v[0], -v[1]); }

		constexpr VectorT Normalized() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return *this / Length(); }

		constexpr T Length() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return std::sqrt(LengthSquared()); }

		constexpr T LengthSquared() const noexcept { return Dot(*this, *this); }

		constexpr T const* GetData() const noexcept { return v; }
	};

	template <class T>
	VectorT<T, 2> const VectorT<T, 2>::Zero = VectorT(T(0), T(0));

	template <class T>
	constexpr VectorT<T, 2> operator+(VectorT<T, 2> const& l, VectorT<T, 2> const& r) noexcept { return VectorT<T, 2>(l.v[0] + r.v[0], l.v[1] + r.v[1]); }
	template <class T>
	constexpr VectorT<T, 2> operator-(VectorT<T, 2> const& l, VectorT<T, 2> const& r) noexcept { return VectorT<T, 2>(l.v[0] - r.v[0], l.v[1] - r.v[1]); }
	template <class T>
	constexpr VectorT<T, 2> operator*(VectorT<T, 2> const& l, VectorT<T, 2> const& r) noexcept { return VectorT<T, 2>(l.v[0] * r.v[0], l.v[1] * r.v[1]); }
	template <class T>
	constexpr VectorT<T, 2> operator*(VectorT<T, 2> const& l, T const& r) noexcept { return VectorT<T, 2>(l.v[0] * r, l.v[1] * r); }
	template <class T>
	constexpr VectorT<T, 2> operator*(T const& l, VectorT<T, 2> const& r) noexcept { return VectorT<T, 2>(l * r.v[0], l * r.v[1]); }
	template <class T>
	constexpr VectorT<T, 2> operator/(VectorT<T, 2> const& l, VectorT<T, 2> const& r) noexcept { return VectorT<T, 2>(l.v[0] / r.v[0], l.v[1] / r.v[1]); }
	template <class T>
	constexpr VectorT<T, 2> operator/(VectorT<T, 2> const& l, T const& r) noexcept { return VectorT<T, 2>(l.v[0] / r, l.v[1] / r); }

	template <class T>
	constexpr bool operator==(VectorT<T, 2> const& l, VectorT<T, 2> const& r) noexcept { return l.v[0] == r.v[0] && l.v[1] == r.v[1]; }
	template <class T>
	constexpr bool operator!=(VectorT<T, 2> const& l, VectorT<T, 2> const& r) noexcept { return l.v[0] != r.v[0] || l.v[1] != r.v[1]; }

	template <class T>
	constexpr T Dot(VectorT<T, 2> const& l, VectorT<T, 2> const& r) noexcept { return l.v[0] * r.v[0] + l.v[1] * r.v[1]; }

	template <class T>
	class VectorT<T, 3>
	{
	public:
		static constexpr uint32 Count = 3;

		static VectorT const Zero;

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

		constexpr VectorT() noexcept = default;

		constexpr VectorT(T const& x, T const& y, T const& z) noexcept : v{ x, y, z } {}
		constexpr VectorT(VectorT<T, 2> const& xy, T const& z) noexcept : v{ xy.v[0], xy.v[1], z } {}
		constexpr VectorT(T const& x, VectorT<T, 2> const& yz) noexcept : v{ x, yz.v[0], yz.v[1] } {}

		constexpr VectorT(VectorT const& r) noexcept : v{ r.v[0], r.v[1], r.v[2] } {}
		template <class U>
		constexpr explicit VectorT(VectorT<U, Count> const& r) noexcept : v{ T(r.v[0]), T(r.v[1]), T(r.v[2]) } {}

		constexpr VectorT& operator=(VectorT const& r) noexcept { v[0] = r.v[0]; v[1] = r.v[1]; v[2] = r.v[2]; return *this; }
		template <class U>
		constexpr VectorT& operator=(VectorT<U, Count> const& r) noexcept { v[0] = T(r.v[0]); v[1] = T(r.v[1]); v[2] = T(r.v[2]); return *this; }

		constexpr T const& X() const { return v[0]; }
		constexpr T const& Y() const { return v[1]; }
		constexpr T const& Z() const { return v[2]; }
		constexpr T& X() { return v[0]; }
		constexpr T& Y() { return v[1]; }
		constexpr T& Z() { return v[2]; }

		constexpr T const& operator[](uint32 index) const noexcept { assert(index < Count); return v[index]; }
		constexpr T& operator[](uint32 index) noexcept { assert(index < Count); return v[index]; }

		template <class Swizzle0>
		constexpr VectorT<T, 1> _() { return VectorT<T, 1>(v[Swizzle0::Index]); }
		template <class Swizzle0, class Swizzle1>
		constexpr VectorT<T, 2> _() { return VectorT<T, 2>(v[Swizzle0::Index], v[Swizzle1::Index]); }
		template <class Swizzle0, class Swizzle1, class Swizzle2>
		constexpr VectorT<T, 3> _() { return VectorT<T, 3>(v[Swizzle0::Index], v[Swizzle1::Index], v[Swizzle2::Index]); }

		constexpr VectorT const& operator+() const noexcept { return *this; }
		constexpr VectorT operator-() const noexcept { return VectorT(-v[0], -v[1], -v[2]); }

		constexpr VectorT Normalized() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return *this / Length(); }

		constexpr T Length() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return std::sqrt(LengthSquared()); }

		constexpr T LengthSquared() const noexcept { return Dot(*this, *this); }

		constexpr T const* GetData() const noexcept { return v; }
	};

	template <class T>
	VectorT<T, 3> const VectorT<T, 3>::Zero = VectorT(T(0), T(0), T(0));

	template <class T>
	constexpr VectorT<T, 3> operator+(VectorT<T, 3> const& l, VectorT<T, 3> const& r) noexcept { return VectorT<T, 3>(l.v[0] + r.v[0], l.v[1] + r.v[1], l.v[2] + r.v[2]); }
	template <class T>
	constexpr VectorT<T, 3> operator-(VectorT<T, 3> const& l, VectorT<T, 3> const& r) noexcept { return VectorT<T, 3>(l.v[0] - r.v[0], l.v[1] - r.v[1], l.v[2] - r.v[2]); }
	template <class T>
	constexpr VectorT<T, 3> operator*(VectorT<T, 3> const& l, VectorT<T, 3> const& r) noexcept { return VectorT<T, 3>(l.v[0] * r.v[0], l.v[1] * r.v[1], l.v[2] * r.v[2]); }
	template <class T>
	constexpr VectorT<T, 3> operator*(VectorT<T, 3> const& l, T const& r) noexcept { return VectorT<T, 3>(l.v[0] * r, l.v[1] * r, l.v[2] * r); }
	template <class T>
	constexpr VectorT<T, 3> operator*(T const& l, VectorT<T, 3> const& r) noexcept { return VectorT<T, 3>(l * r.v[0], l * r.v[1], l * r.v[2]); }
	template <class T>
	constexpr VectorT<T, 3> operator/(VectorT<T, 3> const& l, VectorT<T, 3> const& r) noexcept { return VectorT<T, 3>(l.v[0] / r.v[0], l.v[1] / r.v[1], l.v[2] / r.v[2]); }
	template <class T>
	constexpr VectorT<T, 3> operator/(VectorT<T, 3> const& l, T const& r) noexcept { return VectorT<T, 3>(l.v[0] / r, l.v[1] / r, l.v[2] / r); }

	template <class T>
	constexpr bool operator==(VectorT<T, 3> const& l, VectorT<T, 3> const& r) noexcept { return l.v[0] == r.v[0] && l.v[1] == r.v[1] && l.v[2] == r.v[2]; }
	template <class T>
	constexpr bool operator!=(VectorT<T, 3> const& l, VectorT<T, 3> const& r) noexcept { return l.v[0] != r.v[0] || l.v[1] != r.v[1] || l.v[2] != r.v[2]; }

	template <class T>
	constexpr T Dot(VectorT<T, 3> const& l, VectorT<T, 3> const& r) noexcept { return l.v[0] * r.v[0] + l.v[1] * r.v[1] + l.v[2] * r.v[2]; }
	template <class T>
	constexpr VectorT<T, 3> Cross(VectorT<T, 3> const& l, VectorT<T, 3> const& r) noexcept { return VectorT<T, 3>(l.v[1] * r.v[2] - l.v[2] * r.v[1], l.v[2] * r.v[0] - l.v[0] * r.v[2], l.v[0] * r.v[1] - l.v[1] * r.v[0]); }

	template <class T>
	class VectorT<T, 4>
	{
	public:
		static constexpr uint32 Count = 4;

		static VectorT const Zero;

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

		constexpr VectorT() noexcept = default;

		constexpr VectorT(T const& x, T const& y, T const& z, T const& w) noexcept : v{ x, y, z, w } {}
		constexpr VectorT(VectorT<T, 2> const& xy, T const& z, T const& w) noexcept : v{ xy.v[0], xy.v[1], z, w } {}
		constexpr VectorT(T const& x, VectorT<T, 2> const& yz, T const& w) noexcept : v{ x, yz.v[0], yz.v[1], w } {}
		constexpr VectorT(T const& x, T const& y, VectorT<T, 2> const& zw) noexcept : v{ x, y, zw.v[0], zw.v[1] } {}
		constexpr VectorT(VectorT<T, 2> const& xy, VectorT<T, 2> const& zw) noexcept : v{ xy.v[0], xy.v[1], zw.v[0], zw.v[1] } {}
		constexpr VectorT(VectorT<T, 3> const& xyz, T const& w) noexcept : v{ xyz.v[0], xyz.v[1], xyz.v[2], w } {}
		constexpr VectorT(T const& x, VectorT<T, 3> const& yzw) noexcept : v{ x, yzw.v[0], yzw.v[1], yzw.v[2] } {}

		constexpr VectorT(VectorT const& r) noexcept : v{ r.v[0], r.v[1], r.v[2], r.v[3] } {}
		template <class U>
		constexpr explicit VectorT(VectorT<U, Count> const& r) noexcept : v{ T(r.v[0]), T(r.v[1]), T(r.v[2]), T(r.v[3]) } {}

		constexpr VectorT& operator=(VectorT const& r) noexcept { v[0] = r.v[0]; v[1] = r.v[1]; v[2] = r.v[2]; v[3] = r.v[3]; return *this; }
		template <class U>
		constexpr VectorT& operator=(VectorT<U, Count> const& r) noexcept { v[0] = T(r.v[0]); v[1] = T(r.v[1]); v[2] = T(r.v[2]); v[3] = T(r.v[3]); return *this; }

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
		constexpr VectorT<T, 1> _() { return VectorT<T, 1>(v[Swizzle0::Index]); }
		template <class Swizzle0, class Swizzle1>
		constexpr VectorT<T, 2> _() { return VectorT<T, 2>(v[Swizzle0::Index], v[Swizzle1::Index]); }
		template <class Swizzle0, class Swizzle1, class Swizzle2>
		constexpr VectorT<T, 3> _() { return VectorT<T, 3>(v[Swizzle0::Index], v[Swizzle1::Index], v[Swizzle2::Index]); }
		template <class Swizzle0, class Swizzle1, class Swizzle2, class Swizzle3>
		constexpr VectorT<T, 4> _() { return VectorT<T, 4>(v[Swizzle0::Index], v[Swizzle1::Index], v[Swizzle2::Index], v[Swizzle3::Index]); }

		constexpr VectorT const& operator+() const noexcept { return *this; }
		constexpr VectorT operator-() const noexcept { return VectorT(-v[0], -v[1], -v[2], -v[3]); }

		constexpr VectorT Normalized() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return *this / Length(); }

		constexpr T Length() const noexcept { static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only."); return std::sqrt(LengthSquared()); }

		constexpr T LengthSquared() const noexcept { return Dot(*this, *this); }

		T const* GetData() const noexcept { return v; }
	};

	template <class T>
	VectorT<T, 4> const VectorT<T, 4>::Zero = VectorT(T(0), T(0), T(0), T(0));

	template <class T>
	constexpr VectorT<T, 4> operator+(VectorT<T, 4> const& l, VectorT<T, 4> const& r) noexcept { return VectorT<T, 4>(l.v[0] + r.v[0], l.v[1] + r.v[1], l.v[2] + r.v[2], l.v[3] + r.v[3]); }
	template <class T>
	constexpr VectorT<T, 4> operator-(VectorT<T, 4> const& l, VectorT<T, 4> const& r) noexcept { return VectorT<T, 4>(l.v[0] - r.v[0], l.v[1] - r.v[1], l.v[2] - r.v[2], l.v[3] - r.v[3]); }
	template <class T>
	constexpr VectorT<T, 4> operator*(VectorT<T, 4> const& l, VectorT<T, 4> const& r) noexcept { return VectorT<T, 4>(l.v[0] * r.v[0], l.v[1] * r.v[1], l.v[2] * r.v[2], l.v[3] * r.v[3]); }

	template <class T>
	constexpr VectorT<T, 4> operator*(VectorT<T, 4> const& l, T const& r) noexcept { return VectorT<T, 4>(l.v[0] * r, l.v[1] * r, l.v[2] * r, l.v[3] * r); }
	template <class T>
	constexpr VectorT<T, 4> operator*(T const& l, VectorT<T, 4> const& r) noexcept { return VectorT<T, 4>(l * r.v[0], l * r.v[1], l * r.v[2], l * r.v[3]); }
	template <class T>
	constexpr VectorT<T, 4> operator/(VectorT<T, 4> const& l, VectorT<T, 4> const& r) noexcept { return VectorT<T, 4>(l.v[0] / r.v[0], l.v[1] / r.v[1], l.v[2] / r.v[2], l.v[3] / r.v[3]); }
	template <class T>
	constexpr VectorT<T, 4> operator/(VectorT<T, 4> const& l, T const& r) noexcept { return VectorT<T, 4>(l.v[0] / r, l.v[1] / r, l.v[2] / r, l.v[3] / r); }

	template <class T>
	constexpr bool operator==(VectorT<T, 4> const& l, VectorT<T, 4> const& r) noexcept { return l.v[0] == r.v[0] && l.v[1] == r.v[1] && l.v[2] == r.v[2]&& l.v[3] == r.v[3]; }
	template <class T>
	constexpr bool operator!=(VectorT<T, 4> const& l, VectorT<T, 4> const& r) noexcept { return l.v[0] != r.v[0] || l.v[1] != r.v[1] || l.v[2] != r.v[2] || l.v[3] != r.v[3]; }
	template <class T>
	constexpr T Dot(VectorT<T, 4> const& l, VectorT<T, 4> const& r) noexcept { return l.v[0] * r.v[0] + l.v[1] * r.v[1] + l.v[2] * r.v[2] + l.v[3] * r.v[3]; }

	using V1F32 = VectorT<float32, 1>;
	using V2F32 = VectorT<float32, 2>;
	using V3F32 = VectorT<float32, 3>;
	using V4F32 = VectorT<float32, 4>;

	using V1F64 = VectorT<float64, 1>;
	using V2F64 = VectorT<float64, 2>;
	using V3F64 = VectorT<float64, 3>;
	using V4F64 = VectorT<float64, 4>;

	using V1S32 = VectorT<sint32, 1>;
	using V2S32 = VectorT<sint32, 2>;
	using V3S32 = VectorT<sint32, 3>;
	using V4S32 = VectorT<sint32, 4>;

	using V1U32 = VectorT<uint32, 1>;
	using V2U32 = VectorT<uint32, 2>;
	using V3U32 = VectorT<uint32, 3>;
	using V4U32 = VectorT<uint32, 4>;

}
