#pragma once
#include "Core/BasicType.h"
#include "Math/MathHelper.h"

#include <array>


namespace X
{

	template <typename T, uint32 N>
	class VectorT;


	template <typename T>
	class VectorT<T, 2>
	{
	public:
		static constexpr uint32 Dimension = 2;

		static VectorT const Zero;

		T x = T(0);
		T y = T(0);

	public:

		constexpr VectorT() noexcept = default;

		constexpr VectorT(T const& x, T const& y) noexcept
			: x(x), y(y) {}

		VectorT(VectorT const& r) noexcept
			: x(r.x), y(r.y) {}

		template <typename U>
		constexpr explicit VectorT(VectorT<U, Dimension> const& r) noexcept
			: x(static_cast<T>(r.x)), y(static_cast<T>(r.y)) {}

		constexpr VectorT& operator=(VectorT const& r) noexcept
		{
			x = r.x;
			y = r.y;
			return *this;
		}
		template <typename U>
		constexpr VectorT& operator=(VectorT<U, Dimension> const& r) noexcept
		{
			x = static_cast<T>(r.x);
			y = static_cast<T>(r.y);
			return *this;
		}

		constexpr T const& operator[](uint32 index) const noexcept
		{
			assert(index < Dimension);
			switch (index) // to make this function usable in constexpr
			{
			case 0:
				return x;
			case 1:
				return y;
			}
		}

		friend constexpr VectorT operator+(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x + r.x, l.y + r.y);
		}

		friend constexpr VectorT operator-(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x - r.x, l.y - r.y);
		}

		friend constexpr VectorT operator*(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x * r.x, l.y * r.y);
		}

		friend constexpr VectorT operator*(VectorT const& l, T const& r) noexcept
		{
			return VectorT(l.x * r, l.y * r);

		}
		friend constexpr VectorT operator*(T const& l, VectorT const& r) noexcept
		{
			return VectorT(l * r.x, l * r.y);
		}

		friend constexpr VectorT operator/(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x / r.x, l.y / r.y);
		}

		friend constexpr VectorT operator/(VectorT const& l, T const& r) noexcept
		{
			return VectorT(l.x / r, l.y / r);
		}

		constexpr VectorT const& operator+() const noexcept
		{
			return *this; 
		}
		constexpr VectorT operator-() const noexcept
		{
			return VectorT(-x, -y);
		}

		friend constexpr bool operator==(VectorT const& l, VectorT const& r) noexcept
		{
			return l.x == r.x && l.y == r.y;
		}

		friend constexpr bool operator!=(VectorT const& l, VectorT const& r) noexcept
		{
			return l.x != r.x || l.y != r.y;
		}

		constexpr VectorT Normalized() const noexcept
		{
			static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only.");
			return *this / Length();
		}

		constexpr T Length() const noexcept
		{
			static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only.");
			return std::sqrt(LengthSquared());
		}

		constexpr T LengthSquared() const noexcept
		{
			return Dot(*this, *this);
		}

		friend constexpr T Dot(VectorT const& l, VectorT const& r) noexcept
		{
			return l.x * r.x + l.y * r.y;
		}

		constexpr T const* GetArray() const noexcept
		{
			return &x;
		}
	};

	template <typename T>
	VectorT<T, 2> const VectorT<T, 2>::Zero = VectorT(T(0), T(0));

	template <typename T>
	class VectorT<T, 3>
	{
	public:
		static constexpr uint32 Dimension = 3;

		static VectorT const Zero;

		T x = T(0);
		T y = T(0);
		T z = T(0);

	public:

		constexpr VectorT() noexcept = default;

		constexpr VectorT(T const& x, T const& y, T const& z) noexcept
			: x(x), y(y), z(z) {}
		constexpr VectorT(VectorT<T, 2> const& xy, T const& z) noexcept
			: x(xy.x), y(xy.y), z(z) {}
		constexpr VectorT(T const& x, VectorT<T, 2> const& yz) noexcept
			: x(x), y(yz.x), z(yz.y) {}

		VectorT(VectorT const& r) noexcept
			: x(r.x), y(r.y), z(r.z) {}

		template <typename U>
		constexpr explicit VectorT(VectorT<U, Dimension> const& r) noexcept
			: x(static_cast<T>(r.x)), y(static_cast<T>(r.y)), z(static_cast<T>(r.z)) {}

		constexpr VectorT& operator=(VectorT const& r) noexcept
		{
			x = r.x;
			y = r.y;
			z = r.z;
			return *this;
		}
		template <typename U>
		constexpr VectorT& operator=(VectorT<U, Dimension> const& r) noexcept
		{
			x = static_cast<T>(r.x);
			y = static_cast<T>(r.y);
			z = static_cast<T>(r.z);
			return *this;
		}

		constexpr T const& operator[](uint32 index) const noexcept
		{
			assert(index < Dimension);
			switch (index) // to make this function usable in constexpr
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			}
		}

		friend constexpr VectorT operator+(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x + r.x, l.y + r.y, l.z + r.z);
		}

		friend constexpr VectorT operator-(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x - r.x, l.y - r.y, l.z - r.z);
		}

		friend constexpr VectorT operator*(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x * r.x, l.y * r.y, l.z * r.z);
		}

		friend constexpr VectorT operator*(VectorT const& l, T const& r) noexcept
		{
			return VectorT(l.x * r, l.y * r, l.z * r);

		}
		friend constexpr VectorT operator*(T const& l, VectorT const& r) noexcept
		{
			return VectorT(l * r.x, l * r.y, l * r.z);
		}

		friend constexpr VectorT operator/(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x / r.x, l.y / r.y, l.z / r.z);
		}

		friend constexpr VectorT operator/(VectorT const& l, T const& r) noexcept
		{
			return VectorT(l.x / r, l.y / r, l.z / r);
		}

		constexpr VectorT const& operator+() const noexcept
		{
			return *this;
		}
		constexpr VectorT operator-() const noexcept
		{
			return VectorT(-x, -y, -z);
		}

		friend constexpr bool operator==(VectorT const& l, VectorT const& r) noexcept
		{
			return l.x == r.x && l.y == r.y && l.z == r.z;
		}

		friend constexpr bool operator!=(VectorT const& l, VectorT const& r) noexcept
		{
			return l.x != r.x || l.y != r.y || l.z != r.z;
		}

		constexpr VectorT Normalized() const noexcept
		{
			static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only.");
			return *this / Length();
		}

		constexpr T Length() const noexcept
		{
			static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only.");
			return std::sqrt(LengthSquared());
		}

		constexpr T LengthSquared() const noexcept
		{
			return Dot(*this, *this);
		}

		friend constexpr T Dot(VectorT const& l, VectorT const& r) noexcept
		{
			return l.x * r.x + l.y * r.y + l.z * r.z;
		}

		constexpr T const* GetArray() const noexcept
		{
			return &x;
		}
	};

	template <typename T>
	VectorT<T, 3> const VectorT<T, 3>::Zero = VectorT(T(0), T(0), T(0));

	template <typename T>
	VectorT<T, 3> Cross(VectorT<T, 3> const& l, VectorT<T, 3> const& r)
	{
		return VectorT<T, 3>(
			l.y * r.z - l.z * r.y,
			l.z * r.x - l.x * r.z,
			l.x * r.y - l.y * r.x);
	}

	template <typename T>
	class VectorT<T, 4>
	{
	public:
		static constexpr uint32 Dimension = 4;

		static VectorT const Zero;

		T x = T(0);
		T y = T(0);
		T z = T(0);
		T w = T(0);

	public:

		constexpr VectorT() noexcept = default;

		constexpr VectorT(T const& x, T const& y, T const& z, T const& w) noexcept
			: x(x), y(y), z(z), w(w) {}
		constexpr VectorT(VectorT<T, 2> const& xy, T const& z, T const& w) noexcept
			: x(xy.x), y(xy.y), z(z), w(w) {}
		constexpr VectorT(T const& x, VectorT<T, 2> const& yz, T const& w) noexcept
			: x(x), y(yz.x), z(yz.y), w(w) {}
		constexpr VectorT(T const& x, T const& y, VectorT<T, 2> const& zw) noexcept
			: x(x), y(y), z(zw.x), w(zw.y) {}
		constexpr VectorT(VectorT<T, 2> const& xy, VectorT<T, 2> const& zw) noexcept
			: x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}
		constexpr VectorT(VectorT<T, 3> const& xyz, T const& w) noexcept
			: x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
		constexpr VectorT(T const& x, VectorT<T, 3> const& yzw) noexcept
			: x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}

		VectorT(VectorT const& r) noexcept
			: x(r.x), y(r.y), z(r.z), w(r.w) {}

		template <typename U>
		constexpr explicit VectorT(VectorT<U, Dimension> const& r) noexcept
			: x(static_cast<T>(r.x)), y(static_cast<T>(r.y)), z(static_cast<T>(r.z)), w(static_cast<T>(r.w)) {}

		constexpr VectorT& operator=(VectorT const& r) noexcept
		{
			x = r.x;
			y = r.y;
			z = r.z;
			w = r.w;
			return *this;
		}
		template <typename U>
		constexpr VectorT& operator=(VectorT<U, Dimension> const& r) noexcept
		{
			x = static_cast<T>(r.x);
			y = static_cast<T>(r.y);
			z = static_cast<T>(r.z);
			w = static_cast<T>(r.w);
			return *this;
		}

		constexpr T const& operator[](uint32 index) const noexcept
		{
			assert(index < Dimension);
			switch (index) // to make this function usable in constexpr
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			}
		}

		friend constexpr VectorT operator+(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
		}

		friend constexpr VectorT operator-(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
		}

		friend constexpr VectorT operator*(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
		}

		friend constexpr VectorT operator*(VectorT const& l, T const& r) noexcept
		{
			return VectorT(l.x * r, l.y * r, l.z * r, l.w * r);

		}
		friend constexpr VectorT operator*(T const& l, VectorT const& r) noexcept
		{
			return VectorT(l * r.x, l * r.y, l * r.z, l * r.w);
		}

		friend constexpr VectorT operator/(VectorT const& l, VectorT const& r) noexcept
		{
			return VectorT(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
		}

		friend constexpr VectorT operator/(VectorT const& l, T const& r) noexcept
		{
			return VectorT(l.x / r, l.y / r, l.z / r, l.w / r);
		}

		constexpr VectorT const& operator+() const noexcept
		{
			return *this;
		}
		constexpr VectorT operator-() const noexcept
		{
			return VectorT(-x, -y, -z, -w);
		}

		friend constexpr bool operator==(VectorT const& l, VectorT const& r) noexcept
		{
			return l.x == r.x && l.y == r.y && l.z == r.z&& l.w == r.w;
		}

		friend constexpr bool operator!=(VectorT const& l, VectorT const& r) noexcept
		{
			return l.x != r.x || l.y != r.y || l.z != r.z || l.w != r.w;
		}

		constexpr VectorT Normalized() const noexcept
		{
			static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only.");
			return *this / Length();
		}

		constexpr T Length() const noexcept
		{
			static_assert(std::is_floating_point_v<T>, "Normalized() for floating point types only.");
			return std::sqrt(LengthSquared());
		}

		constexpr T LengthSquared() const noexcept
		{
			return Dot(*this, *this);
		}

		friend constexpr T Dot(VectorT const& l, VectorT const& r) noexcept
		{
			return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
		}

		constexpr T const* GetArray() const noexcept
		{
			return &x;
		}
	};

	template <typename T>
	VectorT<T, 4> const VectorT<T, 4>::Zero = VectorT(T(0), T(0), T(0), T(0));


	using f32V1 = VectorT<float32, 1>;
	using f32V2 = VectorT<float32, 2>;
	using f32V3 = VectorT<float32, 3>;
	using f32V4 = VectorT<float32, 4>;

	using f64V1 = VectorT<float64, 1>;
	using f64V2 = VectorT<float64, 2>;
	using f64V3 = VectorT<float64, 3>;
	using f64V4 = VectorT<float64, 4>;

	using s32V1 = VectorT<sint32, 1>;
	using s32V2 = VectorT<sint32, 2>;
	using s32V3 = VectorT<sint32, 3>;
	using s32V4 = VectorT<sint32, 4>;

	using u32V1 = VectorT<uint32, 1>;
	using u32V2 = VectorT<uint32, 2>;
	using u32V3 = VectorT<uint32, 3>;
	using u32V4 = VectorT<uint32, 4>;

}
