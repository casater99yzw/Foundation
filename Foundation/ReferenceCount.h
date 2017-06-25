#pragma once
#include "BasicType.h"
#include <atomic>

namespace X
{
	// override OnRelease to customize deletion.
	template <bool ThreadSafe = true>
	struct ReferenceCountBase;

	template <>
	struct ReferenceCountBase<true>
	{
#ifdef MemoryDebug
	public:
		static sint32& Count() noexcept
		{
			static sint32 c = 0;
			return c;
		}

		ReferenceCountBase() noexcept
		{
			Count() += 1;
		}

#endif // MemoryDebug

	public:
#ifndef MemoryDebug
		ReferenceCountBase() noexcept = default;
#endif // !MemoryDebug


		ReferenceCountBase(ReferenceCountBase const& other) noexcept
		{
		}

		ReferenceCountBase(ReferenceCountBase&& other) noexcept
		{
		}

		ReferenceCountBase& operator=(ReferenceCountBase const& other) noexcept
		{
			return *this;
		}

		ReferenceCountBase& operator=(ReferenceCountBase&& other) noexcept
		{
			return *this;
		}

		bool IsUniqueReference() const noexcept
		{
			return counter.load() == 1;
		}

		sint32 GetReferenceCount() const noexcept
		{
			return counter.load();
		}

		void IncreaseReference() noexcept
		{
			counter.fetch_add(1);
		}
		void DecreaseReference() noexcept
		{
			if (counter.fetch_sub(1) == 1)
			{
				OnRelease();
			}
		}

		virtual ~ReferenceCountBase() noexcept = 0
		{
#ifdef MemoryDebug
			Count() -= 1;
#endif // MemoryDebug
		}
	protected:
		virtual void OnRelease() noexcept
		{
			delete this;
		}


	private:
		std::atomic<sint32> counter = 1;
	};


	template <>
	struct ReferenceCountBase<false>
	{
#ifdef MemoryDebug
	public:
		static sint32& Count() noexcept
		{
			static sint32 c = 0;
			return c;
		}
		ReferenceCountBase() noexcept
		{
			Count() += 1;
		}
#endif // MemoryDebug
	public:
#ifndef MemoryDebug
		ReferenceCountBase() noexcept = default;
#endif // !MemoryDebug


		ReferenceCountBase(ReferenceCountBase const& other) noexcept
		{
		}

		ReferenceCountBase(ReferenceCountBase&& other) noexcept
		{
		}

		ReferenceCountBase& operator=(ReferenceCountBase const& other) noexcept
		{
			return *this;
		}

		ReferenceCountBase& operator=(ReferenceCountBase&& other) noexcept
		{
			return *this;
		}

		bool IsUniqueReference() const noexcept
		{
			return counter == 1;
		}

		sint32 GetReferenceCount() const noexcept
		{
			return counter;
		}

		void IncreaseReference() noexcept
		{
			counter += 1;
		}
		void DecreaseReference() noexcept
		{
			sint32 c = counter - 1;
			if (c == 0)
			{
				OnRelease();
			}
			counter = c;
		}

		virtual ~ReferenceCountBase() noexcept = 0
		{
#ifdef MemoryDebug
			Count() -= 1;
#endif // MemoryDebug
		}

	protected:
		virtual void OnRelease() noexcept
		{
			delete this;
		}

	private:
		sint32 counter = 1;
	};

	namespace Ownership
	{
		constexpr struct AcquireT
		{
		}
		// Will increase the counter of the object.
		Acquire;

		constexpr struct TransferT
		{
		}
		// Will NOT increase he counter of the object.
		// create ReferenceCountPtr with newed object should using Transfer.
		Transfer;
	}

	template <class T>
	class ReferenceCountPtr
	{
	public:
		template <class Y>
		friend class ReferenceCountPtr;
	public:
		~ReferenceCountPtr() noexcept
		{
			Reset();
		}

		constexpr ReferenceCountPtr() = default;

		explicit constexpr ReferenceCountPtr(nullptr_t)
		{
		}

		explicit ReferenceCountPtr(T* p, Ownership::AcquireT) noexcept : ptr(p)
		{
			if (ptr)
			{
				ptr->IncreaseReference();
			}
		}

		explicit ReferenceCountPtr(T* p, Ownership::TransferT) noexcept : ptr(p)
		{
		}

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		explicit ReferenceCountPtr(Y* y, Ownership::AcquireT) noexcept : ptr(y)
		{
			if (ptr)
			{
				ptr->IncreaseReference();
			}
		}

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		explicit ReferenceCountPtr(Y* y, Ownership::TransferT) noexcept : ptr(y)
		{
		}

		ReferenceCountPtr(ReferenceCountPtr const& other) noexcept
		{
			CopyIn(other);
		}

		ReferenceCountPtr(ReferenceCountPtr&& other) noexcept
		{
			MoveIn(std::move(other));
		}

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		ReferenceCountPtr(ReferenceCountPtr<Y> const& other) noexcept
		{
			CopyIn(other);
		}

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		ReferenceCountPtr(ReferenceCountPtr<Y>&& other) noexcept
		{
			MoveIn(std::move(other));
		}

		ReferenceCountPtr& operator=(nullptr_t) noexcept
		{
			Reset();
			return *this;
		}

		ReferenceCountPtr& operator=(ReferenceCountPtr const& other) noexcept
		{
			CopyIn(other);
			return *this;
		}

		ReferenceCountPtr& operator=(ReferenceCountPtr&& other) noexcept
		{
			MoveIn(std::move(other));
			return *this;
		}

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		ReferenceCountPtr& operator=(ReferenceCountPtr<Y> const& other) noexcept
		{
			CopyIn(other);
			return *this;
		}

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		ReferenceCountPtr& operator=(ReferenceCountPtr<Y>&& other) noexcept
		{
			MoveIn(std::move(other));
			return *this;
		}

		constexpr explicit operator bool() const noexcept
		{
			return ptr != nullptr;
		}

		constexpr T& operator*() const noexcept
		{
			return *ptr;
		}

		constexpr T* operator->() const noexcept
		{
			return ptr;
		}

		constexpr T* Get() const noexcept
		{
			return ptr;
		}

		T* Extract() noexcept
		{
			T* p = ptr;
			ptr = nullptr;
			return p;
		}

		void Reset() noexcept
		{
			if (ptr)
			{
				ptr->DecreaseReference();
				ptr = nullptr;
			}
		}

		template <class Y>
		ReferenceCountPtr<Y> StaticCastTo() const
		{
			ReferenceCountPtr<Y> result(static_cast<Y*>(ptr), Ownership::Acquire);
			return result;
		}

		template <class Y>
		ReferenceCountPtr<Y> DynamicCastTo() const
		{
			ReferenceCountPtr<Y> result(dynamic_cast<Y*>(ptr), Ownership::Acquire);
			return result;
		}

	private:

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		void CopyIn(ReferenceCountPtr<Y> const& other) noexcept
		{
			if (other.ptr)
			{
				other.ptr->IncreaseReference();
			}
			if (ptr)
			{
				ptr->DecreaseReference();
			}
			ptr = other.ptr;
		}

		void MoveIn(ReferenceCountPtr&& other) noexcept
		{
			if (this != &other)
			{
				if (ptr)
				{
					ptr->DecreaseReference();
				}
				ptr = other.ptr;
				other.ptr = nullptr;
			}
		}
		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		void MoveIn(ReferenceCountPtr<Y>&& other) noexcept
		{
			if (ptr)
			{
				ptr->DecreaseReference();
			}
			ptr = other.ptr;
			other.ptr = nullptr;
		}

	private:
		T* ptr = nullptr;
	};



	template <class T1, class T2>
	constexpr bool operator==(ReferenceCountPtr<T1> const& left, ReferenceCountPtr<T2> const& right) noexcept
	{
		using Common = std::common_type_t<T1*, T2*>;
		return static_cast<Common>(left.Get()) == static_cast<Common>(right.Get());
	}

	template <class T1, class T2>
	constexpr bool operator!=(ReferenceCountPtr<T1> const& left, ReferenceCountPtr<T2> const& right) noexcept
	{
		return !(left == right);
	}

	template <class T1, class T2>
	constexpr bool operator<(ReferenceCountPtr<T1> const& left, ReferenceCountPtr<T2> const& right) noexcept
	{
		using Common = std::common_type_t<T1*, T2*>;
		return static_cast<Common>(left.Get()) < static_cast<Common>(right.Get());
	}

	template <class T1, class T2>
	constexpr bool operator>=(ReferenceCountPtr<T1> const& left, ReferenceCountPtr<T2> const& right) noexcept
	{
		return !(left < right);
	}

	template <class T1, class T2>
	constexpr bool operator>(ReferenceCountPtr<T1> const& left, ReferenceCountPtr<T2> const& right) noexcept
	{
		return right < left;
	}

	template <class T1, class T2>
	constexpr bool operator<=(ReferenceCountPtr<T1> const& left, ReferenceCountPtr<T2> const& right) noexcept
	{
		return !(right < left);
	}

	template <class T>
	constexpr bool operator==(ReferenceCountPtr<T> const& left, nullptr_t) noexcept
	{
		return !left;
	}

	template <class T>
	constexpr bool operator==(nullptr_t, ReferenceCountPtr<T> const& right) noexcept
	{
		return !right;
	}

	template <class T>
	constexpr bool operator!=(ReferenceCountPtr<T> const& left, nullptr_t right) noexcept
	{
		return !(left == right);
	}

	template <class T>
	constexpr bool operator!=(nullptr_t left, ReferenceCountPtr<T> const& right) noexcept
	{
		return !(left == right);
	}

	template <class T>
	constexpr bool operator<(ReferenceCountPtr<T> const& left, nullptr_t right) noexcept
	{
		return left.Get() < static_cast<T*>(right);
	}

	template <class T>
	constexpr bool operator<(nullptr_t left, ReferenceCountPtr<T> const& right) noexcept
	{
		return static_cast<T*>(left) < right.Get();
	}

	template <class T>
	constexpr bool operator>=(ReferenceCountPtr<T> const& left, nullptr_t right) noexcept
	{
		return !(left < right);
	}

	template <class T>
	constexpr bool operator>=(nullptr_t left, ReferenceCountPtr<T> const& right) noexcept
	{
		return !(left < right);
	}

	template <class T>
	constexpr bool operator>(ReferenceCountPtr<T> const& left, nullptr_t right) noexcept
	{
		return right < left;
	}

	template <class T>
	constexpr bool operator>(nullptr_t left, ReferenceCountPtr<T> const& right) noexcept
	{
		return right < left;
	}

	template <class T>
	constexpr bool operator<=(ReferenceCountPtr<T> const& left, nullptr_t right) noexcept
	{
		return !(right < left);
	}

	template <class T>
	constexpr bool operator<=(nullptr_t left, ReferenceCountPtr<T> const& right) noexcept
	{
		return !(right < left);
	}

	template <class T, class... Args>
	ReferenceCountPtr<T> CreatePtr(Args... args)
	{
		return ReferenceCountPtr<T>(new T(std::forward<Args>(args)...), Ownership::Transfer);
	}

	template <class T>
	using Ptr = ReferenceCountPtr<T>;
}
