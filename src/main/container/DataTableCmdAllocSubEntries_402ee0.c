#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x7C];
    s8  b07C_0 : 5;
    s8  pb07C_5 : 3;
    u8  pad07D[0x3];
    s32 f080;
    u8  pad084[0xC];
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0x4];
    s32  m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern s32  ArenaNew_4049f0(s32 a, void *b, s32 c, s32 d);

s32 DataTableCmdAllocSubEntries_402ee0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b07C_0 = (s8)VariantGetInt_15f780(src);
    if (e->b07C_0 > 0) e->f080 = ArenaNew_4049f0(e->b07C_0 * 0x1C, p->m6C, 0x4, -1);
    else e->f080 = 0;
    p->m094 = 0;
    return 1;
}
