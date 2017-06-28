#pragma once

#include "Math/Math.h"
#include "Vector.h"
#include "MathHelper.h"

namespace X
{

	/*
	 *	Immutable type.
	 */
	template <typename T>
	class QuaternionT
	{
		template <typename U>
		friend class QuaternionT;

	public:
		static uint32 const Dimension = 4;


	public:
		/*
		 *	Used for making error intentionally.
		 */
		static QuaternionT const Zero;
		static QuaternionT const Identity;
	public:

		/*
		 *	Create an uninitialized QuaternionT.
		 */
		QuaternionT()
		{
		}
		QuaternionT(QuaternionT const& r)
			: values_(r.values_)
		{
		}
		template <typename U>
		explicit QuaternionT(QuaternionT<U> const& r)
			: values_(r.values_)
		{
		}
		explicit QuaternionT(VectorT<T, 4> const& r)
			: values_(r)
		{
		}
		QuaternionT(VectorT<T, 3> const& axis, T const& w)
			: values_(axis.X(), axis.Y(), axis.Z(), w)
		{
		}
		QuaternionT(T const& x, T const& y, T const& z, T const& w)
			: values_(x, y, z, w)
		{
		}

		QuaternionT& operator =(QuaternionT const& r)
		{
			if (this != &r)
			{
				values_ = r.values_;
			}
			return *this;
		}
		template <typename U>
		QuaternionT& operator =(QuaternionT<U> const& r)
		{
			values_ = r.values_;
			return *this;
		}

		/*
		 *	Rotation component is at index 3.
		 */
		T const& operator [](uint32 index) const
		{
			return values_[index];
		}

		T const& X() const
		{
			return values_.X();
		}

		T const& Y() const
		{
			return values_.Y();
		}

		T const& Z() const
		{
			return values_.Z();
		}

		T const& W() const
		{
			return values_.W();
		}

		VectorT<T, 3> const& V() const
		{
			// check offsets equality
			assert(&(reinterpret_cast<VectorT<T, 4>*>(nullptr)->X()) == &(reinterpret_cast<VectorT<T, 4>*>(nullptr)->operator [](0)));
			assert(&(reinterpret_cast<VectorT<T, 4>*>(nullptr)->Z()) == &(reinterpret_cast<VectorT<T, 4>*>(nullptr)->operator [](2)));
			// evil hack, first three component are the axis.
			return *reinterpret_cast<VectorT<T, 3> const*>(&values_);
		}

		friend QuaternionT operator +(QuaternionT const& l, QuaternionT const& r)
		{
			return QuaternionT(l.values_ + r.values_);
		}

		friend QuaternionT operator -(QuaternionT const& l, QuaternionT const& r)
		{
			return QuaternionT(l.values_ - r.values_);

		}

		friend QuaternionT operator *(QuaternionT const& l, QuaternionT const& r)
		{
			// see Mathematics for 3D Game Programming and Computer Graphics, 3rd. 4.6.1 Quaternions Mathematics
			return QuaternionT(
				l.W() * r.X() + l.X() * r.W() + l.Y() * r.Z() - l.Z() * r.Y(),
				l.W() * r.Y() + l.Y() * r.W() + l.Z() * r.X() - l.X() * r.Z(),
				l.W() * r.Z() + l.Z() * r.W() + l.X() * r.Y() - l.Y() * r.X(),
				l.W() * r.W() - l.X() * r.X() - l.Y() * r.Y() - l.Z() * r.Z());
		}

		friend QuaternionT operator *(QuaternionT const& l, T const& r)
		{
			return QuaternionT(l.values_ * r);
		}
		friend QuaternionT operator *(T const& l, QuaternionT const& r)
		{
			return QuaternionT(l * r.values_);
		}

		friend QuaternionT operator /(QuaternionT const& l, T const& r)
		{
			return QuaternionT(l.values_ / r);
		}

		QuaternionT const& operator +() const
		{
			return *this; 
		}
		QuaternionT operator -() const
		{
			return QuaternionT(-values_);
		}

		friend bool operator ==(QuaternionT const& l, QuaternionT const& r)
		{
			return l.values_ == r.values_;
		}

		friend bool	operator !=(QuaternionT const& l, QuaternionT const& r)
		{
			return l.values_ != r.values_;
		}

		QuaternionT Normalize() const
		{
			return QuaternionT(values_.Normalize());
		}

		QuaternionT Conjugate() const
		{
			return QuaternionT(-V(), values_.W());
		}

		QuaternionT Inverse() const
		{
			return QuaternionT(Conjugate() * (T(1) / LengthSquared()));
		}

		T Length() const
		{
			return values_.Length();
		}

		T LengthSquared() const
		{
			return values_.LengthSquared();
		}


	private:
		VectorT<T, Dimension> values_;
	};

	template <typename T>
	QuaternionT<T> const QuaternionT<T>::Zero = QuaternionT(VectorT<T, 3>(T(0)), T(0));

	template <typename T>
	QuaternionT<T> const QuaternionT<T>::Identity = QuaternionT(VectorT<T, 3>(T(0)), T(1));

	typedef QuaternionT<float32> floatQ;

}
