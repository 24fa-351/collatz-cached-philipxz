#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "collatz.h"
#include "cache.h"

unsigned long long random_num(int max_num, int min_num)
{
    return rand() % (max_num - min_num + 1) + min_num;
}

int main(int argc, char *argv[])
{

    int N = atoi(argv[1]);
    unsigned long long MIN = strtoull(argv[2], NULL, 10);
    unsigned long long MAX = strtoull(argv[3], NULL, 10);
    char *cache_policy = argv[4];
    int cache_size = atoi(argv[5]);

    srand(time(NULL));

    CachePolicy policy;
    if (strcmp(cache_policy, "LRU") == 0)
    {
        policy = LRU;
    }
    else if (strcmp(cache_policy, "LFU") == 0)
    {
        policy = LFU;
    }
    else
    {
        policy = NONE;
    }

    Cache *cache = init_cache(policy, cache_size);

    FILE *file = fopen("collatz_results.csv", "w");
    fprintf(file, "Number,Steps\n");

    for (int i = 0; i < N; i++)
    {
        unsigned long long random_number = random_num(MAX, MIN);
        int steps = cache_lookup(cache, random_number);

        if (steps == 0)
        {
            steps = collatz_steps(random_number);
            cache_insert(cache, random_number, steps);
        }

        fprintf(file, "%llu,%d\n", random_number, steps);
    }

    fclose(file);

    printf("Cache hit rate: %.2f%%\n", (float)cache->hits / (cache->hits + cache->misses) * 100);

    free_cache(cache);

    return 0;
}
