#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Decode the game's condition strings (the base64 op streams in .cfg tables: encounter-table
conditions `*_encount_param_EN` #201, trigger_param6, livet / ptalk conditions) into readable
expressions, for the progression census (tools/fixtures/progression.py, docs/GAME-PROGRESSION.md).

    python tools/fixtures/condexpr.py STRING [STRING ..]      # bytes + expression

Format (decomp): Base64Decode_36a700 is base64 with the bits LSB first (6-bit groups packed
from bit 0 of each byte up); ScriptExecOpStream_3dffa0 runs the bytes: op = high nibble.
  0x0T  constant of variant type T (VariantSetRaw_36ee90: 1 = u8, 3 = s16, 5 = s32, 6 = f32)
  0x2N  query, N ignored here: next byte = length L, then L bytes = selector + args
        (ScriptEvalQueryOpMaybe_3daaf0): 70 02 0B = chapter (StateGetChapter_3cd5b0);
        76 74 <s16 code> 02 0B = progress slot of code (ProgressGetByCode_3cd260: chapter*10 +
        sub-chapter, e.g. 10 = ch1, 81 = ch8-A); 64 65/66 <s16 n> 07|0B = story flag n
        (StateFlagTest_3ccd70); 67 68/69 <s16 i> = var i (StateVarGet_3ccac0); 6A 6B/6C <s16 n>
        = flag2 n; 6D 6E/6F <s16 n> = flag256 n; D3 0D = floor (PartyGetFloorNum_3cb000, ghost
        ship floors); others print as Q[hex]
  0x8_  binary op, next byte (ScriptBinaryOpExec_3da740): 1 == 2 != 3 > 4 < 5 >= 6 <= 7 && 8 ||
        9 = (assign) 10 + 11 - 12 * 13 / 15 % 16 & 17 | 18 ^ 20 ! 21 ~
  0x3_/0x4_ commands (actions), 0x5_ scope (+1 byte), 0x6_/0x7_ call (+1 byte), 0x1_ skip:
        printed as <op..> and the decode stops (conditions in the encounter tables have none).
Only what the encounter tables and fixed-battle triggers need is decoded; unknown bytes are
shown in hex, never guessed."""
from __future__ import annotations

import struct
import sys

BINOP = {1: "==", 2: "!=", 3: ">", 4: "<", 5: ">=", 6: "<=", 7: "&&", 8: "||", 9: "=", 10: "+", 11: "-",
         12: "*", 13: "/", 14: "//", 15: "%", 16: "&", 17: "|", 18: "^"}
CONST_SIZE = {1: 1, 2: 1, 3: 2, 4: 2, 5: 4, 6: 4}


def b64_lsb(s: str) -> bytes:
    """Base64Decode_36a700."""
    L = len(s)
    if L < 3:
        return b""
    n = L * 6 // 8
    for _ in range(2):
        if s[L - 1] != "=":
            break
        L -= 1
        n -= 1
    out = bytearray(n)
    for i in range(L):
        c = s[i]
        if "A" <= c <= "Z":
            v = ord(c) - 65
        elif "a" <= c <= "z":
            v = ord(c) - 71
        elif "0" <= c <= "9":
            v = ord(c) + 4
        elif c == "+":
            v = 62
        elif c == "/":
            v = 63
        else:
            v = 0
        idx, bit = i * 6 // 8, i * 6 % 8
        if idx < n:
            out[idx] |= (v << bit) & 0xFF
        if idx < n - 1:
            out[idx + 1] |= (v >> (8 - bit)) & 0xFF
    return bytes(out)


def _s16(b, i):
    return struct.unpack_from("<h", b, i)[0] if i + 2 <= len(b) else None


def query(q: bytes) -> str:
    if not q:
        return "Q[]"
    s = q[0]
    if s == 0x70 and q[1:3] == b"\x02\x0b":
        return "chapter"
    if s == 0x76 and len(q) >= 6 and q[1] in (0x74, 0x75) and q[4:6] == b"\x02\x0b":
        code = _s16(q, 2)
        return f"progress[{code}]"
    if s == 0x98 and q[1:3] == b"":
        return "battle"   # current battle id (CharaSysGetEncounterIdMaybe_3a36d0; lane scenario4)
    if s == 0x98 and len(q) >= 4 and q[1] in (0x99, 0x9A):
        return f"fixed({_s16(q, 2)})"   # named fixed-battle id constant
    if s == 0xD3 and q[1:2] == bytes([0x0D]):
        return "floor"
    names = {0x64: "flag", 0x67: "var", 0x6A: "flag2", 0x6D: "flag256"}
    if s in names and len(q) >= 4:
        return f"{names[s]}[{_s16(q, 2)}]"
    return "Q[" + q.hex(" ") + "]"


def decode(s: str) -> str:
    """Infix expression of a condition string ('' -> 'always')."""
    if not s:
        return "always"
    b = b64_lsb(s)
    st, i = [], 0
    try:
        while i < len(b):
            c = b[i]
            op, lo = c >> 4, c & 0xF
            i += 1
            if op == 0:
                n = CONST_SIZE.get(lo)
                if n is None:
                    st.append(f"<const{lo}?>")
                    break
                raw = b[i:i + n]
                if lo == 6:
                    st.append(f"{struct.unpack('<f', raw)[0]:g}")
                else:
                    st.append(str(int.from_bytes(raw, "little", signed=lo in (3, 5))))
                i += n
            elif op == 2:
                L = b[i]
                st.append(query(b[i + 1:i + 1 + L]))
                i += 1 + L
            elif op == 8:
                k = b[i]
                i += 1
                if k in (20, 21):
                    a = st.pop()
                    st.append(("!" if k == 20 else "~") + a)
                else:
                    r = st.pop()
                    l = st.pop()
                    st.append(f"({l} {BINOP.get(k, f'op{k}')} {r})")
            else:
                st.append(f"<op{c:02x} {b[i - 1:].hex(' ')}>")
                break
    except (IndexError, struct.error):
        st.append("<truncated>")
    e = " ; ".join(st)
    if e.startswith("(") and e.endswith(")") and len(st) == 1:
        e = e[1:-1]
    return e


def main(argv=None):
    for s in (argv if argv is not None else sys.argv[1:]):
        print(f"{s}\n  {b64_lsb(s).hex(' ')}\n  {decode(s)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
