#ifndef CACHE_H
#define CACHE_H

typedef enum
{
    NONE,
    LRU,
    LFU
} CachePolicy;

typedef struct
{
    unsigned long long key;
    int value;
    int frequency; //LFU
    int order;     //LRU
} CacheEntry;

typedef struct
{
    CacheEntry *entries;
    int size;
    int current_order; //LRU
    int hits;
    int misses;
    CachePolicy policy;
} Cache;

Cache *init_cache(CachePolicy policy, int size);
int cache_lookup(Cache *cache, unsigned long long key);
void cache_insert(Cache *cache, unsigned long long key, int value);
void free_cache(Cache *cache);

#endif
