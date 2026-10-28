#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""List a VIF1 stream command by command (docs/NATIVE-RENDER.md "Tools").

  python tools/native/render_vifdump.py CAPTURE.vifcap [--from N] [--count N] [--data]

Prints one line per VIF command: stream word index, command, decoded fields
(UNPACK format / address / USN / FLG / count; STCYCL; MSCAL target; DIRECT
size), and with --data the first qwords of each UNPACK payload as hex.
"""
import struct, sys

FMT = {0x0: 'S-32', 0x1: 'S-16', 0x2: 'S-8', 0x4: 'V2-32', 0x5: 'V2-16', 0x6: 'V2-8',
       0x8: 'V3-32', 0x9: 'V3-16', 0xA: 'V3-8', 0xC: 'V4-32', 0xD: 'V4-16', 0xE: 'V4-8', 0xF: 'V4-5'}
NAMES = {0: 'NOP', 1: 'STCYCL', 2: 'OFFSET', 3: 'BASE', 4: 'ITOP', 5: 'STMOD', 6: 'MSKPATH3', 7: 'MARK',
         0x10: 'FLUSHE', 0x11: 'FLUSH', 0x13: 'FLUSHA', 0x14: 'MSCAL', 0x15: 'MSCALF', 0x17: 'MSCNT',
         0x20: 'STMASK', 0x30: 'STROW', 0x31: 'STCOL', 0x4A: 'MPG', 0x50: 'DIRECT', 0x51: 'DIRECTHL'}

def stream(path):
    b = open(path, 'rb').read()
    assert b[:8] == b'VIFCAP1\0'
    cnt = struct.unpack_from('<I', b, 8)[0]; o = 12; recs = {}
    for _ in range(cnt):
        k, n = struct.unpack_from('<II', b, o); recs.setdefault(k, b[o + 8:o + 8 + n]); o += 8 + n
    cl, wl = struct.unpack_from('<II', recs[2], 0)
    return recs[3], cl, wl

def payload_words(w, cl, wl):
    cmd = (w >> 24) & 0x7F; num = (w >> 16) & 0xFF; imm = w & 0xFFFF
    if cmd == 0x20: return 1
    if cmd in (0x30, 0x31): return 4
    if cmd == 0x4A: return (num or 256) * 2
    if cmd in (0x50, 0x51): return (imm or 65536) * 4
    if cmd >= 0x60:
        vn, vl = (cmd >> 2) & 3, cmd & 3
        n = num or 256
        bits = (32 >> vl) * (vn + 1)
        elems = n if wl <= cl else cl * (n // wl) + min(n % wl, cl)
        return (elems * bits + 31) // 32
    return 0

def main():
    a = sys.argv[1:]
    frm, count, data = 0, 400, '--data' in a
    if '--from' in a: frm = int(a[a.index('--from') + 1], 0)
    if '--count' in a: count = int(a[a.index('--count') + 1], 0)
    d, cl, wl = stream(a[0])
    ws = struct.unpack('<%dI' % (len(d) // 4), d)
    i = 0; k = 0
    while i < len(ws) and k < frm + count:
        w = ws[i]; cmd = (w >> 24) & 0x7F; num = (w >> 16) & 0xFF; imm = w & 0xFFFF
        if cmd == 1: cl, wl = w & 0xFF, (w >> 8) & 0xFF
        n = payload_words(w, cl, wl)
        if k >= frm:
            if cmd >= 0x60:
                s = 'UNPACK %-5s addr %03X%s%s num %d' % (FMT.get(cmd & 0xF, '?%X' % (cmd & 0xF)), imm & 0x3FF,
                                                        ' usn' if imm & 0x4000 else '', ' flg' if imm & 0x8000 else '', num or 256)
                if cmd & 0x10: s += ' mask'
            elif cmd in (0x14, 0x15): s = '%s %04X' % (NAMES[cmd], imm * 8)
            elif cmd == 1: s = 'STCYCL cl %d wl %d' % (cl, wl)
            elif cmd == 0x50: s = 'DIRECT %d qw' % imm
            elif cmd == 0x4A: s = 'MPG %04X %d pairs' % (imm * 8, num or 256)
            else: s = '%s %04X' % (NAMES.get(cmd, 'CMD%02X' % cmd), imm)
            print('%7d %08X %s' % (i, w, s))
            if data and cmd >= 0x60:
                pw = ws[i + 1:i + 1 + n]
                for j in range(0, min(len(pw), 16), 4):
                    print('            ' + ' '.join('%08X' % x for x in pw[j:j + 4]))
        i += 1 + n; k += 1

if __name__ == '__main__':
    main()
