#pragma once
#include "MemoryOwner.hpp"

namespace ArrayPool
{
	template<typename T>
	class MemoryOwnerFactory
	{
	public:
		MemoryOwnerFactory(std::shared_ptr<ArrayPool<T>> pool) noexcept : pool_{std::move(pool)}
		{

		}

		MemoryOwner<T> rentMemory(const int size) const
		{
			return MemoryOwner<T>(pool_, size);
		}

		MemoryOwner<T>* newRentMemory(const int size) const
		{
			return new MemoryOwner<T>(pool_, size);
		}

	private:
		std::shared_ptr<ArrayPool<T>> pool_;
	};
}