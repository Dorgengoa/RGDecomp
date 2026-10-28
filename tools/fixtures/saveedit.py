#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Rogue Galaxy memory-card save editor (docs/SAVE-FORMAT.md).

Works on the game's data file (`BASCUS-97490LV5RG_NN`, 0x1BC00 bytes) inside a
port saves dir (`<saves>/card1/BASCUS-97490LV5RG_NN/`), or on a saves dir /
slot dir (the first save found).  Every write recomputes both MD5 digests
(+0x20 payload, +0x40 summary), so the game's own validation accepts it.

    python tools/fixtures/saveedit.py dump  SAVE [--flags] [--vars] [--chunks] [--inv]
    python tools/fixtures/saveedit.py copy  SRC_SAVES_DIR DST_SAVES_DIR
    python tools/fixtures/saveedit.py patch SAVE [--set-flag N ..] [--clear-flag N ..]
          [--var I=V ..] [--chapter C] [--summary-var5 V] [--add-item ID[:N] ..]
          [--location ID] [--no-summary-sync]
    python tools/fixtures/saveedit.py check SAVE
    python tools/fixtures/saveedit.py make [NAME ..]   (RECIPES + cardlib.LIBRARY, from cards/save2)

Flags/vars are the story state (StateBlock, chunk 2): flag N = bit N of the
2048-bit set at StateBlock+0x28 (StateFlagTest_3ccd70), var I = s16 at
StateBlock+0x128 + 2*I (StateVarGet_3ccac0), chapter = s16 at +0x8
(StateGetChapter_3cd5b0).  Known unlocks (decomp): flag 0x3E8 = main-menu
Factory row (TopMenuRow6UnlockedMaybe_29ac20); var 5 = Insectron rank
(the title's INSECTRON row needs the summary copy >= 3,
McSaveHeaderCheckClearedMaybe_372fd0); key item 0x40E5 (category 10) = the
Insects row (TopMenuRow5UnlockedMaybe_29ac50).  The summary (0x50..0x350,
what the slot list and the title read) mirrors chapter, var 5/6/7 and flags
0x1EA..0x1F1; `patch` keeps it in sync unless --no-summary-sync.
"""
from __future__ import annotations

import argparse
import hashlib
import shutil
import struct
import sys
from pathlib import Path

SIZE = 0x1BC00
VERSION = 0x25
CHUNK_NAMES = {0: "root", 1: "options (OptionsSerialize_3d5de0)", 2: "story state (StateBlockSerialize_3cb9d0)",
               3: "characters (CharaMgrPoolSerialize_3a8390)", 4: "character", 5: "chara sub 5", 6: "chara sub 6",
               7: "equip slots (EquipSlotSerialize_39f4e0)",
               8: "party + inventory (PartySerialize_3bf820)", 9: "party sub 9", 10: "party sub 10 (0xA)",
               11: "item (InvObjSerialize_3d3a80)", 12: "party sub 12 (0xC)", 13: "party sub 13 (0xD)",
               14: "chara sys (CharaSysSerialize_3a0b30)", 15: "insect teams (InsectTeamTableSerialize_42fdd0)"}
# StateBlock: the chunk-2 payload is the object from +4 (v0() = 4) for 0x2324 bytes
SB_PAYLOAD_BASE = 4
SB_CHAPTER, SB_FLAGS, SB_VARS = 0x8, 0x28, 0x128
# GameRec table (chunk 12 = party +0x174 object, 0x33C0 bytes): insect / trap / rearing-cage records
GAMEREC_SIZE, GAMEREC_INSECT, GAMEREC_TRAP, GAMEREC_REAR = 0x33C0, 0x0, 0x30C, 0x1ADC
# inventory list 7 (D_00465AE8..D_00465AF0): where insects live
LIST7_LO, LIST7_HI = 0x284, 0x295


def find_save(p: Path) -> Path:
    p = Path(p)
    if p.is_file():
        return p
    for f in sorted(p.rglob("BASCUS-97490LV5RG_*")):
        if f.is_file() and f.stat().st_size == SIZE:
            return f
    raise SystemExit(f"saveedit: no save data file under {p}")


class Save:
    def __init__(self, path: Path):
        self.path = find_save(path)
        self.b = bytearray(self.path.read_bytes())
        if len(self.b) != SIZE:
            raise SystemExit(f"saveedit: {self.path}: size {len(self.b):#x}, want {SIZE:#x}")
        self.chunks = self._walk(0x800, SIZE, 0)

    # ---- chunks ---------------------------------------------------------------
    def _walk(self, off, end, depth):
        out = []
        while off + 12 <= end:
            k, v, n = struct.unpack_from("<III", self.b, off)
            if k == v == n == 0 or n > end - off - 12:
                break
            ch = {"off": off, "kind": k, "ver": v, "len": n, "data": off + 12, "depth": depth, "sub": []}
            if (depth == 0 and k == 0) or (depth == 1 and k in (3, 8)):
                ch["sub"] = self._walk(off + 12, off + 12 + n, depth + 1)
            out.append(ch)
            off += 12 + n
            if depth == 0:
                break
        return out

    def chunk(self, kind):
        def rec(lst):
            for c in lst:
                if c["kind"] == kind:
                    return c
                r = rec(c["sub"])
                if r:
                    return r
        return rec(self.chunks)

    # ---- story state ------------------------------------------------------------
    def sb(self, obj_off):
        c = self.chunk(2)
        return c["data"] + obj_off - SB_PAYLOAD_BASE

    def flag(self, n):
        o = self.sb(SB_FLAGS) + n // 8
        return (self.b[o] >> (n % 8)) & 1

    def set_flag(self, n, on=True):
        assert 0 <= n < 2048
        o = self.sb(SB_FLAGS) + n // 8
        if on:
            self.b[o] |= 1 << (n % 8)
        else:
            self.b[o] &= ~(1 << (n % 8)) & 0xFF

    def var(self, i):
        return struct.unpack_from("<h", self.b, self.sb(SB_VARS) + 2 * i)[0]

    def set_var(self, i, v):
        struct.pack_into("<h", self.b, self.sb(SB_VARS) + 2 * i, v)

    def unlock_item_group(self, k, progress=1, time=1.0):
        """Unlock item group K (0..63) the way ItemGroupUnlock_3cbac0 does: StateBlock +0x840
        s8[k] = progress ordinal, +0x880 f64[k] = unlock time (reset -1 / -1.0).  Item defs
        with #102 [3] = K >= 0 are listed only when that time is > 0
        (ContainerViewItemFilterMatch_40c280): factory parts Athanor 34 / Assembler III 35 in
        the FACTORY Place list; the game unlocks them when the part's own plan is produced."""
        assert 0 <= k < 0x40
        struct.pack_into("<b", self.b, self.sb(0x840) + k, progress)
        struct.pack_into("<d", self.b, self.sb(0x880) + 8 * k, time)

    def chapter(self):
        return struct.unpack_from("<h", self.b, self.sb(SB_CHAPTER))[0]

    def set_chapter(self, c):
        struct.pack_into("<h", self.b, self.sb(SB_CHAPTER), c)

    # ---- party (chunk 9 = the party object from +4) ------------------------------
    # +0xF8 s16 location record id (GroupGetRecordById_425590; the load places the leader on
    # that record's position: SaveHeaderBuild_3e5520 / the slot list's location line)
    def party_off(self, obj_off):
        return self.chunk(9)["data"] + obj_off - 4

    def set_location(self, rec_id):
        struct.pack_into("<h", self.b, self.party_off(0xF8), rec_id)
        struct.pack_into("<h", self.b, 0x298, rec_id)

    def party_s16(self, off):
        return struct.unpack_from("<h", self.b, self.party_off(off))[0]

    def set_party_s16(self, off, v):
        struct.pack_into("<h", self.b, self.party_off(off), v)

    def set_spawn(self, planet, x, y, z, yaw):
        """Place the party for CONTINUE.  The load does not read the party object's
        positions: title_TitleLoadConfirmCb_4ee2c0 -> SysMsgFillFromSaveRecMaybe_3e4d10 turns
        the SUMMARY into the mode message (kind 1: member k at summary entry k +0x18 x,y,z,
        yaw; camera eye 0x1F4, look-at 0x200) and PartyLoadAndPlaceMembersMaybe_2f4b00 puts
        member k / the camera there.  The map comes from the party object: +0x4 planet
        (MapLoadFromGameDataAndWait_2f4920: PlanetAreaMatrixLookupByProgress_3ed840).  The
        party object's own copies (+0x90 leader, +0xA0 members, +0xD0 yaws) are set too so
        the next in-game save without a location record agrees."""
        import math
        self.set_party_s16(0x4, planet)
        struct.pack_into("<h", self.b, 0x31C, planet)
        fwd = (math.sin(yaw), math.cos(yaw))
        # follower offsets of PartyLoadAndPlaceMembersMaybe_2f4b00 case 0: (+-20, 0, -20) in
        # the leader's frame (MatFromRotPos: rotation about Y)
        offs = [(0.0, 0.0), (20.0, -20.0), (-20.0, -20.0)]
        lead = self.party_s16(0x18E)
        ids = [self.party_s16(0x190 + 2 * k) for k in range(3)]
        follower = 0
        for k in range(3):
            if k < len(ids) and ids[k] == lead:
                ox, oz = offs[0]
            else:
                follower += 1
                ox, oz = offs[min(follower, 2)]
            px = x + ox * math.cos(yaw) + oz * math.sin(yaw)
            pz = z - ox * math.sin(yaw) + oz * math.cos(yaw)
            e = 0x64 + 0x28 * k + 0x18
            struct.pack_into("<4f", self.b, e, px, y, pz, yaw)
            struct.pack_into("<4f", self.b, self.party_off(0xA0 + 16 * k), px, y, pz, 1.0)
            struct.pack_into("<f", self.b, self.party_off(0xD0 + 4 * k), yaw)
        struct.pack_into("<4f", self.b, self.party_off(0x90), x, y, z, 1.0)
        struct.pack_into("<6f", self.b, 0x1F4, x - 120 * fwd[0], y + 30, z - 120 * fwd[1], x, y, z)
        struct.pack_into("<4f", self.b, 0x324, x, y, z, yaw)

    # ---- characters (chunk 3: one kind-4 chunk per character, sub-chunk 5 = the Chara
    # object from +4 (CharaSerialize_3a9e70), sub-chunk 6 = its 10 equip slots) ----------
    # payload +0x0 data id (11001 Jaster ..), +0x4 record version, +0x8 chara id (the id the
    # party arrays hold), +0xC level, +0x10 HP, +0x14 AP, +0x18 / +0x1C max HP, then s16 pairs
    # +0x20 AP, +0x28 stat 3 (with a bonus), +0x2C stat 2, +0x30 stat 3, +0x34 stat 4
    # (chara_levelup_param2 base + increments), +0x230 flag byte (obj +0x234: bit1 in party
    # (PartyAddMember_3c1430), bit2 set by party mode 4/5 (CharaSetFlag234Bit2Related_3ae370))
    def charas(self):
        out = {}
        for c in self.chunk(3)["sub"]:
            k, v, n = struct.unpack_from("<III", self.b, c["data"])
            if k != 5:
                continue
            o = c["data"] + 12
            did, ver, cid = struct.unpack_from("<iii", self.b, o)
            out[did] = {"off": o, "id": cid, "level": struct.unpack_from("<i", self.b, o + 0xC)[0],
                        "hp": struct.unpack_from("<i", self.b, o + 0x10)[0], "flags": self.b[o + 0x230]}
        return out

    def set_chara_level(self, data_id, level):
        import rgdata
        o = self.charas()[data_id]["off"]
        hp, ap, s2, s3, s4 = rgdata.level_stats(data_id, level)
        bonus = struct.unpack_from("<h", self.b, o + 0x28)[0] - struct.unpack_from("<h", self.b, o + 0x30)[0]
        struct.pack_into("<iiiii", self.b, o + 0xC, level, hp, ap, hp, hp)
        struct.pack_into("<hh", self.b, o + 0x20, ap, ap)
        struct.pack_into("<hhhhhhhh", self.b, o + 0x28, s3 + bonus, s3 + bonus, s2, s2, s3, s3, s4, s4)

    # ---- abilities (initial_status #106, WorldDataCmdCharaLearnAbilities_3b9720 ->
    # CharaLearnAbility_3ad460): the character's ability list (chara_ability_param3: data id
    # -> [(index, ability id)]) gives the bit index-1 of the u64 learned set at object +0x2E0
    # (payload +0x2DC); a learned ability clears the bits of the same family (ability def
    # byte m4, its other levels).  Ability defs (ability_param_EN #4: id, name, m2, m3, m4
    # kind, m5 level) with m2 == 0 (actives: Flash Sword, Star Charm, Fated Passion ..) also
    # take one of the 10 equip slots (sub-chunk 6, kind-7 parts = slot object +4..+0x28):
    # the slot of the same family is re-set, else the first empty one
    # (EquipSlotSetAbilityFromObj_39fb80 -> EquipSlotSetAbility_3a07b0: +8 s16 ability id,
    # +0xA s16 owner chara id, +0xC use count, +0x10 f32 gauge kept (0 on a fresh slot));
    # then the slots are bubble-sorted by family, empties last.  Passives (m2 = 1: HP Up,
    # resistances ..) are bits only.
    def chara_slot_parts(self, data_id):
        """Offsets of the 10 equip-slot part payloads (0x24 bytes = slot +4..) of a character."""
        for c in self.chunk(3)["sub"]:
            o, end = c["data"], c["data"] + c["len"]
            did = None
            parts = []
            while o + 12 <= end:
                k, v, n = struct.unpack_from("<III", self.b, o)
                if k == 5:
                    did = struct.unpack_from("<i", self.b, o + 12)[0]
                elif k == 6:
                    q, e = o + 12, o + 12 + n
                    while q + 12 <= e:
                        k2, v2, n2 = struct.unpack_from("<III", self.b, q)
                        if k2 == 7 and n2 >= 0x10:
                            parts.append(q + 12)
                        q += 12 + n2
                o += 12 + n
            if did == data_id:
                return parts
        return []

    def learn_abilities(self, data_id, ids):
        """CharaLearnAbility_3ad460 for each ability id, in order (see above).  Returns the
        ids it could not place (not in the character's list / no def)."""
        import rgdata
        lst, defs = rgdata.chara_abilities().get(data_id, {}), rgdata.ability_defs()
        ch = self.charas().get(data_id)
        if ch is None:
            return list(ids)
        o = ch["off"]
        parts = self.chara_slot_parts(data_id)
        bad = []
        for aid in ids:
            if aid not in lst or aid not in defs:
                bad.append(aid)
                continue
            bits = struct.unpack_from("<Q", self.b, o + 0x2DC)[0]
            bits |= 1 << (lst[aid] - 1)
            kind = defs[aid][2]
            for other, idx in lst.items():
                if other != aid and other in defs and defs[other][2] == kind:
                    bits &= ~(1 << (idx - 1))
            struct.pack_into("<Q", self.b, o + 0x2DC, bits)
            if kind == 0x86:   # Burning Strike: 'Burning Strike Possible' / 'First Burning Strike'
                self.set_flag(0x3ED, True)
                self.set_flag(0x3EE, True)
            if defs[aid][0] != 0 or not parts:
                continue
            slot = None
            for p in parts:
                cur = struct.unpack_from("<h", self.b, p + 4)[0]
                if cur > 0 and cur in defs and defs[cur][2] == kind:
                    slot = p
                    break
            if slot is None:
                slot = next((p for p in parts if struct.unpack_from("<h", self.b, p + 4)[0] <= 0), None)
            if slot is None:
                bad.append(aid)
                continue
            struct.pack_into("<hh", self.b, slot + 4, aid, ch["id"])
        # bubble sort by family, empties last (the loop at the end of CharaLearnAbility_3ad460)
        if parts:
            recs = [bytes(self.b[p:p + 0x24]) for p in parts]
            key = lambda r: (struct.unpack_from("<h", r, 4)[0] <= 0,
                             defs.get(struct.unpack_from("<h", r, 4)[0], (0, 0, 0, 0))[2])
            recs.sort(key=key)
            for p, r in zip(parts, recs):
                self.b[p:p + 0x24] = r
        return bad

    def abilities(self, data_id):
        """(learned ability ids by the bit set, slotted ability ids)."""
        import rgdata
        ch = self.charas().get(data_id)
        if ch is None:
            return [], []
        bits = struct.unpack_from("<Q", self.b, ch["off"] + 0x2DC)[0]
        lst = rgdata.chara_abilities().get(data_id, {})
        learned = [aid for aid, idx in lst.items() if bits >> (idx - 1) & 1]
        slots = [struct.unpack_from("<h", self.b, p + 4)[0] for p in self.chara_slot_parts(data_id)]
        return learned, [s for s in slots if s > 0]

    # party object: +0x18C active count (1..3), +0x18E leader chara id, +0x190 active[3],
    # +0x196 reserve[7] (PartyAddMember_3c1430, PartyMoveToReserve_3c19b0); +0x160 s64 money
    def party_members(self):
        act = [self.party_s16(0x190 + 2 * i) for i in range(3)]
        res = [self.party_s16(0x196 + 2 * i) for i in range(7)]
        return self.party_s16(0x18E), [x for x in act if x >= 0], [x for x in res if x >= 0]

    def set_party(self, members):
        """members: [(data id, mode)] in initial-status order; modes as
        WorldDataCmdSetPartyMember_3b9b00: 0 out, 1/6 in + leader, 2 in, 3 reserve,
        4 reserve (bit2), 5 out (bit2)."""
        ch = self.charas()
        act, res, lead = [], [], -1
        for did, mode in members:
            if did not in ch:
                continue
            c = ch[did]
            fl = self.b[c["off"] + 0x230]
            if mode in (0, 5):
                fl &= ~2
            else:
                fl |= 2
            if mode in (4, 5):
                fl |= 4
            self.b[c["off"] + 0x230] = fl & 0xFF
            if mode in (1, 6):
                lead = c["id"]
                act.insert(0, c["id"])
            elif mode == 2:
                act.append(c["id"])
            elif mode in (3, 4):
                res.append(c["id"])
        res = act[3:] + res
        act = act[:3]
        self.set_party_s16(0x18C, 3)
        self.set_party_s16(0x18E, lead if lead >= 0 else (act[0] if act else 0))
        for i in range(3):
            self.set_party_s16(0x190 + 2 * i, act[i] if i < len(act) else -1)
        for i in range(7):
            self.set_party_s16(0x196 + 2 * i, res[i] if i < len(res) else -1)

    # ---- inventory (chunk 10 = one kind-11 chunk per item object, version = object kind,
    # payload = the object from +4; InvObjSerialize_3d3a80, InvObjLoadState_3d3940) -----
    # +0x0 s16 unique id (what the characters' equip slots hold), +0x2 s16 list slot,
    # +0x4 bits, +0x8 s16 item id, +0xC item-def pointer (looked up again on load);
    # kind 1 (stack) +0x10 s32 count; kind 2 (weapon) +0x10 u16 0, u8 1, 5 bytes of the
    # def's weapon data, s8 -1 (ItemWeaponSetup_3d3730); kind 3 (special weapon) + f32 gauge,
    # s16 state 0x21 (full), s16 0 (ItemSpecialWeaponGaugeFill_3d2f90).
    def inventory(self):
        c = self.chunk(10)
        out, d, e = [], c["data"], c["data"] + c["len"]
        while d + 12 <= e:
            k, v, n = struct.unpack_from("<III", self.b, d)
            uid, slot, _, item = struct.unpack_from("<hhih", self.b, d + 12)
            cnt = struct.unpack_from("<i", self.b, d + 12 + 0x10)[0] if v == 1 and n >= 0x14 else 1
            out.append({"kind": v, "uid": uid, "slot": slot, "item": item, "count": cnt,
                        "raw": bytes(self.b[d + 12:d + 12 + n])})
            d += 12 + n
        return out

    @staticmethod
    def item_payload(kind, uid, slot, item, count=1):
        import rgdata
        p = struct.pack("<hhiiI", uid, slot, 0, item, 0)
        if kind == 1:
            p += struct.pack("<i", count)
        elif kind in (2, 3):
            w = rgdata.items()[item]["weapon"]
            p += struct.pack("<HBBBBBBbBH", 0, 1, *[x & 0xFF for x in w], -1, 0, 0)
            if kind == 3:
                p += struct.pack("<fhh", float(rgdata.items()[item]["special"]), 0x21, 0)
        return p

    def set_inventory(self, objs):
        """Replace chunk 10 with objs = [(kind, payload)], fixing the enclosing chunk
        lengths and the header payload length (the file keeps its 0x1BC00 size)."""
        c10, c8, root = self.chunk(10), self.chunk(8), self.chunks[0]
        new = b"".join(struct.pack("<III", 11, k, len(p)) + p for k, p in objs)
        old_s, old_e = c10["data"], c10["data"] + c10["len"]
        end = root["data"] + root["len"]
        delta = len(new) - c10["len"]
        body = bytes(self.b[:old_s]) + new + bytes(self.b[old_e:end])
        if len(body) > SIZE:
            raise SystemExit("saveedit: inventory does not fit the save file")
        self.b[:] = body + bytes(SIZE - len(body))
        for ch, off in ((c10, c10["off"]), (c8, c8["off"]), (root, root["off"])):
            struct.pack_into("<I", self.b, off + 8, ch["len"] + delta)
        struct.pack_into("<q", self.b, 0x10, end + delta - 0x50)
        self.chunks = self._walk(0x800, SIZE, 0)

    def apply_items(self, sec):
        """Inventory and equipment of an initial_status section: the section clears the
        inventory (WorldDataCmdSectionBegin_3b9f20 -> InvPoolClear_3c8e40), #102 adds items
        at list slots (stacks merge, '*N' = N), #105 equips the party (in-party characters
        only, WorldDataCmdCharaSetEquip_3b97e0): weapon slots 0 / 1, clothes, accessory =
        payload +0x23A / +0x23C / +0x23E / +0x240 of the character record."""
        import rgdata
        objs, skipped = [], []

        def add(item, slot, cnt=1):
            kind = rgdata.item_kind(item)
            if kind is None or kind >= 4:   # insects / cages: --section-insects / --add-insect (opt-in)
                skipped.append(item)
                return -1
            if kind == 1:
                for o in objs:
                    if o["item"] == item:
                        o["count"] += cnt
                        return o["uid"]
            uid = len(objs)
            objs.append({"kind": kind, "uid": uid, "slot": slot, "item": item, "count": cnt})
            return uid

        for slot, item, s in sec["items"]:
            cnt = int(s[1:]) if isinstance(s, str) and s.startswith("*") and s[1:].isdigit() else 1
            add(item, slot, cnt)
        ch = self.charas()
        for p in sec["party"]:
            c = ch.get(p["data_id"])
            if c is None:
                continue
            eq = p.get("equip", [])
            if not (self.b[c["off"] + 0x230] & 2):
                continue
            handles = [add(x, 0) if x is not None and x >= 0 else -1 for x in (eq + [-1] * 4)[:4]]
            struct.pack_into("<4h", self.b, c["off"] + 0x23A, *handles)
        self.set_inventory([(o["kind"], self.item_payload(o["kind"], o["uid"], o["slot"], o["item"], o["count"]))
                            for o in objs])
        return skipped

    def add_items(self, specs):
        """Append items to the inventory (chunk 10): specs = ["ID[:N]", ..] (decimal or 0x;
        a legacy middle CAT field, ID:CAT:N, is accepted and ignored: the kind comes from
        item_param_EN, rgdata.item_kind).  Stacks (kind 1) merge into an existing object
        (+N); other kinds get N objects.  New objects take the next unique id and list slot
        (save2's objects have slot = uid).  Insects (kind 4) go into a Rearing Cage, cages
        (kinds 5 / 6) get a GameRec record (add_insect, add_cage)."""
        import rgdata
        objs = [dict(o) for o in self.inventory()]
        nxt = max([o["uid"] for o in objs] + [-1]) + 1
        slot = max([o["slot"] for o in objs if o["slot"] < LIST7_LO] + [-1]) + 1
        for spec in specs:
            f = [x for x in str(spec).split(":") if x != ""]
            item = parse_int(f[0])
            n = parse_int(f[-1]) if len(f) > 1 else 1
            kind = rgdata.item_kind(item)
            if kind is None:
                raise SystemExit(f"saveedit: --add-item {spec}: unknown item")
            if kind >= 4:
                self.set_inventory([(o["kind"], o["raw"] if "raw" in o else
                                     self.item_payload(o["kind"], o["uid"], o["slot"], o["item"], o["count"]))
                                    for o in objs])
                for _ in range(n):
                    if kind == 4:
                        self.add_insect(item)
                    else:
                        self.add_cage(item)
                objs = [dict(o) for o in self.inventory()]
                nxt = max([o["uid"] for o in objs] + [-1]) + 1
                slot = max([o["slot"] for o in objs if o["slot"] < LIST7_LO] + [-1]) + 1
                continue
            if kind == 1:
                for o in objs:
                    if o["item"] == item and o["kind"] == 1:
                        o["count"] += n
                        o.pop("raw", None)
                        break
                else:
                    objs.append({"kind": 1, "uid": nxt, "slot": slot, "item": item, "count": n})
                    nxt, slot = nxt + 1, slot + 1
                continue
            for _ in range(n):
                objs.append({"kind": kind, "uid": nxt, "slot": slot, "item": item, "count": 1})
                nxt, slot = nxt + 1, slot + 1
        # untouched objects keep their exact bytes; changed / new ones are re-encoded
        self.set_inventory([(o["kind"], o["raw"] if "raw" in o else
                             self.item_payload(o["kind"], o["uid"], o["slot"], o["item"], o["count"]))
                            for o in objs])

    # ---- insects and cages (inventory kinds 4 / 5 / 6 + the GameRec table, chunk 12) -------
    # An insect / cage item object is 0x1C bytes (InvObjCreateForItem_3c7110): the common 0x14
    # header, +0x14 s16 GameRec slot index, +0x18 GameRec record pointer (rebound from the index
    # on load: vtable slot 0x28 ItemGameRecBind_*); payload = object +4 = 0x18 bytes.  The
    # GameRec table is the 0x33C0 object at party +0x174, saved raw as chunk 12
    # (PartyDeserialize_3bf4f0 memcpy):
    #   +0x0000 15 insect records x 0x34 (GameRecGetInsectSlot_3ce350; kind 4, vtable D_00475B10)
    #   +0x030C  3 Insector Trap records x 0x7F0 (GameRecGetCageSlot_3ce1f0; kind 5, D_004759F0)
    #   +0x1ADC  3 Rearing Cage records x 0x84C (GameRecGetInsectRecSlot_3ce090; kind 6, D_004758D0)
    # Every record +0 bit0 = in use, bit1 = reclaimable (GameRecFindFree*).  Rearing cage
    # record (ItemGameRecReset_3d0320): +0x2 s16 insect unique ids[5] (-1 empty), +0xC
    # pointers[5] (re-resolved on load from the ids, InsectRecSlotsResolve_3cfbd0, list 7),
    # +0x20 / +0x22 s16 0, +0x24 two breed records x 0x14 (InsectBreedRecReset_3d2730),
    # +0x4C 16 x 0x80 message entries (cleared).  Trap record (ItemGameRecReset_3d0e50): +0x2..+0x8
    # s16 -1, +0xC..+0x1C 0, +0x7EC f32 -1.  Insect record (GameRecInsectSlotClear_3d2780 then
    # InsectItemSetup_3d1fb0, def data = item_param #115): +0x1 name[16] (+0x10 NUL), +0x12 s16 exp (`InsectItemGetExp_392240`),
    # +0x14 / +0x16 s16 max HP / HP, +0x18 u8 satiety (0.29 * 99 * rand), +0x19 / +0x1A u8 growth
    # cap / left, +0x1C / +0x1E s16 attack / defense, +0x20 u8 six stats (cap 100), +0x26 u8
    # personality (rand % 5), +0x27 u8 level (1..5), +0x28 bit0 sex, bit1 adult, +0x2C s32 colour
    # (0..9), +0x30 f32 satiety timer (InsectItemTickSatiety_3d1110).  Insects live in inventory list 7 (slots 0x284..0x295,
    # InvAddItemCoreMaybe_3c6540(.., 7, ..)); WorldDataCmdAddItemMaybe_3b9d40 puts a section's
    # insect into the first Rearing Cage with a free place (InvGetCageItem_3c8040: category 12,
    # code 0x4B1, def index 0..2; 5 insects per cage) and names it.
    def gamerec(self):
        c = self.chunk(12)
        if c is None or c["len"] < GAMEREC_SIZE:
            raise SystemExit("saveedit: no GameRec table (chunk 12)")
        return c["data"]

    def _free_rec(self, base, stride, count):
        g = self.gamerec()
        for i in range(count):
            if not self.b[g + base + stride * i] & 1:
                return i
        for i in range(count):
            if self.b[g + base + stride * i] & 2:
                return i
        return -1

    @staticmethod
    def _rec_payload(uid, slot, item, rec):
        return struct.pack("<hhiiIhhI", uid, slot, 0, item, 0, rec, 0, 0)

    def _append_obj(self, kind, payload):
        objs = [(o["kind"], o["raw"]) for o in self.inventory()]
        self.set_inventory(objs + [(kind, payload)])

    def add_cage(self, item, slot=None):
        """Add an Insector Trap (kind 5) or Rearing Cage (kind 6): item object + GameRec record."""
        import rgdata
        kind = rgdata.item_kind(item)
        assert kind in (5, 6), item
        base, stride, count = (GAMEREC_TRAP, 0x7F0, 3) if kind == 5 else (GAMEREC_REAR, 0x84C, 3)
        i = self._free_rec(base, stride, count)
        if i < 0:
            raise SystemExit(f"saveedit: no free GameRec slot for item {item}")
        r = self.gamerec() + base + stride * i
        self.b[r:r + stride] = bytes(stride)
        self.b[r] = 1
        if kind == 5:
            struct.pack_into("<hhhh", self.b, r + 2, -1, -1, -1, -1)
            struct.pack_into("<f", self.b, r + 0x7EC, -1.0)
        else:
            struct.pack_into("<5h", self.b, r + 2, *[-1] * 5)
            for k in range(2):
                struct.pack_into("<hhihhff", self.b, r + 0x24 + 0x14 * k, -1, -1, 0, -1, 0, -1.0, -1.0)
        inv = self.inventory()
        uid = max([o["uid"] for o in inv] + [-1]) + 1
        if slot is None:
            slot = max([o["slot"] for o in inv if o["slot"] < LIST7_LO] + [-1]) + 1
        self._append_obj(kind, self._rec_payload(uid, slot, item, i))
        self.sync_summary_cages()
        return uid

    def rearing_cages(self):
        """[(def index 0..2, GameRec record offset, [insect uids])] of the Rearing Cages."""
        import rgdata
        out = []
        g = self.gamerec()
        for o in self.inventory():
            if o["kind"] == 6:
                rec = struct.unpack_from("<h", o["raw"], 0x10)[0]
                r = g + GAMEREC_REAR + 0x84C * rec
                ids = list(struct.unpack_from("<5h", self.b, r + 2))
                out.append((rgdata.items()[o["item"]]["index"], r, ids))
        return sorted(out)

    def insects(self):
        """[{uid, slot, item, rec, name, hp, atk, def, stats, level}] of the insect objects."""
        g = self.gamerec()
        out = []
        for o in self.inventory():
            if o["kind"] == 4:
                rec = struct.unpack_from("<h", o["raw"], 0x10)[0]
                r = g + GAMEREC_INSECT + 0x34 * rec
                mhp, hp = struct.unpack_from("<hh", self.b, r + 0x14)
                atk, dfn = struct.unpack_from("<hh", self.b, r + 0x1C)
                out.append({"uid": o["uid"], "slot": o["slot"], "item": o["item"], "rec": rec,
                            "name": bytes(self.b[r + 1:r + 0x11]).split(bytes(1))[0].decode("latin-1"),
                            "hp": (hp, mhp), "atk": atk, "def": dfn,
                            "stats": list(self.b[r + 0x20:r + 0x26]), "level": self.b[r + 0x27]})
        return out

    def add_insect(self, item, name=None, strong=False):
        """Add an insect (kind 4) the way WorldDataCmdAddItemMaybe_3b9d40 does: into the first
        Rearing Cage (def index order) with a free place, an insect GameRec record with the def's
        (#115) values (deterministic: the top of each random range; strong = level 5, the six
        stats 100, HP x3, attack / defense x4, satiety 99), list-7 slot, name = NAME or the species name's first 6
        letters upper-cased (InsectItemCreateWithRandomName_3cff30 without the random name table)."""
        import rgdata
        it = rgdata.items()[item]
        d = it["insect"]
        assert it["cat"] == 20 and d, item
        cage = next(((idx, r, ids) for idx, r, ids in self.rearing_cages() if -1 in ids), None)
        if cage is None:
            raise SystemExit(f"saveedit: insect {item}: no Rearing Cage with a free place (add 16744.. first)")
        i = self._free_rec(GAMEREC_INSECT, 0x34, 15)
        if i < 0:
            raise SystemExit("saveedit: all 15 insect records in use")
        r = self.gamerec() + GAMEREC_INSECT + 0x34 * i
        self.b[r:r + 0x34] = bytes(0x34)
        self.b[r] = 1
        nm = (name if name is not None else it["name"][:6].upper()).encode("latin-1", "replace")[:15]
        self.b[r + 1:r + 0x11] = nm.ljust(16, bytes(1))
        # strong: HP x3, attack / defense x4 (the battle piece keeps them as u8:
        # insect_InsectPieceLoadFromItem_516360, so at most 255)
        hp = d["hp"][1] * (3 if strong else 1)
        atk, dfn = (min(255, 4 * d["atk"][1]), min(255, 4 * d["def"][1])) if strong else (d["atk"][1], d["def"][1])
        g = max(1, min(255, d["growth"][1]))
        struct.pack_into("<hhhBBBxhh", self.b, r + 0x12, 0, hp, hp, 99 if strong else 28, g, g, atk, dfn)
        for k in range(6):
            self.b[r + 0x20 + k] = 100 if strong else max(0, min(100, d["stats"][k][1]))
        self.b[r + 0x26] = 0
        self.b[r + 0x27] = 5 if strong else 1
        self.b[r + 0x28] = 0
        struct.pack_into("<ii", self.b, r + 0x2C, 0, 0)
        # InsectItemSetup_3d1fb0: Dark Emperor (0x424A) / 0x41ED, 0x41EE, 0x41F1 set flags 0x187 / 0x186
        if item == 0x424A:
            self.set_flag(0x187)
        elif item in (0x41ED, 0x41EE, 0x41F1):
            self.set_flag(0x186)
        inv = self.inventory()
        uid = max([o["uid"] for o in inv] + [-1]) + 1
        used = {o["slot"] for o in inv}
        slot = next(k for k in range(LIST7_LO, LIST7_HI + 1) if k not in used)
        self._append_obj(4, self._rec_payload(uid, slot, item, i))
        _, cr, ids = cage
        struct.pack_into("<h", self.b, cr + 2 + 2 * ids.index(-1), uid)
        self.sync_summary_cages()
        return uid

    def sync_summary_cages(self):
        """Summary 0x348: per Rearing Cage index 0..2, byte 0 bit0 present, byte 1 insects in it
        (SaveHeaderBuild_3e5520; display only)."""
        cs = bytearray(6)
        for idx, r, ids in self.rearing_cages():
            if 0 <= idx < 3:
                cs[2 * idx] = 1
                cs[2 * idx + 1] = sum(1 for x in ids if x >= 0)
        self.b[0x348:0x34E] = cs

    def add_section_insects(self, sid, strong=False, limit=None):
        """The insect side of an initial_status section (#102 rows of categories 9 / 12 / 13 / 20 /
        21: Insectron License, traps, rearing cages, insects with their names, feed), added on top
        of the current inventory: cages first (at the section's list slots), then the insects in
        section order (at most `limit`), then the rest."""
        import rgdata
        its = rgdata.items()
        rows = rgdata.sections()[sid]["items"]
        have = {o["item"] for o in self.inventory()}
        for slot, item, txt in rows:
            if rgdata.item_kind(item) in (5, 6) and item not in have:
                self.add_cage(item, slot)
        n = 0
        for slot, item, txt in rows:
            if rgdata.item_kind(item) == 4 and (limit is None or n < limit):
                if not any(-1 in ids for _, _, ids in self.rearing_cages()):
                    # the game's handler skips it too (InsectItemCreateWithRandomName_3cff30 -> 0)
                    print(f"saveedit: section {sid}: insect {item} skipped, the Rearing Cages are full")
                    continue
                self.add_insect(item, name=txt or None, strong=strong)
                n += 1
        extra = []
        for slot, item, txt in rows:
            cat = its.get(item, {}).get("cat")
            if cat in (9, 13, 21) and item not in have:
                k = int(txt[1:]) if isinstance(txt, str) and txt.startswith("*") and txt[1:].isdigit() else 1
                extra.append(f"{item}:{k}")
                have.add(item)
        if extra:
            self.add_items(extra)

    def set_money(self, v):
        struct.pack_into("<q", self.b, self.party_off(0x160), v)
        struct.pack_into("<q", self.b, 0x58, v)

    def sync_summary_party(self):
        """Summary party list (0x60 count, 0x64 entries: name, id, icon, level) from the party
        and character records, as SaveHeaderBuild_3e5520 writes it; positions kept."""
        import rgdata
        names = rgdata.charas()
        by_id = {c["id"]: (did, c) for did, c in self.charas().items()}
        lead, act, res = self.party_members()
        slots = act + res
        struct.pack_into("<h", self.b, 0x60, len(slots))
        for i in range(10):
            e = 0x64 + 0x28 * i
            if i < len(slots) and slots[i] in by_id:
                did, c = by_id[slots[i]]
                self.b[e:e + 16] = names.get(did, "?").encode("latin-1")[:15].ljust(16, b"\0")
                struct.pack_into("<hhh", self.b, e + 16, did, c["id"], c["level"])
            elif i >= 3:
                self.b[e:e + 0x28] = bytes(0x28)
            else:
                self.b[e:e + 16] = bytes(16)
                struct.pack_into("<hhh", self.b, e + 16, -1, -1, 0)

    def set_flag_in(self, base, n, on):
        o = self.sb(base) + n // 8
        if on:
            self.b[o] |= 1 << (n % 8)
        else:
            self.b[o] &= ~(1 << (n % 8)) & 0xFF

    def set_progress(self, values):
        for i, v in enumerate(values[:15]):
            struct.pack_into("<h", self.b, self.sb(0xA + 2 * i), v)

    def apply_section(self, sid, levels=True, items=True, abilities=False):
        """Apply an initial_status5 section (the developers' start state for a story point)
        the way the WorldDataCmd* handlers do in game, on top of this save: story flags /
        vars (2048-bit set +0x28, s16 +0x128, 2048-bit set +0x228, 256-bit set +0x328),
        map markers (+0x348/+0x34C), money, party members, levels; chapter and the 15
        progress slots from the section id; inventory + equipment (apply_items)."""
        import rgdata
        sec = rgdata.sections()[sid]
        ch, sub, val = rgdata.section_story_point(sid)
        self.story_sub = sub
        if 1 <= ch <= 13:
            self.set_chapter(ch)
            self.set_progress(rgdata.progress_slots(ch, sub, val))
            rows, titles = rgdata.phases()
            struct.pack_into("<h", self.b, 0x210, val)
            self.b[0x214:0x254] = titles.get(ch, "").encode("latin-1", "replace")[:0x3F].ljust(0x40, bytes(1))  # 0x254: Insectron line
        for n, v in sec["flags"]:
            self.set_flag_in(SB_FLAGS, n, v)
        for i, v in sec["vars"]:
            self.set_var(i, v)
        for n, v in sec["flags2"]:
            self.set_flag_in(0x228, n, v)
        for n, v in sec["flags256"]:
            self.set_flag_in(0x328, n, v)
        if sec["markers"]:
            struct.pack_into("<h", self.b, self.sb(0x348), min(4, len(sec["markers"])))
            for i in range(4):
                struct.pack_into("<i", self.b, self.sb(0x34C + 4 * i),
                                 sec["markers"][i] if i < len(sec["markers"]) else -1)
        if sec["money"] is not None:
            self.set_money(sec["money"])
        if sec["party"]:
            self.set_party([(p["data_id"], p["mode"]) for p in sec["party"]])
            if levels:
                ch_ = self.charas()
                for p in sec["party"]:
                    if p["data_id"] in ch_ and p.get("level", 0) > 0:
                        self.set_chara_level(p["data_id"], p["level"])
            if abilities:
                self.skipped_abilities = []
                for p in sec["party"]:
                    if p.get("abilities"):
                        self.skipped_abilities += self.learn_abilities(p["data_id"], p["abilities"])
        if items:
            self.skipped_items = self.apply_items(sec)
        self.sync_summary_party()

    def sync_area(self):
        """Party +0x6 area / +0x8 sky (and +0xA) for the planet at the current story point,
        from planetarea_matrix5 (MapLoadFromGameDataAndWait_2f4920 reads +0x6 / +0x8)."""
        import rgdata
        planet = self.party_s16(0x4)
        try:
            rows, _ = rgdata.phases()
        except (OSError, KeyError):   # no game data (tests): keep +0x6 / +0x8
            return
        ch = self.chapter()
        best = None
        for i, (c, sub, _, ph) in enumerate(rows):
            if c == ch:
                v = struct.unpack_from("<h", self.b, self.sb(0xA + 2 * i))[0]
                r = rgdata.planetarea(planet, c, sub, v)
                if r and (best is None or sub == getattr(self, "story_sub", 0)):
                    best = r
        if best:
            area, sky = best
            self.set_party_s16(0x6, area)
            self.set_party_s16(0xA, area)
            if sky >= 0:
                self.set_party_s16(0x8, sky)
            struct.pack_into("<hh", self.b, 0x31E, area, area)

    # ---- insect teams (chunk 15, InsectTeamTable: payload = object + 4) ----------
    # +0 s32 count, +4 20 teams x 0xE0: name[9] (alnum), owner[6] (alpha), +0xF s8 (3 bits),
    # +0x10 bit0 used / bits 1-2 encoded, +0x18 5 insects x 0x28 (InsectTeamCodeEncode_4319f0):
    # name[13], +0xD species (5 bits, item def 2000+n), +0xE variant (3), +0xF (4),
    # +0x10..+0x15 six stats (7 bits), +0x18 (3), +0x1A u16 (10), +0x1C u16 (7), +0x1E u16 (7),
    # +0x20 bits 0-1, +0x21 (3), +0x22 (1), +0x24 item-def pointer (rebuilt on load)
    def add_insect_team(self, spec, formation=False):
        slot, name, sps = spec.split(":", 2)
        sps, _, stat = sps.partition("@")     # optional "@S": the six 7-bit stats (default 40)
        stat = int(stat, 0) & 127 if stat else 40
        slot = int(slot)
        c = self.chunk(15)
        base = c["data"]
        t = base + 4 + 0xE0 * slot
        self.b[t:t + 0xE0] = bytes(0xE0)
        self.b[t:t + 9] = name.upper().encode()[:8].ljust(9, bytes(1))
        self.b[t + 9:t + 15] = b"JASTE" + bytes(1)
        self.b[t + 0x10] = 1
        for i, sp in enumerate(sps.split(",")[:5]):
            spn, _, var = sp.partition("/")
            e = t + 0x18 + 0x28 * i
            self.b[e:e + 13] = f"BUG{i + 1}".encode().ljust(13, bytes(1))
            self.b[e + 0xD] = int(spn, 0) & 31
            self.b[e + 0xE] = int(var or "0", 0) & 7
            for k in range(6):
                self.b[e + 0x10 + k] = stat
            struct.pack_into("<HHH", self.b, e + 0x1A, 100, 50, 50)
            if formation:
                # found by booting (not decoded): with these left 0 only each team's leader is
                # on the board and a CPU-vs-CPU Watch Battle never ends (the two leaders keep
                # their distance); with insect i's +0x18 / +0x21 = i and +0x20 / +0x22 = 1 all
                # five take the field and the battle ends with the rematch prompt
                self.b[e + 0x18] = i
                self.b[e + 0x20] = 1
                self.b[e + 0x21] = i
                self.b[e + 0x22] = 1
        n = sum(1 for k in range(20) if self.b[base + 4 + 0xE0 * k + 0x10] & 1)
        struct.pack_into("<i", self.b, base, n)
        self.b[0x34E] = n  # summary: "Number of registered Insectron teams"

    # ---- summary (0x50..0x350, SaveHeaderBuild_3e5520) --------------------------
    def summary(self):
        b = self.b
        cstr = lambda o, n: bytes(b[o:o + n]).split(b"\0", 1)[0].decode("latin-1")
        s = {"version": struct.unpack_from("<h", b, 4)[0], "counter": struct.unpack_from("<i", b, 8)[0],
             "payload_len": struct.unpack_from("<q", b, 0x10)[0],
             "play_time": struct.unpack_from("<d", b, 0x50)[0], "t8": struct.unpack_from("<q", b, 0x58)[0],
             "party_n": struct.unpack_from("<h", b, 0x60)[0], "party": []}
        for i in range(10):
            o = 0x64 + 0x28 * i
            nm = cstr(o, 16)
            if nm:
                cid, icon, lv = struct.unpack_from("<hhh", b, o + 16)
                x, y, z, a = struct.unpack_from("<4f", b, o + 24)
                s["party"].append({"name": nm, "id": cid, "icon": icon, "lv": lv, "pos": (x, y, z), "ang": a})
        s["camera"] = struct.unpack_from("<6f", b, 0x1F4)
        s["chapter"], _, s["progress"], s["key_items"] = struct.unpack_from("<hhhh", b, 0x20C)
        s["chapter_name"] = cstr(0x214, 0x80)
        s["var13"] = struct.unpack_from("<h", b, 0x294)[0]
        s["location_id"] = struct.unpack_from("<h", b, 0x298)[0]
        s["location"] = cstr(0x29A, 0x80)
        s["loc_m16"], s["party4"], s["party6"], s["partyA"] = struct.unpack_from("<hhhh", b, 0x31A)
        s["loc_pos"] = struct.unpack_from("<4f", b, 0x324)
        s["insectron_text"] = cstr(0x254, 0x40)
        s["flags1ea"], s["var5"], s["var6"], s["var7"] = struct.unpack_from("<Hhhh", b, 0x338)
        s["unlock_mask"] = "%016x" % struct.unpack_from("<Q", b, 0x340)[0]
        s["cages"] = bytes(b[0x348:0x350]).hex()
        return s

    def sync_summary(self):
        struct.pack_into("<h", self.b, 0x20C, self.chapter())
        fl = 0
        for k in range(8):
            fl |= self.flag(0x1EA + k) << k
        struct.pack_into("<Hhhh", self.b, 0x338, fl, self.var(5), self.var(6), self.var(7))
        struct.pack_into("<h", self.b, 0x294, self.var(0xD))

    # ---- digests ----------------------------------------------------------------
    def fix(self):
        n = struct.unpack_from("<q", self.b, 0x10)[0]
        self.b[0x20:0x30] = hashlib.md5(self.b[0x50:0x50 + n]).digest()
        self.b[0x40:0x50] = hashlib.md5(self.b[0x50:0x350]).digest()

    def check(self):
        errs = []
        if struct.unpack_from("<h", self.b, 4)[0] != VERSION:
            errs.append("version != 0x25 (bad data, error 9)")
        n = struct.unpack_from("<q", self.b, 0x10)[0]
        if hashlib.md5(self.b[0x50:0x350]).digest() != bytes(self.b[0x40:0x50]):
            errs.append("summary MD5 (+0x40) mismatch (error 0xB)")
        if hashlib.md5(self.b[0x50:0x50 + n]).digest() != bytes(self.b[0x20:0x30]):
            errs.append("payload MD5 (+0x20) mismatch (error 0xC)")
        return errs

    def write(self):
        self.fix()
        self.path.write_bytes(bytes(self.b))


def cmd_dump(a):
    s = Save(a.save)
    print(f"file {s.path}")
    for k, v in s.summary().items():
        print(f"  {k}: {v}")
    print(f"  story chapter {s.chapter()}")
    if a.flags or a.all:
        on = [n for n in range(2048) if s.flag(n)]
        try:
            import rgdata
            names = rgdata.flag_names()
        except Exception:  # no game data
            names = {}
        print(f"  flags set ({len(on)}):")
        for n in on:
            print(f"    {n:5d} {n:#05x}  {names.get(n, '')}")
    if a.vars or a.all:
        print("  vars: " + " ".join(f"{i}={s.var(i)}" for i in range(0x80) if s.var(i)))
    if a.chunks or a.all:
        def rec(lst):
            for c in lst:
                print(f"  {'  ' * c['depth']}chunk {c['kind']:2d} ver {c['ver']:5d} at {c['off']:#07x} len {c['len']:#06x}"
                      f"  {CHUNK_NAMES.get(c['kind'], '')}")
                rec(c["sub"])
        rec(s.chunks)
    errs = s.check()
    print("  digests: " + ("OK" if not errs else "; ".join(errs)))
    return 0


def parse_int(x):
    return int(x, 0)


def cmd_patch(a):
    s = Save(a.save)
    for sid in a.section:
        s.apply_section(sid, levels=not a.no_levels, abilities=a.abilities)
    for spec in a.learn:
        did, ids = spec.split(":", 1)
        bad = s.learn_abilities(parse_int(did), [parse_int(x) for x in ids.split(",") if x])
        if bad:
            print(f"saveedit: --learn {spec}: not placed {bad}")
    if a.no_help:
        for n in HELP_SHEET_FLAGS:
            s.set_flag(n, True)
    for n in a.set_flag:
        s.set_flag(parse_int(n), True)
    for n in a.clear_flag:
        s.set_flag(parse_int(n), False)
    for iv in a.var:
        i, v = iv.split("=")
        s.set_var(parse_int(i), parse_int(v))
    if a.chapter is not None:
        s.set_chapter(a.chapter)
    if not a.no_summary_sync:
        s.sync_summary()
    if a.location is not None:
        s.set_location(a.location)
    if a.spawn_jump is not None:
        import rgdata
        pl, x, y, z, yaw, _ = rgdata.map_jumps()[a.spawn_jump]
        s.set_spawn(pl, x, y, z, yaw)
    if a.spawn:
        pl, xyz = a.spawn.split(":", 1)
        s.set_spawn(int(pl, 0), *[float(v) for v in xyz.split(",")])
    if a.spawn or a.spawn_jump is not None or a.section:
        s.sync_area()
    for ov in a.party16:
        o, v = ov.split("=")
        s.set_party_s16(parse_int(o), parse_int(v))
    if a.add_item:
        s.add_items(a.add_item)
    for sid in a.section_insects:
        s.add_section_insects(sid, strong=a.strong_insects, limit=a.insect_limit)
    for spec in a.add_insect:
        f, _, nm = spec.partition(":")
        s.add_insect(parse_int(f), name=nm or None, strong=a.strong_insects)
    for k in a.unlock_group:
        s.unlock_item_group(parse_int(k))
    for t in a.insect_team:
        s.add_insect_team(t, formation=a.insect_formation)
    if a.summary_var5 is not None:
        struct.pack_into("<h", s.b, 0x33A, a.summary_var5)
    s.write()
    print(f"saveedit: wrote {s.path} (digests recomputed)")
    return 0


def cmd_copy(a):
    src, dst = Path(a.src), Path(a.dst)
    if dst.exists():
        shutil.rmtree(dst)
    shutil.copytree(src, dst, ignore=shutil.ignore_patterns("backups"))
    print(f"saveedit: copied {src} -> {dst}")
    return 0


def cmd_check(a):
    errs = Save(a.save).check()
    print("OK" if not errs else "\n".join(errs))
    return 1 if errs else 0


# 'Help Sheet: ...' story flags (bit_flag_param_EN 350..391): a set flag = that tutorial was
# shown, so the library cards set them all (no pop-ups in the smoke runs).
HELP_SHEET_FLAGS = list(range(350, 392))

# Manufactured game-save fixtures (docs/TEST-FIXTURES.md "Manufactured saves"): name ->
# (base card, patch arguments).  `make` rebuilds them from the base in out/fixtures/cards/.
# In front of the Insectron receptionist (NPC 24228: rc/param/zone/zl05_2_en.pac ZL05_*npc.cfg.bin
# #101/#102 place it at (6881.09, -889.8, 3358.88), yaw 0 = facing +z), facing it
INSECT_DESK = "4:6881.09,-919.8,3408.88,3.14159"
RECIPES = {
    "factory": ("save2", ["--set-flag", "0x3E8"]),
    # factory.py: every production plan known (the 72 'Obtained Factory Hint NNNN' story flags
    # 1100..1171; FactoryCompletionUpdate_3e7ae0 marks a plan known when its record's flag is
    # set) + 5 of each material (category 11, ids 16681..16730) for Set Material
    "factory_plans": ("save2", ["--set-flag", "0x3E8"] + [a for k in range(1100, 1172) for a in ("--set-flag", str(k))]
                      + [a for k in range(16681, 16731) for a in ("--add-item", f"{k}:5")]),
    # factory.py --card factory_parts: factory_plans + 10 of each factory part (category 18:
    # Source / Completion Table, Power Cord 16773, tubes, machines 16777..16786), so a plan's
    # layout can be powered and run (soak2 lane)
    "factory_parts": ("save2", ["--set-flag", "0x3E8"] + [a for k in range(1100, 1172) for a in ("--set-flag", str(k))]
                      + [a for k in range(16681, 16731) for a in ("--add-item", f"{k}:5")]
                      + [a for k in range(16771, 16787) if k != 16784 for a in ("--add-item", f"{k}:10")]),
    # factory.py --card factory_prod (cov3 lane): factory_plans + the Athanor / Assembler III parts
    # unlocked (item groups 34 / 35: the FACTORY Place list is the item-def table filtered by
    # ContainerViewItemFilterMatch_40c280, NOT the inventory; a part with an unlock group is listed
    # once its unlock time is > 0), so the alchemy plans can be processed (Athanor) and produced
    "factory_prod": ("save2", ["--set-flag", "0x3E8"] + [a for k in range(1100, 1172) for a in ("--set-flag", str(k))]
                     + [a for k in range(16681, 16731) for a in ("--add-item", f"{k}:5")]
                     + ["--unlock-group", "34", "--unlock-group", "35"]),
    # soak2 lane: the story Insectron venue (Zerard, jump 33) at the late story point, rank var 5
    # = 3 and var 7 = 4 (tournament wins so far: InsectBattleMatchUpdateMaybe_319800 grants the
    # rank reward through InsectronRewardLookupMaybe_3e84f0 when var 7 >= 4 and the player wins)
    "insect_story": ("save2", ["--section", "13020", "--spawn-jump", "33", "--no-help", "--var", "5=3",
                               "--var", "7=4", "--insect-formation", "--insect-team", "0:ALPHA:0,1,2,3,4",
                               "--insect-team", "1:BRAVO:5,6,7,8,9"]),
    # cov3 lane (insectstory.py): the venue card + the insect side of initial_status 115
    # 'Insectron E-5' (traps, 3 Rearing Cages, 15 named insects, feed, Insectron License) and its
    # vars: rank var 5 = 1 (E), var 6 = 1 (entered rank E), var 7 = 4 (battle 5 = the final),
    # so the receptionist (NPC 24228, map m04 script) offers "Continue from Rank E, Battle 5?"
    # and a win runs the rank reward (InsectBattleMatchUpdateMaybe_319800 ->
    # InsectronRewardLookupMaybe_3e84f0).  insect_final_s: the same with strong insects.
    "insect_final": ("save2", ["--section", "13020", "--spawn", INSECT_DESK, "--no-help", "--section-insects", "115",
                               "--var", "5=1", "--var", "6=1", "--var", "7=4"]),
    "insect_final_s": ("save2", ["--section", "13020", "--spawn", INSECT_DESK, "--no-help", "--section-insects", "115",
                                 "--strong-insects", "--var", "5=1", "--var", "6=1", "--var", "7=4"]),
    "insectron": ("save2", ["--var", "5=3", "--insect-team", "0:ALPHA:0,1,2,3,4",
                            "--insect-team", "1:BRAVO:5,6,7,8,9"]),
    # insectrun.py: the same two teams with their formation fields, so a Watch Battle is
    # played to the end (rematch prompt)
    "insectron_play": ("save2", ["--var", "5=3", "--insect-formation", "--insect-team", "0:ALPHA:0,1,2,3,4",
                                 "--insect-team", "1:BRAVO:5,6,7,8,9"]),
}


def all_recipes():
    import cardlib
    r = dict(RECIPES)
    for name in cardlib.LIBRARY:
        r[name] = cardlib.recipe(name)
    for name in cardlib.wide_names():
        r[name] = cardlib.wide_recipe(name)
    for name in cardlib.map_names():
        r[name] = cardlib.map_recipe(name)
    return r


def cmd_make(a):
    cards = Path(a.cards)
    rec = all_recipes()
    # no names: the original set (RECIPES + library); the soak2 sets by name or --wide / --maps
    names = list(a.names) or ([] if (a.wide or a.maps) else [n for n in rec if not n.startswith(("w_", "m_"))])
    if a.wide:
        names += [n for n in rec if n.startswith("w_")]
    if a.maps:
        names += [n for n in rec if n.startswith("m_")]
    for name in names:
        if name not in rec and name.startswith("m_"):
            rec[name] = cardlib.map_recipe(name)
        base, args = rec[name]
        cmd_copy(argparse.Namespace(src=str(cards / base), dst=str(cards / name)))
        main(["patch", str(cards / name)] + args)
    return 0


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    d = sp.add_parser("dump")
    d.add_argument("save")
    d.add_argument("--flags", action="store_true")
    d.add_argument("--vars", action="store_true")
    d.add_argument("--chunks", action="store_true")
    d.add_argument("--all", action="store_true")
    d.set_defaults(fn=cmd_dump)
    p = sp.add_parser("patch")
    p.add_argument("save")
    p.add_argument("--set-flag", action="append", default=[])
    p.add_argument("--clear-flag", action="append", default=[])
    p.add_argument("--var", action="append", default=[], help="I=V")
    p.add_argument("--chapter", type=int)
    p.add_argument("--summary-var5", type=int, help="only the summary's copy of var 5 (title INSECTRON row)")
    p.add_argument("--no-summary-sync", action="store_true")
    p.add_argument("--location", type=lambda x: int(x, 0),
                   help="transporter / location record id the party is placed at on load (party +0xF8)")
    p.add_argument("--section", type=int, metavar="SID", action="append", default=[],
                   help="apply initial_status5 section SID (1010 = ch 1 phase 10 .. 13020; rgdata.sections()); "
                        "repeatable, applied in order")
    p.add_argument("--no-help", action="store_true",
                   help="set the 'Help Sheet' flags 350..391 (tutorial pop-ups seen; bit_flag_param_EN)")
    p.add_argument("--no-levels", action="store_true", help="with --section: keep the character levels")
    p.add_argument("--abilities", action="store_true",
                   help="with --section: also apply the section's abilities (#106: learned bits + the "
                        "10 equip slots, CharaLearnAbility_3ad460)")
    p.add_argument("--learn", action="append", default=[], metavar="DATAID:ID,..",
                   help="learn abilities (ability_param_EN ids) for character DATAID (11001 Jaster ..)")
    p.add_argument("--spawn-jump", type=int, metavar="ID",
                   help="spawn at debug map jump point ID (dbg/map_jump_en.txt, rgdata.map_jumps())")
    p.add_argument("--spawn", metavar="PLANET:X,Y,Z,YAW",
                   help="planet id (party +0x4; 2 Rosa .. 10 ghost ship EX) and the party's position on CONTINUE")
    p.add_argument("--party16", action="append", default=[], metavar="OFF=V",
                   help="raw s16 at party object offset OFF (chunk 9)")
    p.add_argument("--add-item", action="append", default=[], metavar="ID[:N]",
                   help="append N (default 1) of item ID to the inventory (stacks merge; kind from "
                        "item_param_EN; e.g. factory parts 16777.. and materials 16681..)")
    p.add_argument("--unlock-group", action="append", default=[], metavar="K",
                   help="unlock item group K (StateBlock +0x840 / +0x880, ItemGroupUnlock_3cbac0): "
                        "factory parts Athanor 34, Assembler III 35 (item_param #102 [3])")
    p.add_argument("--section-insects", type=int, action="append", default=[], metavar="SID",
                   help="add an initial_status section's insect items (traps, rearing cages, named insects "
                        "in the cages, feed, Insectron License; e.g. 115 'Insectron E-5') on top of the inventory")
    p.add_argument("--insect-limit", type=int, help="with --section-insects: at most N insects")
    p.add_argument("--add-insect", action="append", default=[], metavar="ID[:NAME]",
                   help="add an insect (item_param category 20, 16850..) into the first Rearing Cage with room")
    p.add_argument("--strong-insects", action="store_true",
                   help="insects added by --section-insects / --add-insect get level 5, stats 100, HP x3, "
                        "attack / defense x4 (a quick story Insectron win, insectstory.py)")
    p.add_argument("--insect-team", action="append", default=[],
                   help="SLOT:TEAMNAME:SP[/VAR],SP..[@S]: a registered Insectron team (chunk 15) with 5 insects of "
                        "species SP (item def 0x14 / 2000+SP); the six stats = S (7 bits, default 40)")
    p.add_argument("--insect-formation", action="store_true",
                   help="with --insect-team: give the five insects their formation fields (+0x18 / +0x21 = "
                        "slot, +0x20 / +0x22 = 1) so all of them take the board (insectrun.py)")
    p.set_defaults(fn=cmd_patch)
    c = sp.add_parser("copy")
    c.add_argument("src")
    c.add_argument("dst")
    c.set_defaults(fn=cmd_copy)
    m = sp.add_parser("make", help="rebuild the manufactured cards (RECIPES) from their base card")
    m.add_argument("names", nargs="*")
    m.add_argument("--wide", action="store_true", help="+ the w_<library card> set (abilities, Burning Strike)")
    m.add_argument("--maps", action="store_true", help="+ the m_<jump id> map-sweep set (cardlib.map_points)")
    m.add_argument("--cards", default=str(Path(__file__).resolve().parents[2] / "out" / "fixtures" / "cards"))
    m.set_defaults(fn=cmd_make)
    k = sp.add_parser("check")
    k.add_argument("save")
    k.set_defaults(fn=cmd_check)
    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    sys.exit(main())
