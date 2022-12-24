#pragma once
#include <map>
#include <unordered_map>
#include <thread>
#include <future>

namespace ArrayPool
{
	template<typename T>
	class ArrayPool
	{
	public:
		ArrayPool() : _requestDestruct{false}
		{
			_timer = std::thread (&ArrayPool<T>::timerRoutine, this);
		}
		ArrayPool(const ArrayPool<T>& other) = delete;
		ArrayPool(ArrayPool<T>&& other) = delete;

		ArrayPool<T>& operator=(ArrayPool<T>&& other) = delete;
		ArrayPool<T>& operator=(const ArrayPool<T>& other) = delete;

		~ArrayPool()
		{
			_requestDestruct = true;
			_cv.notify_all();
			_timer.join();

			for (auto i = _freeArrays.begin(); i != _freeArrays.end(); i++)
			{
				delete[](*i).second._ptr;
			}

			for (auto i = _rentedArrays.begin(); i != _rentedArrays.end(); i++)
			{
				delete[](*i).second._ptr;
			}
		}

		T* Rent(int size, int& realSize)
		{
			std::lock_guard lg(_m);

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

			std::lock_guard lg(_m);
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

		void timerRoutine()
		{
			using namespace std::literals::chrono_literals;

			while (waitFor(60s))
			{
				std::lock_guard lg(_m);
				for (auto i = _freeArrays.begin(); i != _freeArrays.end(); i++)
				{
					delete[](*i).second._ptr;
				}

				_freeArrays.clear();
			}
		}

		template<typename R, typename P>
		bool waitFor(std::chrono::duration<R, P> const& time) 
		{
			std::unique_lock<std::mutex> lock(_m);
			return !_cv.wait_for(lock, time, [&] {return _requestDestruct; });
		}

		std::map<int, Bucket> _freeArrays;
		std::unordered_map<T*, Bucket> _rentedArrays;
		
		std::thread _timer;
		volatile bool _requestDestruct;
		std::mutex _m;
		std::condition_variable _cv;
	};
}