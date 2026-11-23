"""Synthetic memory trace generator for stress-testing the cache simulator."""
import random
from pathlib import Path

TRACES_DIR = Path(__file__).resolve().parent.parent / "traces"


def write_trace(filename: str, addresses: list[int]) -> None:
    path = TRACES_DIR / filename
    with path.open("w") as f:
        for addr in addresses:
            f.write(f"L 0x{addr:08x},4\n")
    print(f"Wrote {len(addresses)} accesses -> {path}")


if __name__ == "__main__":
    TRACES_DIR.mkdir(exist_ok=True)
    write_trace("sequential.trace", [0x1000 + i * 4 for i in range(1000)])
    write_trace("strided.trace", [0x1000 + (i * 64) % 4096 for i in range(1000)])
    random.seed(42)
    write_trace("random.trace", [random.randrange(0x1000, 0x8000, 4) for _ in range(1000)])
