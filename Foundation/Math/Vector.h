#pragma once
#include "Core/BasicType.h"
#include "Math/MathHelper.h"

#include <array>


namespace X
{

	/*
	 *	Immutable type.
	 */
	template <typename T, uint32 N>
	class VectorT
	{
		static_assert(N >= 1 && N <= 4, "");

		template <typename U, uint32 M>
		friend class VectorT;

		// Matrix knows the storage details
		template <typename T>
		friend class Matrix4;

	public:
		static constexpr uint32 Dimension = N;

	public:
		static VectorT const Zero;

	public:
		/*
		 *	Create an uninitialized VectorT.
		 */
		constexpr VectorT() = default;

		constexpr explicit VectorT(T const* r)
		{
			MathHelper::VectorHelper<T, N>::DoCopy(&values[0], r);
		}
		VectorT(VectorT const& r)
			: values(r.values)
		{
		}
	private:
		struct SmallerSizeTag
		{
		};
		struct LargerSizeTag
		{
		};
		template <typename U, uint32 M>
		constexpr void DoConstructFromOtherSizedVector(VectorT<U, M> const& r, SmallerSizeTag)
		{
			MathHelper::VectorHelper<T, M>::DoCopy(&values[0], &r[0]);
			MathHelper::VectorHelper<T, N - M>::DoAssign(&values[M], 0); // fill rest with 0
		}
		template <typename U, uint32 M>
		constexpr void DoConstructFromOtherSizedVector(VectorT<U, M> const& r, LargerSizeTag)
		{
			MathHelper::VectorHelper<T, N>::DoCopy(&values[0], &r[0]);
		}
	public:
		template <typename U, uint32 M>
		constexpr explicit VectorT(VectorT<U, M> const& r)
		{
			DoConstructFromOtherSizedVector(r, std::conditional<M >= N, LargerSizeTag, SmallerSizeTag>::type());
		}
		constexpr explicit VectorT(T const& r)
		{
			MathHelper::VectorHelper<T, N>::DoAssign(&values[0], r);
		}
		constexpr VectorT(T const& x, T const& y)
		{
			static_assert(Dimension == 2, "Dimension 2 only");

			values[0] = x;
			values[1] = y;
		}
		constexpr VectorT(T const& x, T const& y, T const& z)
		{
			static_assert(Dimension == 3, "Dimension 3 only");

			values[0] = x;
			values[1] = y;
			values[2] = z;
		}
		constexpr VectorT(T const& x, T const& y, T const& z, T const& w)
		{
			static_assert(Dimension == 4, "Dimension 4 only");

			values[0] = x;
			values[1] = y;
			values[2] = z;
			values[3] = w;
		}
		constexpr VectorT& operator=(VectorT const& r)
		{
			if (this != &r)
			{
				values = r.values;
			}
			return *this;
		}
		template <typename U, uint32 M>
		constexpr VectorT& operator=(VectorT<U, M> const& r)
		{
			DoConstructFromOtherSizedVector(r, std::conditional<M >= N, LargerSizeTag, SmallerSizeTag>::type());
			return *this;
		}


		constexpr T const& operator[](uint32 index) const
		{
			assert(index < Dimension);
			return values[index];
		}

		constexpr T const& X() const
		{
			static_assert(Dimension >= 1, "");
			return values[0];
		}

		constexpr T const& Y() const
		{
			static_assert(Dimension >= 2, "");
			return values[1];
		}

		constexpr T const& Z() const
		{
			static_assert(Dimension >= 3, "");
			return values[2];
		}

		constexpr T const& W() const
		{
			static_assert(Dimension >= 4, "");
			return values[3];
		}


		friend constexpr VectorT operator+(VectorT const& l, VectorT const& r)
		{
			VectorT temp;
			MathHelper::VectorHelper<T, N>::DoAdd(&temp.values[0], &l.values[0], &r.values[0]);
			return temp;
		}

		friend constexpr VectorT operator-(VectorT const& l, VectorT const& r)
		{
			VectorT temp;
			MathHelper::VectorHelper<T, N>::DoSubtract(&temp.values[0], &l.values[0], &r.values[0]);
			return temp;
		}

		friend constexpr VectorT operator*(VectorT const& l, VectorT const& r)
		{
			VectorT temp;
			MathHelper::VectorHelper<T, N>::DoMultiply(&temp.values[0], &l.values[0], &r.values[0]);
			return temp;
		}

		friend constexpr VectorT operator*(VectorT const& l, T const& r)
		{
			VectorT temp;
			MathHelper::VectorHelper<T, N>::DoScale(&temp.values[0], &l.values[0], r);
			return temp;
		}
		friend constexpr VectorT operator*(T const& l, VectorT const& r)
		{
			VectorT temp;
			MathHelper::VectorHelper<T, N>::DoScale(&temp.values[0], &r.values[0], l);
			return temp;
		}

		friend constexpr VectorT operator/(VectorT const& l, VectorT const& r)
		{
			VectorT temp;
			MathHelper::VectorHelper<T, N>::DoDivide(&temp.values[0], &l.values[0], &r.values[0]);
			return temp;
		}

		friend constexpr VectorT operator/(VectorT const& l, T const& r)
		{
			VectorT temp;
			MathHelper::VectorHelper<T, N>::DoScale(&temp.values[0], &l.values[0], T(1) / r);
			return temp;
		}

		constexpr VectorT const& operator+() const
		{
			return *this; 
		}
		constexpr VectorT operator-() const
		{
			VectorT temp;
			MathHelper::VectorHelper<T, N>::DoNegate(&temp.values[0], &values[0]);
			return temp;
		}

		friend constexpr bool operator==(VectorT const& l, VectorT const& r)
		{
			return l.values == r.values;
			//return MathHelper::VectorHelper<T, N>::DoEqual(&l[0], &r[0]);
		}

		friend constexpr bool	operator!=(VectorT const& l, VectorT const& r)
		{
			return l.values != r.values;
		}

		constexpr VectorT Normalize() const // float32 & float64 only
		{
			return *this * ReciprocalSqrt(LengthSquared());
		}

		constexpr T Length() const // float32 & float64 only
		{
			// return T(1) / ReciprocalSqrt(LengthSquared());
			return std::sqrt(LengthSquared());
		}

		constexpr T LengthSquared() const
		{
			return Dot(*this, *this);
		}

		friend constexpr T Dot(VectorT const& l, VectorT const& r)
		{
			return MathHelper::VectorHelper<T, N>::DoDot(&l.values[0], &r.values[0]);
		}

		constexpr T const* GetArray() const
		{
			return &values[0];
		}

		T values[N] = {};
	};


	template <typename T, uint32 N>
	VectorT<T, N> const VectorT<T, N>::Zero = VectorT(T(0));



	template <typename T>
	VectorT<T, 3> Cross(VectorT<T, 3> const& l, VectorT<T, 3> const& r)
	{
		return VectorT<T, 3>(
			l.Y() * r.Z() - l.Z() * r.Y(),
			l.Z() * r.X() - l.X() * r.Z(),
			l.X() * r.Y() - l.Y() * r.X());
	}


	typedef VectorT<float32, 1> f32V1;
	typedef VectorT<float32, 2> f32V2;
	typedef VectorT<float32, 3> f32V3;
	typedef VectorT<float32, 4> f32V4;

	typedef VectorT<float64, 1> f64V1;
	typedef VectorT<float64, 2> f64V2;
	typedef VectorT<float64, 3> f64V3;
	typedef VectorT<float64, 4> f64V4;

	typedef VectorT<sint32, 1> s32V1;
	typedef VectorT<sint32, 2> s32V2;
	typedef VectorT<sint32, 3> s32V3;
	typedef VectorT<sint32, 4> s32V4;

	typedef VectorT<uint32, 1> u32V1;
	typedef VectorT<uint32, 2> u32V2;
	typedef VectorT<uint32, 3> u32V3;
	typedef VectorT<uint32, 4> u32V4;

}
