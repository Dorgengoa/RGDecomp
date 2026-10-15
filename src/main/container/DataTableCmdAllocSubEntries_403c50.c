#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x2D];
    u8  f02D;
    u8  pad02E[0x6];
    s32 f034;
    u8  pad038[0x4];
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0xC];
    s32  m09C;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern s32  ArenaNew_4049f0(s32 a, void *b, s32 c, s32 d);

s32 DataTableCmdAllocSubEntries_403c50(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src);
    e->f02D = t0;
    if ((s8)t0 > 0) e->f034 = ArenaNew_4049f0((s8)t0 * 0x4, p->m6C, 0x4, -1);
    else e->f034 = 0;
    p->m09C = 0;
    return 1;
}
