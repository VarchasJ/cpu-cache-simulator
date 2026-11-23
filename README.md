# CPU Cache Simulator & Trace Analyzer

A trace-driven L1 CPU cache simulator written in **C**, paired with a **SQLite** telemetry store and **Python** parameter-sweep & visualization scripts.

## Features
- Configurable cache geometry: set index bits (`-s`), associativity (`-E`), block offset bits (`-b`)
- Replacement policies: `LRU` and `FIFO`
- Telemetry logging to SQLite (`runs` table) for hit/miss/eviction analysis
- Automated parameter-sweep & plotting in Python

## Quick Start
```bash
# Build with AddressSanitizer + UndefinedBehaviorSanitizer
make sanitize

# Run on the sample trace
./build/cache_sim -s 2 -E 1 -b 2 -p LRU -t traces/sample.trace
```

## Project Structure
- `src/` — Core C cache simulator (`cache.h`, `cache.c`, `main.c`)
- `db/` — SQLite schema (`schema.sql`)
- `scripts/` — Synthetic trace generator & parameter-sweep analyzer
- `traces/` — Sample and generated memory access traces

## AI Usage & Verification
> **Human-Authored Core:** Bitmask extraction (`tag` / `set` / `offset`), set-associative cache layout, and `LRU`/`FIFO` eviction policies in `src/cache.c`.  
> **AI-Assisted:** Project scaffolding, synthetic trace generation, and `matplotlib` plotting boilerplate.  
> **Verification:** Hand-verified against `traces/sample.trace` and compiled with `-fsanitize=address,undefined`.
