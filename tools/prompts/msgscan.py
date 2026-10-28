#!/usr/bin/env python3
"""Scope the "START / SELECT in message words" remap (docs/P6-STATUS.md,
docs/PROMPTS.md "Missing glyphs"): scan every file in the DATA*.HD6 archives
(and the entries of Level-5 packs inside them) for button words, and report
where they occur.  Read-only; prints counts and short context (no file is
written unless -o is given).  Text is matched as raw bytes, so compressed
entries are reported as "no hit" (listed by --list-unreadable).

  python -I tools/prompts/msgscan.py --data data
  python -I tools/prompts/msgscan.py --data data --words START,SELECT --context 40
"""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'assets'))
import gaiji  # noqa: E402  (Hd6, pak_entries)

DEFAULT_WORDS = ['START', 'SELECT', 'Start button', 'SELECT button', 'directional button',
                 'left analog stick', 'right analog stick', 'L3', 'R3', 'DUALSHOCK']


def scan_blob(where, blob, pats, hits, ctx):
    for w, p in pats:
        for m in p.finditer(blob):
            a, b = max(0, m.start() - ctx), min(len(blob), m.end() + ctx)
            snip = blob[a:b].decode('cp932', 'replace').replace('\n', ' ').replace('\r', ' ')
            hits.append((w, where, m.start(), snip))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--data', default='data')
    ap.add_argument('--words', default=','.join(DEFAULT_WORDS))
    ap.add_argument('--context', type=int, default=30)
    ap.add_argument('--max-per-file', type=int, default=3)
    ap.add_argument('-o', help='write every hit as TSV here')
    ap.add_argument('--ext', default='', help='only files / pack entries with this suffix (e.g. .txt)')
    a = ap.parse_args()
    sys.stdout.reconfigure(errors='replace')
    words = [w for w in a.words.split(',') if w]
    pats = [(w, re.compile(re.escape(w.encode('ascii')) + rb'(?![A-Za-z])')) for w in words]
    hits = []
    nfiles = 0
    import glob
    for hd6 in sorted(glob.glob(os.path.join(a.data, 'DATA*.HD6'))):
        arc = gaiji.Hd6(hd6)
        for path in sorted(arc.files):
            blob = arc.read(path)
            nfiles += 1
            where = '%s:%s' % (os.path.basename(hd6), path)
            try:
                ents = gaiji.pak_entries(blob) if path.lower().endswith('.pak') else []
            except ValueError:
                ents = []
            if ents:
                for name, off, size in ents:
                    if a.ext and not name.lower().endswith(a.ext): continue
                    scan_blob(where + '/' + name, blob[off:off + size], pats, hits, a.context)
            elif not a.ext or path.lower().endswith(a.ext):
                scan_blob(where, blob, pats, hits, a.context)
    per = {}
    for w, where, off, snip in hits:
        per.setdefault(w, {}).setdefault(where, []).append((off, snip))
    print('files scanned: %d, hits: %d' % (nfiles, len(hits)))
    for w in words:
        files = per.get(w, {})
        print('\n== %s: %d hits in %d files' % (w, sum(len(v) for v in files.values()), len(files)))
        for where in sorted(files):
            for off, snip in files[where][:a.max_per_file]:
                print('  %s +%#x  %s' % (where, off, snip))
            if len(files[where]) > a.max_per_file:
                print('  %s  ... %d more' % (where, len(files[where]) - a.max_per_file))
    if a.o:
        with open(a.o, 'w', encoding='utf-8') as f:
            f.write('word\tfile\toffset\tcontext\n')
            for w, where, off, snip in hits:
                f.write('%s\t%s\t%#x\t%s\n' % (w, where, off, snip.replace('\t', ' ')))


if __name__ == '__main__':
    main()
