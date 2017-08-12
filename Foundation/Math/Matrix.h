/*
*	Code partially come from KlayGE, with some simplification and improvement.
*/
#pragma once

#include "Core/BasicType.h"
#include "Math/MathHelper.h"
#include "Math/BasicMath.h"
#include "Math/Vector.h"
#include "Math/Size.h"


#include <array>

namespace X
{


	// Column major matrix, column major storage.
	template <class T, uint32 R, uint32 C>
	class MatrixT;

	template <class T>
	class MatrixT<T, 3, 3>
	{

	public:
		static constexpr uint32 R = 3;
		static constexpr uint32 C = 3;
		static constexpr uint32 Count = R * C;

		static MatrixT const Zero;
		static MatrixT const Identity;

		union
		{
			struct
			{
				T	_00, _10, _20,
					_01, _11, _21,
					_02, _12, _22;
			};
			VectorT<VectorT<T, C>, R> v;
		};


		constexpr MatrixT() noexcept = default;
		/*
		*	Create a scalar equivalent matrix, fill principal diagonal with r.
		*/
		explicit constexpr MatrixT(T const& r) noexcept : v({ r, 0, 0 }, { 0, r, 0 }, { 0, 0, r }) {}

		/*
		*	parameters subscript: row, column
		*/
		constexpr MatrixT(
			T const& m00, T const& m10, T const& m20,
			T const& m01, T const& m11, T const& m21,
			T const& m02, T const& m12, T const& m22) noexcept
			: v({ m00, m10, m20 }, { m01, m11, m21 }, { m02, m12, m22 }) {}

		constexpr MatrixT(VectorT<T, C> const& c0, VectorT<T, C> const& c1, VectorT<T, C> const& c2) noexcept : v(c0, c1, c2) {}
		constexpr MatrixT(VectorT<VectorT<T, C>, R> const& rows) noexcept : v(rows) {}


		constexpr MatrixT(MatrixT const& r) noexcept : v(r.v) {}
		template <class U>
		MatrixT(MatrixT<U, R, C> const& r) : v(r.v) {}



		constexpr T const& operator[](Index2UI index) const noexcept { return v[index.Y()][index.X()]; }
		constexpr T& operator[](Index2UI index) noexcept { return v[index.Y()][index.X()]; }

		constexpr VectorT<T, C> const& operator[](uint32 index) const { return v[index]; }
		constexpr VectorT<T, C>& operator[](uint32 index) { return v[index]; }


		constexpr VectorT<T, C> const Row(uint32 index) const noexcept { return VectorT<T, C> result(v[0][index], v[1][index], v[2][index]); }
		constexpr VectorT<T, R> const& Column(uint32 index) const noexcept { return v[index]; }

		constexpr MatrixT& operator=(MatrixT const& r) noexcept { v = r.v; return *this; }
		template <class U>
		constexpr MatrixT const& operator=(MatrixT<U, R, C> const& r) noexcept { v = r.v; return *this; }

		constexpr MatrixT const& operator+() const noexcept { return *this; }
		constexpr MatrixT operator-() const noexcept { return MatrixT(-v); }

		constexpr MatrixT Transposed() const noexcept
		{
			return MatrixT(
				v[0][0], v[0][1], v[0][2], v[0][3],
				v[1][0], v[1][1], v[1][2], v[1][3],
				v[2][0], v[2][1], v[2][2], v[2][3],
				v[3][0], v[3][1], v[3][2], v[3][3]);
		}

		constexpr MatrixT Inversed() const noexcept
		{
			T	m11 = v[0][0], m21 = v[1][0], m31 = v[2][0],
				m12 = v[0][1], m22 = v[1][1], m32 = v[2][1],
				m13 = v[0][2], m23 = v[1][2], m33 = v[2][2];

			T	_2233 = m22 * m33,
				_2133 = m21 * m33,
				_2132 = m21 * m32,
				_2332 = m23 * m32,
				_2331 = m23 * m31,
				_2231 = m22 * m31;

			T	_2233_2332 = _2233 - _2332,
				_2133_2331 = _2133 - _2331,
				_2132_2231 = _2132 - _2231;

			T determinant = m11 * _2233_2332 - m12 * _2133_2331 + m13 * _2132_2231;

			// non-invertible
			if (BasicMath::CEqual<T>(determinant, 0))
			{
				assert(false);
				return MatrixT(T(1));
			}

			T inverseDeterminant = T(1) / determinant;

			return MatrixT(
				_2233_2332 * inverseDeterminant,
				-_2133_2331 * inverseDeterminant,
				_2132_2231 * inverseDeterminant,
				(m13 * m32 - m12 * m33) * inverseDeterminant,
				(m11 * m33 - m13 * m31) * inverseDeterminant,
				(m12 * m31 - m11 * m32) * inverseDeterminant,
				(m12 * m23 - m13 * m22) * inverseDeterminant,
				(m13 * m21 - m11 * m23) * inverseDeterminant,
				(m11 * m22 - m12 * m21) * inverseDeterminant);
		}

		constexpr T Determinant() const noexcept
		{
			T	m11 = v[0][0], m21 = v[1][0], m31 = v[2][0],
				m12 = v[0][1], m22 = v[1][1], m32 = v[2][1],
				m13 = v[0][2], m23 = v[1][2], m33 = v[2][2];

			T	_2233 = m22 * m33,
				_2133 = m21 * m33,
				_2132 = m21 * m32,
				_2332 = m23 * m32,
				_2331 = m23 * m31,
				_2231 = m22 * m31;

			T	_2233_2332 = _2233 - _2332,
				_2133_2331 = _2133 - _2331,
				_2132_2231 = _2132 - _2231;

			T determinant = m11 * _2233_2332 - m12 * _2133_2331 + m13 * _2132_2231;
			return determinant;
		}

		T const* Data() const noexcept
		{
			return v.Data()->Data();
		}
	};

	template <class T>
	MatrixT<T, 3, 3> const MatrixT<T, 3, 3>::Zero = MatrixT(T(0));

	template <class T>
	MatrixT<T, 3, 3> const MatrixT<T, 3, 3>::Identity = MatrixT(T(1));

	template<class T>
	constexpr MatrixT<T, 3, 3> operator*(MatrixT<T, 3, 3> const& l, MatrixT<T, 3, 3> const& r) noexcept
	{
		return MatrixT<T, 3, 3>(
			r[0][0] * l[0][0] + r[0][1] * l[1][0] + r[0][2] * l[2][0],
			r[0][0] * l[0][1] + r[0][1] * l[1][1] + r[0][2] * l[2][1],
			r[0][0] * l[0][2] + r[0][1] * l[1][2] + r[0][2] * l[2][2],
			r[1][0] * l[0][0] + r[1][1] * l[1][0] + r[1][2] * l[2][0],
			r[1][0] * l[0][1] + r[1][1] * l[1][1] + r[1][2] * l[2][1],
			r[1][0] * l[0][2] + r[1][1] * l[1][2] + r[1][2] * l[2][2],
			r[2][0] * l[0][0] + r[2][1] * l[1][0] + r[2][2] * l[2][0],
			r[2][0] * l[0][1] + r[2][1] * l[1][1] + r[2][2] * l[2][1],
			r[2][0] * l[0][2] + r[2][1] * l[1][2] + r[2][2] * l[2][2]);
	}

	template <class T>
	class MatrixT<T, 4, 4>
	{

	public:
		static constexpr uint32 R = 4;
		static constexpr uint32 C = 4;
		static constexpr uint32 Count = R * C;

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
			VectorT<VectorT<T, C>, R> v;
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

		constexpr MatrixT(VectorT<T, C> const& c0, VectorT<T, C> const& c1, VectorT<T, C> const& c2, VectorT<T, C> const& c3) noexcept : v(c0, c1, c2, c3) {}
		constexpr MatrixT(VectorT<VectorT<T, C>, R> const& rows) noexcept : v(rows) {}


		constexpr MatrixT(MatrixT const& r) noexcept : v(r.v) {}
		template <class U>
		MatrixT(MatrixT<U, R, C> const& r) : v(r.v) {}



		constexpr T const& operator[](Index2UI index) const noexcept { return v[index.Y()][index.X()]; }
		constexpr T& operator[](Index2UI index) noexcept { return v[index.Y()][index.X()]; }

		constexpr VectorT<T, C> const& operator[](uint32 index) const { return v[index]; }
		constexpr VectorT<T, C>& operator[](uint32 index) { return v[index]; }


		constexpr VectorT<T, C> const Row(uint32 index) const noexcept { return VectorT<T, C> result(v[0][index], v[1][index], v[2][index], v[3][index]); }
		constexpr VectorT<T, R> const& Column(uint32 index) const noexcept { return v[index]; }

		constexpr MatrixT& operator=(MatrixT const& r) noexcept { v = r.v; return *this; }
		template <class U>
		constexpr MatrixT const& operator=(MatrixT<U, R, C> const& r) noexcept { v = r.v; return *this; }

		constexpr MatrixT const& operator+() const noexcept { return *this; }
		constexpr MatrixT operator-() const noexcept { return MatrixT(-v); }

		constexpr MatrixT Transposed() const noexcept
		{
			return MatrixT(
				v[0][0], v[0][1], v[0][2], v[0][3],
				v[1][0], v[1][1], v[1][2], v[1][3],
				v[2][0], v[2][1], v[2][2], v[2][3],
				v[3][0], v[3][1], v[3][2], v[3][3]);
		}

		constexpr MatrixT Inversed() const noexcept
		{
			T	m11 = v[0][0], m21 = v[1][0], m31 = v[2][0], m41 = v[3][0],
				m12 = v[0][1], m22 = v[1][1], m32 = v[2][1], m42 = v[3][1],
				m13 = v[0][2], m23 = v[1][2], m33 = v[2][2], m43 = v[3][2],
				m14 = v[0][3], m24 = v[1][3], m34 = v[2][3], m44 = v[3][3];

			T	_1122_2112 = m11 * m22 - m21 * m12,
				_1132_3112 = m11 * m32 - m31 * m12,
				_1142_4112 = m11 * m42 - m41 * m12,
				_2132_3122 = m21 * m32 - m31 * m22,
				_2142_4122 = m21 * m42 - m41 * m22,
				_3142_4132 = m31 * m42 - m41 * m32,
				_1324_2314 = m13 * m24 - m23 * m14,
				_1334_3314 = m13 * m34 - m33 * m14,
				_1344_4314 = m13 * m44 - m43 * m14,
				_2334_3324 = m23 * m34 - m33 * m24,
				_2344_4324 = m23 * m44 - m43 * m24,
				_3344_4334 = m33 * m44 - m43 * m34;

			T determinant = (_1122_2112 * _3344_4334 - _1132_3112 * _2344_4324 + _1142_4112 * _2334_3324 + _2132_3122 * _1344_4314 - _2142_4122 * _1334_3314 + _3142_4132 * _1324_2314);

			// non-invertible
			if (BasicMath::CEqual<T>(determinant, 0))
			{
				assert(false);
				return MatrixT(T(1));
			}

			T inverseDeterminant = T(1) / determinant;

			return MatrixT(
				(m22 * _3344_4334 - m32 * _2344_4324 + m42 * _2334_3324) * inverseDeterminant,
				(-m21 * _3344_4334 + m31 * _2344_4324 - m41 * _2334_3324) * inverseDeterminant,
				(m24 * _3142_4132 - m34 * _2142_4122 + m44 * _2132_3122) * inverseDeterminant,
				(-m23 * _3142_4132 + m33 * _2142_4122 - m43 * _2132_3122) * inverseDeterminant,
				(-m12 * _3344_4334 + m32 * _1344_4314 - m42 * _1334_3314) * inverseDeterminant,
				(m11 * _3344_4334 - m31 * _1344_4314 + m41 * _1334_3314) * inverseDeterminant,
				(-m14 * _3142_4132 + m34 * _1142_4112 - m44 * _1132_3112) * inverseDeterminant,
				(m13 * _3142_4132 - m33 * _1142_4112 + m43 * _1132_3112) * inverseDeterminant,
				(m12 * _2344_4324 - m22 * _1344_4314 + m42 * _1324_2314) * inverseDeterminant,
				(-m11 * _2344_4324 + m21 * _1344_4314 - m41 * _1324_2314) * inverseDeterminant,
				(m14 * _2142_4122 - m24 * _1142_4112 + m44 * _1122_2112) * inverseDeterminant,
				(-m13 * _2142_4122 + m23 * _1142_4112 - m43 * _1122_2112) * inverseDeterminant,
				(-m12 * _2334_3324 + m22 * _1334_3314 - m32 * _1324_2314) * inverseDeterminant,
				(m11 * _2334_3324 - m21 * _1334_3314 + m31 * _1324_2314) * inverseDeterminant,
				(-m14 * _2132_3122 + m24 * _1132_3112 - m34 * _1122_2112) * inverseDeterminant,
				(m13 * _2132_3122 - m23 * _1132_3112 + m33 * _1122_2112) * inverseDeterminant);
		}

		constexpr T Determinant() const noexcept
		{
			T	m11 = v[0][0], m21 = v[1][0], m31 = v[2][0], m41 = v[3][0],
				m12 = v[0][1], m22 = v[1][1], m32 = v[2][1], m42 = v[3][1],
				m13 = v[0][2], m23 = v[1][2], m33 = v[2][2], m43 = v[3][2],
				m14 = v[0][3], m24 = v[1][3], m34 = v[2][3], m44 = v[3][3];

			T	_1122_2112 = m11 * m22 - m21 * m12,
				_1132_3112 = m11 * m32 - m31 * m12,
				_1142_4112 = m11 * m42 - m41 * m12,
				_2132_3122 = m21 * m32 - m31 * m22,
				_2142_4122 = m21 * m42 - m41 * m22,
				_3142_4132 = m31 * m42 - m41 * m32,
				_1324_2314 = m13 * m24 - m23 * m14,
				_1334_3314 = m13 * m34 - m33 * m14,
				_1344_4314 = m13 * m44 - m43 * m14,
				_2334_3324 = m23 * m34 - m33 * m24,
				_2344_4324 = m23 * m44 - m43 * m24,
				_3344_4334 = m33 * m44 - m43 * m34;

			T determinant = (_1122_2112 * _3344_4334 - _1132_3112 * _2344_4324 + _1142_4112 * _2334_3324 + _2132_3122 * _1344_4314 - _2142_4122 * _1334_3314 + _3142_4132 * _1324_2314);
			return determinant;
		}

		T const* Data() const noexcept
		{
			return v.Data()->Data();
		}
	};

	template <class T>
	MatrixT<T, 4, 4> const MatrixT<T, 4, 4>::Zero = MatrixT(T(0));

	template <class T>
	MatrixT<T, 4, 4> const MatrixT<T, 4, 4>::Identity = MatrixT(T(1));

	template<class T>
	constexpr MatrixT<T, 4, 4> operator*(MatrixT<T, 4, 4> const& l, MatrixT<T, 4, 4> const& r) noexcept
	{
		return MatrixT<T, 4, 4>(
				r[0][0] * l[0][0] + r[0][1] * l[1][0] + r[0][2] * l[2][0] + r[0][3] * l[3][0],
				r[0][0] * l[0][1] + r[0][1] * l[1][1] + r[0][2] * l[2][1] + r[0][3] * l[3][1],
				r[0][0] * l[0][2] + r[0][1] * l[1][2] + r[0][2] * l[2][2] + r[0][3] * l[3][2],
				r[0][0] * l[0][3] + r[0][1] * l[1][3] + r[0][2] * l[2][3] + r[0][3] * l[3][3],
				r[1][0] * l[0][0] + r[1][1] * l[1][0] + r[1][2] * l[2][0] + r[1][3] * l[3][0],
				r[1][0] * l[0][1] + r[1][1] * l[1][1] + r[1][2] * l[2][1] + r[1][3] * l[3][1],
				r[1][0] * l[0][2] + r[1][1] * l[1][2] + r[1][2] * l[2][2] + r[1][3] * l[3][2],
				r[1][0] * l[0][3] + r[1][1] * l[1][3] + r[1][2] * l[2][3] + r[1][3] * l[3][3],
				r[2][0] * l[0][0] + r[2][1] * l[1][0] + r[2][2] * l[2][0] + r[2][3] * l[3][0],
				r[2][0] * l[0][1] + r[2][1] * l[1][1] + r[2][2] * l[2][1] + r[2][3] * l[3][1],
				r[2][0] * l[0][2] + r[2][1] * l[1][2] + r[2][2] * l[2][2] + r[2][3] * l[3][2],
				r[2][0] * l[0][3] + r[2][1] * l[1][3] + r[2][2] * l[2][3] + r[2][3] * l[3][3],
				r[3][0] * l[0][0] + r[3][1] * l[1][0] + r[3][2] * l[2][0] + r[3][3] * l[3][0],
				r[3][0] * l[0][1] + r[3][1] * l[1][1] + r[3][2] * l[2][1] + r[3][3] * l[3][1],
				r[3][0] * l[0][2] + r[3][1] * l[1][2] + r[3][2] * l[2][2] + r[3][3] * l[3][2],
				r[3][0] * l[0][3] + r[3][1] * l[1][3] + r[3][2] * l[2][3] + r[3][3] * l[3][3]);
	}


	template<class T, uint32 R, uint32 C>
	constexpr MatrixT<T, R, C> operator+(MatrixT<T, R, C> const& l, MatrixT<T, R, C> const& r) noexcept
	{
		return MatrixT<T, R, C>(l.v + r.v);
	}
	template<class T, uint32 R, uint32 C>
	constexpr MatrixT<T, R, C> operator-(MatrixT<T, R, C> const& l, MatrixT<T, R, C> const& r) noexcept
	{
		return MatrixT<T, R, C>(l.v - r.v);
	}

	template<class T, uint32 R, uint32 C>
	constexpr MatrixT<T, R, C> operator*(MatrixT<T, R, C> const& l, T const& r) noexcept
	{
		return MatrixT<T, R, C>(l.v * VectorT<T, C>(r));
	}
	template<class T, uint32 R, uint32 C>
	constexpr MatrixT<T, R, C> operator*(T const& l, MatrixT<T, R, C> const& r) noexcept
	{
		return MatrixT<T, R, C>(VectorT<T, C>(l) * r.v);
	}

	template<class T, uint32 R, uint32 C>
	constexpr MatrixT<T, R, C> operator/(MatrixT<T, R, C> const& l, T const& r) noexcept
	{
		return MatrixT<T, R, C>(l.v * VectorT<T, C>(T(1) / r));
	}

	template<class T, uint32 R, uint32 C>
	constexpr bool operator==(MatrixT<T, R, C> const& l, MatrixT<T, R, C> const& r) noexcept
	{
		return l.v == r.v;
	}
	template<class T, uint32 R, uint32 C>
	constexpr bool operator!=(MatrixT<T, R, C> const& l, MatrixT<T, R, C> const& r) noexcept
	{
		return l.v != r.v;
	}



	using M33F32 = MatrixT<float32, 3, 3>;
	using M33F64 = MatrixT<float64, 3, 3>;
	using M44F32 = MatrixT<float32, 4, 4>;
	using M44F64 = MatrixT<float64, 4, 4>;

}
