#pragma once
#include "ArrayPool.hpp"
#include <memory>
#include <utility>

namespace ArrayPool
{
	template<typename T>
	class MemoryOwner
	{
	public:
		MemoryOwner()
			: pool_{ nullptr }, size_{ 0 }, data_{ nullptr }
		{
		}
		
		MemoryOwner(std::shared_ptr<ArrayPool::ArrayPool<T>> pool, int size)
			: pool_{ std::move(pool) }, data_{nullptr}
		{
			data_ = pool_->Rent(size, size_);
		}

		~MemoryOwner()
		{
			if (data_)
			{
				pool_->Return(data_);
			}
		}

		MemoryOwner(const MemoryOwner& other) = delete;
		MemoryOwner(MemoryOwner&& other) 
			: pool_{ std::move(other.pool_) }, size_{ other.size_ }, data_{ other.data_ }
		{
			other.data_ = nullptr;
		}

		MemoryOwner& operator=(MemoryOwner&& other)
		{
			pool_ = std::move(other.pool_);
			size_ = other.size_;
			data_ = other.data_;

			other.data_ = nullptr;
			
			return *this;
		}
		MemoryOwner& operator=(const MemoryOwner& other) = delete;

		const int size() const noexcept
		{
			return size_;
		}

		T* const data() const noexcept
		{
			return data_;
		}
	private:
		std::shared_ptr<ArrayPool::ArrayPool<T>> pool_;
		int size_;
		T* data_;
	};
}