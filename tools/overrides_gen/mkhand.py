import sys, os
rows = {l.split('\t')[0]: l.rstrip('\n').split('\t') for l in open('rows.tsv')}
PRE = '''#include "types.h"

#define RG_U8(p, o)  (*(u8 *)((char *)(p) + (o)))
#define RG_U16(p, o) (*(u16 *)((char *)(p) + (o)))
#define RG_S32(p, o) (*(s32 *)((char *)(p) + (o)))
#define RG_U32(p, o) (*(u32 *)((char *)(p) + (o)))
#define RG_F32(p, o) (*(f32 *)((char *)(p) + (o)))
#define RG_PTR(p, o) (*(char **)((char *)(p) + (o)))
#define RG_SQ0(p, o) __builtin_memset((char *)(p) + (o), 0, 16) /* sq $0 */

'''
for s in sys.argv[1:]:
    _, rel, sha = rows[s]
    body = open(f'hand/{s}.c').read()
    hdr = (f'/* rg-override: replaces game/{rel} sha256 {sha}\n'
           f' * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */\n')
    dst = f'overrides/{rel}'
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    open(dst, 'w', newline='\n').write(hdr + PRE + body)
    print(rel)
