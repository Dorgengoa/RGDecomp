"""Shared loader for the bring-up censuses: the pinned snapshot's retail listings
(protos.snapshot_addr_table), cached in out/bringup-checkpoint/.listings.pickle."""
import pickle, sys
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "stages"))
import protos  # noqa: E402

SRC = r"../RGDecomp/.git"
REV = "675c07feec314d493f9cc3d51f511bc7eb6ca07d"
CACHE = PORT / "out" / "bringup-checkpoint" / ".listings.pickle"


def table():
    if CACHE.exists():
        with open(CACHE, "rb") as f:
            t = pickle.load(f)
        if t.get("rev") == REV:
            return t
    t = protos.snapshot_addr_table(SRC, REV)
    with open(CACHE, "wb") as f:
        pickle.dump(t, f)
    return t


def all_listings(t=None):
    """[(img, fn, text)] for MAIN and every overlay."""
    t = t or table()
    out = [("main", fn, tx) for fn, tx in (t.get("asm_text") or {}).items()]
    for ov, d in (t.get("ovl_text") or {}).items():
        out += [(ov, fn, tx) for fn, tx in d.items()]
    return out
