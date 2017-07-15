/*
*	Code partially come from KlayGE, with some simplification and improvement.
*/
#pragma once

namespace X
{
	namespace MathHelper
	{
		template <typename T, uint32 N> // is a class due to template function cannot be partially specialized.
		struct TransformHelper
		{
			constexpr static void DoTransform(T out[N], T const m[16], T const v[N], T lastComponent);
			constexpr static void DoTransformDirection(T out[N], T const m[16], T const v[N]);
		};

		template <typename T>
		struct TransformHelper<T, 4>
		{
			constexpr static void DoTransform(T out[4], T const m[16], T const v[4], T lastComponent)
			{
				out[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * v[3];
				out[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * v[3];
				out[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
				out[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
			}
			constexpr static void DoTransformDirection(T out[4], T const m[16], T const v[4])
			{
				out[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2];
				out[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2];
				out[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2];
				out[3] = T(0);
			}
		};
		template <typename T>
		struct TransformHelper<T, 3>
		{
			constexpr static void DoTransform(T out[3], T const m[16], T const v[3], T lastComponent)
			{
				T inverseW = T(1) / (m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * lastComponent);
				out[0] = (m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * lastComponent) * inverseW;
				out[1] = (m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * lastComponent) * inverseW;
				out[2] = (m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * lastComponent) * inverseW;
			}
			constexpr static void DoTransformDirection(T out[3], T const m[16], T const v[3])
			{
				out[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2];
				out[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2];
				out[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2];
			}
		};


		template <typename T, uint32 N>
		struct VectorHelper
		{
			static_assert(N <= 4, "Vector larger than 4 are not support.");
			template <typename U>
			constexpr static void DoCopy(T out[N], U const r[N])
			{
				out[0] = static_cast<T>(r[0]);
				VectorHelper<T, N - 1>::DoCopy(out + 1, r + 1);
			}

			constexpr static void DoAssign(T out[N], T const& r)
			{
				out[0] = r;
				VectorHelper<T, N - 1>::DoAssign(out + 1, r);
			}

			constexpr static void DoAdd(T out[N], T const l[N], T const r[N])
			{
				out[0] = l[0] + r[0];
				VectorHelper<T, N - 1>::DoAdd(out + 1, l + 1, r + 1);
			}

			constexpr static void DoAdd(T out[N], T const l[N], T const& r)
			{
				out[0] = l[0] + r;
				VectorHelper<T, N - 1>::DoAdd(out + 1, l + 1, r);
			}

			constexpr static void DoSubtract(T out[N], T const l[N], T const r[N])
			{
				out[0] = l[0] - r[0];
				VectorHelper<T, N - 1>::DoSubtract(out + 1, l + 1, r + 1);
			}

			constexpr static void DoSubtract(T out[N], T const l[N], T const& r)
			{
				out[0] = l[0] - r;
				VectorHelper<T, N - 1>::DoSubtract(out + 1, l + 1, r);
			}

			constexpr static void DoMultiply(T out[N], T const l[N], T const r[N])
			{
				out[0] = l[0] * r[0];
				VectorHelper<T, N - 1>::DoMultiply(out + 1, l + 1, r + 1);
			}

			constexpr static void DoScale(T out[N], T const l[N], T const& r)
			{
				out[0] = l[0] * r;
				VectorHelper<T, N - 1>::DoScale(out + 1, l + 1, r);
			}

			constexpr static void DoDivide(T out[N], T const l[N], T const r[N])
			{
				out[0] = l[0] / r[0];
				VectorHelper<T, N - 1>::DoDivide(out + 1, l + 1, r + 1);
			}

			constexpr static void DoNegate(T out[N], T const r[N])
			{
				out[0] = -r[0];
				VectorHelper<T, N - 1>::DoNegate(out + 1, r + 1);
			}

			constexpr static bool DoEqual(T const l[N], T const r[N])
			{
				return VectorHelper<T, 1>::DoEqual(l, r) && VectorHelper<T, N - 1>::DoEqual(l + 1, r + 1);
			}

			constexpr static void DoSwap(T l[N], T r[N])
			{
				std::swap(l[0], r[0]);
				VectorHelper<T, N - 1>::DoSwap(l + 1, r + 1);
			}


			constexpr static T DoDot(T const l[1], T const r[1])
			{
				return l[0] * r[0] + VectorHelper<T, N - 1>::DoDot(l + 1, r + 1);
			}
		};

		template <typename T>
		struct VectorHelper<T, 1>
		{
			template <typename U>
			constexpr static void DoCopy(T out[1], U const r[1])
			{
				out[0] = static_cast<T>(r[0]);
			}

			constexpr static void DoAssign(T out[1], T const& r)
			{
				out[0] = r;
			}

			constexpr static void DoAdd(T out[1], T const l[1], T const r[1])
			{
				out[0] = l[0] + r[0];
			}

			constexpr static void DoAdd(T out[1], T const l[1], T const r)
			{
				out[0] = l[0] + r;
			}

			constexpr static void DoSubtract(T out[1], T const l[1], T const r[1])
			{
				out[0] = l[0] - r[0];
			}

			constexpr static void DoSubtract(T out[1], T const l[1], T const& r)
			{
				out[0] = l[0] - r;
			}

			constexpr static void DoMultiply(T out[1], T const l[1], T const r[1])
			{
				out[0] = l[0] * r[0];
			}

			constexpr static void DoScale(T out[1], T const l[1], T const& r)
			{
				out[0] = l[0] * r;
			}

			constexpr static void DoDivide(T out[1], T const l[1], T const r[1])
			{
				out[0] = l[0] / r[0];
			}

			constexpr static void DoNegate(T out[1], T const r[1])
			{
				out[0] = -r[0];
			}

			constexpr static bool DoEqual(T const l[1], T const r[1])
			{
				return l[0] == r[0];
			}

			constexpr static T DoDot(T const l[1], T const r[1])
			{
				return l[0] * r[0];
			}
		};

		template <typename T>
		struct MatrixHepler
		{
			constexpr static void DoMultiply(T out[16], T const l[16], T const r[16])
			{
				out[0] = r[0] * l[0] + r[1] * l[4] + r[2] * l[8] + r[3] * l[12];
				out[1] = r[0] * l[1] + r[1] * l[5] + r[2] * l[9] + r[3] * l[13];
				out[2] = r[0] * l[2] + r[1] * l[6] + r[2] * l[10] + r[3] * l[14];
				out[3] = r[0] * l[3] + r[1] * l[7] + r[2] * l[11] + r[3] * l[15];
				out[4] = r[4] * l[0] + r[5] * l[4] + r[6] * l[8] + r[7] * l[12];
				out[5] = r[4] * l[1] + r[5] * l[5] + r[6] * l[9] + r[7] * l[13];
				out[6] = r[4] * l[2] + r[5] * l[6] + r[6] * l[10] + r[7] * l[14];
				out[7] = r[4] * l[3] + r[5] * l[7] + r[6] * l[11] + r[7] * l[15];
				out[8] = r[8] * l[0] + r[9] * l[4] + r[10] * l[8] + r[11] * l[12];
				out[9] = r[8] * l[1] + r[9] * l[5] + r[10] * l[9] + r[11] * l[13];
				out[10] = r[8] * l[2] + r[9] * l[6] + r[10] * l[10] + r[11] * l[14];
				out[11] = r[8] * l[3] + r[9] * l[7] + r[10] * l[11] + r[11] * l[15];
				out[12] = r[12] * l[0] + r[13] * l[4] + r[14] * l[8] + r[15] * l[12];
				out[13] = r[12] * l[1] + r[13] * l[5] + r[14] * l[9] + r[15] * l[13];
				out[14] = r[12] * l[2] + r[13] * l[6] + r[14] * l[10] + r[15] * l[14];
				out[15] = r[12] * l[3] + r[13] * l[7] + r[14] * l[11] + r[15] * l[15];
			}

			constexpr static void CalculateDeterminant(T in[16]) 
			{
				// subscript: row, column
				T m11 = in[0], m21 = in[1], m31 = in[2], m41 = in[3],
					m12 = in[4], m22 = in[5], m32 = in[6], m42 = in[7],
					m13 = in[8], m23 = in[9], m33 = in[10], m43 = in[11],
					m14 = in[12], m24 = in[13], m34 = in[14], m44 = in[15];

				T _1122_2112 = m11 * m22 - m21 * m12,
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

			constexpr bool static DoInverse(T out[16], T const in[16])
			{
				// subscript: row, column
				T m11 = in[0], m21 = in[1], m31 = in[2], m41 = in[3],
					m12 = in[4], m22 = in[5], m32 = in[6], m42 = in[7],
					m13 = in[8], m23 = in[9], m33 = in[10], m43 = in[11],
					m14 = in[12], m24 = in[13], m34 = in[14], m44 = in[15];

				T _1122_2112 = m11 * m22 - m21 * m12,
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
				if (Equal<T>(determinant, 0))
				{
					return false;
				}

				T inverseDeterminant;
				inverseDeterminant = T(1) / determinant;

				out[0] = (m22 * _3344_4334 - m32 * _2344_4324 + m42 * _2334_3324) * inverseDeterminant;
				out[1] = (-m21 * _3344_4334 + m31 * _2344_4324 - m41 * _2334_3324) * inverseDeterminant;
				out[2] = (m24 * _3142_4132 - m34 * _2142_4122 + m44 * _2132_3122) * inverseDeterminant;
				out[3] = (-m23 * _3142_4132 + m33 * _2142_4122 - m43 * _2132_3122) * inverseDeterminant;
				out[4] = (-m12 * _3344_4334 + m32 * _1344_4314 - m42 * _1334_3314) * inverseDeterminant;
				out[5] = (m11 * _3344_4334 - m31 * _1344_4314 + m41 * _1334_3314) * inverseDeterminant;
				out[6] = (-m14 * _3142_4132 + m34 * _1142_4112 - m44 * _1132_3112) * inverseDeterminant;
				out[7] = (m13 * _3142_4132 - m33 * _1142_4112 + m43 * _1132_3112) * inverseDeterminant;
				out[8] = (m12 * _2344_4324 - m22 * _1344_4314 + m42 * _1324_2314) * inverseDeterminant;
				out[9] = (-m11 * _2344_4324 + m21 * _1344_4314 - m41 * _1324_2314) * inverseDeterminant;
				out[10] = (m14 * _2142_4122 - m24 * _1142_4112 + m44 * _1122_2112) * inverseDeterminant;
				out[11] = (-m13 * _2142_4122 + m23 * _1142_4112 - m43 * _1122_2112) * inverseDeterminant;
				out[12] = (-m12 * _2334_3324 + m22 * _1334_3314 - m32 * _1324_2314) * inverseDeterminant;
				out[13] = (m11 * _2334_3324 - m21 * _1334_3314 + m31 * _1324_2314) * inverseDeterminant;
				out[14] = (-m14 * _2132_3122 + m24 * _1132_3112 - m34 * _1122_2112) * inverseDeterminant;
				out[15] = (m13 * _2132_3122 - m23 * _1132_3112 + m33 * _1122_2112) * inverseDeterminant;

				return true;
			}

		};

	}
}
