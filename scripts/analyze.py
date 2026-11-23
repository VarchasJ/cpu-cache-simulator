"""Sweep cache configs, run the C simulator, and log results to SQLite."""
import re
import sqlite3
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BIN = ROOT / "build" / "cache_sim"
DB_PATH = ROOT / "db" / "telemetry.db"
SCHEMA_PATH = ROOT / "db" / "schema.sql"


def init_db(conn: sqlite3.Connection) -> None:
    conn.executescript(SCHEMA_PATH.read_text())


def run_sim(s: int, E: int, b: int, policy: str, trace: Path) -> dict:
    cmd = [str(BIN), "-s", str(s), "-E", str(E), "-b", str(b), "-p", policy, "-t", str(trace)]
    out = subprocess.check_output(cmd, text=True).strip()
    m = re.search(r"hits:(\d+) misses:(\d+) evictions:(\d+) miss_rate:([\d.]+)%", out)
    if not m:
        raise ValueError(f"Unexpected output: {out}")
    return {
        "hits": int(m.group(1)),
        "misses": int(m.group(2)),
        "evictions": int(m.group(3)),
        "miss_rate": float(m.group(4)),
    }


if __name__ == "__main__":
    trace = ROOT / "traces" / "sample.trace"
    with sqlite3.connect(DB_PATH) as conn:
        init_db(conn)
        for E in (1, 2, 4):
            res = run_sim(s=2, E=E, b=2, policy="LRU", trace=trace)
            conn.execute(
                "INSERT INTO runs (trace_name, s, E, b, policy, hits, misses, evictions, miss_rate) "
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)",
                (trace.name, 2, E, 2, "LRU", res["hits"], res["misses"], res["evictions"], res["miss_rate"]),
            )
            print(f"E={E}: {res}")
