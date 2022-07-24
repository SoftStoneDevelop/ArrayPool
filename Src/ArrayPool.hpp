#pragma once
#include <map>
#include <unordered_map>

namespace ArrayPool
{
	template<typename T>
	class ArrayPool
	{
	public:
		ArrayPool() = default;
		ArrayPool(const ArrayPool& other) = delete;
		ArrayPool(const ArrayPool&& other) = delete;

		ArrayPool& operator=(ArrayPool&& other) = delete;
		ArrayPool& operator=(const ArrayPool& other) = delete;

		~ArrayPool()
		{
			for (auto i = _freeArrays.begin(); i != _freeArrays.end(); i++)
			{
				delete[](*i).second._ptr;
			}

			for (auto i = _rentedArrays.begin(); i != _rentedArrays.end(); i++)
			{
				delete[](*i).second._ptr;
			}
		}

		int* Rent(const int& size, int& realSize)
		{
			auto upiter = _freeArrays.upper_bound(size - 1);
			T* result;

			if (upiter == _freeArrays.end())
			{
				result = new T[size];
				_rentedArrays.emplace(result, Bucket{ result, size });
				realSize = size;

				return result;
			}
			else
			{
				auto& bucket = *upiter;
				result = bucket.second._ptr;
				realSize = bucket.second._size;
				_rentedArrays.emplace(result, bucket.second);
				_freeArrays.erase(upiter);

				return result;
			}
		}

		bool Return(T* arr)
		{
			auto finded = _rentedArrays.find(arr);
			if (finded == _rentedArrays.end())
			{
				return false;
			}

			auto& bucket = *finded;
			_freeArrays.insert(std::pair<int, Bucket>(bucket.second._size, bucket.second));
			_rentedArrays.erase(finded);

			return true;
		}

	private:
		struct Bucket
		{
			T* _ptr;
			int _size;
		};

		std::map<int, Bucket> _freeArrays;
		std::unordered_map<T*, Bucket> _rentedArrays;
	};
}