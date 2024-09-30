#include "collatz.h"
#include "cache.h"



unsigned long long collatz_steps(unsigned long long n)
{
    unsigned long long steps = 0;
    while (n != 1)
    {
        if (n % 2 == 0)
        {
            n /= 2;
        }
        else
        {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

int cached_collatz(Cache *cache, unsigned long long n)
{
    int result = cache_lookup(cache, n);
    if (result != 0)
        return result;

    result = collatz_steps(n);
    cache_insert(cache, n, result);
    return result;
}
