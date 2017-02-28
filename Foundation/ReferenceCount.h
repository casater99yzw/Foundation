#pragma once
#include "BaseType.h"
#include <atomic>

namespace X
{
	template <bool ThreadSafe = false>
	class ReferenceCountBase;

	template <>
	class ReferenceCountBase<true>
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

		virtual void OnRelease() noexcept
		{
			delete this;
		}

		virtual ~ReferenceCountBase() noexcept = 0
		{
#ifdef MemoryDebug
			Count() -= 1;
#endif // MemoryDebug
		}

	private:
		std::atomic<sint32> counter = 1;
	};


	template <>
	class ReferenceCountBase<false>
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

	private:
		virtual void OnRelease() noexcept
		{
			delete this;
		}

		sint32 counter = 1;
	};

	namespace Ownership
	{
		struct AcquireT
		{
		} Acquire;

		struct TransferT
		{
		} Transfer;
	}

	template <class T, bool ThreadSafe = false, class = std::enable_if_t<std::is_base_of<ReferenceCountBase<ThreadSafe>, T>::value>>
	class ReferenceCountPtr
	{
	public:
		template <class Y, bool ThreadSafe, class = std::enable_if_t<std::is_base_of<ReferenceCountBase<ThreadSafe>, T>::value>>
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
		ReferenceCountPtr(ReferenceCountPtr<Y, ThreadSafe> const& other) noexcept
		{
			CopyIn(other);
		}

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		ReferenceCountPtr(ReferenceCountPtr<Y, ThreadSafe>&& other) noexcept
		{
			MoveIn(std::move(other));
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
		ReferenceCountPtr& operator=(ReferenceCountPtr<Y, ThreadSafe> const& other) noexcept
		{
			CopyIn(other);
			return *this;
		}

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		ReferenceCountPtr& operator=(ReferenceCountPtr<Y, ThreadSafe>&& other) noexcept
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

	private:

		template <class Y, class = std::enable_if_t<std::is_convertible<Y*, T*>::value>>
		void CopyIn(ReferenceCountPtr<Y, ThreadSafe> const& other) noexcept
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
		void MoveIn(ReferenceCountPtr<Y, ThreadSafe>&& other) noexcept
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



	template <class T1, class T2, bool ThreadSafe>
	constexpr bool operator==(ReferenceCountPtr<T1, ThreadSafe> const& left, ReferenceCountPtr<T2, ThreadSafe> const& right) noexcept
	{
		using Common = std::common_type_t<T1*, T2*>;
		return static_cast<Common>(left.Get()) == static_cast<Common>(right.Get());
	}

	template <class T1, class T2, bool ThreadSafe>
	constexpr bool operator!=(ReferenceCountPtr<T1, ThreadSafe> const& left, ReferenceCountPtr<T2, ThreadSafe> const& right) noexcept
	{
		return !(left == right);
	}

	template <class T1, class T2, bool ThreadSafe>
	constexpr bool operator<(ReferenceCountPtr<T1, ThreadSafe> const& left, ReferenceCountPtr<T2, ThreadSafe> const& right) noexcept
	{
		using Common = std::common_type_t<T1*, T2*>;
		return static_cast<Common>(left.Get()) < static_cast<Common>(right.Get());
	}

	template <class T1, class T2, bool ThreadSafe>
	constexpr bool operator>=(ReferenceCountPtr<T1, ThreadSafe> const& left, ReferenceCountPtr<T2, ThreadSafe> const& right) noexcept
	{
		return !(left < right);
	}

	template <class T1, class T2, bool ThreadSafe>
	constexpr bool operator>(ReferenceCountPtr<T1, ThreadSafe> const& left, ReferenceCountPtr<T2, ThreadSafe> const& right) noexcept
	{
		return right < left;
	}

	template <class T1, class T2, bool ThreadSafe>
	constexpr bool operator<=(ReferenceCountPtr<T1, ThreadSafe> const& left, ReferenceCountPtr<T2, ThreadSafe> const& right) noexcept
	{
		return !(right < left);
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator==(ReferenceCountPtr<T, ThreadSafe> const& left, nullptr_t) noexcept
	{
		return !left;
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator==(nullptr_t, ReferenceCountPtr<T, ThreadSafe> const& right) noexcept
	{
		return !right;
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator!=(ReferenceCountPtr<T, ThreadSafe> const& left, nullptr_t right) noexcept
	{
		return !(left == right);
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator!=(nullptr_t left, ReferenceCountPtr<T, ThreadSafe> const& right) noexcept
	{
		return !(left == right);
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator<(ReferenceCountPtr<T, ThreadSafe> const& left, nullptr_t right) noexcept
	{
		return left.Get() < static_cast<T*>(right);
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator<(nullptr_t left, ReferenceCountPtr<T, ThreadSafe> const& right) noexcept
	{
		return static_cast<T*>(left) < right.Get();
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator>=(ReferenceCountPtr<T, ThreadSafe> const& left, nullptr_t right) noexcept
	{
		return !(left < right);
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator>=(nullptr_t left, ReferenceCountPtr<T, ThreadSafe> const& right) noexcept
	{
		return !(left < right);
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator>(ReferenceCountPtr<T, ThreadSafe> const& left, nullptr_t right) noexcept
	{
		return right < left;
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator>(nullptr_t left, ReferenceCountPtr<T, ThreadSafe> const& right) noexcept
	{
		return right < left;
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator<=(ReferenceCountPtr<T, ThreadSafe> const& left, nullptr_t right) noexcept
	{
		return !(right < left);
	}

	template <class T, bool ThreadSafe>
	constexpr bool operator<=(nullptr_t left, ReferenceCountPtr<T, ThreadSafe> const& right) noexcept
	{
		return !(right < left);
	}

}
