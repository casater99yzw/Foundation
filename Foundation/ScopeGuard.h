#pragma once
#include "BasicType.h"
#include <utility>

namespace X
{
	template <class T>
	struct DismissableScopeGuard
	{
		T callback;
		bool dismissed = false;
		DismissableScopeGuard(T&& c) : callback(std::move(c))
		{
		}
		~DismissableScopeGuard()
		{
			if (!dismissed)
			{
				callback();
			}
		}
		void Dismiss()
		{
			dismissed = true;
		}
		bool Dismissed() const
		{
			return dismissed;
		}

		DismissableScopeGuard(DismissableScopeGuard const&) = delete;
		DismissableScopeGuard operator=(DismissableScopeGuard const&) = delete;
		DismissableScopeGuard operator=(DismissableScopeGuard&&) = delete;

		DismissableScopeGuard(DismissableScopeGuard&& other) : callback(std::move(other.callback)), dismissed(other.dismissed)
		{
			other.dismissed = true;
		}
	};

	template <class T>
	DismissableScopeGuard<T> CreateScopeGuard(T&& callback)
	{
		return DismissableScopeGuard<T>(std::move(callback));
	}
}