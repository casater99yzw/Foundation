#pragma once
#include "BaseType.h"
#include <type_traits>
namespace X
{
	constexpr uint64 BitValue(uint32 bit) noexcept
	{
		return 1ull << bit;
	}

	template <class E, class = std::enable_if_t<std::is_enum<E>::value>>
	class BitFlag
	{
		using UnderlyingType = std::underlying_type_t<E>;
	public:
		constexpr BitFlag() = default;
		constexpr BitFlag(E e) noexcept : e(e)
		{
		}

		constexpr E Value() const noexcept
		{
			return e;
		}

		constexpr UnderlyingType UnderlyingValue() const noexcept
		{
			return UnderlyingType(e);
		}

		constexpr bool Contains(E bit) const noexcept
		{
			return (UnderlyingType(e) & UnderlyingType(bit)) != 0;
		}

		void SetBits(E bits) noexcept
		{
			e = E(UnderlyingType(e) | UnderlyingType(bits));
		}
		void SetBits(BitFlag bits) noexcept
		{
			e = E(UnderlyingType(e) | bits.UnderlyingValue());
		}

		void UnsetBits(E bits) noexcept
		{
			e = E(UnderlyingType(e) & ~UnderlyingType(bits));
		}
		void UnsetBits(BitFlag bits) noexcept
		{
			e = E(UnderlyingType(e) & ~bits.UnderlyingValue());
		}

	private:
		E e;
	};

	template <class E>
	constexpr BitFlag<E> MakeFlag(E e) noexcept
	{
		return BitFlag<E>(e);
	}

	template <class E>
	constexpr BitFlag<E> Complement(BitFlag<E> e) noexcept
	{
		return MakeFlag(E(~e.UnderlyingValue()));
	}
	template <class E>
	constexpr BitFlag<E> Complement(E e) noexcept
	{
		return Complement(MakeFlag(e));
	}

	template <class E>
	constexpr BitFlag<E> operator~(BitFlag<E> e) noexcept
	{
		return Complement(e);
	}
	template <class E>
	constexpr BitFlag<E> operator~(E e) noexcept
	{
		return Complement(e);
	}

	template <class E>
	constexpr BitFlag<E> Union(BitFlag<E> e0, BitFlag<E> e1) noexcept
	{
		return MakeFlag(E(e0.UnderlyingValue() | e1.UnderlyingValue()));
	}
	template <class E>
	constexpr BitFlag<E> Union(BitFlag<E> e0, E e1) noexcept
	{
		return Union(e0, MakeFlag(e1));
	}
	template <class E>
	constexpr BitFlag<E> Union(E e0, BitFlag<E> e1) noexcept
	{
		return Union(e0, MakeFlag(e1));
	}
	template <class E>
	constexpr BitFlag<E> Union(E e0, E e1) noexcept
	{
		return Union(MakeFlag(e0), MakeFlag(e1));
	}

	template <class E>
	constexpr BitFlag<E> operator|(BitFlag<E> e0, BitFlag<E> e1) noexcept
	{
		return Union(e0, e1);
	}
	template <class E>
	constexpr BitFlag<E> operator|(BitFlag<E> e0, E e1) noexcept
	{
		return Union(e0, e1);
	}
	template <class E>
	constexpr BitFlag<E> operator|(E e0, BitFlag<E> e1) noexcept
	{
		return Union(e0, e1);
	}
	template <class E>
	constexpr BitFlag<E> operator|(E e0, E e1) noexcept
	{
		return Union(e0, e1);
	}

	template <class E>
	constexpr BitFlag<E> Intersection(BitFlag<E> e0, BitFlag<E> e1) noexcept
	{
		return MakeFlag(E(e0.UnderlyingValue() & e1.UnderlyingValue()));
	}
	template <class E>
	constexpr BitFlag<E> Intersection(BitFlag<E> e0, E e1) noexcept
	{
		return Intersection(e0, MakeFlag(e1));
	}
	template <class E>
	constexpr BitFlag<E> Intersection(E e0, BitFlag<E> e1) noexcept
	{
		return Intersection(MakeFlag(e0), e1);
	}
	template <class E>
	constexpr BitFlag<E> Intersection(E e0, E e1) noexcept
	{
		return Intersection(MakeFlag(e0), MakeFlag(e1));
	}

	template <class E>
	constexpr BitFlag<E> operator&(BitFlag<E> e0, BitFlag<E> e1) noexcept
	{
		return Intersection(e0, e1);
	}
	template <class E>
	constexpr BitFlag<E> operator&(BitFlag<E> e0, E e1) noexcept
	{
		return Intersection(e0, MakeFlag(e1));
	}
	template <class E>
	constexpr BitFlag<E> operator&(E e0, BitFlag<E> e1) noexcept
	{
		return Intersection(MakeFlag(e0), e1);
	}
	template <class E>
	constexpr BitFlag<E> operator&(E e0, E e1) noexcept
	{
		return Intersection(MakeFlag(e0), MakeFlag(e1));
	}



}