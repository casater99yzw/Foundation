#include "Core/CompressedPair.h"
#define MemoryDebug
#include "Core/ReferenceCount.h"

#include "Core/BitFlag.h"

#include "Math/Vector.h"
#include "Math/Matrix.h"

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


constexpr auto ConstantV()
{
	V4F32 a(1, 2, 3, 4);
	V4F32 b(5, 6, 7, 8);

	b = a;
	return b;
}

constexpr auto v = ConstantV();

constexpr auto ConstantM()
{
	M44F32 a(2);
	M44F32 b(a.Column(0), a.Column(1), a.Column(2), a.Column(3));
	return a;
}

constexpr auto m = ConstantM();

int main()
{
	auto f = ConstantV();

	std::pair<int, int> p;
	std::unique_ptr<int> up;

	constexpr bool v = std::is_nothrow_constructible<C, int>::value;

	CompressedPair<C, int> cp;
	constexpr int scp = sizeof(cp);
	constexpr bool noexceptcp = noexcept(CompressedPair<C, int>(C(), 1));


	struct NTS : ReferenceCountBase<false>
	{
	};

	struct DNTS : NTS
	{
		int i = 0;
	};


	{
		assert(NTS::Count() == 0);
		ReferenceCountPtr<DNTS> pdntsnull;

		ReferenceCountPtr<DNTS> pdnts(new DNTS, Ownership::Transfer);

		ReferenceCountPtr<NTS> pnts1 = pdnts;
		ReferenceCountPtr<NTS> pnts2(pdnts.Get(), Ownership::Acquire);

		assert(pnts1 == pdnts);
		*pnts1 = *pnts2;

		assert(!(pdnts < pnts1));
		assert(!(pdnts > pnts1));

		pdnts->i = 42;
		pnts1 = std::move(pdnts);
		assert(pnts1.DynamicCastTo<DNTS>()->i == 42);

		assert(NTS::Count() == 1);
		constexpr bool noexceptrcp = noexcept(ReferenceCountPtr<DNTS>());
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
	static_assert(sizeof(SF) == sizeof(int), "");
	BitFlag<SF> sflag(SF::A);
	sflag.SetBits(SF::B);
	sflag.UnsetBits(SF::A | SF::B);
	sflag.SetBits(~SF::C & SF::A);
	sflag.UnsetBits(SF::B);
	sflag.SetBits(SF::C);
	assert(sflag.Contains(SF::C));
	sflag = SF::A | SF::B | SF::C;
	sflag = SF::A;

	return 0;
}