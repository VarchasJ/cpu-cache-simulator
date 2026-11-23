#include "cache.h"
#include <stdio.h>
#include <stdlib.h>

Cache *cache_create(int s, int E, int b, ReplacementPolicy policy) {
    // TODO: Allocate Cache struct, compute num_sets = (1ULL << s),
    //       allocate sets[num_sets][E] initialized to valid = false.
    (void)s; (void)E; (void)b; (void)policy;
    return NULL;
}

void cache_destroy(Cache *cache) {
    // TODO: Free each set and the Cache struct itself.
    (void)cache;
}

void cache_access(Cache *cache, uint64_t address) {
    // TODO:
    // 1. Increment cache->clock
    // 2. Extract set_index and tag from `address` using cache->s and cache->b
    // 3. Scan cache->sets[set_index][0..E-1] for a valid line with matching tag (HIT)
    // 4. On MISS:
    //    - Look for an invalid (empty) line first
    //    - If none, evict victim based on cache->policy (LRU or FIFO) and increment evictions
    (void)cache; (void)address;
}

void cache_print_stats(const Cache *cache) {
    if (!cache) return;
    uint64_t total = cache->hits + cache->misses;
    double miss_rate = total > 0 ? (100.0 * cache->misses / total) : 0.0;
    printf("hits:%llu misses:%llu evictions:%llu miss_rate:%.2f%%\n",
           (unsigned long long)cache->hits,
           (unsigned long long)cache->misses,
           (unsigned long long)cache->evictions,
           miss_rate);
}
