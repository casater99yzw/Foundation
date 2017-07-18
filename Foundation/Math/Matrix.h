/*
*	Code partially come from KlayGE, with some simplification and improvement.
*/
#pragma once

#include "Core/BasicType.h"
#include "Math/MathHelper.h"
#include "Math/Vector.h"


#include <array>

namespace X
{

	/*
	 *	Column major matrix.
	 *	Stored as [column][row].
	 */
// 	template <class T>
// 	class Matrix4T
// 	{
// 		template <class U>
// 		template<class T, uint32 R, uint32 C>class Matrix4T;
// 
// 	public:
// 		static uint32 const Dimension = 4;
// 		static uint32 const ElementCount = Dimension * Dimension;
// 
// 	public:
// 		static Matrix4T const Zero;
// 		static Matrix4T const Identity;
// 
// 	public:
// 		/*
// 		 *	Create an uninitialized Matrix.
// 		 */
// 		Matrix4T()
// 		{
// 		}
// 		/*
// 		 *	Create a scalar equivalent matrix, fill principal diagonal with r.
// 		 */
// 		explicit Matrix4T(T const& r)
// 		{
// 			T* temp = GetFirstElementNonConstPointer(*this);
// 			temp[0] = r;
// 			temp[1] = 0;
// 			temp[2] = 0;
// 			temp[3] = 0;
// 
// 			temp[4] = 0;
// 			temp[5] = r;
// 			temp[6] = 0;
// 			temp[7] = 0;
// 
// 			temp[8] = 0;
// 			temp[9] = 0;
// 			temp[10] = r;
// 			temp[11] = 0;
// 
// 			temp[12] = 0;
// 			temp[13] = 0;
// 			temp[14] = 0;
// 			temp[15] = r;
// 		}
// 		/*
// 		 *	@r: column major array.
// 		 */
// 		explicit Matrix4T(T const* r)
// 		{
// 			for (uint32 i = 0; i < Dimension; ++i)
// 			{
// 				vectors_[i] = VectorT<T, Dimension>(r);
// 				r += Dimension;
// 			}
// 		}
// 		/*
// 		 *	@r: column major array.
// 		 */
// 		explicit Matrix4T(std::array<T, ElementCount> const& r) // TODO need test
// 		{
// 			for (uint32 i = 0; i < Dimension; ++i)
// 			{
// 				vectors_[i] = VectorT<T, Dimension>(&r[i * Dimension]);
// 			}
// 		}
// 		/*
// 		 *	@r: column major vectors.
// 		 */
// 		explicit Matrix4T(VectorT<VectorT<T, Dimension>, Dimension> const& r)
// 			: vectors_(r)
// 		{
// 		}
// 		Matrix4T(Matrix4T const& r)
// 			: vectors_(r.vectors_)
// 		{
// 		}
// 		template <class U>
// 		Matrix4T(Matrix4T<U> const& r)
// 			: vectors_(r.vectors_)
// 		{
// 		}
// 		/*
// 		 *	parameters subscript: row, column
// 		 */
// 		Matrix4T(T const& m11, T const& m21, T const& m31, T const& m41,
// 			T const& m12, T const& m22, T const& m32, T const& m42,
// 			T const& m13, T const& m23, T const& m33, T const& m43,
// 			T const& m14, T const& m24, T const& m34, T const& m44)
// 		{
// 
// 			T* temp = GetFirstElementNonConstPointer(*this);
// 			temp[0] = m11;
// 			temp[1] = m21;
// 			temp[2] = m31;
// 			temp[3] = m41;
// 
// 			temp[4] = m12;
// 			temp[5] = m22;
// 			temp[6] = m32;
// 			temp[7] = m42;
// 
// 			temp[8] = m13;
// 			temp[9] = m23;
// 			temp[10] = m33;
// 			temp[11] = m43;
// 
// 			temp[12] = m14;
// 			temp[13] = m24;
// 			temp[14] = m34;
// 			temp[15] = m44;
// 		}
// 
// 
// 		T const& operator ()(uint32 row, uint32 column) const
// 		{
// 			return vectors_[column][row];
// 		}
// 
// 		/*
// 		 *	@index: column major index.
// 		 */
// 		T const& operator [](uint32 index) const
// 		{
// 			return *(&vectors_[0][0] + index);
// 		}
// 
// 
// 		VectorT<T, Dimension> const Row(uint32 index) const
// 		{
// 			VectorT<T, Dimension> result;
// 			for (uint32 i = 0; i < Dimension; ++ i)
// 			{
// 				result.values_[i] = vectors_[i][index];
// 			}
// 			return result;
// 		}
// 		VectorT<T, Dimension> const& Column(uint32 index) const
// 		{
// 			return vectors_[index];
// 		}
// 
// 		template<class T, uint32 R, uint32 C>Matrix4T operator +(Matrix4T const& l, Matrix4T const& r)
// 		{
// 			return Matrix4T(l.vectors_ + r.vectors_);
// 		}
// 		template<class T, uint32 R, uint32 C>Matrix4T operator -(Matrix4T const& l, Matrix4T const& r)
// 		{
// 			return Matrix4T(l.vectors_ - r.vectors_);
// 		}
// 
// 		template<class T, uint32 R, uint32 C>Matrix4T operator *(Matrix4T const& l, Matrix4T const& r)
// 		{
// 			Matrix4T temp;
// 			MathHelper::MatrixHepler<T>::DoMultiply(Matrix4T::GetFirstElementNonConstPointer(temp), Matrix4T::GetFirstElementNonConstPointer(l), Matrix4T::GetFirstElementNonConstPointer(r));
// 			return temp;
// 		}
// 		template<class T, uint32 R, uint32 C>Matrix4T operator *(Matrix4T const& l, T const& r)
// 		{
// 			return Matrix4T(l.vectors_ * VectorT<T, Dimension>(r));
// 		}
// 		template<class T, uint32 R, uint32 C>Matrix4T operator *(T const& l, Matrix4T const& r)
// 		{
// 			return Matrix4T(VectorT<T, Dimension>(l) * r.vectors_);
// 		}
// 
// 		template<class T, uint32 R, uint32 C>Matrix4T operator /(Matrix4T const& l, T const& r)
// 		{
// 			return Matrix4T(l.vectors_ / VectorT<T, Dimension>(r));
// 		}
// 
// 		Matrix4T& operator =(Matrix4T const& r)
// 		{
// 			if (this != &r)
// 			{
// 				vectors_ = r.vectors_;
// 			}
// 			return *this;
// 		}
// 		template <class U>
// 		Matrix4T const& operator =(Matrix4T<U> const& r)
// 		{
// 			if (this != &r)
// 			{
// 				vectors_ = r.vectors_;
// 			}
// 			return *this;
// 		}
// 
// 		Matrix4T const& operator +() const
// 		{
// 			return *this;
// 		}
// 		Matrix4T operator -() const
// 		{
// 			Matrix4T temp(*this);
// 			temp.vectors_ = -vectors_;
// 			return temp;
// 		}
// 
// 		template<class T, uint32 R, uint32 C>bool operator ==(Matrix4T const& l, Matrix4T const& r)
// 		{
// 			return l.vectors_ == r.vectors_;
// 		}
// 		template<class T, uint32 R, uint32 C>bool operator !=(Matrix4T const& l, Matrix4T const& r)
// 		{
// 			return l.vectors_ != r.vectors_;
// 		}
// 
// 		Matrix4T Transpose() const
// 		{
// 			return Matrix4T(operator [](0), operator [](4), operator [](8), operator [](12),
// 				operator [](1), operator [](5), operator [](9),operator [](13),
// 				operator [](2), operator [](6), operator [](10), operator [](14),
// 				operator [](3), operator [](7), operator [](11), operator [](15));
// 		}
// 
// 		Matrix4T Inverse() const
// 		{
// 			Matrix4T temp;
// 			bool invertible = MathHelper::MatrixHepler<T>::DoInverse(GetFirstElementNonConstPointer(temp), GetFirstElementNonConstPointer(*this));
// 			assert(invertible);
// 			return temp;
// 		}
// 
// 		T Determinant() const
// 		{
// 			return MathHelper::MatrixHepler<T>::CalculateDeterminant(&vectors_[0][0]);
// 		}
// 
// 		T const* GetData() const
// 		{
// 			return &vectors_[0][0];
// 		}
// 	
// 	private:
// // 		static Pointer GetFirstElementNonConstPointer(Matrix4T const& result)
// // 		{
// // 			return const_cast<Pointer>(&result.vectors_[0][0]);
// // 		}
// 
// 	private:
// 		VectorT<VectorT<T, Dimension>, Dimension> vectors_;
// 	};


	template <class T, uint32 R, uint32 C>
	class MatrixT;

	template <class T>
	class MatrixT<T, 4, 4>
	{

	public:
		static constexpr uint32 Row = 4;
		static constexpr uint32 Column = 4;
		static constexpr uint32 Count = Row * Column;

		static MatrixT const Zero;
		static MatrixT const Identity;

		union
		{
			struct
			{
				T	_00, _10, _20, _30,
					_01, _11, _21, _31,
					_02, _12, _22, _32,
					_03, _13, _23, _34;
			};
			VectorT<VectorT<T, Column>, Row> v;
		};


		constexpr MatrixT() noexcept = default;
		/*
		*	Create a scalar equivalent matrix, fill principal diagonal with r.
		*/
		explicit constexpr MatrixT(T const& r) noexcept : v({ r, 0, 0, 0 }, { 0, r, 0, 0 }, { 0, 0, r, 0 }, { 0, 0, 0, r }) {}

		/*
		*	parameters subscript: row, column
		*/
		constexpr MatrixT(T const& m00, T const& m10, T const& m20, T const& m30,
			T const& m01, T const& m11, T const& m21, T const& m31,
			T const& m02, T const& m12, T const& m22, T const& m32,
			T const& m03, T const& m13, T const& m23, T const& m33) noexcept
			: v({ m00, m10, m20, m30 }, { m01, m11, m21, m31 }, { m02, m12, m22, m32 }, { m03, m13, m23, m33 }) {}

		constexpr MatrixT(VectorT<T, Column> const& r0, VectorT<T, Column> const& r1, VectorT<T, Column> const& r2, VectorT<T, Column> const& r3) noexcept : v(r0, r1, r2, r3) {}
		constexpr MatrixT(VectorT<VectorT<T, Column>, Row> const& rows) noexcept : v(rows) {}


		constexpr MatrixT(MatrixT const& r) noexcept : v(r.v) {}
		template <class U>
		MatrixT(MatrixT<U, Row, Column> const& r) : v(r.v) {}



		constexpr T const& operator()(uint32 row, uint32 column) const noexcept { return v[column][row]; }

		constexpr VectorT<T, Column> const& operator[](uint32 index) const { return v[index]; }
		constexpr VectorT<T, Column>& operator[](uint32 index) { return v[index]; }


		constexpr VectorT<T, Column> const Row(uint32 index) const noexcept { return VectorT<T, Column> result(v[0][index], v[1][index], v[2][index], v[3][index]); }
		constexpr VectorT<T, Row> const& Column(uint32 index) const noexcept { return v[index]; }

		constexpr MatrixT& operator=(MatrixT const& r) noexcept { v = r.v; return *this; }
		template <class U>
		constexpr MatrixT const& operator=(MatrixT<U, Row, Column> const& r) noexcept { v = r.v; return *this; }

		constexpr MatrixT const& operator+() const noexcept { return *this; }
		constexpr MatrixT operator-() const noexcept { return MatrixT(-v); }

		MatrixT Transpose() const
		{
			return MatrixT(
				v[0][0], v[0][1], v[0][2], v[0][3],
				v[1][0], v[1][1], v[1][2], v[1][3],
				v[2][0], v[2][1], v[2][2], v[2][3],
				v[3][0], v[3][1], v[3][2], v[3][3]);
		}

		MatrixT Inverse() const
		{
			MatrixT temp;
			bool invertible = MathHelper::Matrix44Hepler<T>::DoInverse(GetFirstElementNonConstPointer(temp), GetFirstElementNonConstPointer(*this));
			assert(invertible);
			return temp;
		}

		T Determinant() const
		{
			return MathHelper::Matrix44Hepler<T>::CalculateDeterminant(&v[0][0]);
		}

		constexpr T const* GetData() const
		{
			return v.GetData()->GetData();
		}

	};

	
	template<class T, uint32 R, uint32 C>
	MatrixT<T, R, C> operator+(MatrixT<T, R, C> const& l, MatrixT<T, R, C> const& r)
	{
		return MatrixT<T, R, C>(l.v + r.v);
	}
	template<class T, uint32 R, uint32 C>
	MatrixT<T, R, C> operator-(MatrixT<T, R, C> const& l, MatrixT<T, R, C> const& r)
	{
		return MatrixT<T, R, C>(l.v - r.v);
	}

	template<class T, uint32 R, uint32 C>
	MatrixT<T, R, C> operator*(MatrixT<T, R, C> const& l, MatrixT<T, R, C> const& r)
	{
		MatrixT<T, R, C> temp;
		MathHelper::Matrix44Hepler<T>::DoMultiply(MatrixT<T, R, C>::GetFirstElementNonConstPointer(temp), MatrixT<T, R, C>::GetFirstElementNonConstPointer(l), MatrixT<T, R, C>::GetFirstElementNonConstPointer(r));
		return temp;
	}
	template<class T, uint32 R, uint32 C>
	MatrixT<T, R, C> operator*(MatrixT<T, R, C> const& l, T const& r)
	{
		return MatrixT<T, R, C>(l.v * VectorT<T, Dimension>(r));
	}
	template<class T, uint32 R, uint32 C>
	MatrixT<T, R, C> operator*(T const& l, MatrixT<T, R, C> const& r)
	{
		return MatrixT<T, R, C>(VectorT<T, Dimension>(l) * r.v);
	}

	template<class T, uint32 R, uint32 C>
	MatrixT<T, R, C> operator/(MatrixT<T, R, C> const& l, T const& r)
	{
		return MatrixT<T, R, C>(l.v / VectorT<T, Dimension>(r));
	}

	template<class T, uint32 R, uint32 C>
	bool operator==(MatrixT<T, R, C> const& l, MatrixT<T, R, C> const& r)
	{
		return l.v == r.v;
	}
	template<class T, uint32 R, uint32 C>
	bool operator!=(MatrixT<T, R, C> const& l, MatrixT<T, R, C> const& r)
	{
		return l.v != r.v;
	}



// 	template <class T>
// 	Matrix4T<T> const Matrix4T<T>::Zero = Matrix4T(T(0));
// 
// 	template <class T>
// 	Matrix4T<T> const Matrix4T<T>::Identity = Matrix4T(T(1));

	using M33F32 = MatrixT<float32, 3, 3>;
	using M33F64 = MatrixT<float64, 3, 3>;
	using M44F32 = MatrixT<float32, 4, 4>;
	using M44F64 = MatrixT<float64, 4, 4>;

}
