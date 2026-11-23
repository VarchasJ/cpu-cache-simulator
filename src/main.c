#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s -s <s> -E <E> -b <b> -p <LRU|FIFO> -t <trace_file>\n", prog);
}

int main(int argc, char *argv[]) {
    int s = -1, E = -1, b = -1;
    ReplacementPolicy policy = POLICY_LRU;
    const char *trace_path = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            s = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-E") == 0 && i + 1 < argc) {
            E = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            b = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            const char *p = argv[++i];
            if (strcmp(p, "LRU") == 0) policy = POLICY_LRU;
            else if (strcmp(p, "FIFO") == 0) policy = POLICY_FIFO;
            else {
                fprintf(stderr, "Unknown policy: %s\n", p);
                return 1;
            }
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            trace_path = argv[++i];
        } else {
            print_usage(argv[0]);
            return 1;
        }
    }

    if (s < 0 || E <= 0 || b < 0 || !trace_path) {
        print_usage(argv[0]);
        return 1;
    }

    FILE *fp = fopen(trace_path, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    Cache *cache = cache_create(s, E, b, policy);
    if (!cache) {
        fprintf(stderr, "cache_create returned NULL (implement it in src/cache.c)\n");
        fclose(fp);
        return 1;
    }

    // TODO: Parse trace lines of format "<op> <hex_address>,<size>" (e.g., "L 0x10,4")
    //       and call cache_access(cache, addr) (note: 'M' = load + store = 2 accesses).

    cache_print_stats(cache);
    cache_destroy(cache);
    fclose(fp);
    return 0;
}
