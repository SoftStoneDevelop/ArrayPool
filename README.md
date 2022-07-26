# ArrayPool

A simple thread safety pool of arrays.
If the array in the pool is not used for more than 60 seconds, then it will be deleted.

Usage:

```C++

auto pool = ArrayPool::ArrayPool<int>();
int realSize = 0;

auto arr = pool.Rent(10, realSize);
//arr array realSize equal to 10, because poll was empty when we rent him
pool.Return(arr);

auto arr2 = pool.Rent(5, realSize);
//arr array realSize is still equal to 10, because pool have free array with size 10
pool.Return(arr2);

using namespace std::literals::chrono_literals;
std::this_thread::sleep_for(120s);
//now the pool is empty, because arrays have not been used for too long

```
