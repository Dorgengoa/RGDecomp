#!/usr/bin/env python3
# SPDX-License-Identifier: CC0-1.0
"""Remove or list top-level C/C++ functions (and their leading comment blocks) by name.

    python tools/native/srcfuncs.py list FILE
    python tools/native/srcfuncs.py drop FILE NAME [NAME ...]     (in place)

A function is found by a line at column 0 containing `NAME(` that is not a prototype
(followed by a `{` before the next `;`); its body ends at the matching `}` at column 0.
The comment block directly above (lines starting with `/*`, ` *` or `//`) goes with it.
Used to fork gpu_core.cpp into the native device (docs/NATIVE-RENDER.md checkpoint 10).
"""
import re, sys

def spans(lines):
    out = []
    i = 0
    while i < len(lines):
        l = lines[i]
        m = re.match(r'^[A-Za-z_].*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(', l)
        if m and not l.rstrip().endswith(';') and not l.startswith(('#', 'typedef', 'struct ', 'enum ')):
            # find '{' before ';'
            j = i
            ok = False
            while j < len(lines) and j < i + 8:
                if '{' in lines[j]: ok = True; break
                if lines[j].rstrip().endswith(';'): break
                j += 1
            if ok:
                depth = 0
                k = j
                started = False
                while k < len(lines):
                    depth += lines[k].count('{') - lines[k].count('}')
                    if lines[k].count('{'): started = True
                    if started and depth <= 0: break
                    k += 1
                s = i
                while s > 0 and lines[s-1].lstrip().startswith(('/*', '*', '//')) and not lines[s-1].strip().startswith('*/') or (s > 0 and lines[s-1].strip().endswith('*/') and lines[s-1].lstrip().startswith(('/*','*'))):
                    s -= 1
                out.append((m.group(1), s, k))
                i = k + 1
                continue
        i += 1
    return out

def main():
    cmd, f = sys.argv[1], sys.argv[2]
    lines = open(f, encoding='utf-8').read().split('\n')
    sp = spans(lines)
    if cmd == 'list':
        for n, s, e in sp: print(f'{s+1}-{e+1} {n}')
        return
    names = set(sys.argv[3:])
    drop = set()
    found = set()
    for n, s, e in sp:
        if n in names:
            found.add(n)
            drop.update(range(s, e + 1))
    missing = names - found
    if missing: print('not found:', ' '.join(sorted(missing)), file=sys.stderr)
    lines = [l for i, l in enumerate(lines) if i not in drop]
    open(f, 'w', encoding='utf-8').write('\n'.join(lines))

main()
