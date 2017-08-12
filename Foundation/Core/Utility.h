#pragma once
#include "BasicType.h"

namespace X
{
	template <class T, uint32 N>
	constexpr uint32 ArraySize(T(&)[N]) noexcept
	{
		return N;
	}

}

