#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
    POLICY_LRU,
    POLICY_FIFO
} ReplacementPolicy;

typedef struct {
    bool valid;
    uint64_t tag;
    uint64_t last_used;   // For LRU
    uint64_t inserted_at; // For FIFO
} CacheLine;

typedef struct {
    int s;                  // Number of set index bits (S = 2^s sets)
    int E;                  // Associativity (lines per set)
    int b;                  // Number of block offset bits (B = 2^b bytes)
    ReplacementPolicy policy;

    size_t num_sets;
    CacheLine **sets;       // 2D array: [num_sets][E]

    uint64_t clock;         // Monotonic access counter
    uint64_t hits;
    uint64_t misses;
    uint64_t evictions;
} Cache;

Cache *cache_create(int s, int E, int b, ReplacementPolicy policy);
void cache_destroy(Cache *cache);
void cache_access(Cache *cache, uint64_t address);
void cache_print_stats(const Cache *cache);

#endif // CACHE_H
