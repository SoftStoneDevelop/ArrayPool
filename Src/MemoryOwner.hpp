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
		MemoryOwner(std::shared_ptr<ArrayPool::ArrayPool<T>> pool, const int size)
			: pool_{ std::move(pool) }, size_{ size }, data_{nullptr}
		{
			data_ = pool_->Rent(size_, realSize_);
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
			: pool_{ std::move(other.pool_) }, size_{ other.size_ }, data_{ other.data_ }, realSize_{other.realSize_}
		{
			other.data_ = nullptr;
		}

		MemoryOwner& operator=(MemoryOwner&& other)
		{
			pool_ = std::move(other.pool_);
			size_ = other.size_;
			realSize_ = other.realSize_;
			data_ = other.data_;

			other.data_ = nullptr;
			
			return *this;
		}
		MemoryOwner& operator=(const MemoryOwner& other) = delete;

		const int size() const noexcept
		{
			return size_;
		}

		const int realSize() const noexcept
		{
			return realSize_;
		}

		T* const data() const noexcept
		{
			return data_;
		}
	private:
		std::shared_ptr<ArrayPool::ArrayPool<T>> pool_;
		int size_;
		int realSize_;
		T* data_;
	};
}