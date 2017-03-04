#include "CompressedPair.h"
#define MemoryDebug
#include "ReferenceCount.h"

#include "BitFlag.h"

#include <utility>
#include <memory>
#include <cassert>

using namespace X;

struct C
{
	C() = default;
	C(int&& i) noexcept
	{
	}
	C(int const& i)
	{
	}
};

int main()
{
	std::pair<int, int> p;
	std::unique_ptr<int> up;

	constexpr bool v = std::is_nothrow_constructible<C, int>::value;

	CompressedPair<C, int> cp;
	constexpr int scp = sizeof(cp);
	constexpr bool noexceptcp = noexcept(CompressedPair<C, int>(C(), 1));


	struct NTS : ReferenceCountBase<true>
	{
	};

	struct DNTS : NTS
	{
		int i = 0;
	};


	{
		assert(NTS::Count() == 0);
		ReferenceCountPtr<DNTS, true> pdntsnull;

		ReferenceCountPtr<DNTS, true> pdnts(new DNTS, Ownership::Transfer);

		ReferenceCountPtr<NTS, true> pnts1 = pdnts;
		ReferenceCountPtr<NTS, true> pnts2(pdnts.Get(), Ownership::Acquire);

		assert(pnts1 == pdnts);
		*pnts1 = *pnts2;

		assert(!(pdnts < pnts1));
		assert(!(pdnts > pnts1));

		pdnts->i = 42;
		pnts1 = std::move(pdnts);
		assert(pnts1.DynamicCastTo<DNTS>()->i == 42);

		assert(NTS::Count() == 1);
		constexpr bool noexceptrcp = noexcept(ReferenceCountPtr<DNTS, true>());
		constexpr bool noexceptrcpget = noexcept(pdnts.Get());
	}
	assert(NTS::Count() == 0);

	constexpr auto bit0 = BitValue(0);
	enum class SF
	{
		A = BitValue(0),
		B = BitValue(1),
		C = BitValue(2),
	};

	BitFlag<SF> sflag(SF::A);
	sflag.SetBits(SF::B);
	sflag.UnsetBits(SF::A | SF::B);
	sflag.SetBits(~SF::C & SF::A);
	sflag.UnsetBits(SF::B);
	sflag.SetBits(SF::C);
	sflag = SF::A | SF::B | SF::C;

	return 0;
}