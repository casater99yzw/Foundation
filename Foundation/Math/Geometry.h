#pragma once

#include "Core/BasicType.h"
#include "Math/Vector.h"

// TODO
namespace X
{

	template <typename T>
	class RayT
	{
		template <typename U>
		friend class RayT;

	public:
		typedef T ValueType;

		typedef ValueType* Pointer;
		typedef ValueType const* ConstPointer;

		typedef ValueType& Reference;
		typedef ValueType const& ConstReference;

	public:
		RayT(VectorT<T, 3> const& origin, VectorT<T, 3> const& direction)
			: origin_(origin), direction_(direction.Normalize())
		{
			auto& zero = VectorT<T, 3>::Zero;
			assert(direction != zero);
		}
		RayT(RayT const& r)
			: origin_(r.origin_), direction_(r.direction_)
		{
		}
		template <typename U>
		RayT(RayT<U> const& r)
			: origin_(r.origin_), direction_(r.direction_)
		{
		}

		RayT& operator =(RayT const& r)
		{
			if (this != &r)
			{
				origin_ = r.origin_;
				direction_ = r.direction_;
			}
		}
		template <typename U>
		RayT& operator =(RayT<U> const& r)
		{
			if (this != &r)
			{
				origin_ = r.origin_;
				direction_ = r.direction_;
			}
		}

		VectorT<T, 3> const& GetOrigin() const
		{
			return origin_;
		}
		VectorT<T, 3> const& GetDirection() const
		{
			return direction_;
		}
		VectorT<T, 3> const& GetPoint(T const& t) const
		{
			return origin_ + t * direction_;
		}
	private:
		VectorT<T, 3> origin_;
		VectorT<T, 3> direction_;
	};
	typedef RayT<float32> Ray;


	template <typename T>
	class SegmentT
	{
	public:
		SegmentT();

	private:

	};

	/*
	 *	Plane: Ax + By + Cz + D, represented as normal * p + distance, where p is a point on the plane.
	 */
	template <typename T>
	class PlaneT
	{
		template <typename U>
		friend class PlaneT;

	public:
		typedef T ValueType;

		typedef ValueType* Pointer;
		typedef ValueType const* ConstPointer;

		typedef ValueType& Reference;
		typedef ValueType const& ConstReference;

	public:
		PlaneT(VectorT<T, 3> const& normal, T const& distance)
			: normal_(normal), distance_(distance)
		{
		}

		PlaneT(PlaneT const& r)
			: normal_(r.normal_), distance_(r.distance_)
		{
		}
		template <typename U>
		PlaneT(PlaneT<U> const& r)
			: normal_(r.normal_), distance_(r.distance_)
		{
		}

		PlaneT& operator =(PlaneT const& r)
		{
			if (this != &r)
			{
				normal_ = r.normal_;
				distance_ = r.distance_;
			}
		}
		template <typename U>
		PlaneT& operator =(PlaneT<U> const& r)
		{
			if (this != &r)
			{
				normal_ = r.normal_;
				distance_ = r.distance_;
			}
		}

		VectorT<T, 3> const& GetNormal() const
		{
			return normal_;
		}
		T const& GetDistance() const
		{
			return distance_;
		}

	private:
		VectorT<T, 3> normal_;
		T distance_;
	};
	typedef PlaneT<float32> Plane;

	template <typename T>
	class FrustumT
	{
	public:
		FrustumT();

	private:

	};

}
