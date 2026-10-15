#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x4];
    s16 f004;
    u8  pad006[0x2];
    s32 f008;
    u8  pad00C[0xC];
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern s32  ArenaNew_409ec0(s32 a, void *b, s32 c, s32 d);
extern s32  D_00480230;

s32 DataTableCmdAllocSubEntries_409220(R8 *src)
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
    e->f004 = t0;
    if ((s16)t0 > 0) e->f008 = ArenaNew_409ec0((s16)t0 * 0x1C, p->m6C, 0x4, -1);
    else e->f008 = 0;
    D_00480230 = 0;
    return 1;
}
