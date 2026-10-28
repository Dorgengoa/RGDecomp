# SPDX-License-Identifier: CC0-1.0
"""Pack the one-save library cards (out/fixtures/cards/<name>/card1/...) into ONE memory
card with a file per save, for play-testing (CONTINUE -> Slot 1 -> FILE NN).

    python tools/fixtures/make_allcard.py [--cards out/fixtures/cards] [--out out/playtest/saves-all]

The port's card layer scans the host directory, so no card1.card metadata is needed; each
save is renamed BASCUS-97490LV5RG_NN (dir and data file).  Order: save2, the chapter cards,
then the side cards; save1 is skipped.  Writes <out>/FILES.txt (FILE number -> card name).
"""
import argparse
import pathlib
import shutil

PORT = pathlib.Path(__file__).resolve().parents[2]
SIDE = ["alistia", "ghost_ship", "ghost_ship_ex", "space_deck", "late_game", "factory", "insectron", "insect_final",
        "factory_prod"]


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--cards", default=str(PORT / "out" / "fixtures" / "cards"))
    ap.add_argument("--out", default=str(PORT / "out" / "playtest" / "saves-all"))
    a = ap.parse_args()
    src, out = pathlib.Path(a.cards), pathlib.Path(a.out)
    names = sorted(p.name for p in src.iterdir() if (p / "card1").is_dir() and p.name != "save1")
    order = (["save2"] if "save2" in names else []) + [n for n in names if n.startswith("ch")]
    order += [n for n in SIDE if n in names]
    order += [n for n in names if n not in order]
    if out.exists():
        shutil.rmtree(out)
    dst = out / "card1"
    dst.mkdir(parents=True)
    lines = []
    for i, name in enumerate(order):
        sd = next(p for p in (src / name / "card1").iterdir() if p.is_dir())
        nn = f"BASCUS-97490LV5RG_{i:02d}"
        d = dst / nn
        d.mkdir()
        for f in ("icon.sys", "RG.ICO"):
            shutil.copy(sd / f, d)
        shutil.copy(sd / sd.name, d / nn)
        lines.append(f"FILE {i + 1:02d}  {name}")
    (out / "FILES.txt").write_text("\n".join(lines) + "\n")
    print("\n".join(lines))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
