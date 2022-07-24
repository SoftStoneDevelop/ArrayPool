#include <cstdlib>
#include "ArrayPool.hpp"

int main()
{
	for (int i = 0; i < 20000; i++)
	{
		auto pool = ArrayPool::ArrayPool<int>();
		int realSize = 0;
		auto arr = pool.Rent(10, realSize);
		pool.Return(arr);

		realSize = 0;
		auto arr2 = pool.Rent(8, realSize);
		pool.Return(arr2);
	}

	return EXIT_SUCCESS;
}