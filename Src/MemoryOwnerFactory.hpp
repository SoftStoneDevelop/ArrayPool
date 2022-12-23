#pragma once
#include "MemoryOwner.hpp"

namespace ArrayPool
{
	template<typename T>
	class MemoryOwnerFactory
	{
	public:
		MemoryOwnerFactory(std::shared_ptr<ArrayPool::ArrayPool<T>> pool) noexcept : pool_{std::move(pool)}
		{

		}

		MemoryOwner<T> rentMemory(const int size)
		{
			return MemoryOwner<char>(pool_, size);
		}

	private:
		std::shared_ptr<ArrayPool::ArrayPool<T>> pool_;
	};
}