import csv,sys
syms=open('syms.txt').read().split()
cov={}
for r in csv.DictReader(open('build/bind-i686/excluded_coverage.tsv',encoding='utf-8'),delimiter='\t'):
    cov[r['symbol']]=r
man={}
for l in open('game/MANIFEST.tsv',encoding='utf-8'):
    p=l.rstrip('\n').split('\t')
    if len(p)>1: man[p[0]]=p[1]
sigs={}
for l in open('build/bind-i686/caller_sigs.tsv',encoding='utf-8'):
    p=l.rstrip('\n').split('\t')
    sigs.setdefault(p[0],[]).append(p[1:])
rts={}
for l in open('build/bind-i686/caller_rettypes.tsv',encoding='utf-8'):
    p=l.rstrip('\n').split('\t')
    rts.setdefault(p[0],[]).append(p[1:])
out=open('rows.tsv','w')
for s in syms:
    r=cov.get(s)
    if not r: print('MISSING',s); continue
    f=r['file']
    out.write('\t'.join([s,f,man.get(f,'?')])+'\n')
    print(s,f,r['refs'],r['detail'][:80], 'MAN' if f in man else 'NOMAN')
    for x in sigs.get(s,[])[:3]: print('   SIG',x)
    for x in rts.get(s,[]): print('   RT',x)
