#pragma once
#include <type_traits>

namespace X
{
	namespace Detail
	{
		template <class T0, class T1, bool LeftEmpty, bool RightEmpty>
		struct CompressedPairImpl;

		template <class T0, class T1>
		struct CompressedPairImpl<T0, T1, false, false>
		{
			T0 t0;
			T1 t1;

			constexpr CompressedPairImpl() = default;

			template <class TT0, class TT1>
			constexpr CompressedPairImpl(TT0&& t0, TT1&& t1) : t0(std::forward<TT0>(t0)), t1(std::forward<TT1>(t1))
			{
			}

			T0& E0() noexcept
			{
				return t0;
			}
			constexpr T0 const& E0() const noexcept
			{
				return t0;
			}
			T1& E1() noexcept
			{
				return t1;
			}
			constexpr T1 const& E1() const noexcept
			{
				return t1;
			}
		};

		template <class T0, class T1>
		struct CompressedPairImpl<T0, T1, true, false> : T0
		{
			T1 t1;

			constexpr CompressedPairImpl() = default;

			template <class TT0, class TT1>
			constexpr CompressedPairImpl(TT0&& t0, TT1&& t1) : T0(std::forward<TT0>(t0)), t1(std::forward<TT1>(t1))
			{
			}

			T0& E0() noexcept
			{
				return *this;
			}
			constexpr T0 const& E0() const noexcept
			{
				return *this;
			}
			T1& E1() noexcept
			{
				return t1;
			}
			constexpr T1 const& E1() const noexcept
			{
				return t1;
			}
		};

		template <class T0, class T1>
		struct CompressedPairImpl<T0, T1, false, true> : T1
		{
			T0 t0;

			constexpr CompressedPairImpl() = default;

			template <class TT0, class TT1>
			constexpr CompressedPairImpl(TT0&& t0, TT1&& t1) : t0(std::forward<TT0>(t0)), T1(std::forward<TT1>(t1))
			{
			}

			T0& E0() noexcept
			{
				return t0;
			}
			constexpr T0 const& E0() const noexcept
			{
				return t0;
			}
			T1& E1() noexcept
			{
				return *this;
			}
			constexpr T1 const& E1() const noexcept
			{
				return *this;
			}
		};

		template <class T0, class T1>
		struct CompressedPairImpl<T0, T1, true, true> : CompressedPairImpl<T0, T1, true, false>
		{
			constexpr CompressedPairImpl() = default;

			template <class TT0, class TT1>
			constexpr CompressedPairImpl(TT0&& t0, TT1&& t1) : CompressedPairImpl<T0, T1, true, false>(std::forward<TT0>(t0), std::forward<TT1>(t1))
			{
			}
		};


	}

	template <class T0, class T1>
	struct CompressedPair : Detail::CompressedPairImpl<T0, T1, std::is_empty<T0>::value, std::is_empty<T1>::value>
	{
		constexpr CompressedPair() = default;

		template <class TT0, class TT1>
		constexpr CompressedPair(TT0&& t0, TT1&& t1) : CompressedPairImpl(std::forward<TT0>(t0), std::forward<TT1>(t1))
		{
		}
	};
}

