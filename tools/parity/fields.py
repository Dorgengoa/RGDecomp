# SPDX-License-Identifier: CC0-1.0
"""Game-state fields the retail-parity harness samples (docs/TEST-FIXTURES.md "Retail parity").

A field is a value reached from a MAIN global through a pointer chain, read at the same
code point on both sides (the entry of GfxEndFrame_141c20 = once per game frame, after the
frame's logic):

    chain "=ADDR"           the global itself (no dereference)
    chain "@ADDR/H1/H2.."   q = *(u32 *)ADDR, then q = *(q + Hk) per hop
    value = the TYPE at (q or ADDR) + OFF

ADDR is the retail address of the global (the port's data symbol D_00xxxxxx has the same
name, so the port side resolves it through rg-game.map).  A field may carry a port-only
chain (`port=`) when the port keeps the value elsewhere (the newlib RNG state is a host
variable).  Struct layouts are retail's on both sides (the decomp uses retail offsets,
pointers are 4 bytes on i686), so values compare directly; TYPE "ptr" compares only
NULL-ness (addresses differ by design).

Groups: `core` (mode, RNG, frame time), `party` (records, money), `chara` (the action
manager's chara list: position, yaw, action, motion, command masks), `enemy`, `camera`,
`anim` (the leader's motion player).  parity.py --groups picks a subset.
"""
from __future__ import annotations

from dataclasses import dataclass, field as dfield

TYPES = {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "s32": 4, "f32": 4, "ptr": 4, "u64": 8}


@dataclass(frozen=True)
class Field:
    name: str
    chain: str          # "=ADDR" | "@ADDR[/H..]"
    off: int
    typ: str
    group: str
    port: tuple | None = None   # (chain, off) for the port when it differs ("&SYMBOL" = a host symbol)
    note: str = ""


def _chara_fields(k: int) -> list[Field]:
    """The k-th chara of the action manager's sorted DList (D_004B8680 +0x20 head; node +4
    next; the Chara at node +0x10; party ids 0..9 first, enemies 128+)."""
    ch = "@4B86A0" + "/4" * k
    n = f"c{k}."
    C = 0x10
    out = [
        Field(n + "id", ch, C + 0x424, "s16", "chara"),
        Field(n + "x", ch, C + 0x70, "f32", "chara"),
        Field(n + "y", ch, C + 0x74, "f32", "chara"),
        Field(n + "z", ch, C + 0x78, "f32", "chara"),
        Field(n + "yaw", ch, C + 0x64, "f32", "chara"),
        Field(n + "mphase", ch, C + 0x3FC, "f32", "chara", note="motion phase (CharaGetMotionFrame)"),
        Field(n + "act", ch, C + 0xA0C, "u32", "chara", note="action handle"),
        Field(n + "step", ch, C + 0xA20, "s32", "chara"),
        Field(n + "a24", ch, C + 0xA24, "f32", "chara"),
        Field(n + "acttime", ch, C + 0xAD0, "f32", "chara", note="action frame counter"),
        Field(n + "a34", ch, C + 0xA34, "u32", "chara"),
        Field(n + "a38", ch, C + 0xA38, "u32", "chara"),
        Field(n + "a44", ch, C + 0xA44, "u32", "chara"),
        Field(n + "cmd", ch, C + 0x568, "u64", "chara", note="battle command flags (SQUARE gun = bit 56)"),
        Field(n + "m570", ch, C + 0x570, "u64", "chara"),
        Field(n + "m3d0", ch, C + 0x3D0, "u64", "chara"),
        Field(n + "m3d8", ch, C + 0x3D8, "u32", "chara"),
        # its model's motion player (Chara +0x3F4 model, +0x1F0 motion list, +4 player;
        # MotionPlayerUpdate_172e00's Anim = player + 0x10)
        Field(n + "aframe", ch + "/404/1F4", 0x24, "s32", "anim"),
        Field(n + "atime", ch + "/404/1F4", 0x28, "f32", "anim"),
        Field(n + "astate", ch + "/404/1F4", 0x34, "s32", "anim"),
        Field(n + "ablend", ch + "/404/1F4", 0x44, "f32", "anim"),
        Field(n + "amode", ch + "/404/1F4", 0x4C, "s32", "anim"),
        Field(n + "aspeed", ch + "/404/1F4", 0x50, "f32", "anim"),
        Field(n + "adelta", ch + "/404/1F4", 0x54, "f32", "anim"),
    ]
    return out


def _party_fields(k: int) -> list[Field]:
    """Party record k (CharaSys D_004837C0 -> +0x14 manager -> +0x8 pool -> +0x8 base;
    0x4C8 bytes each): +0xC id, +0x14 HP, +0x1C max HP, +0x4B8 EXP."""
    ch = "@4837C0/14/8/8"
    b = k * 0x4C8
    n = f"p{k}."
    return [Field(n + "id", ch, b + 0xC, "s32", "party"),
            Field(n + "hp", ch, b + 0x14, "s32", "party"),
            Field(n + "w18", ch, b + 0x18, "s32", "party"),
            Field(n + "maxhp", ch, b + 0x1C, "s32", "party"),
            Field(n + "w20", ch, b + 0x20, "s32", "party"),
            Field(n + "exp", ch, b + 0x4B8, "s32", "party")]


def _enemy_fields(k: int) -> list[Field]:
    ch = "@4837C0/1C/10/8"
    b = k * 0x410
    n = f"e{k}."
    return [Field(n + "id", ch, b + 0xC, "s32", "enemy"),
            Field(n + "hp", ch, b + 0x14, "s32", "enemy"),
            Field(n + "maxhp", ch, b + 0x1C, "s32", "enemy")]


def _camera_fields(k: int) -> list[Field]:
    base = 0x4B5660 + k * 0x2F0
    n = f"cam{k}."
    out = []
    for nm, o in (("lx", 0x50), ("ly", 0x54), ("lz", 0x58), ("ex", 0x60), ("ey", 0x64), ("ez", 0x68)):
        out.append(Field(n + nm, f"={base:X}", o, "f32", "camera"))
    return out


def all_fields(nchara: int = 8, nparty: int = 4, nenemy: int = 6, ncam: int = 2) -> list[Field]:
    F = [
        Field("vbl", "=4810C4", 0, "u32", "core", note="game VBlank counter (alignment info, not compared)"),
        Field("mode", "=4B51A0", 0, "s32", "core"),
        Field("phase", "=4B51E0", 0, "s32", "core"),
        Field("ovl", "=47E254", 0, "s32", "core"),
        Field("rng", "@449858", 0xA8, "u64", "core", port=("&rg_crt_rand_next", 0),
              note="newlib rand state (_impure_ptr->_rand_next)"),
        Field("frametime", "@4810A4", 0xF10, "f32", "core", note="DrawCtx +0xF10 (DrawCtxGetFrameTime)"),
        Field("pause", "=48276C", 0, "s32", "core", note="GetPauseStep"),
        Field("leader", "@4837C0/18", 0x18E, "s16", "party"),
        Field("active0", "@4837C0/18", 0x190, "s16", "party"),
        Field("active1", "@4837C0/18", 0x192, "s16", "party"),
        Field("active2", "@4837C0/18", 0x194, "s16", "party"),
        Field("money", "@4837C0/18", 0x160, "s32", "party"),
    ]
    for k in range(nparty):
        F += _party_fields(k)
    for k in range(nchara):
        F += _chara_fields(k)
    for k in range(nenemy):
        F += _enemy_fields(k)
    for k in range(ncam):
        F += _camera_fields(k)
    return F


NOT_COMPARED = {"vbl"}


def select(groups: str | None = None, **kw) -> list[Field]:
    F = all_fields(**kw)
    if not groups:
        return F
    want = set(groups.split(","))
    return [f for f in F if f.group in want or f.name in ("vbl", "mode", "phase", "ovl")]


def parse_chain(chain: str) -> tuple[str, int, list[int]]:
    """-> (kind, addr, hops): kind '=' absolute global, '@' dereferenced, '&' host symbol."""
    kind = chain[0]
    if kind == "&":
        return kind, 0, []
    parts = chain[1:].split("/")
    return kind, int(parts[0], 16), [int(h, 16) for h in parts[1:]]
