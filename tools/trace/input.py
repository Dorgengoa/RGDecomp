# SPDX-License-Identifier: CC0-1.0
"""Deterministic scripted pad input for PCSX2 reference runs.

Mechanism ("guest input table"):
  * An input script lists (first_vbl, last_vbl, buttons). It is compiled into a
    table of u16 button words, one per game VBlank count, and written by PINE
    into unused EE RAM (TABLE).
  * A 12-instruction trampoline (TRAMP) is written next to it, and the game's
    pad decoder FUN_00184df0 is patched at 0x184E58 to jump there. After the
    game computes its active-high button word for port 0 from the real pad
    frame, the trampoline ORs in table[vbl], where vbl is the game's own
    VBlank counter [0x004810C4].
  So the button word the game sees on VBlank N comes from table[N], no matter
  how host timing jitters. The port gets the same input by ORing the same
  table entry into the same word (pad struct +4 = 0x004B2574) for the same N.

The hook must be in place before the game's first pad read, otherwise the
extra instructions would start at a host-timing-dependent point. install()
waits for the ELF to be loaded (original opcode appears at the hook site) and
patches immediately; the game opens the pad seconds later.

Game button bits (active high, = SCE pad bits): see BUTTONS.

Sticks (opt-in, 2026-10-18): `#!stick` lines (docs/INPUT.md "Scripted sticks", the
port's format: `#!stick FIRST LAST LX LY [RX RY]` after a `#!stick 1 0` header)
compile into a second table of u32 words at STICK_TABLE (bytes RX, RY, LX, LY =
the scePadRead frame bytes 4..7), a window of at most STICK_MAX VBlanks starting at
the first stick line (the free EE RAM between probe.py's log ring and its DATA). Only a script WITH stick lines gets the longer
trampoline (trampoline(sticks=True)): it also stores table2[vbl], when non-zero,
over the frame's stick bytes at 0x34($sp) before the decoder copies them into the
pad struct. Scripts without stick lines keep the original 17-word trampoline, so
golden runs are cycle-identical to before.
"""
import struct
import time

HOOK = 0x00184E58          # xori v0,v0,0xFFFF ; andi v0,v0,0xFFFF ; (L00184E60)
HOOK_ORIG = (0x3842FFFF, 0x3042FFFF)
RESUME = 0x00184E60
VBL = 0x004810C4
PAD0_DST = 0x004B2574      # FUN_00184df0 arg0 ($s1) for port 0
TRAMP = 0x000F0000         # 0x98000-0xFFFFF is zero after boot (EELOAD is long gone)
TABLE = 0x000F0100         # u32 count, then u16 words
MAX_ENTRIES = (0x00100000 - TABLE - 8) // 2   # 32636 VBlanks = 9.1 minutes
STICK_TABLE = 0x000E0020   # u32 base vbl, u32 count, then u32 per VBlank (RX | RY<<8 | LX<<16 | LY<<24), 0 = real pad
STICK_MAX = (0x000E1000 - STICK_TABLE - 8) // 4   # 1014 VBlanks (probe.py: LOG ring ends 0xE0010, DATA 0xE1000)

BUTTONS = {
    "L2": 0x0001, "R2": 0x0002, "L1": 0x0004, "R1": 0x0008,
    "TRIANGLE": 0x0010, "CIRCLE": 0x0020, "CROSS": 0x0040, "SQUARE": 0x0080,
    "SELECT": 0x0100, "L3": 0x0200, "R3": 0x0400, "START": 0x0800,
    "UP": 0x1000, "RIGHT": 0x2000, "DOWN": 0x4000, "LEFT": 0x8000,
}


def _j(target):
    return (2 << 26) | ((target >> 2) & 0x03FFFFFF)


def _r(op, rs, rt, rd, sa, fn):
    return (op << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (sa << 6) | fn


def _i(op, rs, rt, imm):
    return (op << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


V0, V1, A2, A3, S1, SP = 2, 3, 6, 7, 17, 29


def trampoline(sticks=False):
    # v0 = buttons (xori already done in the hook's delay slot); v1,a2,a3 are dead here.
    hi = lambda a: (a + 0x8000) >> 16
    lo = lambda a: a & 0xFFFF
    code = [
        _i(0x0C, V0, V0, 0xFFFF),                 # andi  v0,v0,0xffff   (original insn)
        _i(0x0F, 0, A2, hi(PAD0_DST)),            # lui   a2,%hi(PAD0_DST)
        _i(0x09, A2, A2, lo(PAD0_DST)),           # addiu a2,a2,%lo
        _i(0x05, S1, A2, 8),                      # bne   s1,a2,+8 -> out
        _i(0x0F, 0, V1, hi(VBL)),                 # lui   v1,%hi(VBL)       (delay slot, harmless)
        _i(0x23, V1, V1, lo(VBL)),                # lw    v1,%lo(VBL)(v1)
        _i(0x0F, 0, A2, hi(TABLE)),               # lui   a2,%hi(TABLE)
        _i(0x23, A2, A3, lo(TABLE)),              # lw    a3,%lo(TABLE)(a2) = count
        _i(0x09, A2, A2, lo(TABLE)),              # addiu a2,a2,%lo(TABLE)
        _r(0, V1, A3, A3, 0, 0x2B),               # sltu  a3,v1,a3
        _i(0x04, A3, 0, 4),                       # beq   a3,zero,+4 -> out
        _r(0, 0, V1, V1, 1, 0x00),                # sll   v1,v1,1           (delay slot)
        _r(0, A2, V1, A2, 0, 0x21),               # addu  a2,a2,v1
        _i(0x25, A2, A3, 4),                      # lhu   a3,4(a2)
        _r(0, V0, A3, V0, 0, 0x25),               # or    v0,v0,a3
        # out:
        _j(RESUME),                               # j     0x184E60
        0,                                        # nop
    ]
    # branch offsets above: bne at idx3 -> out at idx15: 15-(3+1)=11; beq idx10 -> 15-11=4
    code[3] = _i(0x05, S1, A2, 15 - 4)
    code[10] = _i(0x04, A3, 0, 15 - 11)
    if not sticks:
        return code
    # sticks: v1 = vbl*2 here; i = vbl - base; if i < count and table2[i] != 0,
    # store it over the frame's stick bytes (sp+0x34..0x37: RX RY LX LY; the
    # scePadRead buffer is at sp+0x30)
    out = len(code) - 2
    code[out:out] = [
        _r(0, 0, V1, V1, 1, 0x02),                # srl   v1,v1,1   -> vbl
        _i(0x0F, 0, A2, hi(STICK_TABLE)),         # lui   a2,%hi(STICK_TABLE)
        _i(0x23, A2, A3, lo(STICK_TABLE)),        # lw    a3,%lo(STICK_TABLE)(a2)    base
        _r(0, V1, A3, V1, 0, 0x23),               # subu  v1,v1,a3
        _i(0x23, A2, A3, lo(STICK_TABLE) + 4),    # lw    a3,%lo+4(a2)               count
        _r(0, V1, A3, A3, 0, 0x2B),               # sltu  a3,v1,a3
        _i(0x04, A3, 0, 6),                       # beq   a3,zero,out
        _r(0, 0, V1, V1, 2, 0x00),                # sll   v1,v1,2   (delay slot)
        _r(0, A2, V1, A2, 0, 0x21),               # addu  a2,a2,v1
        _i(0x23, A2, A3, lo(STICK_TABLE) + 8),    # lw    a3,%lo+8(a2)
        _i(0x04, A3, 0, 2),                       # beq   a3,zero,out
        0,                                        # nop
        _i(0x2B, SP, A3, 0x34),                   # sw    a3,0x34(sp)
    ]
    new_out = out + 13
    code[out + 6] = _i(0x04, A3, 0, new_out - (out + 7))
    code[out + 10] = _i(0x04, A3, 0, new_out - (out + 11))
    code[3] = _i(0x05, S1, A2, new_out - 4)
    code[10] = _i(0x04, A3, 0, new_out - 11)
    return code


def parse_sticks(path):
    """`#!stick` lines -> [(first, last, word)]; [] when the script has none.
    Same syntax and meaning as the port (src/host/host_script.c): bytes 0..255,
    RX RY centred when omitted, a later line overrides an earlier one."""
    events, version = [], None
    with open(path, encoding="utf-8") as f:
        for ln, line in enumerate(f, 1):
            line = line.split("#!stick", 1)
            if len(line) != 2 or not line[0].strip() == "":
                continue
            vals = [int(x, 0) for x in line[1].split("#", 1)[0].split()]
            if version is None:
                if vals != [1, 0]:
                    raise SystemExit("%s:%d: '#!stick 1 0' header expected first" % (path, ln))
                version = 1
                continue
            if len(vals) not in (4, 6) or any(not 0 <= v <= 255 for v in vals[2:]):
                raise SystemExit("%s:%d: '#!stick FIRST LAST LX LY [RX RY]' expected" % (path, ln))
            a, b, lx, ly = vals[:4]
            rx, ry = vals[4:6] if len(vals) == 6 else (0x80, 0x80)
            w = rx | ry << 8 | lx << 16 | ly << 24
            if w == 0:
                raise SystemExit("%s:%d: all-zero sticks cannot be expressed (0 = real pad)" % (path, ln))
            events.append((a, b, w))
    return events


def build_stick_table(events):
    """-> [base, count, word...] (u32s), or None when there are no stick lines."""
    if not events:
        return None
    base = min(a for a, _, _ in events)
    end = max(b for _, b, _ in events) + 1
    if end - base > STICK_MAX:
        raise SystemExit("stick lines span %d vblanks (max %d in one script)" % (end - base, STICK_MAX))
    words = [0] * (end - base)
    for a, b, w in events:
        for v in range(a, b + 1):
            words[v - base] = w
    return [base, len(words)] + words


def parse_script(path):
    """Lines: `first_vbl last_vbl BUTTON[+BUTTON...]` (inclusive, game VBlank
    counter values) or `first_vbl BUTTON` for a single VBlank. '#' comments."""
    events = []
    with open(path, encoding="utf-8") as f:
        for ln, line in enumerate(f, 1):
            line = line.split("#", 1)[0].strip()
            if not line:
                continue
            parts = line.split()
            a = int(parts[0], 0)
            if len(parts) == 2:
                b, btn = a, parts[1]
            else:
                b, btn = int(parts[1], 0), parts[2]
            mask = 0
            for name in btn.upper().split("+"):
                if name not in BUTTONS:
                    raise SystemExit("%s:%d: unknown button %r" % (path, ln, name))
                mask |= BUTTONS[name]
            events.append((a, b, mask))
    return events


def build_table(events):
    """Always MAX_ENTRIES long (zero padded): the trampoline then takes the
    same path, with the same EE cycle cost, on every VBlank of every run, so
    a run with input and one without differ only by the buttons. (A shorter
    table made the no-input path 3 instructions shorter, and that alone moved
    IOP/EE state within ~10 game frames.)"""
    n = max((b for _, b, _ in events), default=-1) + 1
    if n > MAX_ENTRIES:
        raise SystemExit("input script too long (%d vblanks, max %d)" % (n, MAX_ENTRIES))
    words = [0] * MAX_ENTRIES
    for a, b, m in events:
        for v in range(a, b + 1):
            words[v] |= m
    return words


def install(pine, words, timeout=60, sampler=None, extra=(), precheck=None, sticks=None):
    """Wait for the ELF, then write table + trampoline + hook. Returns the
    game VBlank count observed right after patching (must be before the game
    starts polling the pad for the run to be deterministic).

    With a live.LiveSampler, the writes are made while PCSX2's CPU thread is
    frozen at a vsync (the BIOS 60 Hz grid; the ELF loads around vsync 28), so
    the recompiler's code-page invalidation never races the running EE.

    extra = [(addr, bytes)] written in the same frozen call (probe.py's
    trampolines and code patches, written after the table and trampoline);
    precheck() runs first, frozen, and must return True (e.g. "the area is
    still zero").  sticks = build_stick_table(...) words or None (no stick
    lines: the original trampoline)."""
    t0 = time.time()
    while True:  # wait for the main ELF to be loaded
        if (pine.read32(HOOK), pine.read32(HOOK + 4)) == HOOK_ORIG:
            break
        if time.time() - t0 > timeout:
            raise RuntimeError("hook site never showed the original code")
        time.sleep(0.002)
    blob = struct.pack("<I%dH" % len(words), len(words), *words)
    blob += bytes(-len(blob) % 8)
    code = trampoline(sticks=bool(sticks))
    code += [0] * (-len(code) % 2)
    sblob = struct.pack("<%dI" % len(sticks), *sticks) if sticks else b""
    sblob += bytes(-len(sblob) % 8)

    def write():
        if precheck is not None and not precheck():
            raise RuntimeError("install precheck failed (probe area not free)")
        if sblob:
            pine.write_block(STICK_TABLE, sblob)
        pine.write_block(TABLE, blob)
        pine.write_block(TRAMP, struct.pack("<%dI" % len(code), *code))
        # j TRAMP with the original xori moved into the delay slot; one 64-bit
        # write so the two words can never be seen half-patched.
        pine.write64(HOOK, _j(TRAMP) | (HOOK_ORIG[0] << 32))
        for addr, data in extra:
            if len(data) == 8 and addr % 8 == 0:
                pine.write64(addr, struct.unpack("<Q", data)[0])   # a code patch: one write
            elif len(data) == 8:
                pine.write32(addr, struct.unpack_from("<I", data, 0)[0])
                pine.write32(addr + 4, struct.unpack_from("<I", data, 4)[0])
            else:
                pine.write_block(addr, data + bytes(-len(data) % 8))

    if sampler is None:
        write()
    else:
        on_grid = lambda c: min((c & 0xFFFFFFFF) % 4915200, -(c & 0xFFFFFFFF) % 4915200) < 3000
        if sampler.frozen_call(on_grid, write, timeout=timeout) is None:
            raise RuntimeError("no vsync idle to install the input hook")
    return pine.read32(VBL)


def verify(snap, words, sticks=None):
    """Check (in a snapshot) that hook, trampoline and table are intact."""
    ee = snap.ee
    ok = struct.unpack_from("<II", ee, HOOK) == (_j(TRAMP), HOOK_ORIG[0])
    ok &= all(struct.unpack_from("<I", ee, TRAMP + 4 * k)[0] == w
              for k, w in enumerate(trampoline(sticks=bool(sticks))))
    ok &= struct.unpack_from("<I", ee, TABLE)[0] == len(words)
    return ok
