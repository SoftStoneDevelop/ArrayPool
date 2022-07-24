#include <cstdlib>
#include "ArrayPool.hpp"
#include <iostream>

int main()
{
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

	return EXIT_SUCCESS;
}