"""First divergence of one chara's AI native-call sequence: port rows (brklog.py rows
--base-from-call --words 3) vs retail nat.txt (retnat.py)."""
import sys, re
port, ret, cid = sys.argv[1], sys.argv[2], int(sys.argv[3])
def P():
    cur = None
    for l in open(port):
        m = re.search(r'AiScript(RunEntry|Resume)_\w+ eax=\S+ args=\S+ (\S+) (\S+)', l)
        if m:
            a1, a2 = int(m.group(2), 16), int(m.group(3), 16)
            cur = a2 if 'RunEntry' in l else a1
            continue
        m = re.search(r'^(\d+) .* args=(\S+) .*target=(\w+?)_[0-9a-f]{6} dump=(\S+) (\S+)', l)
        if m and cur == cid:
            yield int(m.group(1)), m.group(3), int(m.group(2), 16) + 1, m.group(5)
def R():
    for l in open(ret):
        m = re.match(r'(\d+)\s+id (\d+) (\w+?)(?:_[0-9a-f]{6})? argc (\d+) vals (\S+) (\S+)', l)
        if m and int(m.group(2)) == cid and m.group(3) != '0x0':
            yield int(m.group(1)), m.group(3), int(m.group(4)) - 1, m.group(5)
p, r = list(P()), list(R())
print(len(p), 'port', len(r), 'retail')
# align on the first common name
for i, (a, b) in enumerate(zip(p, r)):
    if a[1] != b[1] or a[2] != b[2] or (a[3] != b[3] and not (a[3].startswith('0') and a[3][1] in '67')):
        print('diverge at', i)
        for k in range(max(0, i - 4), min(len(p), len(r), i + 8)):
            print('  port', p[k], '| retail', r[k])
        break
else:
    print('no divergence over', min(len(p), len(r)))
