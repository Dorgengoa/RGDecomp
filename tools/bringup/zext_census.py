"""Census (docs/PROTOS.md ret-zext): call sites whose retail listing zero-extends $v0
(dsll32 X,$2,0 .. dsrl32 Y,X,0). Run from the port root: python tools/bringup/zext_census.py"""
import sys, re, collections
sys.path.insert(0, 'out/bringup-checkpoint')
import listings
sys.path.insert(0, 'tools/stages')
import asmflow
out = collections.defaultdict(list)
for img, fn, tx in listings.all_listings():
    ins, _ = asmflow.parse_listing(tx)
    ins = [x for x in ins if x[0] != '.label']
    for i, (op, ops) in enumerate(ins):
        if op != 'jal':
            continue
        tgt = ops[0]
        # scan forward from after the delay slot: first reader of $2
        for j in range(i + 2, min(i + 10, len(ins))):
            o2, a2 = ins[j]
            if o2 == 'dsll32' and a2[1] == '$2' and a2[2] == '0':
                x = a2[0]
                for k in range(j + 1, min(j + 6, len(ins))):
                    o3, a3 = ins[k]
                    if o3 == 'dsrl32' and a3[1] == x and a3[2] == '0':
                        out[tgt].append(f'{img}:{fn}')
                        break
                break
            if any('$2' == a for a in a2[1:]) or (a2 and a2[0] == '$2') or o2 in ('jal', 'jalr'):
                break
for t, v in sorted(out.items(), key=lambda kv: -len(kv[1])):
    print(len(v), t, ' '.join(v[:6]))
