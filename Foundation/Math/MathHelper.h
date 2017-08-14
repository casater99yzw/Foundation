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
	}
}
