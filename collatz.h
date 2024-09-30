#ifndef COLLATZ_H
#define COLLATZ_H
#include "cache.h"

unsigned long long collatz_steps(unsigned long long n);
int cached_collatz(Cache *cache, unsigned long long n);

#endif
