#include <stdlib.h>
#include <string.h>
#include "cache.h"

Cache *init_cache(CachePolicy policy, int size)
{
    Cache *cache = malloc(sizeof(Cache));
    cache->entries = malloc(sizeof(CacheEntry) * size);
    cache->size = size;
    cache->current_order = 0;
    cache->hits = 0;
    cache->misses = 0;
    cache->policy = policy;
    
    return cache;
}

int cache_lookup(Cache *cache, unsigned long long key)
{
    for (int i = 0; i < cache->size; i++)
    {
        if (cache->entries[i].key == key)
        {
            if (cache->policy == LRU)
            {
                cache->current_order++;
                cache->entries[i].order = cache->current_order;
            }
            else if (cache->policy == LFU)
            {
                cache->entries[i].frequency++;
            }
            cache->hits++;
            return cache->entries[i].value;
        }
    }
    cache->misses++;
    return 0;
}

// Insert a key-value pair into the cache
void cache_insert(Cache *cache, unsigned long long key, int value)
{
    int index = 0;

    if (cache->misses < cache->size)
    {
        index = cache->misses;
    }
    else
    {
        if (cache->policy == LRU)
        {
            int oldest_order = cache->entries[0].order;
            for (int i = 1; i < cache->size; i++)
            {
                if (cache->entries[i].order < oldest_order)
                {
                    oldest_order = cache->entries[i].order;
                    index = i;
                }
            }
        }
        else if (cache->policy == LFU)
        {
            int least_frequency = cache->entries[0].frequency;
            for (int i = 1; i < cache->size; i++)
            {
                if (cache->entries[i].frequency < least_frequency)
                {
                    least_frequency = cache->entries[i].frequency;
                    index = i;
                }
            }
        }
    }

    cache->current_order++;
    cache->entries[index].key = key;
    cache->entries[index].value = value;
    cache->entries[index].frequency = (cache->policy == LFU) ? 1 : cache->entries[index].frequency;
    cache->entries[index].order = (cache->policy == LRU) ? cache->current_order : cache->entries[index].order;
}

void free_cache(Cache *cache)
{
    free(cache->entries);
    free(cache);
}
