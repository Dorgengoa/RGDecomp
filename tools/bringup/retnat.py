# SPDX-License-Identifier: CC0-1.0
"""Decode a PCSX2 AI-native trace (probe.py --fn "Nat:0x176600:w=@0x4DB928,a12+8,a2+0xc,a2+0x14,a2+0x1c,a2+0x24"
--fn "RunEntry:0x2c1550") into one line per native call; the natives table is read from a
savestate's eeMemory.bin taken in the same scene.  Pair with natdiff.py and a port trace
(RG_BREAK on ScriptVmExec's `call *%ecx`, brklog.py rows --base-from-call --words 3).

    retnat.py TRACE.jsonl FROM_VBL EE.bin > nat.txt
"""
import json, os, re, struct, sys
HERE = os.path.dirname(os.path.abspath(__file__))
m = open(sys.argv[3], 'rb').read()
w = lambda a: struct.unpack_from('<I', m, a)[0]
names = {}
src = open(os.path.join(HERE, '..', '..', 'game', 'src', 'main_data', 'data2c_004511E0.c'),
           encoding='utf-8', errors='replace').read()
for fn, a in re.findall(r'&(\w+_([0-9a-fA-F]{6,8}))\b', src):
    names[int(a, 16)] = fn
for l in open(sys.argv[1]):
    r = json.loads(l)
    if r.get('t') != 'r' or r['vbl'] < int(sys.argv[2]):
        continue
    if r['fn'] == 'RunEntry':
        print(r['vbl'], 'RUNENTRY label', r['a'][1], 'id', r['a'][2])
        continue
    d = r['d']; idx = r['a'][0]; tbl = d[1]
    fa = w(tbl + 4 * idx) if tbl and tbl < 0x2000000 else 0
    print(r['vbl'], '  id', d[0], names.get(fa, hex(fa)), 'argc', r['a'][1] + 1,
          'vals', ' '.join('%08x' % x for x in d[2:]))
