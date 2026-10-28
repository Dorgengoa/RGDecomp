#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""ctest fixtures.saveedit: tools/fixtures/saveedit.py on a SYNTHETIC save file
(docs/SAVE-FORMAT.md; no game data, no rg-game).  Builds a 0x1BC00 data file
with the header, a summary and the chunk tree the editor walks (root 0 >
options 1, story state 2, characters 3 > 4, party 8 > 9 / 12 / 10 / 13, chara
sys 14, insect teams 15), then patches flags / vars / chapter / location / an
insect team and checks bit positions, summary mirrors and both MD5 digests
(the game's SaveHeaderValidate_3e5100 checks).
"""
from __future__ import annotations

import hashlib
import struct
import sys
import tempfile
from pathlib import Path

PORT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PORT / "tools" / "fixtures"))
import saveedit as se  # noqa: E402


def chunk(kind, payload, ver=0):
    return struct.pack("<III", kind, ver, len(payload)) + payload


def synth() -> bytes:
    sb = bytes(0x2324)
    party = bytearray(0x4CAC)
    struct.pack_into("<h", party, 0xF8 - 4, 201)
    inner = (chunk(1, bytes(0x2C)) + chunk(2, sb) + chunk(3, chunk(4, bytes(0x6B4), 1002))
             + chunk(8, chunk(9, bytes(party)) + chunk(12, bytes(0x33C0)) + chunk(10, bytes(0x114))
                     + chunk(13, bytes(0x800)))
             + chunk(14, bytes(0xB94)) + chunk(15, bytes(0x1188)))
    b = bytearray(se.SIZE)
    struct.pack_into("<hhhh", b, 0, -1, -1, se.VERSION, 0)
    root = chunk(0, inner)
    b[0x800:0x800 + len(root)] = root
    struct.pack_into("<q", b, 0x10, 0x800 + len(root) - 0x50)
    struct.pack_into("<q", b, 0x30, 0x300)
    return bytes(b)


def main() -> int:
    errs = []
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / "card1" / "BASCUS-97490LV5RG_00" / "BASCUS-97490LV5RG_00"
        f.parent.mkdir(parents=True)
        f.write_bytes(synth())
        if se.Save(f).check() == []:
            errs.append("synthetic file with zero digests passed check")
        rc = se.main(["patch", td, "--set-flag", "0x3E8", "--set-flag", "0x1EB", "--var", "5=3",
                      "--chapter", "4", "--location", "301", "--insect-team", "0:ALPHA:0,1,2,3,4"])
        b = f.read_bytes()
        s = se.Save(f)
        sbd = s.chunk(2)["data"]
        if rc != 0:
            errs.append(f"patch rc {rc}")
        if not b[sbd - 4 + 0x28 + 0x3E8 // 8] & (1 << (0x3E8 % 8)):
            errs.append("flag 0x3E8 not at StateBlock+0x28 bit 1000")
        if struct.unpack_from("<h", b, sbd - 4 + 0x128 + 10)[0] != 3:
            errs.append("var 5 not at StateBlock+0x132")
        if struct.unpack_from("<h", b, sbd - 4 + 8)[0] != 4:
            errs.append("chapter not at StateBlock+0x8")
        if struct.unpack_from("<Hh", b, 0x338) != (2, 3):
            errs.append(f"summary flags/var5 {struct.unpack_from('<Hh', b, 0x338)} != (2, 3)")
        if struct.unpack_from("<h", b, 0x20C)[0] != 4:
            errs.append("summary chapter")
        if struct.unpack_from("<h", b, s.chunk(9)["data"] + 0xF8 - 4)[0] != 301:
            errs.append("party location")
        t = s.chunk(15)["data"]
        if struct.unpack_from("<i", b, t)[0] != 1 or b[t + 4 + 0x10] & 1 != 1 or b[0x34E] != 1:
            errs.append("insect team count / used bit / summary count")
        if b[t + 4 + 0x18 + 0x28 * 3 + 0xD] != 3:
            errs.append("insect 4 species")
        n = struct.unpack_from("<q", b, 0x10)[0]
        if hashlib.md5(b[0x50:0x350]).digest() != b[0x40:0x50]:
            errs.append("summary MD5")
        if hashlib.md5(b[0x50:0x50 + n]).digest() != b[0x20:0x30]:
            errs.append("payload MD5")
        if s.check():
            errs.append("check: " + "; ".join(s.check()))
        # spawn: summary entries / camera / party +0x4 (what CONTINUE reads,
        # SysMsgFillFromSaveRecMaybe_3e4d10)
        rc = se.main(["patch", td, "--spawn", "3:-271.11,2.55,12000.07,1.57"])
        s = se.Save(f)
        b = f.read_bytes()
        if rc != 0 or s.party_s16(0x4) != 3 or struct.unpack_from("<h", b, 0x31C)[0] != 3:
            errs.append("spawn planet (party +0x4 / summary 0x31C)")
        x, y, z, yaw = struct.unpack_from("<4f", b, 0x64 + 0x18)
        if abs(x + 271.11) > 0.01 or abs(z - 12000.07) > 0.01 or abs(yaw - 1.57) > 1e-4:
            errs.append(f"spawn summary entry 0 position {x, y, z, yaw}")
        if abs(struct.unpack_from("<f", b, 0x200)[0] + 271.11) > 0.01:
            errs.append("spawn camera look-at (0x200)")
        # inventory rebuild: chunk 10 replaced, enclosing lengths and payload length fixed
        s.set_inventory([(0, s.item_payload(0, 0, 0, 16749)), (1, s.item_payload(1, 1, 1, 16580, 7))])
        s.write()
        s = se.Save(f)
        inv = s.inventory()
        if [(o["kind"], o["item"], o["count"]) for o in inv] != [(0, 16749, 1), (1, 16580, 7)]:
            errs.append(f"inventory {inv}")
        if s.chunk(13) is None or s.chunk(15) is None or s.check():
            errs.append("chunks after the inventory rebuild / digests")
        root = s.chunks[0]
        if struct.unpack_from("<q", s.b, 0x10)[0] != root["data"] + root["len"] - 0x50:
            errs.append("payload length after the inventory rebuild")
        # insects and cages (kinds 4 / 5 / 6 + GameRec chunk 12), with a stub item table (no game data)
        import rgdata
        ins = {"param": 14301, "hp": [100, 200], "atk": [15, 20], "def": [8, 12],
               "stats": [[18, 25]] * 6, "growth": [140, 160], "w": [95, 60, 60], "feed": [16722, 16732, 16736]}
        stub = {16740: {"name": "Insector Trap I", "cat": 12, "code": 1200, "index": 0, "weapon": None, "special": 0, "insect": None},
                16744: {"name": "Rearing Cage I", "cat": 12, "code": 1201, "index": 0, "weapon": None, "special": 0, "insect": None},
                16850: {"name": "Knife Beetle", "cat": 20, "code": 2000, "index": 0, "weapon": None, "special": 0, "insect": ins}}
        saved = rgdata.items
        rgdata.items = lambda: stub
        try:
            s = se.Save(f)
            s.add_cage(16740)
            s.add_cage(16744, slot=131)
            for k in range(5):
                s.add_insect(16850, name=f"KNIFE {k}")
            try:
                s.add_insect(16850)
                errs.append("a sixth insect fit into one Rearing Cage")
            except SystemExit:
                pass
            s.write()
            s = se.Save(f)
            inv = s.inventory()
            kinds = [o["kind"] for o in inv]
            if kinds[-7:] != [5, 6, 4, 4, 4, 4, 4]:
                errs.append(f"insect / cage kinds {kinds}")
            g = s.gamerec()
            if s.b[g + 0x30C] & 1 != 1 or s.b[g + 0x1ADC] & 1 != 1:
                errs.append("trap / rearing GameRec records not in use")
            cages = s.rearing_cages()
            ids = [o["uid"] for o in inv if o["kind"] == 4]
            if len(cages) != 1 or cages[0][2] != ids:
                errs.append(f"rearing cage insect ids {cages} != {ids}")
            bugs = s.insects()
            if [b_["name"] for b_ in bugs] != [f"KNIFE {k}" for k in range(5)] or bugs[0]["hp"] != (200, 200) or bugs[0]["atk"] != 20 \
                    or [b_["rec"] for b_ in bugs] != list(range(5)) or bugs[0]["slot"] != se.LIST7_LO:
                errs.append(f"insect records {bugs[:1]}")
            if any(len(o["raw"]) != 0x18 for o in inv if o["kind"] >= 4):
                errs.append("insect / cage payload size != 0x18 (InsectItemGetSaveSize_3d5b20 - 4)")
            if bytes(s.b[0x348:0x34E]) != bytes([1, 5, 0, 0, 0, 0]):
                errs.append(f"summary cages {bytes(s.b[0x348:0x34E]).hex()}")
            if s.check():
                errs.append("digests after insects")
        finally:
            rgdata.items = saved
    for e in errs:
        print("FAIL:", e)
    print("saveedit_test:", "FAIL" if errs else "PASS")
    return 1 if errs else 0


if __name__ == "__main__":
    sys.exit(main())
