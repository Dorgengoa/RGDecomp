#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""VU1 piece census for the native renderer (docs/NATIVE-RENDER.md "Tools").

  python tools/native/render_vucov.py DISDIR CAPTURE COV RUNS [--cov-out DIR]

DISDIR   listings from `rg-vucensus --dis DIR` (one file per retail MPG block,
         vu1_<packet>_<dest>_<sha1>.txt; lines "PC: UPPER LOWER  upper  lower").
CAPTURE  the VIFCAP1 file (its initial VU1 code memory names upload 0).
COV/RUNS outputs of rg-nr-vutrace --cov / --runs on that capture.

Prints the variant tuples (resident pieces at 0x320/0x960/0x10E0/0x1900/
0x2620/0x39D0) by run count and pair count, and per piece the share of its
pairs that ran.  --cov-out writes each executed piece's listing with the
execution count in front of every line (for reading the code that matters).
"""
import os, re, struct, sys, collections

def load_listings(d):
    L = {}
    for fn in os.listdir(d):
        m = re.match(r'vu1_([0-9A-F]{6})_([0-9A-F]{4})_([0-9a-f]+)\.txt$', fn)
        if not m:
            continue
        pk, dest = int(m.group(1), 16), int(m.group(2), 16)
        pairs = []
        for line in open(os.path.join(d, fn)):
            mm = re.match(r'([0-9A-F]{4}): ([0-9A-F]{8}) ([0-9A-F]{8})  (.*)$', line.rstrip('\n'))
            if mm:
                pairs.append((int(mm.group(1), 16), int(mm.group(2), 16), int(mm.group(3), 16), mm.group(4)))
        L[(pk, dest)] = dict(name='%06X@%04X' % (pk, dest), pk=pk, dest=dest, pairs=pairs, file=fn)
    return L

def fnv(l):
    if 'fnv' not in l:
        h = 2166136261
        for pc, uw, lw, _ in l['pairs']:
            for b in struct.pack('<II', lw, uw):
                h = ((h ^ b) * 16777619) & 0xFFFFFFFF
        l['fnv'] = h
    return l['fnv']

def capture_code(path):
    b = open(path, 'rb').read()
    assert b[:8] == b'VIFCAP1\0'
    n = struct.unpack_from('<I', b, 8)[0]
    off = 12
    for _ in range(n):
        kind, nb = struct.unpack_from('<II', b, off)
        if kind == 1:
            return b[off + 8 + 0x4000: off + 8 + 0x8000]
        off += 8 + nb
    return None

def main():
    a = sys.argv[1:]
    covout = None
    if '--cov-out' in a:
        i = a.index('--cov-out'); covout = a[i + 1]; del a[i:i + 2]
    disdir, cap, covp, runsp = a
    L = load_listings(disdir)
    code0 = capture_code(cap)
    # upload id -> listing key
    up = {}
    cov = collections.defaultdict(int)
    for line in open(covp):
        f = line.rstrip('\n').split('\t')
        if f[0] == 'U':
            uid, dest, nb = int(f[1]), int(f[2], 16), int(f[3])
            w = [int(x, 16) for x in f[4:8]]
            if uid == 0:
                up[0] = None
                continue
            hit = None
            h = int(f[8], 16)
            for k, l in L.items():
                if l['dest'] == dest and len(l['pairs']) * 8 == nb and fnv(l) == h:
                    hit = k
            up[uid] = hit
        elif f[0] == 'C':
            cov[(int(f[1]), int(f[2], 16))] += int(f[3])
    # upload 0: which listings match the initial code memory
    init = {}
    for k, l in L.items():
        ok = all(struct.unpack_from('<II', code0, pc) == (lw, uw) for pc, uw, lw, _ in l['pairs'])
        if ok:
            for pc, _, _, _ in l['pairs']:
                init[pc] = k

    def piece_at(uid, pc):
        if uid == 0:
            return init.get(pc)
        return up.get(uid)

    def name(k):
        return L[k]['name'] if k else '?'

    runs = [l.rstrip('\n').split('\t') for l in open(runsp)][1:]
    tup = collections.Counter(); tpairs = collections.Counter(); entry = collections.Counter()
    epairs = collections.Counter()
    for r in runs:
        e = int(r[1], 16); pr = int(r[2])
        entry[e] += 1; epairs[e] += pr
        if e in (0x328, 0x330):
            t = tuple(name(piece_at(int(r[5 + i]), base)) for i, base in
                      enumerate((0x320, 0x960, 0x10E0, 0x1900, 0x2620, 0x39D0)))
            tup[t] += 1; tpairs[t] += pr
    tot = sum(epairs.values())
    print('entries (runs, pairs, share):')
    for e, n in entry.most_common():
        print('  %04X %6d %9d %5.1f%%' % (e, n, epairs[e], 100.0 * epairs[e] / max(tot, 1)))
    print('model-program variant tuples (0x320 0x960 0x10E0 0x1900 0x2620 0x39D0): runs, pairs, share')
    for t, n in tpairs.most_common():
        print('  %-90s %6d %9d %5.1f%%' % (' '.join(t), tup[t], n, 100.0 * n / max(tot, 1)))
    # per-piece coverage
    per = collections.defaultdict(lambda: [0, 0, set()])
    for (uid, pc), n in cov.items():
        k = piece_at(uid, pc)
        per[k][0] += n
        per[k][2].add(pc)
    print('pieces executed (pairs run, distinct pcs / size):')
    for k, v in sorted(per.items(), key=lambda kv: -kv[1][0]):
        size = len(L[k]['pairs']) if k else 0
        print('  %-14s %10d  %4d / %4d' % (name(k), v[0], len(v[2]), size))
    if covout:
        os.makedirs(covout, exist_ok=True)
        cnt = collections.defaultdict(int)
        for (uid, pc), n in cov.items():
            cnt[(piece_at(uid, pc), pc)] += n
        for k in per:
            if not k:
                continue
            with open(os.path.join(covout, L[k]['file']), 'w') as f:
                for pc, uw, lw, text in L[k]['pairs']:
                    f.write('%9d %04X: %s\n' % (cnt.get((k, pc), 0), pc, text))

if __name__ == '__main__':
    main()
