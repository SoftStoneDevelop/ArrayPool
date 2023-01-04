#include <cstdlib>
#include <iostream>

#include "ArrayPool.hpp"
#include "MemoryOwnerFactory.hpp"

int main()
{
	std::cout << "Start press enter" << std::endl;
	std::cin.get();
	//Usage example 1
	{
		auto pool = ArrayPool::ArrayPool<int>();
		int realSize = 0;

		std::cout << "Start 'rent and release' loop 2000000" << std::endl;
		for (int i = 0; i < 200000; i++)
		{
			realSize = 0;
			auto arr = pool.Rent(10, realSize);
			pool.Return(arr);

			realSize = 0;
			auto arr2 = pool.Rent(8, realSize);
			pool.Return(arr2);
		}

		std::cout << "End loop" << std::endl;
	}
	std::cin.get();

	//Usage example 2
	{
		auto pool = std::make_shared<ArrayPool::ArrayPool<int>>();
		ArrayPool::MemoryOwnerFactory<int> memoryFactory(std::move(pool));

		std::cout << "Start 'rentMemory' Loop 2000000" << std::endl;
		for (int i = 0; i < 200000; i++)
		{
			ArrayPool::MemoryOwner<int> arr = memoryFactory.rentMemory(10);
			ArrayPool::MemoryOwner<int> arr2 = memoryFactory.rentMemory(8);
		}//return memory to pool in destructor automatically

		std::cout << "End 'rentMemory' Loop" << std::endl;
	}

	//Usage example 2
	{
		auto pool = std::make_shared<ArrayPool::ArrayPool<int>>();
		ArrayPool::MemoryOwnerFactory<int> memoryFactory(std::move(pool));

		std::cout << "Start 'rentMemory' Loop 2000000" << std::endl;
		for (int i = 0; i < 200000; i++)
		{
			ArrayPool::MemoryOwner<int>* arr = memoryFactory.newRentMemory(10);
			ArrayPool::MemoryOwner<int>* arr2 = memoryFactory.newRentMemory(8);

			//return memory to pool manual
			delete arr;
			delete arr2;
		}

		std::cout << "End 'rentMemory' Loop" << std::endl;
	}

	std::cin.get();

	return EXIT_SUCCESS;
}